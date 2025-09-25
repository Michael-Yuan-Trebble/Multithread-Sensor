from PyQt5.QtWidgets import QDialog, QWidget, QPushButton, QLabel, QHBoxLayout, QVBoxLayout, QFileDialog, QStackedWidget, QLineEdit
import json
from PyQt5.QtCore import Qt, pyqtSignal


class SelectFileScreen(QWidget):

    fileSelected = pyqtSignal(str)
    def __init__(self,controller):
        super().__init__()
        self.controller = controller
        self.initUI()

    def initUI(self):
        self.selectFileBtn = QPushButton("Select CSV File")
        self.selectFileBtn.clicked.connect(self.selectFile)

        self.master = QHBoxLayout()
        self.master.addWidget(self.selectFileBtn)

        self.setLayout(self.master)


    def selectFile(self):
        filePath, _ = QFileDialog.getOpenFileName(
            self,
            "Open File",
            "",
            "CSVs (*.csv)"
        )
        if filePath:
            self.fileSelected.emit(filePath)
        else:
            print("ERROR")