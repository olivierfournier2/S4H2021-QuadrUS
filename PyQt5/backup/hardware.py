# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'hardware.ui'
#
# Created by: PyQt5 UI code generator 5.14.1
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets
import os ####################### AJOUT  


class Ui_hardwareWindow(object):
    def setupUi(self, hardwareWindow):
        hardwareWindow.setObjectName("hardwareWindow")
        hardwareWindow.resize(947, 744)
        hardwareWindow.setStyleSheet("background-color: rgb(238, 238, 236);")
        self.centralwidget = QtWidgets.QWidget(hardwareWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.EstopButton = QtWidgets.QPushButton(self.centralwidget)
        self.EstopButton.setGeometry(QtCore.QRect(90, 380, 231, 101))
        self.EstopButton.setStyleSheet("background-color: rgb(245, 121, 0);\n"
"font: 75 oblique 15pt \"Ubuntu Condensed\";")
        self.EstopButton.setObjectName("EstopButton")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(0, 0, 231, 131))
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
        self.enableButton = QtWidgets.QPushButton(self.centralwidget)
        self.enableButton.setGeometry(QtCore.QRect(90, 180, 231, 101))
        self.enableButton.setStyleSheet("background-color: rgb(252, 233, 79);\n"
"font: 75 oblique 15pt \"Ubuntu Condensed\";")
        self.enableButton.setObjectName("enableButton")
        self.backButton = QtWidgets.QPushButton(self.centralwidget)
        self.backButton.setGeometry(QtCore.QRect(20, 600, 201, 71))
        self.backButton.setStyleSheet("background-color: rgb(186, 189, 182);\n"
"font: 75 oblique 15pt \"Ubuntu Condensed\";")
        self.backButton.setObjectName("backButton")
        self.textBrowser = QtWidgets.QTextBrowser(self.centralwidget)
        self.textBrowser.setGeometry(QtCore.QRect(690, 20, 231, 391))
        self.textBrowser.setObjectName("textBrowser")
        self.textBrowser_2 = QtWidgets.QTextBrowser(self.centralwidget)
        self.textBrowser_2.setGeometry(QtCore.QRect(440, 20, 231, 391))
        self.textBrowser_2.setObjectName("textBrowser_2")
        self.textBrowser_3 = QtWidgets.QTextBrowser(self.centralwidget)
        self.textBrowser_3.setGeometry(QtCore.QRect(630, 470, 256, 192))
        self.textBrowser_3.setObjectName("textBrowser_3")
        self.graphicsView = QtWidgets.QGraphicsView(self.centralwidget)
        self.graphicsView.setGeometry(QtCore.QRect(340, 470, 256, 192))
        self.graphicsView.setObjectName("graphicsView")
        hardwareWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(hardwareWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 947, 22))
        self.menubar.setObjectName("menubar")
        hardwareWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(hardwareWindow)
        self.statusbar.setObjectName("statusbar")
        hardwareWindow.setStatusBar(self.statusbar)

        self.enableButton.clicked.connect( self.onClick_enable ) ####################### AJOUT    
        self.EstopButton.clicked.connect( self.onClick_Estop ) ####################### AJOUT
        self.backButton.clicked.connect( lambda:self.onClick_back(hardwareWindow) ) ####################### AJOUT
        self.EstopClicked = False ####################### AJOUT

        self.retranslateUi(hardwareWindow)
        QtCore.QMetaObject.connectSlotsByName(hardwareWindow)

    def retranslateUi(self, hardwareWindow):
        _translate = QtCore.QCoreApplication.translate
        hardwareWindow.setWindowTitle(_translate("hardwareWindow", "MainWindow"))
        self.EstopButton.setText(_translate("hardwareWindow", "EMERGENCY STOP"))
        self.label.setText(_translate("hardwareWindow", "QuadrUS"))
        self.enableButton.setText(_translate("hardwareWindow", "Enable joystick "))
        self.backButton.setText(_translate("hardwareWindow", "Back"))
        self.textBrowser.setHtml(_translate("hardwareWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">FEEDBACK</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"))
        self.textBrowser_2.setHtml(_translate("hardwareWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">COMMAND</p></body></html>"))


    def onClick_enable(self):
        print("Enable joystick..")

        
    def onClick_back(self, hardwareWindow):
        os.system("killall rosmaster")
        hardwareWindow.hide()
        
    def onClick_Estop(self):       
        _translate = QtCore.QCoreApplication.translate

        if self.EstopClicked:
            print("RESET ESTOP")
            self.EstopButton.setText(_translate("hardwareWindow", "EMERGENCY STOP"))
            self.EstopButton.setStyleSheet("background-color: rgb(245, 121, 0);\n"
"font: 75 oblique 15pt \"Ubuntu Condensed\";")
            self.EstopClicked= False

        elif not self.EstopClicked:
            print("EMERGENCY STOP")
            self.EstopButton.setText(_translate("hardwareWindow", "RESET ESTOP"))
            self.EstopButton.setStyleSheet("background-color: rgb(252, 233, 79);\n"
"font: 75 oblique 15pt \"Ubuntu Condensed\";")
            self.EstopClicked= True


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    hardwareWindow = QtWidgets.QMainWindow()
    ui = Ui_hardwareWindow()
    ui.setupUi(hardwareWindow)
    hardwareWindow.show()
    sys.exit(app.exec_())
