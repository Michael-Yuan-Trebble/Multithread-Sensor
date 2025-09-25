from PyQt5.QtWidgets import QApplication
from Navigator import NavigationController
import sys

if __name__ in "__main__":
    
    app = QApplication([])

    # Create Navigation Controller, starting the program
    controller = NavigationController()
    controller.show()
    
    sys.exit(app.exec_())