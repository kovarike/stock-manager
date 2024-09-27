[Setup]
AppName=StockManager
AppVersion=1.1
DefaultDirName={pf}\StockManager
DefaultGroupName=StockManager
OutputBaseFilename=AppStockManager
SetupIconFile=F:\www\c\src\public\manage.ico


[Files]
Source: "F:\www\c\apps\App_StockManager.exe"; DestDir: "{app}";


[Icons]
Name: "{group}\StockManager"; Filename: "{app}\App_StockManager.exe";

