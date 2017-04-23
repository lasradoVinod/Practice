import threading
import os
import glob
import platform
from subprocess import Popen, PIPE

apps = []
generatedApps = []
compiledApps = []

lock = threading.Lock()
listGenLock = threading.Lock()
listCompLock = threading.Lock()

def display(val):
	global lock
	lock.acquire()
	print val
	lock.release()
	
def deleteFile(fname):
	print os.path.isfile(fname)
	if (os.path.isfile(fname)) == True:
		delFiles.write(fname + "\n")
		os.remove(fname)

def deleteFilesWithExt(dirname,ext):
	for root, dirs, files in os.walk(dirname):
   		for file in files:
   			if file.endswith(ext):
   				delFiles.write(os.path.join(root, file) + "\n")
   				os.remove(os.path.join(root, file))

def deleteAllFiles(dirname):
	for root, dirs, files in os.walk(dirname):
   		for file in files:
   			delFiles.write(os.path.join(root, file) + "\n")
   			os.remove(os.path.join(root, file))

class myGenerateThread (threading.Thread):
    def __init__(self,func):
        threading.Thread.__init__(self)
        self.func = func
    def run(self):
 		self.func()

def generateMacFile(currentApp):
	templateMacFile = '''execUserExecutionStopped() 
{ 
	__message "Execution stopped.\n";  	
	__message "Reading variable......\n";  			
	__var byte,address,_fileHandle,loop_count,loop1_count; 
	_fileHandle = __openFile("Temp_!test_app!.txt", "w"); 
	__fmessage _fileHandle, "Scalability Class =",(int)App_Os_GaaAppInfo[0].Class,"\n"; 
	__fmessage _fileHandle, "Application Id =",App_Os_GaaAppInfo[0].AppID,"\n"; 
	for(loop_count=0;loop_count ^< !test_cases!;loop_count++)
	{ 
		__fmessage _fileHandle, "App_Os_GaaTestArray[",loop_count,"] => Requirement IDs = (";
		for(loop1_count=0;loop1_count ^< 15;loop1_count++)
		{
			__fmessage _fileHandle,App_Os_GaaTestArray[loop_count].RequirementID[loop1_count];
			if(loop1_count ^< 14)
			{
				__fmessage _fileHandle,",";
			}		
		}
		__fmessage _fileHandle,");TestcaseID = ",App_Os_GaaTestArray[loop_count].TestcaseID,"; Result = ",(int)App_Os_GaaTestArray[loop_count].Result,";";
		__fmessage _fileHandle,"\n";
	}
	__closeFile( _fileHandle );
}'''
	templateMacFile.replace("!test_app!",currentApp[0])
	templateMacFile.replace("!test_cases!",currentApp[1])
	f = open ("comman_mac.mac",'w')
	f.write(templateMacFile)


def PortSpecificDebug(currentApp):
	command = '''"C:\Program Files\IAR Systems\Embedded Workbench 7.3\common\bin\cspybat" "C:\Program Files\IAR Systems\Embedded Workbench 7.3\arm\bin\armproc.dll" "C:\Program Files\IAR Systems\Embedded Workbench 7.3\arm\bin\armJET.dll" !Root!\!test_app!\obj\!test_app!.elf --plugin "C:\Program Files\IAR Systems\Embedded Workbench 7.3\arm\bin\armbat.dll" --device_macro "C:\Program Files\IAR Systems\Embedded Workbench 7.3\arm\config\debugger\Freescale\S32K.dmac" --macro !Root!\comman_mac.mac --flash_loader !Root!\App_Test.board --timeout 10000 --backend --endian=little --cpu=Cortex-M4 --fpu=VFPv4_SP -p "C:\Program Files\IAR Systems\Embedded Workbench 7.3\arm\CONFIG\debugger\Freescale\S32K144.ddf" --semihosting = none --device=S32K144 --multicore_nr_of_cores=1 --jet_standard_reset=5,0,0 --reset_style=\"0,-,0,Disabled__no_reset_\" --reset_style=\"1,-,0,Software\" --reset_style=\"2,-,0,Hardware\" --reset_style=\"3,-,0,Core\" --reset_style=\"4,-,0,System\" --reset_style=\"5,ResetAndDisableWatchdog,1,Custom\" --jet_power_from_probe=leave_on --drv_verify_download --drv_interface=SWD --drv_catch_exceptions=0x3f0 --drv_trace_size=8388608 --board_file=!Root!\App_Test.board > NUL 2>&1'''
	command.replace("!Root!",rootDir)
	command.replace("!test_app!",currentApp[0])
	generateMacFile(currentApp)
	cmd = [command]
	p = Popen(cmd,shell=True)
	p.communicate()

def Generate():
	for ent in apps:
		# Deleting Compilation log file
		deleteFile (logComp + directoryStr + ent[0] + ".txt")
		#Deleting Result File
		deleteFile (testRes + directoryStr + ent[0] + ".txt")
		#Deleting all files from src folder
		deleteAllFiles (osConf + directoryStr + ent[0] + directoryStr + "src")
		#Deleting all files from inc folder
		deleteAllFiles (osConf + directoryStr + ent[0] + directoryStr + "inc")
		#Deleting all files from obj folder
		deleteAllFiles (rootDir + directoryStr + ent[0] + directoryStr + "obj")

		display( "generating for " + ent[0])

		fname = rootDir + directoryStr + ent[0] + ".mak"

		if os.path.isfile(fname):
			cmdStr = "make OS_PROCESSOR_VARIANT=REV1 -f " + ent[0] + ".mak" + "generate_os_config >" + logComp + \
						directoryStr + ent[0] + ".txt 2>&1"
			cmd = [cmdStr]
			p = Popen(cmd, shell = True)
			p.communicate() #waiting for execution to complete
			listGenLock.acquire()
			generatedApps.append(ent)
			listGenLock.release()
		else:
			errorStr = "Makefile for " + ent[0] + " does not exist "
			display(errorStr)
			fileLog = open ((logComp + directoryStr + ent[0] + ".txt") , 'w' )
			fileLog.write(errorStr)
	genDone = True

def Compile():
	while (True):
		if (len(generatedApps) > 0):
			listGenLock.acquire()
			currentApp = generatedApps[0]
			del generatedApps[0]
			listGenLock.release()

			display( "compiling " + currentApp[0])
			cmdStr = "make OS_PROCESSOR_VARIANT=REV1 -f " + currentApp[0] + ".mak" + "-B " + currentApp[0] +".elf >>" + logComp + \
						directoryStr + ent[0] + ".txt 2>&1"
			cmd = [cmdStr]
			p = Popen(cmd,shell=True)
			p.communicate() #waiting for execution to complete

			eflPath = rootDir + directoryStr + currentApp[0] + directoryStr + "obj" + directoryStr + currentApp[0] + ".elf"
			if os.path.isfile(eflPath):
				listCompLock.acquire()
				compiledApps.append(currentApp)
				listCompLock.release()
		if genDone == True and len(generatedApps) == 0 :
			compDone = True
			break

def Debug():
	while (True):
		if (len(compiledApps) > 0):
			
			listCompLock.acquire()
			currentApp = compiledApps[0]
			del compiledApps[0]
			listCompLock.release()

			display( "debugging " + currentApp[0])
			PortSpecificDebug(currentApp)
		
		if compDone == True and len(compiledApps) == 0 :
			debDone = True
			break


osName = platform.system()
directoryStr = '/'
if (osName == 'Windows'):
	directoryStr = "\\"

rootDir = os.getcwd()
logComp = rootDir + directoryStr + "Log_Compile"
testRes = rootDir + directoryStr + "Test_Results"
osConf  = rootDir + directoryStr + "Os_TestCfg"
testApp = rootDir + directoryStr + "Test_App.txt"
deletedFiles = rootDir + directoryStr + "DeletedFiles.txt"

delFiles = open(deletedFiles,'w')

deleteFilesWithExt(logComp,".xlsx")
deleteFilesWithExt(logComp,".xml")

with open(testApp, 'r') as f:
    for line in f:
        if (line[0] == ";"):
        	continue
        current = line.split("#")
        del current[-1]
        apps.append(current)

print apps

genDone = False
compDone = False
debDone = False

genThread = myGenerateThread(Generate)
compThread = myGenerateThread(Compile)
#debThread = myGenerateThread(Debug)

genThread.start()
compThread.start()
#debThread.start()

genThread.join()
compThread.join()
#debThread.join()

while(debDone == False):
	continue

cmdStr = "java -jar Build_Checker.jar -module Os -cpu S32K144 -compiler IAR -testlogs Test_Results \
-buildlogs Log_Compile -strconfigid ASR421_S32K144_ESTR -debug CSPY -cpucore 1 -arversion R4.2.1"

cmd = [cmdStr]
p = Popen(cmd,shell=True)
p.communicate() #waiting for execution to complete

print ("Completed All Files.")
print ("ESTR Generated")