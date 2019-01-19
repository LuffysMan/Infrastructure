'''
构建一个多层卷积网络(输入层+卷积池化x2+全连接层x2)
参照Tensorflow中文社区-MNIST进阶-编写
'''
#encoding=utf-8
import tensorflow as tf 
import input_data
#interactivesession, 允许tensorflow在运行图的时候, 插入一些计算图, 不然只能先构建整个计算图, 然后启动图, 可对比Mnist_Primary的做法
sess = tf.InteractiveSession()

#数据, 如果比赛的话需要自己处理
mnist = input_data.read_data_sets("MNIST_data", one_hot=True)
###################### 构建计算图###############
#占位符, 运行session时填入具体的值
x = tf.placeholder("float", shape = [None, 784])
y_ = tf.placeholder("float", shape = [None, 10])           #真实值, 用于计算交叉熵

#权重初始化
def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)  #用截断的正态分布初始化tensor, 标准差0.1
    return tf.Variable(initial)
def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)           #使用常数0.1初始化tensor
    return tf.Variable(initial)
#卷积和池化
def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides=[1,1,1,1], padding='SAME')
def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1,2,2,1], strides=[1,2,2,1], padding='SAME')
#第一层卷积
W_conv1 = weight_variable([5,5,1,32])       #patch大小5x5, 输入通道数1, 输出通道数32
b_conv1 = bias_variable([32])               #每一个输出通道对应一个偏置量
x_image = tf.reshape(x, [-1, 28, 28, 1])    #第二 三维代表图像宽高, 第四维代表通道数, 灰度图为1
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)    #卷积并整流
h_pool1 = max_pool_2x2(h_conv1)              #池化
#第二层卷积
W_conv2 = weight_variable([5,5,32,64])      #不是很明白第三 四维为什么是32和64
b_conv2 = bias_variable([64])

h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
h_pool2 = max_pool_2x2(h_conv2)
#密集连接层
W_fc1 = weight_variable([7*7*64, 1024])     #1024个神经元的全连接层
b_fc1 = bias_variable([1024])
h_pool2_flat = tf.reshape(h_pool2, [-1 ,7*7*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)
#Dropout, 防止过拟合
keep_prob = tf.placeholder("float")
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)
#输出层
W_fc2 = weight_variable([1024, 10])
b_fc2 = bias_variable([10])
y_conv = tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)
#训练和评估模型
cross_entropy = -tf.reduce_sum(y_ * tf.log(y_conv))                #定义交叉熵
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)  #ADAM优化器来做梯度最速下降
correct_prediction = tf.equal(tf.argmax(y_conv, 1), tf.argmax(y_, 1))  #对比真实值和预测值
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))    #求准确率
sess.run(tf.global_variables_initializer())
for i in range(20000):
    batch = mnist.train.next_batch(50)        #每次随机抽取50个样本进行训练
    if i%100 == 0:
        train_accuracy = accuracy.eval(feed_dict={x: batch[0], y_:batch[1], keep_prob: 1.0})#训练准确率
        print("step%d, training accuracy %g"%(i, train_accuracy))       
    train_step.run(feed_dict={x: batch[0], y_: batch[1], keep_prob: 0.5})
print("test accuracy %g"%accuracy.eval(feed_dict={x: mnist.test.images, y_: mnist.test.labels, keep_prob: 1.0}))#测试准确率













