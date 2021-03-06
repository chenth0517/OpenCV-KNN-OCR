#ifndef OPENCV_FLANN_HDF5_H_
#define OPENCV_FLANN_HDF5_H_ 

#include <hdf5.h>

#include "matrix.h"


namespace cvflann
{

namespace
{

template<typename T>
hid_t get_hdf5_type()
{
    throw FLANNException("Unsupported type for IO operations");
}

template<>
hid_t get_hdf5_type<char>() { return H5T_NATIVE_CHAR; }
template<>
hid_t get_hdf5_type<unsigned char>() { return H5T_NATIVE_UCHAR; }
template<>
hid_t get_hdf5_type<short int>() { return H5T_NATIVE_SHORT; }
template<>
hid_t get_hdf5_type<unsigned short int>() { return H5T_NATIVE_USHORT; }
template<>
hid_t get_hdf5_type<int>() { return H5T_NATIVE_INT; }
template<>
hid_t get_hdf5_type<unsigned int>() { return H5T_NATIVE_UINT; }
template<>
hid_t get_hdf5_type<long>() { return H5T_NATIVE_LONG; }
template<>
hid_t get_hdf5_type<unsigned long>() { return H5T_NATIVE_ULONG; }
template<>
hid_t get_hdf5_type<float>() { return H5T_NATIVE_FLOAT; }
template<>
hid_t get_hdf5_type<double>() { return H5T_NATIVE_DOUBLE; }
}


#define CHECK_ERROR(x,y) if ((x)<0) throw FLANNException((y));

template<typename T>
void save_to_file(const cvflann::Matrix<T>& dataset, const std::string& filename, const std::string& name)
{

#if H5Eset_auto_vers == 2
    H5Eset_auto( H5E_DEFAULT, NULL, NULL );
#else
    H5Eset_auto( NULL, NULL );
#endif

    herr_t status;
    hid_t file_id;
    file_id = H5Fopen(filename.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) {
        file_id = H5Fcreate(filename.c_str(), H5F_ACC_EXCL, H5P_DEFAULT, H5P_DEFAULT);
    }
    CHECK_ERROR(file_id,"Error creating hdf5 file.");

    hsize_t dimsf[2];
    dimsf[0] = dataset.rows;
    dimsf[1] = dataset.cols;

    hid_t space_id = H5Screate_simple(2, dimsf, NULL);
    hid_t memspace_id = H5Screate_simple(2, dimsf, NULL);

    hid_t dataset_id;
#if H5Dcreate_vers == 2
    dataset_id = H5Dcreate2(file_id, name.c_str(), get_hdf5_type<T>(), space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
#else
    dataset_id = H5Dcreate(file_id, name.c_str(), get_hdf5_type<T>(), space_id, H5P_DEFAULT);
#endif

    if (dataset_id<0) {
#if H5Dopen_vers == 2
        dataset_id = H5Dopen2(file_id, name.c_str(), H5P_DEFAULT);
#else
        dataset_id = H5Dopen(file_id, name.c_str());
#endif
    }
    CHECK_ERROR(dataset_id,"Error creating or opening dataset in file.");

    status = H5Dwrite(dataset_id, get_hdf5_type<T>(), memspace_id, space_id, H5P_DEFAULT, dataset.data );
    CHECK_ERROR(status, "Error writing to dataset");

    H5Sclose(memspace_id);
    H5Sclose(space_id);
    H5Dclose(dataset_id);
    H5Fclose(file_id);

}


template<typename T>
void load_from_file(cvflann::Matrix<T>& dataset, const std::string& filename, const std::string& name)
{
    herr_t status;
    hid_t file_id = H5Fopen(filename.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
    CHECK_ERROR(file_id,"Error opening hdf5 file.");

    hid_t dataset_id;
#if H5Dopen_vers == 2
    dataset_id = H5Dopen2(file_id, name.c_str(), H5P_DEFAULT);
#else
    dataset_id = H5Dopen(file_id, name.c_str());
#endif
    CHECK_ERROR(dataset_id,"Error opening dataset in file.");

    hid_t space_id = H5Dget_space(dataset_id);

    hsize_t dims_out[2];
    H5Sget_simple_extent_dims(space_id, dims_out, NULL);

    dataset = cvflann::Matrix<T>(new T[dims_out[0]*dims_out[1]], dims_out[0], dims_out[1]);

    status = H5Dread(dataset_id, get_hdf5_type<T>(), H5S_ALL, H5S_ALL, H5P_DEFAULT, dataset[0]);
    CHECK_ERROR(status, "Error reading dataset");

    H5Sclose(space_id);
    H5Dclose(dataset_id);
    H5Fclose(file_id);
}


#ifdef HAVE_MPI

namespace mpi
{






template<typename T>
void load_from_file(cvflann::Matrix<T>& dataset, const std::string& filename, const std::string& name)
{
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Info info = MPI_INFO_NULL;

    int mpi_size, mpi_rank;
    MPI_Comm_size(comm, &mpi_size);
    MPI_Comm_rank(comm, &mpi_rank);

    herr_t status;

    hid_t plist_id = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_mpio(plist_id, comm, info);
    hid_t file_id = H5Fopen(filename.c_str(), H5F_ACC_RDWR, plist_id);
    CHECK_ERROR(file_id,"Error opening hdf5 file.");
    H5Pclose(plist_id);
    hid_t dataset_id;
#if H5Dopen_vers == 2
    dataset_id = H5Dopen2(file_id, name.c_str(), H5P_DEFAULT);
#else
    dataset_id = H5Dopen(file_id, name.c_str());
#endif
    CHECK_ERROR(dataset_id,"Error opening dataset in file.");

    hid_t space_id = H5Dget_space(dataset_id);
    hsize_t dims[2];
    H5Sget_simple_extent_dims(space_id, dims, NULL);

    hsize_t count[2];
    hsize_t offset[2];

    hsize_t item_cnt = dims[0]/mpi_size+(dims[0]%mpi_size==0 ? 0 : 1);
    hsize_t cnt = (mpi_rank<mpi_size-1 ? item_cnt : dims[0]-item_cnt*(mpi_size-1));

    count[0] = cnt;
    count[1] = dims[1];
    offset[0] = mpi_rank*item_cnt;
    offset[1] = 0;

    hid_t memspace_id = H5Screate_simple(2,count,NULL);

    H5Sselect_hyperslab(space_id, H5S_SELECT_SET, offset, NULL, count, NULL);

    dataset.rows = count[0];
    dataset.cols = count[1];
    dataset.data = new T[dataset.rows*dataset.cols];

    plist_id = H5Pcreate(H5P_DATASET_XFER);
    H5Pset_dxpl_mpio(plist_id, H5FD_MPIO_COLLECTIVE);
    status = H5Dread(dataset_id, get_hdf5_type<T>(), memspace_id, space_id, plist_id, dataset.data);
    CHECK_ERROR(status, "Error reading dataset");

    H5Pclose(plist_id);
    H5Sclose(space_id);
    H5Sclose(memspace_id);
    H5Dclose(dataset_id);
    H5Fclose(file_id);
}
}
#endif
}

#endif
