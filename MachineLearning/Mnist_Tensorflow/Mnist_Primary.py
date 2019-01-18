'''
编程之前首先需要建立问题的数学模型, 对于Mnist手写字体识别问题, 采用softmax回归模型Y=sotfmax(Wx+b), 
单隐层神经网络(), 损失函数采用交叉熵(你看, 回归问题用的是均方误差, 这种分类的问题用交叉熵)
'''
#encoding=utf-8
import tensorflow as tf 
import input_data
#数据, 如果比赛的话需要自己处理
mnist = input_data.read_data_sets("MNIST_data", one_hot=True)
###################### 构建计算图###############
#tensorflow构造计算图
#创建变量
x = tf.placeholder("float", [None, 784])
W = tf.Variable(tf.zeros([784, 10]))
b = tf.Variable(tf.zeros([10]))
#回归模型
y = tf.nn.softmax(tf.matmul(x, W) + b)

#构建训练模型(损失函数采用交叉熵)
y_ = tf.placeholder("float", [None, 10])           #用于输入正确值, 用于计算交叉熵
cross_entropy = -tf.reduce_sum(y_ * tf.log(y))     #定义交叉熵
train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)  #梯度下降法, 自动反向传播, 计算使cross_entropy最小的参数
#初始化参数
init = tf.global_variables_initializer()

#################运行计算图################
sess = tf.Session()
sess.run(init)
#开始训练模型
for i in range(1000):
    batch_xs, batch_ys = mnist.train.next_batch(100)        #每次随机抽取100个样本进行训练, 属于随机梯度下降法
    sess.run(train_step, feed_dict={x: batch_xs, y_: batch_ys})

#评估模型(预测的准确率)
correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))   #argmax()可返回tensor在某一维上最大值的索引, 可通过比较索引判断预测的准确性
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))    #cast(a, "float")将a转为float类型
print(sess.run(accuracy, feed_dict={x: mnist.test.images, y_: mnist.test.labels}))




