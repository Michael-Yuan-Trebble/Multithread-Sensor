from PyQt5.QtWidgets import QDialog, QWidget, QPushButton, QLabel, QHBoxLayout, QVBoxLayout, QFileDialog, QStackedWidget, QLineEdit
import json
from PyQt5.QtCore import Qt, pyqtSignal

class HomeScreen(QWidget):

    GPSNav = pyqtSignal(str)
    IMUNav = pyqtSignal(str)
    RadarNav = pyqtSignal(str)
    CombinedNav = pyqtSignal(str)

    def __init__(self,controller,file):
        super().__init__()
        self.controller = controller
        self.file = file
        self.initUI()

    def initUI(self):
        self.GPSbtn = QPushButton("Plot GPS")
        self.GPSbtn.clicked.connect(self.PlotGPS)
        self.IMUbtn = QPushButton("Plot IMU")
        self.IMUbtn.clicked.connect(self.PlotIMU)
        self.Radarbtn = QPushButton("Plot Radar")
        self.Radarbtn.clicked.connect(self.PlotRadar)
        self.Combinedbtn = QPushButton("Plot Combined")
        self.Combinedbtn.clicked.connect(self.PlotCombined)

        self.master = QVBoxLayout()

        self.row1 = QHBoxLayout()
        self.row2 = QHBoxLayout()

        self.row1.addWidget(self.GPSbtn)
        self.row1.addWidget(self.IMUbtn)
        self.row1.addWidget(self.Radarbtn)

        self.row2.addWidget(self.Combinedbtn)

        self.master.addLayout(self.row1)
        self.master.addLayout(self.row2)

        self.setLayout(self.master)

    def PlotGPS(self):
        self.GPSNav.emit(self.file)

    def PlotIMU(self):
        self.IMUNav.emit(self.file)

    def PlotRadar(self):
        self.RadarNav.emit(self.file)

    def PlotCombined(self):
        self.CombinedNav.emit(self.file)

    