# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'simulation.ui'
#
# Created by: PyQt5 UI code generator 5.14.1
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QProcess  ####################### AJOUT
import os ####################### AJOUT  
import rosgraph ####################### AJOUT  
import subprocess
import time


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(947, 744)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.sim_rviz = QtWidgets.QPushButton(self.centralwidget)
        self.sim_rviz.setGeometry(QtCore.QRect(150, 400, 241, 101))
        self.sim_rviz.setObjectName("sim_rviz")
        self.sim_gazebo = QtWidgets.QPushButton(self.centralwidget)
        self.sim_gazebo.setGeometry(QtCore.QRect(450, 400, 241, 101))
        self.sim_gazebo.setObjectName("sim_gazebo")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(370, 90, 201, 111))
        font = QtGui.QFont()
        font.setFamily("Ubuntu Condensed")
        font.setPointSize(24)
        font.setBold(True)
        font.setItalic(True)
        font.setWeight(75)
        self.label.setFont(font)
        self.label.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label.setAutoFillBackground(True)
        self.label.setWordWrap(False)
        self.label.setObjectName("label")
        self.roscore = QtWidgets.QPushButton(self.centralwidget)
        self.roscore.setGeometry(QtCore.QRect(300, 260, 231, 101))
        self.roscore.setObjectName("roscore")
        self.killAll = QtWidgets.QPushButton(self.centralwidget)
        self.killAll.setGeometry(QtCore.QRect(320, 560, 201, 71))
        self.killAll.setObjectName("killAll")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 947, 22))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        
        self.sim_gazebo.clicked.connect( self.onClick_gazebo ) ####################### AJOUT    
        self.sim_rviz.clicked.connect( self.onClick_rviz ) ####################### AJOUT
        self.roscore.clicked.connect( self.onClick_roscore ) ####################### AJOUT
        self.killAll.clicked.connect( self.onClick_killAll ) ####################### AJOUT

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.sim_rviz.setText(_translate("MainWindow", "Simulation rviz"))
        self.sim_gazebo.setText(_translate("MainWindow", "Simulation gazebo"))
        self.label.setText(_translate("MainWindow", "Quadrus"))
        self.roscore.setText(_translate("MainWindow", "Démarrer roscore"))
        self.killAll.setText(_translate("MainWindow", "Tout fermer"))
        
    def onClick_rviz(self):
        print("Launching rviz...")

	#ROS_PROGRAM = QProcess()
        #program = 'roslaunch qd_simulation qd_rviz.launch'
        #ROS_PROGRAM.start(program)  
        
        os.system("roslaunch qd_simulation qd_rviz.launch") 
        
        #roscore = subprocess.Popen('roslaunch qd_simulation qd_rviz.launch')   
        
    def onClick_gazebo(self):
        print("Launching gazebo...")

	#ROS_PROGRAM = QProcess()
        #program = 'roslaunch qd_simulation qd_gazebo.launch'
        #ROS_PROGRAM.start(program)  
        
        os.system("roslaunch qd_simulation qd_gazebo.launch")      
        
        #roscore = subprocess.Popen('roslaunch qd_simulation qd_gazebo.launch')   
        
        
    def onClick_roscore(self):
        if not rosgraph.is_master_online(): # Checks the master uri and results boolean (True or False)
                roscore = subprocess.Popen('roscore')

        print("ROS MASTER is Online")
        
    def onClick_killAll(self):
        print("kill all ...")
        
        os.system("^C; killall -9 rosmaster; killall -9 roscore") 


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
