# OpenCV-KNN-OCR
【算法】
采用“K维最邻近分类算法”

【程序中分类器的指标】
分类：13（13个俄语字母）
维度：10
维度和分类均可以自行调整

【目录】
include：	OpenCV2.3.1头文件
lib：		OpenCV2.3.1导入库（32bit）
train_pic：	训练样本集(图片尺寸18x28)
test_pic：	测试样本集(图片尺寸18x28)

【函数】
threshold：	二值化（预处理）
getData：	取训练数据
train：		训练
classify：	分类
test：		测试
