# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'simulation.ui'
#
# Created by: PyQt5 UI code generator 5.14.1
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets
import os ####################### AJOUT  


class Ui_simulationWindow(object):
    def setupUi(self, simulationWindow):
        simulationWindow.setObjectName("simulationWindow")
        simulationWindow.resize(947, 744)
        simulationWindow.setStyleSheet("background-color: rgb(238, 238, 236);")
        self.centralwidget = QtWidgets.QWidget(simulationWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.rvizButton = QtWidgets.QPushButton(self.centralwidget)
        self.rvizButton.setGeometry(QtCore.QRect(350, 140, 241, 101))
        self.rvizButton.setStyleSheet("background-color: rgb(252, 233, 79);\n"
"font: 75 oblique 15pt \"Ubuntu Condensed\";")
        self.rvizButton.setObjectName("rvizButton")
        self.gazeboButton = QtWidgets.QPushButton(self.centralwidget)
        self.gazeboButton.setGeometry(QtCore.QRect(350, 270, 241, 101))
        self.gazeboButton.setStyleSheet("background-color: rgb(252, 233, 79);\n"
"font: 75 oblique 15pt \"Ubuntu Condensed\";")
        self.gazeboButton.setObjectName("gazeboButton")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(10, 10, 201, 111))
        font = QtGui.QFont()
        font.setFamily("Ubuntu Condensed")
        font.setPointSize(30)
        font.setBold(True)
        font.setItalic(True)
        font.setWeight(75)
        self.label.setFont(font)
        self.label.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label.setAutoFillBackground(False)
        self.label.setStyleSheet("color: rgb(78, 154, 6);\n"
"")
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setWordWrap(False)
        self.label.setObjectName("label")
        self.backButton = QtWidgets.QPushButton(self.centralwidget)
        self.backButton.setGeometry(QtCore.QRect(20, 600, 201, 71))
        self.backButton.setStyleSheet("background-color: rgb(186, 189, 182);\n"
"font: 75 oblique 15pt \"Ubuntu Condensed\";")
        self.backButton.setObjectName("backButton")
        self.stopButton = QtWidgets.QPushButton(self.centralwidget)
        self.stopButton.setGeometry(QtCore.QRect(370, 440, 201, 81))
        self.stopButton.setStyleSheet("background-color: rgb(252, 175, 62);\n"
"font: 75 oblique 15pt \"Ubuntu Condensed\";")
        self.stopButton.setObjectName("stopButton")
        simulationWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(simulationWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 947, 22))
        self.menubar.setObjectName("menubar")
        simulationWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(simulationWindow)
        self.statusbar.setObjectName("statusbar")
        simulationWindow.setStatusBar(self.statusbar)

        self.gazeboButton.clicked.connect( self.onClick_gazebo ) ####################### AJOUT    
        self.rvizButton.clicked.connect( self.onClick_rviz ) ####################### AJOUT
        self.backButton.clicked.connect( lambda:self.onClick_back(simulationWindow) ) ####################### AJOUT
        self.stopButton.clicked.connect( self.onClick_stop) ####################### AJOUT

        self.isGazeboRunning = False
        self.isRvizRunning = False

        self.retranslateUi(simulationWindow)
        QtCore.QMetaObject.connectSlotsByName(simulationWindow)

    def retranslateUi(self, simulationWindow):
        _translate = QtCore.QCoreApplication.translate
        simulationWindow.setWindowTitle(_translate("simulationWindow", "MainWindow"))
        self.rvizButton.setText(_translate("simulationWindow", "Kinematic simulation"))
        self.gazeboButton.setText(_translate("simulationWindow", "Dynamic simulation"))
        self.label.setText(_translate("simulationWindow", "QuadrUS"))
        self.backButton.setText(_translate("simulationWindow", "Back"))
        self.stopButton.setText(_translate("simulationWindow", "Stop simulation"))


    def onClick_rviz(self):
        print("Launching rviz...")

        if self.isGazeboRunning:
            self.onClick_stop()

        if not self.isRvizRunning:
            self.isRvizRunning = True
            os.system("gnome-terminal -x roslaunch qd_master qd_master.launch mode:=sim sim_mode:=kin")
        
    def onClick_gazebo(self):
        print("Launching gazebo...")

        if self.isRvizRunning:
            self.onClick_stop()

        if not self.isGazeboRunning:
            self.isGazeboRunning = True
            os.system("gnome-terminal -x roslaunch qd_master qd_master.launch mode:=sim sim_mode:=dyn")
        
    def onClick_back(self, simulationWindow):
        if self.isRvizRunning or self.isGazeboRunning:
            self.onClick_stop()
        simulationWindow.hide()

        
    def onClick_stop(self):
        print("kill all ...")
        
        if self.isRvizRunning:
            os.system("killall roslaunch")
            self.isRvizRunning = False

        elif self.isGazeboRunning:
            #os.system("killall roslaunch")
            os.system("killall rosmaster")
            self.isGazeboRunning = False


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    simulationWindow = QtWidgets.QMainWindow()
    ui = Ui_simulationWindow()
    ui.setupUi(simulationWindow)
    simulationWindow.show()
    sys.exit(app.exec_())
