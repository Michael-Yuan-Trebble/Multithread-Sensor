from PyQt5.QtWidgets import QWidget, QHBoxLayout, QPushButton
from PyQt5.QtCore import pyqtSignal
import matplotlib.pyplot as plot
import pandas
import mplcursors

class CombinedPlotScreen(QWidget):
    goBack = pyqtSignal()
    def __init__(self, controller,file):
        super().__init__()
        self.controller = controller
        self.file = file
        self.initUI()

    def initUI(self):
        try:
            self.data = pandas.read_csv(self.file)
        except FileNotFoundError:
            raise RuntimeError(f"CSV file not found: {self.file}")
        
        self.mainLayout = QHBoxLayout()
        self.goBackbtn = QPushButton("Go Back")
        self.goBackbtn.clicked.connect(self.returnHome)
        self.mainLayout.addWidget(self.goBackbtn)
        self.setLayout(self.mainLayout)

        CombinedType = self.data[self.data["sensor type"] == "Combined"]

        self.figure = plot.figure(figsize=(8,6))
        ax = self.figure.add_subplot(111,projection="3d")

        sc = ax.scatter(CombinedType["x"], CombinedType["y"], CombinedType["z"],color = "red",label="Combined")

        ax.set_title("Combined Sensor Positions (3D)")
        ax.set_xlabel("X")
        ax.set_ylabel("Y")
        ax.set_zlabel("Z")
        ax.legend()

        cursor = mplcursors.cursor(sc,hover=True)
        @cursor.connect("add")
        def on_add(sel):
            i=sel.index
            sel.annotation.set_text(
                f"({CombinedType['x'].iloc[i]}, {CombinedType['y'].iloc[i]}, {CombinedType['z'].iloc[i]})"
            )
        plot.show()

    def returnHome(self):
        plot.close(self.figure)
        self.goBack.emit()