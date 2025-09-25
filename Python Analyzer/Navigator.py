from PyQt5.QtWidgets import QStackedWidget
from Screens.SelectFileScreen import SelectFileScreen
from Screens.HomeScreen import HomeScreen
from Screens.GPSPlotScreen import GPSPlotScreen
from Screens.RadarPlotScreen import RadarPlotScreen
from Screens.IMUPlotScreen import IMUPlotScreen
from Screens.CombinedPlotScreen import CombinedPlotScreen

class NavigationController:
    def __init__(self):
        self.stack = QStackedWidget()
        self.screens = {}
        
        self.startScreen = SelectFileScreen(self)
        self.startScreen.fileSelected.connect(self.goToHome)
        
        self.addScreen("select",self.startScreen)
        self.setCurrent("select")
        
    def addScreen(self,name,widget):
        self.screens[name] = widget
        self.stack.addWidget(widget)    
    
    def setCurrent(self,name):
        if name in self.screens:
            self.stack.setCurrentWidget(self.screens[name])
        else:
            raise ValueError(f"Screen {name} not found")
    
    def show(self):
        self.stack.setWindowTitle("Aircraft Calculator")
        self.stack.setGeometry(250,250,600,500)
        self.stack.show()

    # ----- Changing Screens -----

    def goToStart(self):
        self.setCurrent("select")

    def goToGPS(self,filePath=None):
        self.GPSScreen = GPSPlotScreen(self,filePath)
        self.GPSScreen.goBack.connect(self.goBack)
        self.addScreen("gps",self.GPSScreen)
        self.setCurrent("gps")

    def goToIMU(self,filePath=None):
        self.IMUScreen = IMUPlotScreen(self,filePath)
        self.IMUScreen.goBack.connect(self.goBack)
        self.addScreen("imu",self.IMUScreen)
        self.setCurrent("imu")

    def goToRadar(self,filePath=None):
        self.RadarScreen = RadarPlotScreen(self,filePath)
        self.RadarScreen.goBack.connect(self.goBack)
        self.addScreen("radar",self.RadarScreen)
        self.setCurrent("radar")
        
    def goToCombined(self,filePath=None):
        self.CombinedScreen = CombinedPlotScreen(self,filePath)
        self.CombinedScreen.goBack.connect(self.goBack)
        self.addScreen("combined",self.CombinedScreen)
        self.setCurrent("combined")
    
    def goToHome(self, filePath=None):
        self.homeScreen = HomeScreen(self,filePath)
        self.homeScreen.GPSNav.connect(self.goToGPS)
        self.homeScreen.IMUNav.connect(self.goToIMU)
        self.homeScreen.RadarNav.connect(self.goToRadar)
        self.homeScreen.CombinedNav.connect(self.goToCombined)
        self.addScreen("home",self.homeScreen)
        self.setCurrent("home")

    def goBack(self):
        self.setCurrent("home")