import sys
import os
import re
import logging
import xml.etree.ElementTree as ET


EsConfigureName='ES_Configure.h'
configPath=os.path.join('nbproject','configurations.xml')

# class for building the string form of enum and modifying the file
# note that there is a specific sequence for calling the defs, wrong order will break things
# a superfunction of the ordering will be the default way to call them
class EnumToString(object):
	enumpreRegEx = r"typedef[ ]+enum.*\{(?P<enum_names>[^\}]+)\}[ ]+"
	enumpostRegEx = '_t;'
	enumNameRegEx=r"[\t ]*(?P<Names>[a-zA-Z0-9_]+)[ ]*,"
	stringPrefix='\nstatic const char *'
	stringMiddle='Names[] = {\n'
	stringSuffix='\n};\n\n'

	def __init__(self,fileName,fileType):
		self.fileName=fileName
		self.fileType=fileType
		if fileType=='ES_Configure':
			self.enumRegEx= enumpreRegEx + 'ES_EventTyp' + enumpostRegEx
			self.stringID='Event'
		elif fileType=='State_Machine':
			self.enumRegEx=enumpreRegEx + '.*?[sS]tate' + enumpostRegEx
			self.stringID='State'
		else:
			sys.exit(1) # bad form to exit here, but need to refresh proper pythonic methods in my head
		self.regExObject=re.compile(self.enumRegEx,re.MULTILINE)
		self.enumNameRegExObject=re.compile(enumNameRegEx,re.MULTILINE)


		# set up logging manually to set up two different streams
		stdLog = logging.getLogger()
		stdLog.setLevel(logging.DEBUG)
		stdLogHandler=logging.StreamHandler(sys.stdout)
		stdLogHandler.setLevel(logging.INFO)
		formatter = logging.Formatter('[%(levelname)s]%(asctime)s: %(message)s')
		stdLogHandler.setFormatter(formatter)
		stdLog.addHandler(stdLogHandler)

		fileHandler=logging.FileHandler('EnumToString.log')
		fileHandler.setFormatter(formatter)
		fileHandler.setLevel(logging.DEBUG)
		stdLog.addHandler(fileHandler)



	def modifyFileToIncludeStringForm(self):
		self.readInFile()
		if self.extractEnumNames() is False:
			print('Could not find a valid enum for '+self.fileName)
			return False
		self.buildStringForm()
		self.removeOldStringForm()
		self.addStringToFile()
		if self.origFileContents!=self.FileContents:
			self.writeFiletoDisk()
			print("modifications made")
		return True

	def readInFile(self):
		# read in the file to get the enum and close it for this pass
		with open(self.fileName, 'r') as f:
			f = open(self.fileName, 'r')
			self.FileContents = f.read()
			self.origFileContents=self.FileContents
		if self.FileContents is None:
			return False
		return True

	def extractEnumNames(self):
		# run the regex to get the contents of the enum and
		results = self.regExObject.search(self.FileContents)
		logging.debug(results)
		if results is None:
			return False
		enumContents = results.group('enum_names')
		self.endOfEnum=results.end()+1

		self.enumNames = []
		# we iterate line by line through the names to skip comments
		for line in enumContents.split('\n'):
			commentStart = line.find('/*')
			if commentStart == -1:
				commentStart = line.find('//')
				if commentStart == -1:
					commentStart = len(line)
			self.enumNames.extend(self.enumNameRegExObject.findall(line[:commentStart]))
		logging.debug(self.enumNames)
		return True


	#assembles the list already generated into the string form
	def buildStringForm(self):
		self.stringArray=self.stringPrefix+self.stringID+self.stringMiddle
		self.stringArray+='\n'.join(['\t\"'+x+'\",' for x in self.enumNames])
		self.stringArray+=self.stringSuffix
		logging.debug(self.stringArray)

	def addStringToFile(self):
		self.FileContents = self.FileContents [:self.endOfEnum] + self.stringArray + self.FileContents[self.endOfEnum:]


	def writeFiletoDisk(self):
		with open(self.fileName,'w') as f:
			f.write(self.FileContents)

	#remove the old string form regardless, nothing will happen if it doesn't exist
	def removeOldStringForm(self):
		# build a regEx locally
		stringFromRegEx=re.escape(self.stringPrefix)+self.stringID+re.escape(self.stringMiddle)+r"[^\}]+"+re.escape(self.stringSuffix)
		stringFromRegExObject=re.compile(stringFromRegEx,re.MULTILINE)

		if stringFromRegExObject.search(self.FileContents):
			self.FileContents=stringFromRegExObject.sub("",self.FileContents)




# build the regex designed to find the enum typedef
enumpreRegEx= r"typedef[ ]+enum.*\{(?P<enum_names>[^\}]+)\}[ ]+"
enumpostRegEx= '_t;'

esConRegEx= enumpreRegEx + 'ES_EventTyp' + enumpostRegEx
#print(esConRegEx)

# we also need a regex to find the ENUM Names
enumNameRegEx=r"[\t ]*(?P<Names>[a-zA-Z0-9_]+)[ ]*,"





# we start with processing es_configure.h, a file that will always be in the project

# without an es_configure we make the assumption that this is not an ES_Framework Project
# hence this script should not run
# the double search of the tree is weird but needed to ensure we have found es_configure.h
if os.path.exists(configPath):
	tree = ET.parse(configPath)
	sourceFileRoot=tree.getroot()
	for child in sourceFileRoot.iter('itemPath'):
		EsConfigurePath=child.text
		EsFileName=os.path.split(EsConfigurePath)[1]
		if EsFileName == EsConfigureName:
			print(EsFileName)
			break
else:
	print('No '+EsConfigureName+', exiting as not ES_Framework Project')
	sys.exit(0)
print("Found "+EsConfigureName+", continuing process")



eSConfigureBuild=EnumToString(EsConfigurePath,'ES_Configure')

eSConfigureBuild.modifyFileToIncludeStringForm()

if os.path.exists(configPath):
	tree = ET.parse(configPath)
	sourceFileRoot=tree.getroot()
	fileListingRoot=sourceFileRoot.find('logicalFolder')
	for child in sourceFileRoot:
		if child.tag == 'logicalFolder':
			sourceFileRoot=child
			break
	for child in fileListingRoot.findall('logicalFolder'):
		if child.get('name')=='SourceFiles':
			sourceFileRoot=child
			break
	for child in sourceFileRoot.iter('itemPath'):
		curSourceFile=child.text
		if os.path.exists(curSourceFile):
			print('Processing :' + curSourceFile)
			StringEnumBuild=EnumToString(curSourceFile,'State_Machine')
			StringEnumBuild.modifyFileToIncludeStringForm()