'''''''''''''''''''''''mnist_inference.py定义了前向传播的过程以及神经网络的参数'''''''''''''''''''''''''''
'''''''''''''''''''''''mnist_train.py定义了神经网络的训练过程'''''''''''''''''''''''''''
'''''''''''''''''''''''mnist_eval.py定义了测试的过程'''''''''''''''''''''''''''
# -*- coding: utf-8 -*-
import tensorflow as tf 
import os 
#from tensorflow.examples.tutorials.mnist import input_data
import input_data

#加载mnist_inference.py中定义的常量和前向传播的函数
import mnist_inference

#配置神经网络中的参数
BATCH_SIZE = 100
LEARNING_RATE_BASE = 0.8
LEARNING_RATE_DECAY = 0.99
REGULARIZATION_RATE = 0.0001
TRAINING_STEPS = 30000
MOVING_AVERAGE_DECAY = 0.99
#模型保存的路径和文件名
MODEL_SAVE_PATH = "./path/to/model/"
MODLE_NAME = "model.ckpt"

def train(mnist):
    #定义输入输出placeholder.
    x = tf.placeholder(tf.float32, [None, mnist_inference.INPUT_NODE], name='x-input')
    y_ = tf.placeholder(tf.float32, [None, mnist_inference.OUTPUT_NODE], name='y-input')
    regularizer = tf.contrib.layers.l2_regularizer(REGULARIZATION_RATE)
    y = mnist_inference.inference(x, regularizer)
    global_step = tf.Variable(0, trainable=False)

    #定义损失函数, 学习率, 滑动平均操作以及训练过程.
    Variable_averages = tf.train.ExponentialMovingAverage(MOVING_AVERAGE_DECAY, global_step)
    Variable_averages_op = Variable_averages.apply(tf.trainable_variables())
    cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=y, labels=tf.argmax(y_, 1))
    cross_entropy_mean = tf.reduce_mean(cross_entropy)
    loss = cross_entropy_mean + tf.add_n(tf.get_collection('losses'))
    learning_rate = tf.train.exponential_decay(
        LEARNING_RATE_BASE,
        global_step, 
        mnist.train.num_examples/BATCH_SIZE,
        LEARNING_RATE_DECAY)
    train_step = tf.train.GradientDescentOptimizer(learning_rate).minimize(loss, global_step=global_step)
    with tf.control_dependencies([train_step, Variable_averages_op]):train_op = tf.no_op(name='train')
    
    #初始化tensorflow持久化类
    saver = tf.train.Saver()
    with tf.Session() as sess:
        tf.global_variables_initializer().run()
        #在训练过程中不再测试模型在验证数据上的表现, 验证和测试的过程将会有一个独立的程序来完成
        for i in range(TRAINING_STEPS):
            xs, ys = mnist.train.next_batch(BATCH_SIZE)
            _, loss_value, step = sess.run([train_op, loss, global_step], feed_dict={x:xs, y_:ys})
            #每1000轮保存一次模型.
            if i % 1000 == 0:
                #输出损失函数值. 在验证集上的正确率信息将会有一个单独的程序完成
                print("After %d training step(s), loss on training batch is %g." %(step, loss_value))
                #保存当前的模型. 这里给出了global_step参数, 可以在每个被保存模型的文件名末尾加上训练的轮数
                saver.save(sess, os.path.join(MODEL_SAVE_PATH, MODLE_NAME), global_step=global_step)

def main(argv=None):
    mnist = input_data.read_data_sets("./MNIST_data", one_hot=True)
    train(mnist)

if __name__ == '__main__':
    tf.app.run()





































