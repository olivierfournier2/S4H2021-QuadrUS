#!/usr/bin/env python3

# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'quadrus.ui'
#
# Created by: PyQt5 UI code generator 5.14.1
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets
from simulation import  Ui_simulationWindow ####################### AJOUT
from hardware import  Ui_hardwareWindow ####################### AJOUT
import os ####################### AJOUT  


class Ui_quadrusWindow(object):
    def setupUi(self, quadrusWindow):
        quadrusWindow.setObjectName("quadrusWindow")
        quadrusWindow.resize(947, 743)
        quadrusWindow.setStyleSheet("background-color: rgb(238, 238, 236);")
        self.centralwidget = QtWidgets.QWidget(quadrusWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.simulationButton = QtWidgets.QPushButton(self.centralwidget)
        self.simulationButton.setGeometry(QtCore.QRect(340, 260, 241, 101))
        font = QtGui.QFont()
        font.setFamily("Ubuntu Condensed")
        font.setPointSize(15)
        font.setBold(False)
        font.setItalic(True)
        font.setWeight(9)
        self.simulationButton.setFont(font)
        self.simulationButton.setStyleSheet("background-color: rgb(252, 233, 79);\n"
"font: 75 oblique 15pt \"Ubuntu Condensed\";")
        self.simulationButton.setAutoDefault(False)
        self.simulationButton.setDefault(False)
        self.simulationButton.setObjectName("simulationButton")
        self.hardwareButton = QtWidgets.QPushButton(self.centralwidget)
        self.hardwareButton.setGeometry(QtCore.QRect(340, 410, 241, 101))
        self.hardwareButton.setStyleSheet("background-color: rgb(252, 233, 79);\n"
"font: 75 oblique 15pt \"Ubuntu Condensed\";")
        self.hardwareButton.setObjectName("hardwareButton")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(210, 10, 481, 171))
        font = QtGui.QFont()
        font.setFamily("Ubuntu Condensed")
        font.setPointSize(69)
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
        self.closeButton = QtWidgets.QPushButton(self.centralwidget)
        self.closeButton.setGeometry(QtCore.QRect(20, 590, 191, 81))
        self.closeButton.setStyleSheet("background-color: rgb(186, 189, 182);\n"
"font: 75 oblique 15pt \"Ubuntu Condensed\";")
        self.closeButton.setObjectName("closeButton")
        quadrusWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(quadrusWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 947, 22))
        self.menubar.setObjectName("menubar")
        quadrusWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(quadrusWindow)
        self.statusbar.setObjectName("statusbar")
        quadrusWindow.setStatusBar(self.statusbar)

        self.simulationButton.clicked.connect( self.onClick_simulation ) ####################### AJOUT    
        self.hardwareButton.clicked.connect( self.onClick_hardware ) ####################### AJOUT
        self.closeButton.clicked.connect( self.onClick_close ) ####################### AJOUT

        self.hardwareWindow = QtWidgets.QMainWindow() ####################### AJOUT
        self.ui = Ui_hardwareWindow() ####################### AJOUT
        self.ui.setupUi(self.hardwareWindow) ####################### AJOUT

        self.simulationWindow = QtWidgets.QMainWindow() ####################### AJOUT
        self.ui = Ui_simulationWindow() ####################### AJOUT
        self.ui.setupUi(self.simulationWindow) ####################### AJOUT

        self.retranslateUi(quadrusWindow)
        QtCore.QMetaObject.connectSlotsByName(quadrusWindow)

    def retranslateUi(self, quadrusWindow):
        _translate = QtCore.QCoreApplication.translate
        quadrusWindow.setWindowTitle(_translate("quadrusWindow", "MainWindow"))
        self.simulationButton.setText(_translate("quadrusWindow", "Simulation"))
        self.hardwareButton.setText(_translate("quadrusWindow", "Real time control"))
        self.label.setText(_translate("quadrusWindow", "QuadrUS"))
        self.closeButton.setText(_translate("quadrusWindow", "Close"))

    def onClick_simulation(self):
        self.simulationWindow.show()
        


    def onClick_hardware(self):
        self.hardwareWindow.show()


    def onClick_close(self):
        quadrusWindow.close()
        self.simulationWindow.close()
        self.hardwareWindow.close()
        
if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    quadrusWindow = QtWidgets.QMainWindow()
    ui = Ui_quadrusWindow()
    ui.setupUi(quadrusWindow)
    quadrusWindow.show()
    sys.exit(app.exec_())
