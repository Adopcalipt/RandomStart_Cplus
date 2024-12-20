/*
			Random Start++ Systems
		--Created By Adoppocalipt 2023--
*/

#include "ModSystems.h"
#include "GtaVMenu.h"
#include "keyboard.h"

#include <cstdlib>		//sRand - Random Number Generator
#include <ctime>		//time_t - Get the current date/time
#include <cmath>		//Math Functions Cos Tan etc...
#include <filesystem>	//Directory control Add/Remove Folders
#include <fstream>		//ofstream read/write text documents
#include <iostream>		//Header that defines the standard input/output stream objects:

using namespace Mod_Data;

#include <stdio.h>		//Makes Stream Pointers to files
#include <wchar.h>		//Support for w_Chars
#include <locale>		//streamng Support for w_Chars
#include <random>		//Randomize vector lists

#pragma comment(lib, "Winmm.lib")

namespace Mod_Systems
{
	void LoggerLight(const std::string& text);

	Hash MyHashKey(const std::string& name)
	{
		return GAMEPLAY::GET_HASH_KEY((LPSTR)name.c_str());
	}

	std::string ConvertWideToUtf8(const std::wstring& wstr)
	{
		int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
		std::string str(count, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
		return str;
	}

	std::string GetExeFileName()
	{
		WCHAR buffer[MAX_PATH]{};
		GetModuleFileNameW(NULL, buffer, ARRAYSIZE(buffer));

		return ConvertWideToUtf8(std::wstring(buffer));
	}
	std::string GetDir()
	{
		std::string f = GetExeFileName();
		std::string Dir = f.substr(0, f.find_last_of("\\/"));

		return Dir;
	}
	std::string TimeDate()
	{
		time_t curr_time;
		curr_time = time(NULL);
		std::string tm = ctime(&curr_time);
		tm[tm.length() - 1] = char(32);//32 is this fails testing the _s version..
		return tm;
	}
	

	void BuildMissingDirectory(std::string dir)
	{
		if (CreateDirectoryA((LPSTR)dir.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
		{		}
	}
	void DirectoryTest()
	{
		BuildMissingDirectory(DirRandStart);
		BuildMissingDirectory(DirRandNumb);
		BuildMissingDirectory(DirSavedPed);
		BuildMissingDirectory(DirWeapons);
		BuildMissingDirectory(DirVehicles);
		BuildMissingDirectory(DirTranslate);
		BuildMissingDirectory(DirCustPeds);
		BuildMissingDirectory(DirectOutfitFolder);
		BuildMissingDirectory(DirectOutfitMale);
		BuildMissingDirectory(DirectOutfitFemale);
		BuildMissingDirectory(DirectOutfitMichael);
		BuildMissingDirectory(DirectOutfitFranklin);
		BuildMissingDirectory(DirectOutfitTrevor);
	}

	bool File_exists(const std::string& filename)
	{
		try
		{
			std::ifstream Infield(filename);
			return Infield.good();
		}
		catch (...)
		{
			return false;
		}
	}
	void Write_ini(const std::string& file, const std::vector<std::string>& text)
	{
		std::ofstream MyFile(file);
		for (int i = 0; i < text.size(); i++)
		{
			MyFile << text[i];
			MyFile << "\n";
		}
		MyFile.close();
	}
	void Edit_ini(const std::string& file, const std::string& text)
	{
		if (File_exists(file))
		{
			std::ofstream MyFile(file, std::ios_base::app | std::ios_base::out);

			MyFile << text;
			MyFile << "\n";
			MyFile.close();
		}
	}
	void Delete_ini(const std::string& filename)
	{
		LoggerLight("Delete_ini == " + filename);
		if (File_exists(filename))
		{
			try
			{
				std::filesystem::remove(filename);
			}
			catch (...)
			{
				LoggerLight(filename + "Has Not Been Deleted");
			}
		}
		else
			LoggerLight("Delete_ini == " + filename + " Does not exist...");
	}
	std::vector<std::string> Read_ini(const std::string& fileName)
	{
		std::string myText;
		std::vector<std::string> textList = {};

		if (File_exists(fileName))
		{
			std::ifstream MyReadFile(fileName);

			while (std::getline(MyReadFile, myText))
			{
				// Output the text from the file
				textList.push_back(myText);
			}
			MyReadFile.close();
		}

		return textList;
	}

	const std::string VFunk = GetDir() + "/V_Functions.asi";
	typedef bool(*SnowFallType)();
	typedef void(*LetItSnowType)(bool snow);

	bool AccessSnowFallType()
	{
		// Load the first .asi file (DLL)
		bool b = false;
		if (File_exists(VFunk))
		{
			HMODULE hMod = LoadLibrary(L"V_Functions.asi");
			if (hMod != nullptr)
			{
				// Get the function pointer
				SnowFallType MyExportedFunction = (SnowFallType)GetProcAddress(hMod, "SnowFall");

				if (MyExportedFunction != nullptr)
					b = MyExportedFunction();

				FreeLibrary(hMod);
			}
		}
		else
			MissingFilesNag = true;

		return b;
	}
	void AccessLetItSnowType(bool snow)
	{
		if (File_exists(VFunk))
		{
			// Load the first .asi file (DLL)
			HMODULE hMod = LoadLibrary(L"V_Functions.asi");

			if (hMod != nullptr)
			{
				// Get the function pointer
				LetItSnowType MyExportedFunction = (LetItSnowType)GetProcAddress(hMod, "LetItSnow");

				if (MyExportedFunction != nullptr)
					MyExportedFunction(snow);

				FreeLibrary(hMod);
			}
		}
		else
			MissingFilesNag = true;
	}

	bool startLogs = false;
	void LoggerLight(const std::string& text)
	{
		if (Mod_Data::Mod_Settings.Loging)
		{
			if (startLogs)
				Edit_ini(LoggingFile, TimeDate() + text);
			else
			{
				startLogs = true;
				std::vector<std::string> NewFile = { TimeDate() + text };
				Write_ini(LoggingFile, NewFile);
			}
		}
	}

	void Play_wav(const std::string& soundFile)
	{
		PlaySoundA((LPSTR)soundFile.c_str(), GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
		//const wchar_t* path = ConvertAnsiToWide((LPSTR)soundFile.c_str()).c_str();
		//PlaySound(path, GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
		//(LPCWSTR)soundFile.c_str()
	}

	void Remove_blanks(std::vector<std::string>* stringlist)
	{
		for (int i = 0; i < (int)stringlist->size(); i++)
		{
			if (stringlist->at(i) == "")
				stringlist->erase(stringlist->begin() + i);
		}
	}
	
	std::vector<std::string> Convert_to_strings(const std::vector<int>& text)
	{
		std::vector<std::string> output = {};

		for (int i = 0; i < text.size(); i++)
			output.push_back(std::to_string(text[i]));

		return output;
	}
	int Find_String_Pos(const std::vector<std::string>& stringList, const std::string& item) 
	{
		int Output = -1;
		for (int i = 0; i < (int)stringList.size(); i++)
		{
			if (MyHashKey(stringList[i]) == MyHashKey(item))
			{
				Output = i;
				break;
			}
		}
		return Output;
	}

	bool Contains_int(const std::vector<int>& intList, int item)
	{
		bool b = false;
		for (int i = 0; i < intList.size(); i++)
		{
			if (intList[i] == item)
				b = true;
		}
		return b;
	}
	bool Contains_string(const std::string& line, const std::string& wholeString)
	{
		bool Contain = false;
		int iLine = 0;
		std::string Word = "";
		for (int i = 0; i < wholeString.length(); i++)
		{
			if (iLine < line.length())
			{
				if (line[iLine] == wholeString[i])
				{
					Contain = true;
					Word += wholeString[i];
					iLine++;
				}
				else
				{
					iLine = 0;
					Word = "";
				}
			}
			else if (iLine > 0)
			{
				if (line == Word)
					break;
				else
				{
					iLine = 0;
					Word = "";

					if (line[0] == wholeString[i])
					{
						Contain = true;
						Word += wholeString[i];
						iLine++;
					}
				}
			}
		}

		if (Contain)
		{
			if (line != Word)
				Contain = false;
		}

		return Contain;
	}
	bool Contains_string(char line, const std::string& wholeString)
	{
		bool Contain = false;
		for (int i = 0; i < wholeString.length(); i++)
		{
			if (line == wholeString[i])
			{
				Contain = true;
				break;
			}
		}
		return Contain;
	}
	int Find_char_position(char chars, const std::string& wholeString)
	{
		int iLine = -1;
		for (int i = 0; i < wholeString.length(); i++)
		{
			if (chars == wholeString[i])
			{
				iLine = i;
				break;
			}
		}
		return iLine;
	}
	int Find_char_position(const std::string& chars, const std::string& wholeString)
	{
		int iLine = -1;
		for (int i = 0; i < wholeString.length(); i++)
		{
			if (chars[0] == wholeString[i])
			{
				iLine = i;
				break;
			}
		}
		return iLine;
	}

	int Convert_to_int(const std::string& line)
	{
		int iNum = 0;
		int iTimes = 0;
		bool bNegative = false;
		for (int i = (int)line.size(); i > -1; i--)
		{
			bool bSkip = false;
			int iAdd = 0;
			char sComp = line[i];

			if (sComp == char(45))
				bNegative = true;
			else if (sComp == char(49))
			{
				bNegative = false;
				iAdd = 1;
			}
			else if (sComp == char(50))
			{
				bNegative = false;
				iAdd = 2;
			}
			else if (sComp == char(51))
			{
				bNegative = false;
				iAdd = 3;
			}
			else if (sComp == char(52))
			{
				bNegative = false;
				iAdd = 4;
			}
			else if (sComp == char(53))
			{
				bNegative = false;
				iAdd = 5;
			}
			else if (sComp == char(54))
			{
				bNegative = false;
				iAdd = 6;
			}
			else if (sComp == char(55))
			{
				bNegative = false;
				iAdd = 7;
			}
			else if (sComp == char(56))
			{
				bNegative = false;
				iAdd = 8;
			}
			else if (sComp == char(57))
			{
				bNegative = false;
				iAdd = 9;
			}
			else if (sComp == char(48))
			{

			}
			else
				bSkip = true;

			if (!bSkip)
			{
				if (iTimes == 0)
				{
					iNum = iAdd;
					iTimes = 1;
				}
				else
					iNum += iAdd * iTimes;
				iTimes *= 10;
			}
		}

		if (bNegative)
			iNum = iNum * (-1);

		return iNum;
	}
	float Convert_to_float(const std::string& line)
	{
		float fNum = 0;
		std::string decOp = ".";
		int endIndex = -1; // Index to print until (exclusive)
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == decOp[0])
			{
				endIndex = i;
				break;
			}
		}

		if (endIndex >= 0 && endIndex <= line.length())
		{
			std::string afterDec = line.substr(endIndex + 1);
			std::string bigNum = line.substr(0, endIndex) + afterDec;
			fNum = (float)Convert_to_int(bigNum);

			for (int i = 0; i < afterDec.length(); i++)
				fNum = fNum / 10;
		}
		else
			fNum = (float)Convert_to_int(line);

		return fNum;
	}
	bool Convert_to_bool(const std::string& line)
	{
		if (Contains_string("True", line))
			return true;
		else if (Contains_string("true", line))
			return true;
		else if (Contains_string("TRUE", line))
			return true;
		else
			return false;
	}
	std::string Remove_char61(const std::string& line)
	{
		int iSt = 0;
		std::string Output;
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == char(61))
			{
				iSt = i + 1;
				break;
			}
		}
		for (int i = iSt; i < line.length(); i++)
			Output += line[i];

		return Output;
	}
	std::string Convert_to_string(bool outPut)
	{
		std::string s = "false";
		if (outPut)
			s = "true";

		return s;
	}
	float Two_decimal(const std::string& num)
	{
		int iSize = (int)num.length();
		std::string Output = "";
		for (int i = 0; i < iSize; i++)
		{
			Output += num[i];
			int iMore = i + 3;
			if (num[i] == char(46) && iMore < num.length())
				iSize = i + 3;
		}
		return Convert_to_float(Output);
	}

	int DayOfWeek()
	{
		int iDay;
		std::string t = TimeDate();
		if (Contains_string("Mon", t))
			iDay = 1;
		else if (Contains_string("Tue", t))
			iDay = 2;
		else if (Contains_string("Wed", t))
			iDay = 3;
		else if (Contains_string("Thu", t))
			iDay = 4;
		else if (Contains_string("Fri", t))
			iDay = 5;
		else
			iDay = 6;

		return iDay;
	}

	bool ERando = false;
	bool DirTest = true;	
	void RandomizeIntList(std::vector<int>* numbers)
	{
		std::random_device Randv;
		std::mt19937 Output(Randv());

		std::shuffle(numbers->begin(), numbers->end(), Output);
	}
	float RandomFloat(float min, float max)
	{
		if (min < max)
		{
			std::random_device RandoNum;
			std::mt19937 Mt(RandoNum());
			std::uniform_real_distribution<double> Output((double)min, (double)max);

			return (float)Output(Mt);
		}
		else
			return min;
	}
	int RandomInt(int min, int max)
	{
		if (min < max)
		{
			std::random_device RandoNum;
			std::mt19937 Mt(RandoNum());
			std::uniform_real_distribution<double> Output((double)min, (double)max);

			return (int)Output(Mt);
		}
		else
			return min;
	}
	void NewNums(std::vector<int>* numbers, int min, int max)
	{
		numbers->clear();
		for (int i = min; i < max + 1; i++)
			numbers->push_back(i);
		RandomizeIntList(numbers);
	}
	int LessRandomInt(const std::string& file, int min, int max)
	{
		if (min < max)
		{
			int Place = 0;
			int Num = min;
			std::string FileLoc = DirRandNumb + "/" + file + ".txt";
			std::vector<std::string> MyNums = Read_ini(FileLoc);
			std::vector<int> NumList = {};

			if (MyNums.size() < 2)
				NewNums(&NumList, min, max);
			else
			{
				bool NewWrite = false;
				if (Contains_string("min=", MyNums[0]))
				{
					if (Convert_to_int(MyNums[0]) != min)
						NewWrite = true;
				}
				else
					NewWrite = true;

				if (Contains_string("max=", MyNums[1]))
				{
					if (Convert_to_int(MyNums[1]) != max)
						NewWrite = true;
				}
				else
					NewWrite = true;

				for (int i = 2; i < MyNums.size(); i++)
					NumList.push_back(Convert_to_int(MyNums[i]));

				if (NumList.size() == 0 || NewWrite)
					NewNums(&NumList, min, max);
			}

			Place = RandomInt(0, (int)NumList.size() - 1);
			Num = NumList[Place];
			NumList.erase(NumList.begin() + Place);

			std::vector<std::string> Output = { "min=" + std::to_string(min) , "max=" + std::to_string(max) };

			for (int i = 0; i < NumList.size(); i++)
				Output.push_back(std::to_string(NumList[i]));

			Write_ini(FileLoc, Output);

			LoggerLight("LessRandomInt, id == " + file + ", min == " + std::to_string(min) + ", max == " + std::to_string(max) + "Num == " + std::to_string(Num));

			return Num;
		}
		else
			return min;
	}
	int LessRandomInt(const std::string& file, const std::vector<int>& intList)
	{
		if ((int)intList.size() > 0)
		{
			int yourPlace = 0;
			int yourNum = 0;
			std::vector<std::string> MyNums = Read_ini(DirRandNumb + "/" + file + ".txt");
			std::vector<int> NumList = {};

			for (int i = 0; i < MyNums.size(); i++)
				NumList.push_back(Convert_to_int(MyNums[i]));;

			if (NumList.size() == 0)
				NumList = intList;

			yourPlace = RandomInt(0, (int)NumList.size());
			yourNum = NumList[yourPlace];
			NumList.erase(NumList.begin() + yourPlace);

			std::vector<std::string> output = {};

			for (int i = 0; i < NumList.size(); i++)
				output.push_back(std::to_string(NumList[i]));

			Write_ini(DirRandNumb + "/" + file + ".txt", output);

			return yourNum;
		}
		else
			return 0;
	}

	bool PressAnyKey()
	{
		bool AnyKey = false;
		Mod_Systems::Menu_Button_state(&AnyKey, Mod_Data::KeyFind[Mod_Data::Mod_Settings.MenuKey]);
		int LastPressed = (int)CONTROLS::_0xD7D22F5592AED8BA(0);

		if (LastPressed < 100)
			AnyKey = true;
		return AnyKey;
	}

	void StartScript(const std::string& scriptName, int buffer)
	{
		SCRIPT::REQUEST_SCRIPT((LPSTR)scriptName.c_str());
		while (!SCRIPT::HAS_SCRIPT_LOADED((LPSTR)scriptName.c_str()))
		{
			SCRIPT::REQUEST_SCRIPT((LPSTR)scriptName.c_str());
			WAIT(1);
		}

		SYSTEM::START_NEW_SCRIPT((LPSTR)scriptName.c_str(), buffer);
		SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED((LPSTR)scriptName.c_str());
	}

	void ReBuildIni(void* obj)
	{
		LoggerLight("ReBuildIni");
		Mod_Class::Settings_Ini* PSet = static_cast<Mod_Class::Settings_Ini*>(obj);
		if (PSet != nullptr)
		{
			std::vector<std::string> AddIni = {
				"[Settings]",
				"MenuKey=" + std::to_string(PSet->MenuKey),
				"Auto_Run=" + Convert_to_string(PSet->Auto_Run),
				"Random_Ped=" + Convert_to_string(PSet->Random_Ped),
				"Saved_Ped=" + Convert_to_string(PSet->Saved_Ped),
				"Disable_Record_Key=" + Convert_to_string(PSet->Disable_Record_Key),
				"Random_Weapons=" + Convert_to_string(PSet->Random_Weapons),
				"WatchDead=" + Convert_to_string(PSet->WatchDead),
				"Funeral=" + Convert_to_string(PSet->Funeral),
				"Prison=" + Convert_to_string(PSet->Prison),
				"BeachPart=" + Convert_to_string(PSet->BeachPart),
				"Auto_Save=" + Convert_to_string(PSet->Auto_Save),
				"Menu_Left_Side=" + Convert_to_string(PSet->Menu_Left_Side),
				"[Reincarnation]",
				"Reincarnate=" + Convert_to_string(PSet->Reincarnate),
				"ReCurr=" + Convert_to_string(PSet->ReCurr),
				"[Controler]",
				"ControlSupport=" + Convert_to_string(PSet->ControlSupport),
				"ControlA=" + std::to_string(PSet->ControlA),
				"ControlB=" + std::to_string(PSet->ControlB),
				"[Language]",
				"Lang_Set=" + std::to_string(PSet->Lang_Set),
				"[Senarios]",
				"BeachPed=" + Convert_to_string(PSet->BeachPed),
				"Tramps=" + Convert_to_string(PSet->Tramps),
				"Highclass=" + Convert_to_string(PSet->Highclass),
				"Midclass=" + Convert_to_string(PSet->Midclass),
				"Lowclass=" + Convert_to_string(PSet->Lowclass),
				"Business=" + Convert_to_string(PSet->Business),
				"Bodybuilder=" + Convert_to_string(PSet->Bodybuilder),
				"GangStars=" + Convert_to_string(PSet->GangStars),
				"Epsilon=" + Convert_to_string(PSet->Epsilon),
				"Jogger=" + Convert_to_string(PSet->Jogger),
				"Golfer=" + Convert_to_string(PSet->Golfer),
				"Hiker=" + Convert_to_string(PSet->Hiker),
				"Methaddict=" + Convert_to_string(PSet->Methaddict),
				"Rural=" + Convert_to_string(PSet->Rural),
				"Cyclist=" + Convert_to_string(PSet->Cyclist),
				"LGBTWXYZ=" + Convert_to_string(PSet->LGBTWXYZ),
				"PoolPeds=" + Convert_to_string(PSet->PoolPeds),
				"Workers=" + Convert_to_string(PSet->Workers),
				"Jetski=" + Convert_to_string(PSet->Jetski),
				"BikeATV=" + Convert_to_string(PSet->BikeATV),
				"Services=" + Convert_to_string(PSet->Services),
				"Pilot=" + Convert_to_string(PSet->Pilot),
				"Animals=" + Convert_to_string(PSet->Animals),
				"Yankton=" + Convert_to_string(PSet->Yankton),
				"Cayo=" + Convert_to_string(PSet->Cayo),
				"[Additional]",
				"Loging=" + Convert_to_string(PSet->Loging),
				"[Snow Months]",
				"SDJan=" + Convert_to_string(PSet->Jan),
				"SDFeb=" + Convert_to_string(PSet->Feb),
				"SDMar=" + Convert_to_string(PSet->Mar),
				"SDApr=" + Convert_to_string(PSet->Apr),
				"SDMay=" + Convert_to_string(PSet->May),
				"SDJun=" + Convert_to_string(PSet->Jun),
				"SDJul=" + Convert_to_string(PSet->Jul),
				"SDAug=" + Convert_to_string(PSet->Aug),
				"SDSep=" + Convert_to_string(PSet->Sep),
				"SDOct=" + Convert_to_string(PSet->Oct),
				"SDNov=" + Convert_to_string(PSet->Nov),
				"SDDec=" + Convert_to_string(PSet->Dec)
			};
			Write_ini(SettingsFile, AddIni);
		}
	}
	void FindSettings(Mod_Class::Settings_Ini* modSets)
	{
		if (modSets != nullptr)
		{
			LoggerLight("FindSettings");
			std::vector<std::string> MySet = Read_ini(SettingsFile);
			if (MySet.size() == 0)
				Mod_Data::First_Load = true;
			else
			{
				for (int i = 0; i < (int)MySet.size(); i++)
				{
					std::string line = MySet[i];
					if (Contains_string("MenuKey", line))
						modSets->MenuKey = Convert_to_int(line);
					else if (Contains_string("Auto_Run", line))
						modSets->Auto_Run = Convert_to_bool(line);
					else if (Contains_string("Random_Ped", line))
						modSets->Random_Ped = Convert_to_bool(line);
					else if (Contains_string("Saved_Ped", line))
						modSets->Saved_Ped = Convert_to_bool(line);
					else if (Contains_string("Disable_Record_Key", line))
						modSets->Disable_Record_Key = Convert_to_bool(line);
					else if (Contains_string("Random_Weapons", line))
						modSets->Random_Weapons = Convert_to_bool(line);
					else if (Contains_string("WatchDead", line))
						modSets->WatchDead = Convert_to_bool(line);
					else if (Contains_string("Funeral", line))
						modSets->Funeral = Convert_to_bool(line);
					else if (Contains_string("Prison", line))
						modSets->Prison = Convert_to_bool(line);
					else if (Contains_string("BeachPart", line))
						modSets->BeachPart = Convert_to_bool(line);
					else if (Contains_string("Reincarnate", line))
						modSets->Reincarnate = Convert_to_bool(line);
					else if (Contains_string("ReCurr", line))
						modSets->ReCurr = Convert_to_bool(line);
					else if (Contains_string("Auto_Save", line))
						modSets->Auto_Save = Convert_to_bool(line);
					else if (Contains_string("Menu_Left_Side", line))
						modSets->Menu_Left_Side = Convert_to_bool(line);
					else if (Contains_string("ControlSupport", line))
						modSets->ControlSupport = Convert_to_bool(line);
					else if (Contains_string("ControlA", line))
						modSets->ControlA = Convert_to_int(line);
					else if (Contains_string("ControlB", line))
						modSets->ControlB = Convert_to_int(line);
					else if (Contains_string("Lang_Set", line))
						modSets->Lang_Set = Convert_to_int(line);
					else if (Contains_string("BeachPed", line))
						modSets->BeachPed = Convert_to_bool(line);
					else if (Contains_string("Tramps", line))
						modSets->Tramps = Convert_to_bool(line);
					else if (Contains_string("Highclass", line))
						modSets->Highclass = Convert_to_bool(line);
					else if (Contains_string("Midclass", line))
						modSets->Midclass = Convert_to_bool(line);
					else if (Contains_string("Lowclass", line))
						modSets->Lowclass = Convert_to_bool(line);
					else if (Contains_string("Business", line))
						modSets->Business = Convert_to_bool(line);
					else if (Contains_string("Bodybuilder", line))
						modSets->Bodybuilder = Convert_to_bool(line);
					else if (Contains_string("GangStars", line))
						modSets->GangStars = Convert_to_bool(line);
					else if (Contains_string("Epsilon", line))
						modSets->Epsilon = Convert_to_bool(line);
					else if (Contains_string("Jogger", line))
						modSets->Jogger = Convert_to_bool(line);
					else if (Contains_string("Golfer", line))
						modSets->Golfer = Convert_to_bool(line);
					else if (Contains_string("Hiker", line))
						modSets->Hiker = Convert_to_bool(line);
					else if (Contains_string("Methaddict", line))
						modSets->Methaddict = Convert_to_bool(line);
					else if (Contains_string("Rural", line))
						modSets->Rural = Convert_to_bool(line);
					else if (Contains_string("Cyclist", line))
						modSets->Cyclist = Convert_to_bool(line);
					else if (Contains_string("LGBTWXYZ", line))
						modSets->LGBTWXYZ = Convert_to_bool(line);
					else if (Contains_string("PoolPeds", line))
						modSets->PoolPeds = Convert_to_bool(line);
					else if (Contains_string("Workers", line))
						modSets->Workers = Convert_to_bool(line);
					else if (Contains_string("Jetski", line))
						modSets->Jetski = Convert_to_bool(line);
					else if (Contains_string("BikeATV", line))
						modSets->BikeATV = Convert_to_bool(line);
					else if (Contains_string("Services", line))
						modSets->Services = Convert_to_bool(line);
					else if (Contains_string("Pilot", line))
						modSets->Pilot = Convert_to_bool(line);
					else if (Contains_string("Animals", line))
						modSets->Animals = Convert_to_bool(line);
					else if (Contains_string("Yankton", line))
						modSets->Yankton = Convert_to_bool(line);
					else if (Contains_string("Cayo", line))
						modSets->Cayo = Convert_to_bool(line);
					else if (Contains_string("Loging", line))
						modSets->Loging = Convert_to_bool(line);
					else if (Contains_string("SDJan", line))
						modSets->Jan = Convert_to_bool(line);
					else if (Contains_string("SDFeb", line))
						modSets->Feb = Convert_to_bool(line);
					else if (Contains_string("SDMar", line))
						modSets->Mar = Convert_to_bool(line);
					else if (Contains_string("SDApr", line))
						modSets->Apr = Convert_to_bool(line);
					else if (Contains_string("SDMay", line))
						modSets->May = Convert_to_bool(line);
					else if (Contains_string("SDJun", line))
						modSets->Jun = Convert_to_bool(line);
					else if (Contains_string("SDJul", line))
						modSets->Jul = Convert_to_bool(line);
					else if (Contains_string("SDAug", line))
						modSets->Aug = Convert_to_bool(line);
					else if (Contains_string("SDSep", line))
						modSets->Sep = Convert_to_bool(line);
					else if (Contains_string("SDOct", line))
						modSets->Oct = Convert_to_bool(line);
					else if (Contains_string("SDNov", line))
						modSets->Nov = Convert_to_bool(line);
					else if (Contains_string("SDDec", line))
						modSets->Dec = Convert_to_bool(line);
				}
			
				if (modSets->Random_Ped && modSets->Saved_Ped)
					modSets->Saved_Ped = false;
				else if (!modSets->Random_Ped && !modSets->Saved_Ped && modSets->ReCurr)
					modSets->ReCurr = false;

				if (modSets->Reincarnate && modSets->Funeral)
					modSets->Reincarnate = false;
			}

			ReBuildIni(modSets);
		}
	}

	void FindWeapons(std::vector<Mod_Class::Weap_Read>* myWeaps, const std::string& file)
	{
		std::vector<std::string> MySet = Read_ini(file);
		std::string Lingos = LangosPick[Mod_Data::Mod_Settings.Lang_Set];
		LoggerLight("FindWeapons == " + Lingos);
		if (MySet.size() == 0)
			LoggerLight("FindWeapons...Some_Div_Cant_just_add_the_files_in_the Zip_file");
		else
		{
			std::string Weap = "", Desc = "";
			int Tint = 7;
			bool Addons = false, Liverys = false;

			for (int i = 0; i < (int)MySet.size(); i++)
			{
				std::string line = MySet[i];
				if (Contains_string("Name", line))
					Weap = Remove_char61(line);
				else if (Contains_string(Lingos, line))
					Desc = Remove_char61(line);
				else if (Contains_string("Tints", line))
					Tint = Convert_to_int(line);
				else if (Contains_string("Components", line))
					Addons = Convert_to_bool(line);
				else if (Contains_string("Liveries", line))
				{
					Liverys = Convert_to_bool(line);
					myWeaps->push_back(Mod_Class::Weap_Read(Weap, Desc, Tint, Addons, Liverys));
				}
			}
		}
	}
	void FindWeaponComponents(std::vector<Mod_Class::Weap_Addons>* myWeaps, const std::string& file, const std::string& weapon)
	{
		LoggerLight("FindWeaponComponents == " + weapon);
		if (myWeaps != nullptr)
		{
			LoggerLight("FindWeaponComponents " + weapon);
			std::vector<std::string> MySet = Read_ini(file);
			std::string Lingos = LangosPick[Mod_Data::Mod_Settings.Lang_Set];
			if (MySet.size() == 0)
				LoggerLight("FindWeaponComponents...Some_Div_Cant_just_add_the_files_in_the Zip_file");
			else
			{
				std::string Addon = "", Desc = "";
				for (int i = 0; i < (int)MySet.size(); i++)
				{
					std::string line = MySet[i];
					if (Contains_string("Name=", line))
					{
						Addon = Remove_char61(line);
					}
					else if (Contains_string(Lingos, line))
					{
						if ((bool)WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(Mod_Systems::MyHashKey(weapon), Mod_Systems::MyHashKey(Addon)))
						{
							Desc = Remove_char61(line);
							myWeaps->push_back(Mod_Class::Weap_Addons(Addon, Desc));
						}

					}

				}
			}
		}
	}
	void FindWeaponTints(std::vector<std::string>* myWeaps, int list)
	{
		if (myWeaps != nullptr)
		{
			LoggerLight("FindWeaponTints list == " + std::to_string(list));
			std::vector<std::string> MySet = Read_ini(WeapTints);
			std::string Lingos = LangosPick[Mod_Data::Mod_Settings.Lang_Set];
			bool thisList = false;
			if (MySet.size() == 0)
				LoggerLight("FindWeaponTints...Some_Div_Cant_just_add_the_files_in_the Zip_file");
			else
			{
				int Mode = 6;
				for (int i = 0; i < (int)MySet.size(); i++)
				{
					std::string line = MySet[i];
					if (Contains_string("Version=", line))
					{
						Mode = Convert_to_int(line);
						if (Mode == list)
							thisList = true;
						else
							thisList = false;
						LoggerLight("FindWeaponTints iMode == " + std::to_string(Mode));
					}
					else if (thisList)
					{
						if (Contains_string(Lingos, line))
							myWeaps->push_back(Remove_char61(line));
					}
				}
			}
		}
	}

	void SaveMyWeaps()
	{
		std::vector<std::string> NewSave = {};

		for (int i = 0; i < (int)Mod_Data::Player_Weaps.size(); i++)
		{
			NewSave.push_back("[WeaponSaver]");
			NewSave.push_back("MyWeapon=" + Mod_Data::Player_Weaps[i].MyWeapon);
			NewSave.push_back("MyAmmo=" + std::to_string(Mod_Data::Player_Weaps[i].Ammo));
			NewSave.push_back("TintSet=" + std::to_string(Mod_Data::Player_Weaps[i].TintSet));
			NewSave.push_back("WeapTint=" + std::to_string(Mod_Data::Player_Weaps[i].WeapTint));
			NewSave.push_back("[Addons]");

			for (int j = 0; j < Mod_Data::Player_Weaps[i].MyAddons.size(); j++)
				NewSave.push_back("MyAddon=" + Mod_Data::Player_Weaps[i].MyAddons[j]);
		}
		Write_ini(SaveWeapsFile, NewSave);
	}
	std::vector<Mod_Class::WeaponSaver> LoadSavedWeapons()
	{
		bool Addons = false;
		std::vector<Mod_Class::WeaponSaver> MyWeaopns = {};
		std::vector<std::string> MyColect = Read_ini(SaveWeapsFile);

		std::string weapon = "";
		int ammo = 0;
		int tintSet = 0;
		int weapTint = 0;
		std::vector<std::string> MyAddons = {};

		for (int i = 0; i < MyColect.size(); i++)
		{
			std::string line = MyColect[i];
			if (Addons)
			{
				if (Contains_string("[WeaponSaver]", line))
				{
					Addons = false;
					MyWeaopns.push_back(Mod_Class::WeaponSaver(weapon, MyAddons, ammo, tintSet, weapTint));
					MyAddons.clear();
				}
				else
					MyAddons.push_back(Remove_char61(line));
			}
			else if (Contains_string("MyWeapon=", line))
				weapon = Remove_char61(line);
			else if (Contains_string("MyAmmo", line))
				ammo = Convert_to_int(line);
			else if (Contains_string("TintSet", line))
				ammo = Convert_to_int(line);
			else if (Contains_string("WeapTint", line))
				ammo = Convert_to_int(line);
			else if (Contains_string("[Addons]", line))
				Addons = true;
		}

		return MyWeaopns;
	}
	std::vector<Mod_Class::WeaponSaver> BuildWeaponList()
	{
		LoggerLight("BuildWeaponList");
		std::string weapon = "";
		std::vector<Mod_Class::WeaponSaver> output = {};
		int ammo = 0;
		int tint = 0;
		int tintSet = 0;
		for (int i = 0; i < (int)Mod_Data::Weapons_List.size(); i++)
		{
			weapon = Mod_Data::Weapons_List[i];
			if (WEAPON::HAS_PED_GOT_WEAPON(PLAYER::PLAYER_PED_ID(), Mod_Systems::MyHashKey(weapon), false))
			{
				tintSet = WEAPON::GET_WEAPON_TINT_COUNT(Mod_Systems::MyHashKey(weapon));
				tint = WEAPON::GET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), Mod_Systems::MyHashKey(weapon));
				ammo = WEAPON::GET_AMMO_IN_PED_WEAPON(PLAYER::PLAYER_PED_ID(), Mod_Systems::MyHashKey(weapon));

				std::vector<std::string> myAddons = {};
				for (int j = 0; j < (int)Mod_Data::WeapAdd_List.size(); j++)
				{
					if (WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(PLAYER::PLAYER_PED_ID(), Mod_Systems::MyHashKey(weapon), Mod_Systems::MyHashKey(Mod_Data::WeapAdd_List[j])))
						myAddons.push_back(Mod_Data::WeapAdd_List[j]);
				}
				output.push_back(Mod_Class::WeaponSaver(weapon, myAddons, ammo, tintSet, tint));
			}
		}
		return output;
	}
	
	void LoadLang()
	{
		LoggerLight("LoadLang");

		std::vector<std::string> LangEng = Mod_Data::RSLangMenu;

		int MyLan = Mod_Data::Mod_Settings.Lang_Set;
		
		if (MyLan == -1 || MyLan >= TranlsteDir.size())
			MyLan = UNK::_GET_UI_LANGUAGE_ID(); // 2BDD44CC428A7EAE

		Mod_Data::RSLangMenu = Read_ini(TranlsteDir[MyLan]);

		if ((int)Mod_Data::RSLangMenu.size() < 276)
			Mod_Data::RSLangMenu = LangEng;

		Mod_Data::Mod_Settings.Lang_Set = MyLan;
	}

	const std::vector<std::string> ControlSym = {
	" ~INPUT_NEXT_CAMERA~ ",//V~ ");//BACK
	" ~INPUT_LOOK_LR~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_LOOK_UD~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_LOOK_UP_ONLY~ ",//(NONE);~ ");//RIGHT STICK
	" ~INPUT_LOOK_DOWN_ONLY~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_LOOK_LEFT_ONLY~ ",//(NONE);~ ");//RIGHT STICK
	" ~INPUT_LOOK_RIGHT_ONLY~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_CINEMATIC_SLOWMO~ ",//(NONE);~ ");//R3
	" ~INPUT_SCRIPTED_FLY_UD~ ",//S~ ");//LEFT STICK
	" ~INPUT_SCRIPTED_FLY_LR~ ",//D~ ");//LEFT STICK
	" ~INPUT_SCRIPTED_FLY_ZUP~ ",//PAGEUP~ ");//LT
	" ~INPUT_SCRIPTED_FLY_ZDOWN~ ",//PAGEDOWN~ ");//RT
	" ~INPUT_WEAPON_WHEEL_UD~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_WEAPON_WHEEL_LR~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_WEAPON_WHEEL_NEXT~ ",//SCROLLWHEEL DOWN~ ");//DPAD RIGHT
	" ~INPUT_WEAPON_WHEEL_PREV~ ",//SCROLLWHEEL UP~ ");//DPAD LEFT
	" ~INPUT_SELECT_NEXT_WEAPON~ ",//SCROLLWHEEL DOWN~ ");//(NONE);
	" ~INPUT_SELECT_PREV_WEAPON~ ",//SCROLLWHEEL UP~ ");//(NONE);
	" ~INPUT_SKIP_CUTSCENE~ ",//ENTER / LEFT MOUSE BUTTON / SPACEBAR~ ");//A
	" ~INPUT_CHARACTER_WHEEL~ ",//LEFT ALT~ ");//DPAD DOWN
	" ~INPUT_MULTIPLAYER_INFO~ ",//Z~ ");//DPAD DOWN
	" ~INPUT_SPRINT~ ",//LEFT SHIFT~ ");//A
	" ~INPUT_JUMP~ ",//SPACEBAR~ ");//X
	" ~INPUT_ENTER~ ",//F~ ");//Y
	" ~INPUT_ATTACK~ ",//LEFT MOUSE BUTTON~ ");//RT
	" ~INPUT_AIM~ ",//RIGHT MOUSE BUTTON~ ");//LT
	" ~INPUT_LOOK_BEHIND~ ",//C~ ");//R3
	" ~INPUT_PHONE~ ",//ARROW UP / SCROLLWHEEL BUTTON (PRESS);~ ");//DPAD UP
	" ~INPUT_SPECIAL_ABILITY~ ",//(NONE);~ ");//L3
	" ~INPUT_SPECIAL_ABILITY_SECONDARY~ ",//B~ ");//R3
	" ~INPUT_MOVE_LR~ ",//D~ ");//LEFT STICK
	" ~INPUT_MOVE_UD~ ",//S~ ");//LEFT STICK
	" ~INPUT_MOVE_UP_ONLY~ ",//W~ ");//LEFT STICK
	" ~INPUT_MOVE_DOWN_ONLY~ ",//S~ ");//LEFT STICK
	" ~INPUT_MOVE_LEFT_ONLY~ ",//A~ ");//LEFT STICK
	" ~INPUT_MOVE_RIGHT_ONLY~ ",//D~ ");//LEFT STICK
	" ~INPUT_DUCK~ ",//LEFT CTRL~ ");//L3
	" ~INPUT_SELECT_WEAPON~ ",//TAB~ ");//LB
	" ~INPUT_PICKUP~ ",//E~ ");//LB
	" ~INPUT_SNIPER_ZOOM~ ",//[~ ");//LEFT STICK
	" ~INPUT_SNIPER_ZOOM_IN_ONLY~ ",//]~ ");//LEFT STICK
	" ~INPUT_SNIPER_ZOOM_OUT_ONLY~ ",//[~ ");//LEFT STICK
	" ~INPUT_SNIPER_ZOOM_IN_SECONDARY~ ",//]~ ");//DPAD UP
	" ~INPUT_SNIPER_ZOOM_OUT_SECONDARY~ ",//[~ ");//DPAD DOWN
	" ~INPUT_COVER~ ",//Q~ ");//RB
	" ~INPUT_RELOAD~ ",//R~ ");//B
	" ~INPUT_TALK~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_DETONATE~ ",//G~ ");//DPAD LEFT
	" ~INPUT_HUD_SPECIAL~ ",//Z~ ");//DPAD DOWN
	" ~INPUT_ARREST~ ",//F~ ");//Y
	" ~INPUT_ACCURATE_AIM~ ",//SCROLLWHEEL DOWN~ ");//R3
	" ~INPUT_CONTEXT~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_CONTEXT_SECONDARY~ ",//Q~ ");//DPAD LEFT
	" ~INPUT_WEAPON_SPECIAL~ ",//(NONE);~ ");//Y
	" ~INPUT_WEAPON_SPECIAL_TWO~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_DIVE~ ",//SPACEBAR~ ");//RB
	" ~INPUT_DROP_WEAPON~ ",//F9~ ");//Y
	" ~INPUT_DROP_AMMO~ ",//F10~ ");//B
	" ~INPUT_THROW_GRENADE~ ",//G~ ");//DPAD LEFT
	" ~INPUT_VEH_MOVE_LR~ ",//D~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_UD~ ",//LEFT CTRL~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_UP_ONLY~ ",//LEFT SHIFT~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_DOWN_ONLY~ ",//LEFT CTRL~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_LEFT_ONLY~ ",//A~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_RIGHT_ONLY~ ",//D~ ");//LEFT STICK
	" ~INPUT_VEH_SPECIAL~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_VEH_GUN_LR~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_GUN_UD~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_VEH_AIM~ ",//RIGHT MOUSE BUTTON~ ");//LB
	" ~INPUT_VEH_ATTACK~ ",//LEFT MOUSE BUTTON~ ");//RB
	" ~INPUT_VEH_ATTACK2~ ",//RIGHT MOUSE BUTTON~ ");//A
	" ~INPUT_VEH_ACCELERATE~ ",//W~ ");//RT
	" ~INPUT_VEH_BRAKE~ ",//S~ ");//LT
	" ~INPUT_VEH_DUCK~ ",//X~ ");//A
	" ~INPUT_VEH_HEADLIGHT~ ",//H~ ");//DPAD RIGHT
	" ~INPUT_VEH_EXIT~ ",//F~ ");//Y
	" ~INPUT_VEH_HANDBRAKE~ ",//SPACEBAR~ ");//RB
	" ~INPUT_VEH_HOTWIRE_LEFT~ ",//W~ ");//LT
	" ~INPUT_VEH_HOTWIRE_RIGHT~ ",//S~ ");//RT
	" ~INPUT_VEH_LOOK_BEHIND~ ",//C~ ");//R3
	" ~INPUT_VEH_CIN_CAM~ ",//R~ ");//B
	" ~INPUT_VEH_NEXT_RADIO~ ",//.~ ");//(NONE);
	" ~INPUT_VEH_PREV_RADIO~ ",//,~ ");//(NONE);
	" ~INPUT_VEH_NEXT_RADIO_TRACK~ ",//=~ ");//(NONE);
	" ~INPUT_VEH_PREV_RADIO_TRACK~ ",//-~ ");//(NONE);
	" ~INPUT_VEH_RADIO_WHEEL~ ",//Q~ ");//DPAD LEFT
	" ~INPUT_VEH_HORN~ ",//E~ ");//L3
	" ~INPUT_VEH_FLY_THROTTLE_UP~ ",//W~ ");//RT
	" ~INPUT_VEH_FLY_THROTTLE_DOWN~ ",//S~ ");//LT
	" ~INPUT_VEH_FLY_YAW_LEFT~ ",//A~ ");//LB
	" ~INPUT_VEH_FLY_YAW_RIGHT~ ",//D~ ");//RB
	" ~INPUT_VEH_PASSENGER_AIM~ ",//RIGHT MOUSE BUTTON~ ");//LT
	" ~INPUT_VEH_PASSENGER_ATTACK~ ",//LEFT MOUSE BUTTON~ ");//RT
	" ~INPUT_VEH_SPECIAL_ABILITY_FRANKLIN~ ",//(NONE);~ ");//R3
	" ~INPUT_VEH_STUNT_UD~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_VEH_CINEMATIC_UD~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_VEH_CINEMATIC_UP_ONLY~ ",//NUMPAD- / SCROLLWHEEL UP~ ");//(NONE);
	" ~INPUT_VEH_CINEMATIC_DOWN_ONLY~ ",//NUMPAD+ / SCROLLWHEEL DOWN~ ");//(NONE);
	" ~INPUT_VEH_CINEMATIC_LR~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_SELECT_NEXT_WEAPON~ ",//SCROLLWHEEL UP~ ");//X
	" ~INPUT_VEH_SELECT_PREV_WEAPON~ ",//[~ ");//(NONE);
	" ~INPUT_VEH_ROOF~ ",//H~ ");//DPAD RIGHT
	" ~INPUT_VEH_JUMP~ ",//SPACEBAR~ ");//RB
	" ~INPUT_VEH_GRAPPLING_HOOK~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_VEH_SHUFFLE~ ",//H~ ");//DPAD RIGHT
	" ~INPUT_VEH_DROP_PROJECTILE~ ",//X~ ");//A
	" ~INPUT_VEH_MOUSE_CONTROL_OVERRIDE~ ",//LEFT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_VEH_FLY_ROLL_LR~ ",//NUMPAD 6~ ");//LEFT STICK
	" ~INPUT_VEH_FLY_ROLL_LEFT_ONLY~ ",//NUMPAD 4~ ");//LEFT STICK
	" ~INPUT_VEH_FLY_ROLL_RIGHT_ONLY~ ",//NUMPAD 6~ ");//LEFT STICK
	" ~INPUT_VEH_FLY_PITCH_UD~ ",//NUMPAD 5~ ");//LEFT STICK
	" ~INPUT_VEH_FLY_PITCH_UP_ONLY~ ",//NUMPAD 8~ ");//LEFT STICK
	" ~INPUT_VEH_FLY_PITCH_DOWN_ONLY~ ",//NUMPAD 5~ ");//LEFT STICK
	" ~INPUT_VEH_FLY_UNDERCARRIAGE~ ",//G~ ");//L3
	" ~INPUT_VEH_FLY_ATTACK~ ",//RIGHT MOUSE BUTTON~ ");//A
	" ~INPUT_VEH_FLY_SELECT_NEXT_WEAPON~ ",//SCROLLWHEEL UP~ ");//DPAD LEFT
	" ~INPUT_VEH_FLY_SELECT_PREV_WEAPON~ ",//[~ ");//(NONE);
	" ~INPUT_VEH_FLY_SELECT_TARGET_LEFT~ ",//NUMPAD 7~ ");//LB
	" ~INPUT_VEH_FLY_SELECT_TARGET_RIGHT~ ",//NUMPAD 9~ ");//RB
	" ~INPUT_VEH_FLY_VERTICAL_FLIGHT_MODE~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_VEH_FLY_DUCK~ ",//X~ ");//A
	" ~INPUT_VEH_FLY_ATTACK_CAMERA~ ",//INSERT~ ");//R3
	" ~INPUT_VEH_FLY_MOUSE_CONTROL_OVERRIDE~ ",//LEFT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_VEH_SUB_TURN_LR~ ",//NUMPAD 6~ ");//LEFT STICK
	" ~INPUT_VEH_SUB_TURN_LEFT_ONLY~ ",//NUMPAD 4~ ");//LEFT STICK
	" ~INPUT_VEH_SUB_TURN_RIGHT_ONLY~ ",//NUMPAD 6~ ");//LEFT STICK
	" ~INPUT_VEH_SUB_PITCH_UD~ ",//NUMPAD 5~ ");//LEFT STICK
	" ~INPUT_VEH_SUB_PITCH_UP_ONLY~ ",//NUMPAD 8~ ");//LEFT STICK
	" ~INPUT_VEH_SUB_PITCH_DOWN_ONLY~ ",//NUMPAD 5~ ");//LEFT STICK
	" ~INPUT_VEH_SUB_THROTTLE_UP~ ",//W~ ");//RT
	" ~INPUT_VEH_SUB_THROTTLE_DOWN~ ",//S~ ");//LT
	" ~INPUT_VEH_SUB_ASCEND~ ",//LEFT SHIFT~ ");//X
	" ~INPUT_VEH_SUB_DESCEND~ ",//LEFT CTRL~ ");//A
	" ~INPUT_VEH_SUB_TURN_HARD_LEFT~ ",//A~ ");//LB
	" ~INPUT_VEH_SUB_TURN_HARD_RIGHT~ ",//D~ ");//RB
	" ~INPUT_VEH_SUB_MOUSE_CONTROL_OVERRIDE~ ",//LEFT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_VEH_PUSHBIKE_PEDAL~ ",//W~ ");//A
	" ~INPUT_VEH_PUSHBIKE_SPRINT~ ",//CAPSLOCK~ ");//A
	" ~INPUT_VEH_PUSHBIKE_FRONT_BRAKE~ ",//Q~ ");//LT
	" ~INPUT_VEH_PUSHBIKE_REAR_BRAKE~ ",//S~ ");//RT
	" ~INPUT_MELEE_ATTACK_LIGHT~ ",//R~ ");//B
	" ~INPUT_MELEE_ATTACK_HEAVY~ ",//Q~ ");//A
	" ~INPUT_MELEE_ATTACK_ALTERNATE~ ",//LEFT MOUSE BUTTON~ ");//RT
	" ~INPUT_MELEE_BLOCK~ ",//SPACEBAR~ ");//X
	" ~INPUT_PARACHUTE_DEPLOY~ ",//F / LEFT MOUSE BUTTON~ ");//Y
	" ~INPUT_PARACHUTE_DETACH~ ",//F~ ");//Y
	" ~INPUT_PARACHUTE_TURN_LR~ ",//D~ ");//LEFT STICK
	" ~INPUT_PARACHUTE_TURN_LEFT_ONLY~ ",//A~ ");//LEFT STICK
	" ~INPUT_PARACHUTE_TURN_RIGHT_ONLY~ ",//D~ ");//LEFT STICK
	" ~INPUT_PARACHUTE_PITCH_UD~ ",//S~ ");//LEFT STICK
	" ~INPUT_PARACHUTE_PITCH_UP_ONLY~ ",//W~ ");//LEFT STICK
	" ~INPUT_PARACHUTE_PITCH_DOWN_ONLY~ ",//S~ ");//LEFT STICK
	" ~INPUT_PARACHUTE_BRAKE_LEFT~ ",//Q~ ");//LB
	" ~INPUT_PARACHUTE_BRAKE_RIGHT~ ",//E~ ");//RB
	" ~INPUT_PARACHUTE_SMOKE~ ",//X~ ");//A
	" ~INPUT_PARACHUTE_PRECISION_LANDING~ ",//LEFT SHIFT~ ");//(NONE);
	" ~INPUT_MAP~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_UNARMED~ ",//1~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_MELEE~ ",//2~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_HANDGUN~ ",//6~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_SHOTGUN~ ",//3~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_SMG~ ",//7~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_AUTO_RIFLE~ ",//8~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_SNIPER~ ",//9~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_HEAVY~ ",//4~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_SPECIAL~ ",//5~ ");//(NONE);
	" ~INPUT_SELECT_CHARACTER_MICHAEL~ ",//F5~ ");//(NONE);
	" ~INPUT_SELECT_CHARACTER_FRANKLIN~ ",//F6~ ");//(NONE);
	" ~INPUT_SELECT_CHARACTER_TREVOR~ ",//F7~ ");//(NONE);
	" ~INPUT_SELECT_CHARACTER_MULTIPLAYER~ ",//F8 (CONSOLE);~ ");//(NONE);
	" ~INPUT_SAVE_REPLAY_CLIP~ ",//F3~ ");//B
	" ~INPUT_SPECIAL_ABILITY_PC~ ",//CAPSLOCK~ ");//(NONE);
	" ~INPUT_CELLPHONE_UP~ ",//ARROW UP~ ");//DPAD UP
	" ~INPUT_CELLPHONE_DOWN~ ",//ARROW DOWN~ ");//DPAD DOWN
	" ~INPUT_CELLPHONE_LEFT~ ",//ARROW LEFT~ ");//DPAD LEFT
	" ~INPUT_CELLPHONE_RIGHT~ ",//ARROW RIGHT~ ");//DPAD RIGHT
	" ~INPUT_CELLPHONE_SELECT~ ",//ENTER / LEFT MOUSE BUTTON~ ");//A
	" ~INPUT_CELLPHONE_CANCEL~ ",//BACKSPACE / ESC / RIGHT MOUSE BUTTON~ ");//B
	" ~INPUT_CELLPHONE_OPTION~ ",//DELETE~ ");//Y
	" ~INPUT_CELLPHONE_EXTRA_OPTION~ ",//SPACEBAR~ ");//X
	" ~INPUT_CELLPHONE_SCROLL_FORWARD~ ",//SCROLLWHEEL DOWN~ ");//(NONE);
	" ~INPUT_CELLPHONE_SCROLL_BACKWARD~ ",//SCROLLWHEEL UP~ ");//(NONE);
	" ~INPUT_CELLPHONE_CAMERA_FOCUS_LOCK~ ",//L~ ");//RT
	" ~INPUT_CELLPHONE_CAMERA_GRID~ ",//G~ ");//RB
	" ~INPUT_CELLPHONE_CAMERA_SELFIE~ ",//E~ ");//R3
	" ~INPUT_CELLPHONE_CAMERA_DOF~ ",//F~ ");//LB
	" ~INPUT_CELLPHONE_CAMERA_EXPRESSION~ ",//X~ ");//L3
	" ~INPUT_FRONTEND_DOWN~ ",//ARROW DOWN~ ");//DPAD DOWN
	" ~INPUT_FRONTEND_UP~ ",//ARROW UP~ ");//DPAD UP
	" ~INPUT_FRONTEND_LEFT~ ",//ARROW LEFT~ ");//DPAD LEFT
	" ~INPUT_FRONTEND_RIGHT~ ",//ARROW RIGHT~ ");//DPAD RIGHT
	" ~INPUT_FRONTEND_RDOWN~ ",//ENTER~ ");//A
	" ~INPUT_FRONTEND_RUP~ ",//TAB~ ");//Y
	" ~INPUT_FRONTEND_RLEFT~ ",//(NONE);~ ");//X
	" ~INPUT_FRONTEND_RRIGHT~ ",//BACKSPACE~ ");//B
	" ~INPUT_FRONTEND_AXIS_X~ ",//D~ ");//LEFT STICK
	" ~INPUT_FRONTEND_AXIS_Y~ ",//S~ ");//LEFT STICK
	" ~INPUT_FRONTEND_RIGHT_AXIS_X~ ",//]~ ");//RIGHT STICK
	" ~INPUT_FRONTEND_RIGHT_AXIS_Y~ ",//SCROLLWHEEL DOWN~ ");//RIGHT STICK
	" ~INPUT_FRONTEND_PAUSE~ ",//P~ ");//START
	" ~INPUT_FRONTEND_PAUSE_ALTERNATE~ ",//ESC~ ");//(NONE);
	" ~INPUT_FRONTEND_ACCEPT~ ",//ENTER / NUMPAD ENTER~ ");//A
	" ~INPUT_FRONTEND_CANCEL~ ",//BACKSPACE / ESC~ ");//B
	" ~INPUT_FRONTEND_X~ ",//SPACEBAR~ ");//X
	" ~INPUT_FRONTEND_Y~ ",//TAB~ ");//Y
	" ~INPUT_FRONTEND_LB~ ",//Q~ ");//LB
	" ~INPUT_FRONTEND_RB~ ",//E~ ");//RB
	" ~INPUT_FRONTEND_LT~ ",//PAGE DOWN~ ");//LT
	" ~INPUT_FRONTEND_RT~ ",//PAGE UP~ ");//RT
	" ~INPUT_FRONTEND_LS~ ",//LEFT SHIFT~ ");//L3
	" ~INPUT_FRONTEND_RS~ ",//LEFT CONTROL~ ");//R3
	" ~INPUT_FRONTEND_LEADERBOARD~ ",//TAB~ ");//RB
	" ~INPUT_FRONTEND_SOCIAL_CLUB~ ",//HOME~ ");//BACK
	" ~INPUT_FRONTEND_SOCIAL_CLUB_SECONDARY~ ",//HOME~ ");//RB
	" ~INPUT_FRONTEND_DELETE~ ",//DELETE~ ");//X
	" ~INPUT_FRONTEND_ENDSCREEN_ACCEPT~ ",//ENTER~ ");//A
	" ~INPUT_FRONTEND_ENDSCREEN_EXPAND~ ",//SPACEBAR~ ");//X
	" ~INPUT_FRONTEND_SELECT~ ",//CAPSLOCK~ ");//BACK
	" ~INPUT_SCRIPT_LEFT_AXIS_X~ ",//D~ ");//LEFT STICK
	" ~INPUT_SCRIPT_LEFT_AXIS_Y~ ",//S~ ");//LEFT STICK
	" ~INPUT_SCRIPT_RIGHT_AXIS_X~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_SCRIPT_RIGHT_AXIS_Y~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_SCRIPT_RUP~ ",//RIGHT MOUSE BUTTON~ ");//Y
	" ~INPUT_SCRIPT_RDOWN~ ",//LEFT MOUSE BUTTON~ ");//A
	" ~INPUT_SCRIPT_RLEFT~ ",//LEFT CTRL~ ");//X
	" ~INPUT_SCRIPT_RRIGHT~ ",//RIGHT MOUSE BUTTON~ ");//B
	" ~INPUT_SCRIPT_LB~ ",//(NONE);~ ");//LB
	" ~INPUT_SCRIPT_RB~ ",//(NONE);~ ");//RB
	" ~INPUT_SCRIPT_LT~ ",//(NONE);~ ");//LT
	" ~INPUT_SCRIPT_RT~ ",//LEFT MOUSE BUTTON~ ");//RT
	" ~INPUT_SCRIPT_LS~ ",//(NONE);~ ");//L3
	" ~INPUT_SCRIPT_RS~ ",//(NONE);~ ");//R3
	" ~INPUT_SCRIPT_PAD_UP~ ",//W~ ");//DPAD UP
	" ~INPUT_SCRIPT_PAD_DOWN~ ",//S~ ");//DPAD DOWN
	" ~INPUT_SCRIPT_PAD_LEFT~ ",//A~ ");//DPAD LEFT
	" ~INPUT_SCRIPT_PAD_RIGHT~ ",//D~ ");//DPAD RIGHT
	" ~INPUT_SCRIPT_SELECT~ ",//V~ ");//BACK
	" ~INPUT_CURSOR_ACCEPT~ ",//LEFT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_CURSOR_CANCEL~ ",//RIGHT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_CURSOR_X~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_CURSOR_Y~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_CURSOR_SCROLL_UP~ ",//SCROLLWHEEL UP~ ");//(NONE);
	" ~INPUT_CURSOR_SCROLL_DOWN~ ",//SCROLLWHEEL DOWN~ ");//(NONE);
	" ~INPUT_ENTER_CHEAT_CODE~ ",//~ / `~ ");//(NONE);
	" ~INPUT_INTERACTION_MENU~ ",//M~ ");//BACK
	" ~INPUT_MP_TEXT_CHAT_ALL~ ",//T~ ");//(NONE);
	" ~INPUT_MP_TEXT_CHAT_TEAM~ ",//Y~ ");//(NONE);
	" ~INPUT_MP_TEXT_CHAT_FRIENDS~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_MP_TEXT_CHAT_CREW~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_PUSH_TO_TALK~ ",//N~ ");//(NONE);
	" ~INPUT_CREATOR_LS~ ",//R~ ");//L3
	" ~INPUT_CREATOR_RS~ ",//F~ ");//R3
	" ~INPUT_CREATOR_LT~ ",//X~ ");//LT
	" ~INPUT_CREATOR_RT~ ",//C~ ");//RT
	" ~INPUT_CREATOR_MENU_TOGGLE~ ",//LEFT SHIFT~ ");//(NONE);
	" ~INPUT_CREATOR_ACCEPT~ ",//SPACEBAR~ ");//A
	" ~INPUT_CREATOR_DELETE~ ",//DELETE~ ");//X
	" ~INPUT_ATTACK2~ ",//LEFT MOUSE BUTTON~ ");//RT
	" ~INPUT_RAPPEL_JUMP~ ",//(NONE);~ ");//A
	" ~INPUT_RAPPEL_LONG_JUMP~ ",//(NONE);~ ");//X
	" ~INPUT_RAPPEL_SMASH_WINDOW~ ",//(NONE);~ ");//RT
	" ~INPUT_PREV_WEAPON~ ",//SCROLLWHEEL UP~ ");//DPAD LEFT
	" ~INPUT_NEXT_WEAPON~ ",//SCROLLWHEEL DOWN~ ");//DPAD RIGHT
	" ~INPUT_MELEE_ATTACK1~ ",//R~ ");//B
	" ~INPUT_MELEE_ATTACK2~ ",//Q~ ");//A
	" ~INPUT_WHISTLE~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_MOVE_LEFT~ ",//D~ ");//LEFT STICK
	" ~INPUT_MOVE_RIGHT~ ",//D~ ");//LEFT STICK
	" ~INPUT_MOVE_UP~ ",//S~ ");//LEFT STICK
	" ~INPUT_MOVE_DOWN~ ",//S~ ");//LEFT STICK
	" ~INPUT_LOOK_LEFT~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_LOOK_RIGHT~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_LOOK_UP~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_LOOK_DOWN~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_SNIPER_ZOOM_IN~ ",//[~ ");//RIGHT STICK
	" ~INPUT_SNIPER_ZOOM_OUT~ ",//[~ ");//RIGHT STICK
	" ~INPUT_SNIPER_ZOOM_IN_ALTERNATE~ ",//[~ ");//LEFT STICK
	" ~INPUT_SNIPER_ZOOM_OUT_ALTERNATE~ ",//[~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_LEFT~ ",//D~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_RIGHT~ ",//D~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_UP~ ",//LEFT CTRL~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_DOWN~ ",//LEFT CTRL~ ");//LEFT STICK
	" ~INPUT_VEH_GUN_LEFT~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_GUN_RIGHT~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_GUN_UP~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_GUN_DOWN~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_LOOK_LEFT~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_LOOK_RIGHT~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_REPLAY_START_STOP_RECORDING~ ",//F1~ ");//A
	" ~INPUT_REPLAY_START_STOP_RECORDING_SECONDARY~ ",//F2~ ");//X
	" ~INPUT_SCALED_LOOK_LR~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_SCALED_LOOK_UD~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_SCALED_LOOK_UP_ONLY~ ",//(NONE);~ ");//RIGHT STICK
	" ~INPUT_SCALED_LOOK_DOWN_ONLY~ ",//(NONE);~ ");//RIGHT STICK
	" ~INPUT_SCALED_LOOK_LEFT_ONLY~ ",//(NONE);~ ");//RIGHT STICK
	" ~INPUT_SCALED_LOOK_RIGHT_ONLY~ ",//(NONE);~ ");//RIGHT STICK
	" ~INPUT_REPLAY_MARKER_DELETE~ ",//DELETE~ ");//X
	" ~INPUT_REPLAY_CLIP_DELETE~ ",//DELETE~ ");//Y
	" ~INPUT_REPLAY_PAUSE~ ",//SPACEBAR~ ");//A
	" ~INPUT_REPLAY_REWIND~ ",//ARROW DOWN~ ");//LB
	" ~INPUT_REPLAY_FFWD~ ",//ARROW UP~ ");//RB
	" ~INPUT_REPLAY_NEWMARKER~ ",//M~ ");//A
	" ~INPUT_REPLAY_RECORD~ ",//S~ ");//(NONE);
	" ~INPUT_REPLAY_SCREENSHOT~ ",//U~ ");//DPAD UP
	" ~INPUT_REPLAY_HIDEHUD~ ",//H~ ");//R3
	" ~INPUT_REPLAY_STARTPOINT~ ",//B~ ");//(NONE);
	" ~INPUT_REPLAY_ENDPOINT~ ",//N~ ");//(NONE);
	" ~INPUT_REPLAY_ADVANCE~ ",//ARROW RIGHT~ ");//DPAD RIGHT
	" ~INPUT_REPLAY_BACK~ ",//ARROW LEFT~ ");//DPAD LEFT
	" ~INPUT_REPLAY_TOOLS~ ",//T~ ");//DPAD DOWN
	" ~INPUT_REPLAY_RESTART~ ",//R~ ");//BACK
	" ~INPUT_REPLAY_SHOWHOTKEY~ ",//K~ ");//DPAD DOWN
	" ~INPUT_REPLAY_CYCLEMARKERLEFT~ ",//[~ ");//DPAD LEFT
	" ~INPUT_REPLAY_CYCLEMARKERRIGHT~ ",//]~ ");//DPAD RIGHT
	" ~INPUT_REPLAY_FOVINCREASE~ ",//NUMPAD +~ ");//RB
	" ~INPUT_REPLAY_FOVDECREASE~ ",//NUMPAD -~ ");//LB
	" ~INPUT_REPLAY_CAMERAUP~ ",//PAGE UP~ ");//(NONE);
	" ~INPUT_REPLAY_CAMERADOWN~ ",//PAGE DOWN~ ");//(NONE);
	" ~INPUT_REPLAY_SAVE~ ",//F5~ ");//START
	" ~INPUT_REPLAY_TOGGLETIME~ ",//C~ ");//(NONE);
	" ~INPUT_REPLAY_TOGGLETIPS~ ",//V~ ");//(NONE);
	" ~INPUT_REPLAY_PREVIEW~ ",//SPACEBAR~ ");//(NONE);
	" ~INPUT_REPLAY_TOGGLE_TIMELINE~ ",//ESC~ ");//(NONE);
	" ~INPUT_REPLAY_TIMELINE_PICKUP_CLIP~ ",//X~ ");//(NONE);
	" ~INPUT_REPLAY_TIMELINE_DUPLICATE_CLIP~ ",//C~ ");//(NONE);
	" ~INPUT_REPLAY_TIMELINE_PLACE_CLIP~ ",//V~ ");//(NONE);
	" ~INPUT_REPLAY_CTRL~ ",//LEFT CTRL~ ");//(NONE);
	" ~INPUT_REPLAY_TIMELINE_SAVE~ ",//F5~ ");//(NONE);
	" ~INPUT_REPLAY_PREVIEW_AUDIO~ ",//SPACEBAR~ ");//RT
	" ~INPUT_VEH_DRIVE_LOOK~ ",//LEFT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_VEH_DRIVE_LOOK2~ ",//RIGHT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_VEH_FLY_ATTACK2~ ",//RIGHT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_RADIO_WHEEL_UD~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_RADIO_WHEEL_LR~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_SLOWMO_UD~ ",//SCROLLWHEEL DOWN~ ");//LEFT STICK
	" ~INPUT_VEH_SLOWMO_UP_ONLY~ ",//SCROLLWHEEL UP~ ");//LEFT STICK
	" ~INPUT_VEH_SLOWMO_DOWN_ONLY~ ",//SCROLLWHEEL DOWN~ ");//LEFT STICK
	" ~INPUT_VEH_HYDRAULICS_CONTROL_TOGGLE~ ",//X~ ");//A
	" ~INPUT_VEH_HYDRAULICS_CONTROL_LEFT~ ",//A~ ");//LEFT STICK
	" ~INPUT_VEH_HYDRAULICS_CONTROL_RIGHT~ ",//D~ ");//LEFT STICK
	" ~INPUT_VEH_HYDRAULICS_CONTROL_UP~ ",//LEFT SHIFT~ ");//LEFT STICK
	" ~INPUT_VEH_HYDRAULICS_CONTROL_DOWN~ ",//LEFT CTRL~ ");//LEFT STICK
	" ~INPUT_VEH_HYDRAULICS_CONTROL_UD~ ",//D~ ");//LEFT STICK
	" ~INPUT_VEH_HYDRAULICS_CONTROL_LR~ ",//LEFT CTRL~ ");//LEFT STICK
	" ~INPUT_SWITCH_VISOR~ ",//F11~ ");//DPAD RIGHT
	" ~INPUT_VEH_MELEE_HOLD~ ",//X~ ");//A
	" ~INPUT_VEH_MELEE_LEFT~ ",//LEFT MOUSE BUTTON~ ");//LB
	" ~INPUT_VEH_MELEE_RIGHT~ ",//RIGHT MOUSE BUTTON~ ");//RB
	" ~INPUT_MAP_POI~ ",//SCROLLWHEEL BUTTON (PRESS);~ ");//Y
	" ~INPUT_REPLAY_SNAPMATIC_PHOTO~ ",//TAB~ ");//X
	" ~INPUT_VEH_CAR_JUMP~ ",//E~ ");//L3
	" ~INPUT_VEH_ROCKET_BOOST~ ",//E~ ");//L3
	" ~INPUT_VEH_FLY_BOOST~ ",//LEFT SHIFT~ ");//L3
	" ~INPUT_VEH_PARACHUTE~ ",//SPACEBAR~ ");//A
	" ~INPUT_VEH_BIKE_WINGS~ ",//X~ ");//A
	" ~INPUT_VEH_FLY_BOMB_BAY~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_VEH_FLY_COUNTER~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_VEH_TRANSFORM~ ",//X~ ");//A
	" ~INPUT_QUAD_LOCO_REVERSE~ ",//~ ");//RB
	" ~INPUT_RESPAWN_FASTER~ ",//~ ");//
	" ~INPUT_HUDMARKER_SELECT~ "
	};

	void menu_beep()
	{
		AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
	}

	void get_button_state(bool* ent, bool* del, bool* up, bool* down, bool* left, bool* right, bool* shutDown)
	{
		if (ent) *ent = IsKeyDown(VK_RETURN);
		if (del) *del = IsKeyDown(VK_DELETE) || IsKeyDown(VK_BACK);
		if (up) *up = IsKeyDown(VK_UP);
		if (down) *down = IsKeyDown(VK_DOWN);
		if (left) *left = IsKeyDown(VK_LEFT);
		if (right) *right = IsKeyDown(VK_RIGHT);
		if (shutDown) *shutDown = IsKeyDown(VK_ESCAPE);
	}
	void Menu_Button_state(bool* returnBool, DWORD myButton)
	{
		if (returnBool) *returnBool = IsKeyDown(myButton);//VK_NUMPAD0
	}
	int FindKeyBinds(bool controler)
	{
		WAIT(4000);
		int iReturn = -1;
		int TestCase = 0;

		while (true)
		{
			if ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
				break;

			GVM::TopLeft(Mod_Data::RSLangMenu[189]);

			if (controler)
			{
				if (TestCase < (int)ControlSym.size())
				{
					if (GVM::ButtonDown(TestCase))
					{
						GVM::BottomLeft(Mod_Data::RSLangMenu[190]);
						iReturn = TestCase;
						break;
					}
					TestCase++;
				}
				else
					TestCase = 0;
			}
			else
			{
				if (TestCase < (int)Mod_Data::KeyFind.size())
				{
					if (IsKeyDown(Mod_Data::KeyFind[TestCase]))
					{
						GVM::BottomLeft(Mod_Data::RSLangMenu[190]);
						iReturn = TestCase;
						break;
					}
					TestCase++;
				}
				else
					TestCase = 0;
			}
			WAIT(1);
		}
		return iReturn;
	}

	int InGameTime()
	{
		return (int)GAMEPLAY::GET_GAME_TIMER();
	}
	bool IsIsSafe(int key)
	{
		bool IsSafe = false;
		if (!(bool)PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(PLAYER::PLAYER_PED_ID()))
		{
			while (GVM::ButtonDown(key))
			{
				WAIT(1000);
				if (GVM::ButtonDown(key))
					IsSafe = true;
				break;
			}
		}
		return IsSafe;
	}

	void LoadSavedPeds(Mod_Class::ClothBank& clothBank)
	{
		LoggerLight("LoadSavedPeds");

		Mod_Data::SavedPeds.clear();
		std::vector<Mod_Class::ClothBank> PzCont = {};
		Mod_Data::SavedPeds.push_back(clothBank);

		std::vector<std::string> Files = {};
		for (const auto& entry : std::filesystem::directory_iterator(DirSavedPed))
			Files.push_back(entry.path().string());

		for (int i = 0; i < Files.size(); i++)
		{
			std::string model = "", name = "", HairTag = "H_FMM_3_4", HairName = "";		
			Hash modelHash = 0;
			int hairColour = 7, hairStreaks = 7, eyeColour = 0, comp = 3, text = 4, overLib = -1, over = 1, cloth_Pick = 0, shapeFirstID = 5, shapeSecondID = 5, voice = 0, walkySt = 0, moods = 0;		
			float shapeMix = 0.0, skinMix = 0.92, thirdMix = 0.0;
			bool male = true, animal_Farm = false, freeMode = false, ClothBuild = false, ReDoOverlay = false;

			int intList = 0;
			int ClothNo = -1;
			int WeaponsNo = -1;

			int PlHealth = 200;
			float PlRunSp = 1.0f;
			float PlSwimSp = 1.0f;

			std::vector<Mod_Class::WeaponSaver> myWeapons = {};
			std::vector<Mod_Class::ClothX> myOutfits = {};
			std::vector<Mod_Class::FreeOverLay> myOverlay = {};
			std::vector<Mod_Class::Tattoo> myTattoo = {};
			std::vector<float> faceScale = {};

			std::vector<std::string> MyColect = Read_ini(Files[i]);

			for (int i = 0; i < MyColect.size(); i++)
			{
				std::string line = MyColect[i];

				if (ClothBuild)
				{
					if (Contains_string("Title", line))
					{
						ClothNo++;
						myOutfits.push_back(Mod_Class::ClothX(Remove_char61(line), {}, {}, {}, {}));
					}
					else if (Contains_string("DecalLib", line))
					{
						myOutfits[ClothNo].Badge.BaseName = Remove_char61(line);
					}
					else if (Contains_string("DecalName", line))
					{
						myOutfits[ClothNo].Badge.TatName = Remove_char61(line);
					}
					else if (Contains_string("[ClothA]", line))
					{
						intList = 1;
					}
					else if (Contains_string("[ClothB]", line))
					{
						intList = 2;
					}
					else if (Contains_string("[ExtraA]", line))
					{
						intList = 3;
					}
					else if (Contains_string("[ExtraB]", line))
					{
						intList = 4;
					}
					else if (intList == 1)
					{
						if (Contains_string("ClothA", line))
							myOutfits[ClothNo].ClothA.push_back(Convert_to_int(line));
					}
					else if (intList == 2)
					{
						if (Contains_string("ClothB", line))
							myOutfits[ClothNo].ClothB.push_back(Convert_to_int(line));
					}
					else if (intList == 3)
					{
						if (Contains_string("ExtraA", line))
							myOutfits[ClothNo].ExtraA.push_back(Convert_to_int(line));
					}
					else if (intList == 4)
					{
						if (Contains_string("ExtraB", line))
							myOutfits[ClothNo].ExtraB.push_back(Convert_to_int(line));
					}
				}
				else if (Contains_string("CharName", line))
					name = Remove_char61(line);
				else if (Contains_string("Model", line))
					model = Remove_char61(line);
				else if (Contains_string("XmodelHash", line))
					modelHash = (Hash)Convert_to_int(line);
				else if (Contains_string("FreeMode", line))
					freeMode = Convert_to_bool(line);
				else if (Contains_string("Male", line))
					male = Convert_to_bool(line);
				else if (Contains_string("Animal_Farm", line))
					animal_Farm = Convert_to_bool(line);
				else if (Contains_string("Voice", line))
					voice = Convert_to_int(line);
				else if (Contains_string("Cloth_Pick", line))
					cloth_Pick = Convert_to_int(line);
				else if (Contains_string("EyeColour", line))
					eyeColour = Convert_to_int(line);
				else if (Contains_string("WalkStyle", line))
					walkySt = Convert_to_int(line);
				else if (Contains_string("ShapeFirstID", line))
					shapeFirstID = Convert_to_int(line);
				else if (Contains_string("ShapeSecondID", line))
					shapeSecondID = Convert_to_int(line);
				else if (Contains_string("ShapeMix", line))
					shapeMix = Convert_to_float(line);
				else if (Contains_string("SkinMix", line))
					skinMix = Convert_to_float(line);
				else if (Contains_string("ThirdMix", line))
					thirdMix = Convert_to_float(line);
				else if (Contains_string("HairColour", line))
					hairColour = Convert_to_int(line);
				else if (Contains_string("HairStreaks", line))
					hairStreaks = Convert_to_int(line);
				else if (Contains_string("Comp", line))
					comp = Convert_to_int(line);
				else if (Contains_string("Text", line))
					text = Convert_to_int(line);
				else if (Contains_string("HairTag", line))
					HairTag = Remove_char61(line);
				else if (Contains_string("HairName", line))
					HairName = Remove_char61(line);
				else if (Contains_string("OverLib", line))
					overLib = Convert_to_int(line);
				else if (Contains_string("OverOb", line))
					over = Convert_to_int(line);
				else if (Contains_string("[FreeOverLay]", line))
					intList = 5;
				else if (Contains_string("[Tattoo]", line))
					intList = 6;
				else if (Contains_string("[FaceScale]", line))
					intList = 7;
				else if (Contains_string("[WeaponSaver]", line))
					intList = 8;
				else if (Contains_string("Mood", line))
					moods = Convert_to_int(line);
				else if (Contains_string("PlHealth", line))
					PlHealth = Convert_to_int(line);
				else if (Contains_string("PlRunSp", line))
					PlRunSp = Convert_to_float(line);
				else if (Contains_string("PlSwimSp", line))
					PlSwimSp = Convert_to_float(line);
				else if (Contains_string("[ClothX]", line))
					ClothBuild = true;
				else if (intList == 5)
				{
					if (Contains_string("Overlay", line))
					{
						if (MyColect[i + 1] == "ColourOver=")
						{
							float Optics = Convert_to_float(MyColect[i + 3]);
							myOverlay.push_back(Mod_Class::FreeOverLay(Convert_to_int(line), Convert_to_int(MyColect[i + 1]), Convert_to_int(MyColect[i + 2]), Optics));
						}
						else
						{
							ReDoOverlay = true;
							float Optics = Convert_to_float(MyColect[i + 2]);
							if (Optics > 1.0f || Optics < 0.0f)
								Optics = 0.65f;

							myOverlay.push_back(Mod_Class::FreeOverLay(-1, Convert_to_int(line), Convert_to_int(MyColect[i + 1]), Optics));
						}
					}
				}
				else if (intList == 6)
				{
					if (Contains_string("BaseName", line))
						myTattoo.push_back(Mod_Class::Tattoo(Remove_char61(line), Remove_char61(MyColect[i + 1]), Remove_char61(MyColect[i + 2])));
				}
				else if (intList == 7)
				{
					if (Contains_string("Face", line))
						faceScale.push_back(Convert_to_float(line));
				}
				else if (intList == 8)
				{
					if (Contains_string("MyWeapon=", line))
					{
						myWeapons.push_back(Mod_Class::WeaponSaver(Remove_char61(line), {}, 0, 0, 0));
						WeaponsNo++;
					}
					else if (Contains_string("MyAddon=", line))
					{
						myWeapons[WeaponsNo].MyAddons.push_back(Remove_char61(line));
					}
					else if (Contains_string("MyAmmo=", line))
					{
						myWeapons[WeaponsNo].Ammo = Convert_to_int(line);
					}
					else if (Contains_string("TintSet=", line))
					{
						myWeapons[WeaponsNo].TintSet = Convert_to_int(line);
					}
					else if (Contains_string("WeapTint=", line))
					{
						myWeapons[WeaponsNo].WeapTint = Convert_to_int(line);
					}
				}
			}

			bool bReBuild = false;

			if (ReDoOverlay)
			{
				for (int i = 0; i < (int)myOverlay.size(); i++)
				{
					if (i == 1)
						myOverlay[i].Colour = 1;
					else if (i == 2)
						myOverlay[i].Colour = 1;
					else if (i == 5)
						myOverlay[i].Colour = 2;
					else if (i == 8)
						myOverlay[i].Colour = 2;
					else if (i == 10)
						myOverlay[i].Colour = 1;
				}
			}

			Mod_Class::FaceBank myFaces = Mod_Class::FaceBank(shapeFirstID, shapeSecondID, shapeMix, skinMix, thirdMix);
			Mod_Class::HairSets myHair = Mod_Class::HairSets(comp, text, HairTag, HairName, overLib, over);

			Mod_Class::ClothBank ThisBank = Mod_Class::ClothBank(name, model, modelHash, freeMode, myFaces, male, animal_Farm, myHair, hairColour, hairStreaks, eyeColour, cloth_Pick, myWeapons, myOverlay, myTattoo, myOutfits, faceScale, voice, walkySt, moods, PlHealth, PlRunSp, PlSwimSp);
			 
			PzCont.push_back(ThisBank);
		}
		for (int i = 0; i < PzCont.size(); i++)
		{
			if (PzCont[i].Cloth_Pick < 0 || PzCont[i].Cloth_Pick >(int)PzCont[i].Cothing.size() - 1)
				PzCont[i].Cloth_Pick = 0;

			Mod_Data::SavedPeds.push_back(PzCont[i]);
		}
	}
	void SaveClothBank(const Mod_Class::ClothBank& clothBank)
	{
		LoggerLight("SaveClothBank == " + clothBank.CharName);

		if (clothBank.CharName != "")
		{
			std::vector<std::string> NewSave = {
				"[ClothBank]",
				"CharName=" + clothBank.CharName,
				"Model=" + clothBank.Model,
				"XmodelHash=" + std::to_string(clothBank.ModelHash),
				"FreeMode=" + Convert_to_string(clothBank.FreeMode),
				"Male=" + Convert_to_string(clothBank.Male),
				"Animal_Farm=" + Convert_to_string(clothBank.Animal_Farm),
				"Voice=" + std::to_string(clothBank.Voice),
				"Cloth_Pick=" + std::to_string(clothBank.Cloth_Pick),
				"EyeColour=" + std::to_string(clothBank.EyeColour),
				"WalkStyle=" + std::to_string(clothBank.Walkies),
				"Mood=" + std::to_string(clothBank.Moods),
				"PlHealth=" + std::to_string(clothBank.PlHealth),
				"PlRunSp=" + std::to_string(clothBank.PlRunSp),
				"PlSwimSp=" + std::to_string(clothBank.PlSwimSp),
				"[FaceBank]",
				"ShapeFirstID=" + std::to_string(clothBank.MyFaces.ShapeFirstID),
				"ShapeSecondID=" + std::to_string(clothBank.MyFaces.ShapeSecondID),
				"ShapeMix=" + std::to_string(clothBank.MyFaces.ShapeMix),
				"SkinMix=" + std::to_string(clothBank.MyFaces.SkinMix),
				"ThirdMix=" + std::to_string(clothBank.MyFaces.ThirdMix),
				"[Hair]",
				"HairColour=" + std::to_string(clothBank.HairColour),
				"HairStreaks=" + std::to_string(clothBank.HairStreaks),
				"Comp=" + std::to_string(clothBank.MyHair.Comp),
				"Text=" + std::to_string(clothBank.MyHair.Text),
				"HairTag=" + clothBank.MyHair.HandName,
				"HairName=" + clothBank.MyHair.Name,
				"OverLib=" + std::to_string(clothBank.MyHair.OverLib),
				"OverOb=" + std::to_string(clothBank.MyHair.Over),
				"[FreeOverLay]"
			};

			for (int i = 0; i < clothBank.MyOverlay.size(); i++)
			{
				NewSave.push_back("[OverLay]");
				NewSave.push_back("ColourOver=" + std::to_string(clothBank.MyOverlay[i].Colour));
				NewSave.push_back("Overlay=" + std::to_string(clothBank.MyOverlay[i].Overlay));
				NewSave.push_back("OverCol=" + std::to_string(clothBank.MyOverlay[i].OverCol));
				NewSave.push_back("OverOpc=" + std::to_string(clothBank.MyOverlay[i].OverOpc));
			}

			NewSave.push_back("[Tattoo]");

			for (int i = 0; i < clothBank.MyTattoo.size(); i++)
			{
				NewSave.push_back("[Tat]");
				NewSave.push_back("BaseName=" + clothBank.MyTattoo[i].BaseName);
				NewSave.push_back("TatsDesc=" + clothBank.MyTattoo[i].Name);
				NewSave.push_back("TatName=" + clothBank.MyTattoo[i].TatName);
			}

			NewSave.push_back("[FaceScale]");

			for (int i = 0; i < clothBank.FaceScale.size(); i++)
				NewSave.push_back("Face=" + std::to_string(clothBank.FaceScale[i]));

			NewSave.push_back("[WeaponSaver]");

			for (int i = 0; i < clothBank.MyWeapons.size(); i++)
			{
				NewSave.push_back("MyWeapon=" + clothBank.MyWeapons[i].MyWeapon);
				NewSave.push_back("MyAmmo=" + std::to_string(clothBank.MyWeapons[i].Ammo));
				for (int j = 0; j < clothBank.MyWeapons[i].MyAddons.size(); j++)
					NewSave.push_back("MyAddon=" + clothBank.MyWeapons[i].MyAddons[j]);
			}

			for (int i = 0; i < clothBank.Cothing.size(); i++)
			{
				NewSave.push_back("[ClothX]");
				NewSave.push_back("Title=" + clothBank.Cothing[i].Title);
				NewSave.push_back("DecalLib=" + clothBank.Cothing[i].Badge.BaseName);
				NewSave.push_back("DecalName=" + clothBank.Cothing[i].Badge.TatName);

				NewSave.push_back("[ClothA]");
				for (int j = 0; j < clothBank.Cothing[i].ClothA.size(); j++)
					NewSave.push_back("ClothA=" + std::to_string(clothBank.Cothing[i].ClothA[j]));

				NewSave.push_back("[ClothB]");
				for (int j = 0; j < clothBank.Cothing[i].ClothB.size(); j++)
					NewSave.push_back("ClothB=" + std::to_string(clothBank.Cothing[i].ClothB[j]));

				NewSave.push_back("[ExtraA]");
				for (int j = 0; j < clothBank.Cothing[i].ExtraA.size(); j++)
					NewSave.push_back("ExtraA=" + std::to_string(clothBank.Cothing[i].ExtraA[j]));

				NewSave.push_back("[ExtraB]");
				for (int j = 0; j < clothBank.Cothing[i].ExtraA.size(); j++)
					NewSave.push_back("ExtraB=" + std::to_string(clothBank.Cothing[i].ExtraB[j]));
			}

			Write_ini(DirSavedPed + "/" + clothBank.CharName + ".ini", NewSave);
		}
	}

	void AddMonies(int amount)
	{
		Hash H1 = ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID());
		int iPedCred = -1;
		if (H1 == -1686040670)
			iPedCred = MyHashKey("SP2_TOTAL_CASH");
		else if (H1 == -1692214353)
			iPedCred = MyHashKey("SP1_TOTAL_CASH");
		else if (H1 == 225514697)
			iPedCred = MyHashKey("SP0_TOTAL_CASH");
		int Credit = 0;
		STATS::STAT_GET_INT(iPedCred, &Credit, -1);
		Credit += amount;
		STATS::STAT_SET_INT(iPedCred, Credit, 1);
	}

	void FindAddCars()
	{
		LoggerLight("FindAddCars");

		const std::string sVehList01 = DirVehicles + "/Boats.ini";
		Mod_Data::PreVeh_01 = Read_ini(sVehList01);
		if (Mod_Data::PreVeh_01.size() == 0)
		{
			const std::vector<std::string> PreVehSet_01 = {
				"AVISA",//<!-- Kraken Avisa -->
				"DINGHY",//
				"DINGHY5",//<!-- Dinghy weaponized variant -->
				"JETMAX",//
				"LONGFIN",//<!-- Shitzu Longfin -->
				"MARQUIS",//
				"PREDATOR",//
				"PATROLBOAT",//<!-- Kurtz 31 Patrol Boat -->
				"SEASHARK",//
				"SPEEDER",//
				"SQUALO",//
				"SUNTRAP",//
				"TORO",//
				"TROPIC"//
			};

			Mod_Data::PreVeh_01 = PreVehSet_01;
			Write_ini(sVehList01, Mod_Data::PreVeh_01);
		}
		else
			Remove_blanks(&Mod_Data::PreVeh_01);
		const std::string sVehList02 = DirVehicles + "/HighValueVeh.ini";
		Mod_Data::PreVeh_02 = Read_ini(sVehList02);
		if (Mod_Data::PreVeh_02.size() == 0)
		{
			const std::vector<std::string> PreVehSet_02 = {
				"PFISTER811",  //<!-- 811 -->
				"ADDER",  //
				"AUTARCH",  //
				"BANSHEE2",  //<!-- Banshee 900R -->
				"BULLET",  //
				"CHAMPION",  //
				"CHEETAH",  //
				"CYCLONE",  //
				"DEVESTE",  //
				"EMERUS",  //
				"ENTITYXF",  //
				"ENTITY3",  //<!-- Entity MT -->
				"ENTITY2",  //<!-- Entity XXR -->
				"SHEAVA",  //<!-- ETR1 -->
				"FMJ",  //
				"FURIA",  //
				"GP1",  //
				"IGNUS",  //
				"INFERNUS",  //
				"ITALIGTB",  //
				"ITALIGTB2",  //<!-- Itali GTB Custom -->
				"KRIEGER",  //
				"LM87",  //
				"OSIRIS",  //
				"NERO",  //
				"NERO2",  //<!-- Nero Custom -->
				"PENETRATOR",  //
				"LE7B",  //<!-- RE-7B -->
				"REAPER",  //
				"VOLTIC2",  //<!-- Rocket Voltic -->
				"S80",  //
				"SC1",  //
				"SCRAMJET",  //
				"SULTANRS",  //
				"T20",  //
				"TAIPAN",  //
				"TEMPESTA",  //
				"TEZERACT",  //
				"THRAX",  //
				"TIGON",  //
				"TORERO2",  //<!-- Torero XO -->
				"TURISMOR",  //
				"TYRANT",  //
				"TYRUS",  //
				"VACCA",  //
				"VAGNER",  //
				"VIGILANTE",  //
				"VIRTUE",  //
				"VISIONE",  //
				"VOLTIC",  //
				"PROTOTIPO",  //<!-- X80 Proto -->
				"XA21",  //
				"ZENO",  //
				"ZENTORNO",  //
				"ZORRUSSO",  //
				"R300",  //<!-- 300R -->
				"DRAFTER",  //<!-- 8F Drafter -->
				"NINEF",  //
				"NINEF2",  //<!-- 9F Cabrio -->
				"TENF",  //
				"TENF2",  //<!-- 10F Widebody -->
				"ALPHA",  //
				"ZR380",  //<!-- Apocalypse ZR380 -->
				"BANSHEE",  //
				"BESTIAGTS",  //
				"BLISTA2",  //<!-- Blista Compact -->
				"BUFFALO",  //
				"BUFFALO2",  //<!-- Buffalo S -->
				"CALICO",  //<!-- Calico GTF -->
				"CARBONIZZARE",  //
				"COMET2",  //<!-- Comet -->
				"COMET3",  //<!-- Comet Retro Custom -->
				"COMET6",  //<!-- Comet S2 -->
				"COMET7",  //<!-- Comet S2 Cabrio -->
				"COMET4",  //<!-- Comet Safari -->
				"COMET5",  //<!-- Comet SR -->
				"COQUETTE",  //
				"COQUETTE4",  //<!-- Coquette D10 -->
				"CORSITA",  //
				"CYPHER",  //
				"TAMPA2",  //<!-- Drift Tampa -->
				"ELEGY",  //<!-- Elegy Retro Custom -->
				"ELEGY2",  //<!-- Elegy RH8 -->
				"EUROS",  //
				"FELTZER2",  //<!-- Feltzer -->
				"FLASHGT",  //
				"FUROREGT",  //
				"FUSILADE",  //
				"FUTO",  //
				"FUTO2",  //<!-- Futo GTX -->
				"ZR3802",  //<!-- Future Shock ZR380 -->
				"GB200",  //
				"BLISTA3",  //<!-- Go Go Monkey Blista -->
				"GROWLER",  //
				"EVERON2",  //<!-- Hotring Everon -->
				"GAUNTLET6",  //<!-- Hotring Hellfire -->
				"HOTRING",  //<!-- Hotring Sabre -->
				"IMORGON",  //
				"ISSI7",  //<!-- Issi Sport -->
				"ITALIGTO",  //
				"STINGERTT",  //<!-- Issi GTO Stinger TT -->
				"ITALIRSX",  //
				"JESTER",  //
				"JESTER2",  //<!-- Jester (Racecar) -->
				"JESTER3",  //<!-- Jester Classic -->
				"JESTER4",  //<!-- Jester RR -->
				"JUGULAR",  //
				"KHAMELION",  //
				"KOMODA",  //
				"KURUMA",  //
				"KURUMA2",  //<!-- Kuruma (Armored) -->
				"COUREUR",  //<!-- La Coureuse -->
				"LOCUST",  //
				"LYNX",  //
				"MASSACRO",  //
				"MASSACRO2",  //<!-- Massacro (Racecar) -->
				"NEO",  //
				"NEON",  //
				"ZR3803",  //<!-- Nightmare ZR380 -->
				"OMNIS",  //
				"OMNISEGT",  //
				"PANTHERE",  //
				"PARAGON",  //
				"PARAGON2",  //<!-- Paragon R (Armored) -->
				"PARIAH",  //
				"PENUMBRA",  //
				"PENUMBRA2",  //<!-- Penumbra FF -->
				"RAIDEN",  //
				"RAPIDGT",  //
				"RAPIDGT2",  //<!-- Rapid GT Cabrio -->
				"RAPTOR",  //
				"REMUS",  //
				"REVOLTER",  //
				"RT3000",  //
				"RUSTON",  //
				"SCHAFTER4",  //<!-- Schafter LWB -->
				"SCHAFTER3",  //<!-- Schafter V12 -->
				"SCHLAGEN",  //
				"SCHWARZER",  //
				"SENTINEL3",  //<!-- Sentinel Classic -->
				"SENTINEL4",  //<!-- Sentinel Classic Widebody -->
				"SEVEN70",  //
				"SM722",  //
				"SPECTER",  //
				"SPECTER2",  //<!-- Specter Custom -->
				"BUFFALO3",  //<!-- Sprunk Buffalo -->
				"STREITER",  //
				"SUGOI",  //
				"SULTAN",  //
				"SULTAN2",  //<!-- Sultan Classic -->
				"SULTAN3",  //<!-- Sultan RS Classic -->
				"SURANO",  //
				"TROPOS",  //
				"VSTR",  //<!-- V-STR -->
				"VECTRE",  //
				"VERLIERER2",  //
				"VETO",  //<!-- Veto Classic -->
				"VETO2",  //<!-- Veto Modern -->
				"ZR350",  //
				"turismo3", // Super
				"dominator9", // Muscle
				"driftyosemite", // Muscle
				"impaler6", // Muscle
				"Vigero3",	// Muscle
				"niobe",	//Sports--
				"paragon3",	//Sports--
				"coquette5",	//Sports Classics--
				"pipistrello"	//super--
			};

			Mod_Data::PreVeh_02 = PreVehSet_02;
			Write_ini(sVehList02, Mod_Data::PreVeh_02);
		}
		else
			Remove_blanks(&Mod_Data::PreVeh_02);

		const std::string sVehList03 = DirVehicles + "/MidValueVeh.ini";
		Mod_Data::PreVeh_03 = Read_ini(sVehList03);
		if (Mod_Data::PreVeh_03.size() == 0)
		{
			const std::vector<std::string> PreVehSet_03 = {
				"COGCABRIO",  //
				"EXEMPLAR",  //
				"F620",  //
				"BRIGHAM",  //
				"FELON",  //
				"FELON2",  //<!-- Felon GT -->
				"JACKAL",  //
				"KANJOSJ",  //
				"ORACLE",  //
				"ORACLE2",  //<!-- Oracle XS -->
				"POSTLUDE",  //
				"PREVION",  //
				"SENTINEL2",  //<!-- Sentinel -->
				"SENTINEL",  //<!-- Sentinel XS -->
				"WINDSOR",  //
				"WINDSOR2",  //<!-- Windsor Drop -->
				"ZION",  //
				"ZION2",  //<!-- Zion Cabrio -->
				"ASEA",  //
				"ASEA2",  //<!-- Asea North Mod_Data::Yankton variant -->
				"ASTEROPE",  //
				"CINQUEMILA",  //
				"COGNOSCENTI",  //
				"COGNOSCENTI2",  //<!-- Cognoscenti (Armored) -->
				"COG55",  //<!-- Cognoscenti 55 -->
				"COG552",  //<!-- Cognoscenti 55 (Armored) -->
				"DEITY",  //
				"FUGITIVE",  //
				"GLENDALE2",  //<!-- Glendale Custom -->
				"INTRUDER",  //
				"PREMIER",  //
				"PRIMO2",  //<!-- Primo Custom -->
				"REGINA",  //
				"RHINEHART",  //
				"ROMERO",  //
				"SCHAFTER2",  //
				"SCHAFTER6",  //<!-- Schafter LWB (Armored) -->
				"SCHAFTER5",  //<!-- Schafter V12 (Armored) -->
				"STAFFORD",  //
				"STANIER",  //
				"STRATUM",  //
				"STRETCH",  //
				"SUPERD",  //
				"SURGE",  //
				"TAILGATER",  //
				"TAILGATER2",  //<!-- Tailgater S -->
				"LIMO2",  //<!-- Turreted Limo -->
				"WARRENER2",  //<!-- Warrener HKR -->
				"WASHINGTON",  //
				"ASTRON",  //
				"BALLER",  //
				"BALLER2",  //<!-- Baller 2nd gen variant -->
				"BALLER3",  //<!-- Baller LE -->
				"BALLER5",  //<!-- Baller LE (Armored) -->
				"BALLER4",  //<!-- Baller LE LWB -->
				"BALLER6",  //<!-- Baller LE LWB (Armored) -->
				"BALLER7",  //<!-- Baller ST -->
				"BJXL",  //
				"CAVALCADE",  //
				"CAVALCADE2",  //<!-- Cavalcade 2nd gen variant -->
				"CONTENDER",  //
				"DUBSTA",  //
				"DUBSTA2",  //<!-- Dubsta black variant -->
				"FQ2",  //
				"GRANGER",  //
				"GRANGER2",  //<!-- Granger 3600LX -->
				"GRESLEY",  //
				"HUNTLEY",  //
				"ISSI8",  //<!-- Issi Rally -->
				"IWAGEN",  //
				"JUBILEE",  //
				"LANDSTALKER",  //
				"LANDSTALKER2",  //<!-- Landstalker XL -->
				"MESA",  //
				"MESA2",  //<!-- Mesa North Mod_Data::Yankton variant -->
				"NOVAK",  //
				"PATRIOT",  //
				"PATRIOT2",  //<!-- Patriot Stretch -->
				"RADI",  //
				"REBLA",  //
				"ROCOTO",  //
				"SEMINOLE",  //
				"SEMINOLE2",  //<!-- Seminole Frontier -->
				"SERRANO",  //
				"SQUADDIE",  //
				"TOROS",  //
				"XLS",  //
				"XLS2",  //<!-- XLS (Armored) -->
				"aleutian", // SUVs
				"baller8", // SUVs
				"cavalcade3", // SUVs
				"dorado", // SUVs
				"vivanite", // SUVs
				"asterope2", // Sedans
				"impaler5", // Sedans
				"drifteuros", // Sports
				"driftfuto", // Sports
				"driftjester", // Sports
				"driftremus", // Sports
				"drifttampa", // Sports
				"driftzr350", // Sports
				"driftfr36", // Coupes
				"fr36", // Coupes
				"terminus", // Off-Road
				"castigator", 		//SUV
				"driftcypher",		//Sports
				"driftsentinel",	//Sports
				"envisage",	//Sports
				"driftvorschlag",	//Sedans
				"vorschlaghammer",	//Sedans
				"eurosX32"	//Coupes
			};

			Mod_Data::PreVeh_03 = PreVehSet_03;
			Write_ini(sVehList03, Mod_Data::PreVeh_03);
		}
		else
			Remove_blanks(&Mod_Data::PreVeh_03);

		const std::string sVehList04 = DirVehicles + "/LowValueVeh.ini";
		Mod_Data::PreVeh_04 = Read_ini(sVehList04);
		if (Mod_Data::PreVeh_04.size() == 0)
		{
			const std::vector<std::string> PreVehSet_04 = {
				"GREENWOOD",  //
				"MOONBEAM",  //
				"DILETTANTE",  //
				"PANTO",  //
				"RHAPSODY",  //
				"EMPEROR",  //
				"EMPEROR2",  //<!-- Emperor beater variant -->
				"GLENDALE",  //
				"INGOT",  //
				"PRIMO",  //
				"WARRENER",  //
				"HABANERO",  //
				"dominator10",		//Muscle
				"driftnebula",		//Sports Classics
				"pizzaboy",		//Motorcycles
				"yosemite1500"		//Off-Road
			};

			Mod_Data::PreVeh_04 = PreVehSet_04;
			Write_ini(sVehList04, Mod_Data::PreVeh_04);
		}
		else
			Remove_blanks(&Mod_Data::PreVeh_04);

		const std::string sVehList10 = DirVehicles + "/Planes.ini";
		Mod_Data::PreVeh_10 = Read_ini(sVehList10);
		if (Mod_Data::PreVeh_10.size() == 0)
		{
			const std::vector<std::string> PreVehSet_10 = {
				"ALPHAZ1",  //
				"STRIKEFORCE",  //<!-- B-11 Strikeforce -->
				"BESRA",  //
				"RAIJU",  //<!-- F-160 Raiju -->
				"HYDRA",  //
				"STARLING",  //<!-- LF-22 Starling -->
				"MAMMATUS",  //
				"MOGUL",  //
				"LAZER",  //<!-- P-996 LAZER -->
				"PYRO",  //
				"BOMBUSHKA",  //<!-- RM-10 Bombushka -->
				"ROGUE",  //
				"ALKONOST",  //<!-- RO-86 Alkonost -->
				"TITAN",  //
				"TULA",  //
				"MOLOTOK",  //<!-- V-65 Molotok -->
				"VOLATOL",  //
				"CARGOPLANE",  //
				"CARGOPLANE2",  //
				"CUBAN800",  //
				"DODO",  //
				"JET",  //
				"LUXOR",  //
				"LUXOR2",  //<!-- Luxor Deluxe -->
				"MILJET",  //
				"NIMBUS",  //
				"SHAMAL",  //
				"STREAMER216",  //
				"VELUM",  //
				"VELUM2",  //<!-- Velum 5-Seater -->
				"VESTRA"  //
			};

			Mod_Data::PreVeh_10 = PreVehSet_10;
			Write_ini(sVehList10, Mod_Data::PreVeh_10);
		}
		else
			Remove_blanks(&Mod_Data::PreVeh_10);

		const std::string sVehList11 = DirVehicles + "/Helicopters.ini";
		Mod_Data::PreVeh_11 = Read_ini(sVehList11);
		if (Mod_Data::PreVeh_11.size() == 0)
		{
			const std::vector<std::string> PreVehSet_11 = {
				"CONADA",  //
				"FROGGER",  //
				"MAVERICK",  //
				"SUPERVOLITO",  //
				"SUPERVOLITO2",  //<!-- SuperVolito Carbon -->
				"SWIFT",  //
				"SWIFT2",  //<!-- Swift Deluxe -->
				"VOLATUS"  //
			};

			Mod_Data::PreVeh_11 = PreVehSet_11;
			Write_ini(sVehList11, Mod_Data::PreVeh_11);
		}
		else
			Remove_blanks(&Mod_Data::PreVeh_11);
	}
	void FindAddPeds()
	{
		LoggerLight("FindAddPeds");

		const std::string sPedList01 = DirCustPeds + "/Beach.ini";
		Mod_Data::PrePed_01 = Read_ini(sPedList01);
		if (Mod_Data::PrePed_01.size() == 0)
		{
			const std::vector<std::string> PrePeSet_01 = {
				"a_f_m_beach_01",//"Beach Female",  		
				"a_f_m_fatcult_01",//"Fat Cult Female",  
				"a_f_y_hippie_01",//"Hippie Female", 
				"a_f_y_yoga_01",//"Yoga Female", 
				"a_m_m_beach_01",//"Beach Male",  
				"a_m_y_beach_01",//"Beach Young Male",  
				"a_m_y_beach_02",//"Beach Young Male 2",  
				"a_m_y_beach_03",//"Beach Young Male 3", 
				"a_m_y_breakdance_01",//"Breakdancer Male",
				"a_m_y_hippy_01",//"Hippie Male",  
				"a_m_y_sunbathe_01",//"Sunbather Male",  
				"a_m_y_surfer_01",//"Surfer",
				"a_m_y_beachvesp_01",//"Vespucci Beach Male",  
				"a_m_y_beachvesp_02",//"Vespucci Beach Male 2",  
				"a_m_y_stwhi_01",//"White Street Male",  
				"a_m_y_yoga_01",//"Yoga Male",
				"a_f_m_trampbeac_01"//"Beach Tramp Female", 
			};

			Mod_Data::PrePed_01 = PrePeSet_01;
			Write_ini(sPedList01, Mod_Data::PrePed_01);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_01);

		const std::string sPedList02 = DirCustPeds + "/Tramp.ini";
		Mod_Data::PrePed_02 = Read_ini(sPedList02);
		if (Mod_Data::PrePed_02.size() == 0)
		{
			const std::vector<std::string> PrePeSet_02 = {
				"a_f_m_trampbeac_01",//"Beach Tramp Female",  
				"a_f_m_tramp_01",//"Tramp Female",  
				"a_m_o_beach_01",//"Beach Old Male",  
				"a_m_m_trampbeac_01",//"Beach Tramp Male",  
				"a_m_m_tramp_01",//"Tramp Male",  
				"a_m_o_tramp_01"//"Tramp Old Male",  
			};

			Mod_Data::PrePed_02 = PrePeSet_02;
			Write_ini(sPedList02, Mod_Data::PrePed_02);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_02);

		const std::string sPedList03 = DirCustPeds + "/HighClass.ini";
		Mod_Data::PrePed_03 = Read_ini(sPedList03);
		if (Mod_Data::PrePed_03.size() == 0)
		{
			const std::vector<std::string> PrePeSet_03 = {
				"a_f_y_scdressy_01",//"Dressy Female",  
				"a_f_y_bevhills_04",//"Beverly Hills Young Female 4", 
				"a_f_y_clubcust_01",//"Club Customer Female 1",  
				"a_f_y_clubcust_02",//"Club Customer Female 2",  
				"a_f_y_clubcust_03",//"Club Customer Female 3", 
				"a_f_y_smartcaspat_01",//"Formel Casino Guest",  
				"s_f_y_movprem_01",//"Movie Premiere Female",  
				"A_F_Y_StudioParty_01",
				"A_F_Y_StudioParty_02",
				"a_m_y_bevhills_02",//"Beverly Hills Young Male 2", 
				"a_m_y_smartcaspat_01",//"Formel Casino Guests", 
				"a_m_m_malibu_01",//"Malibu Male",  
				"a_m_y_soucent_04",//"South Central Young Male 4",  
				"s_m_m_movprem_01",//"Movie Premiere Male",  
				"A_M_M_StudioParty_01",
				"A_M_Y_StudioParty_01",
				"a_f_y_bevhills_01",//"Beverly Hills Young Female",  
				"a_f_y_bevhills_02",//"Beverly Hills Young Female 2",  
				"a_f_y_bevhills_03",//"Beverly Hills Young Female 3", 
				"a_f_y_eastsa_01",//"East SA Young Female",  
				"a_f_y_eastsa_02",//"East SA Young Female 2",  
				"a_f_y_genhot_01",//"General Hot Young Female",  
				"a_f_y_hipster_01",//"Hipster Female",  
				"a_f_y_hipster_02",//"Hipster Female 2",  
				"a_f_y_hipster_03",//"Hipster Female 3",  
				"a_f_y_hipster_04"//"Hipster Female 4", 
			};

			Mod_Data::PrePed_03 = PrePeSet_03;
			Write_ini(sPedList03, Mod_Data::PrePed_03);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_03);

		const std::string sPedList04 = DirCustPeds + "/MidClass.ini";
		Mod_Data::PrePed_04 = Read_ini(sPedList04);
		if (Mod_Data::PrePed_04.size() == 0)
		{
			const std::vector<std::string> PrePeSet_04 = {
				"a_f_y_indian_01",//"Indian Young Female",  
				"a_f_y_soucent_03",//"South Central Young Female 3",  
				"a_f_y_tourist_01",//"Tourist Young Female",  
				"a_f_y_vinewood_01",//"Vinewood Female",  
				"a_f_y_vinewood_02",//"Vinewood Female 2",  
				"a_f_y_vinewood_03",//"Vinewood Female 3",  
				"a_f_y_vinewood_04",//"Vinewood Female 4", 
				"A_F_Y_CarClub_01",
				"A_M_Y_CarClub_01",
				"a_m_m_afriamer_01",//"African American Male",  
				"a_m_m_bevhills_01",//"Beverly Hills Male",  
				"a_m_m_bevhills_02",//"Beverly Hills Male 2",  
				"a_m_y_bevhills_01",//"Beverly Hills Young Male",  
				"a_m_y_stbla_02",//"Black Street Male 2",
				"a_m_y_gencaspat_01",//"Casual Casino Guests",  
				"a_m_y_genstreet_01",//"General Street Young Male",  
				"a_m_y_genstreet_02",//"General Street Young Male 2",  
				"a_m_m_hasjew_01",//"Hasidic Jew Male",  
				"a_m_y_hasjew_01",//"Hasidic Jew Young Male",  
				"a_m_y_hipster_01",//"Hipster Male",  
				"a_m_y_hipster_02",//"Hipster Male 2",  
				"a_m_y_hipster_03",//"Hipster Male 3",  
				"a_m_y_indian_01",//"Indian Young Male",  
				"a_m_y_ktown_01",//"Korean Young Male",  
				"a_m_y_ktown_02",//"Korean Young Male 2",  
				"a_m_y_polynesian_01",//"Polynesian Young", 
				"a_m_y_vindouche_01",//"Vinewood Douche",  
				"a_m_y_vinewood_01",//"Vinewood Male",  
				"a_m_y_vinewood_02",//"Vinewood Male 2",  
				"a_m_y_vinewood_03",//"Vinewood Male 3",  
				"a_m_y_vinewood_04",//"Vinewood Male 4",  
				"a_m_y_stwhi_02",//"White Street Male 2", 
				"a_m_y_clubcust_01",//"Club Customer Male 1",  
				"a_m_y_clubcust_02",//"Club Customer Male 2",  
				"a_m_y_clubcust_03",//"Club Customer Male 3", 
				"A_M_Y_CarClub_01",
				"a_f_m_downtown_01",//"Downtown Female", 
				"a_f_y_gencaspat_01"//"Casual Casino Guest",  
			};

			Mod_Data::PrePed_04 = PrePeSet_04;
			Write_ini(sPedList04, Mod_Data::PrePed_04);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_04);

		const std::string sPedList05 = DirCustPeds + "/LowClass.ini";
		Mod_Data::PrePed_05 = Read_ini(sPedList05);
		if (Mod_Data::PrePed_05.size() == 0)
		{
			const std::vector<std::string> PrePeSet_05 = {
				"a_f_m_eastsa_01",//"East SA Female",  
				"a_f_m_eastsa_02",//"East SA Female 2",  
				"a_f_m_fatbla_01",//"Fat Black Female",  
				"a_f_m_fatwhite_01",//"Fat White Female",  
				"a_f_o_genstreet_01",//"General Street Old Female",  
				"a_f_o_indian_01",//"Indian Old Female",  
				"a_f_m_ktown_01",//"Korean Female",  
				"a_f_m_ktown_02",//"Korean Female 2",  
				"a_f_o_ktown_01",//"Korean Old Female",  
				"a_f_m_skidrow_01",//"Skid Row Female",  
				"a_f_m_soucent_01",//"South Central Female",  
				"a_f_m_soucent_02",//"South Central Female 2",  
				"a_f_m_soucentmc_01",//"South Central MC Female",  
				"a_f_o_soucent_01",//"South Central Old Female",  
				"a_f_o_soucent_02",//"South Central Old Female 2",  
				"a_f_y_soucent_01",//"South Central Young Female",  
				"a_f_y_soucent_02",//"South Central Young Female 2",  
				"a_f_m_tourist_01",//"Tourist Female",  
				"a_f_y_tourist_02",//"Tourist Young Female 2",  
				"a_m_y_stbla_01",//"Black Street Male",  
				"a_m_y_downtown_01",//"Downtown Male",  
				"a_m_m_eastsa_01",//"East SA Male",  
				"a_m_m_eastsa_02",//"East SA Male 2",  
				"a_m_y_eastsa_01",//"East SA Young Male",  
				"a_m_y_eastsa_02",//"East SA Young Male 2",  
				"a_m_m_fatlatin_01",//"Fat Latino Male",  
				"a_m_m_genfat_01",//"General Fat Male",  
				"a_m_m_genfat_02",//"General Fat Male 2",  
				"a_m_o_genstreet_01",//"General Street Old Male",  
				"a_m_m_indian_01",//"Indian Male", 
				"a_m_m_ktown_01",//"Korean Male",  
				"a_m_o_ktown_01",//"Korean Old Male", 
				"a_m_m_stlat_02",//"Latino Street Male 2",  
				"a_m_y_stlat_01",//"Latino Street Young Male",  
				"a_m_y_latino_01",//"Latino Young Male",
				"a_m_m_mexlabor_01",//"Mexican Labourer",  
				"a_m_m_mexcntry_01",//"Mexican Rural", 
				"a_m_m_polynesian_01",//"Polynesian",   
				"a_m_m_skidrow_01",//"Skid Row Male",  
				"a_m_m_socenlat_01",//"South Central Latino Male",  
				"a_m_m_soucent_01",//"South Central Male",  
				"a_m_m_soucent_02",//"South Central Male 2",  
				"a_m_m_soucent_03",//"South Central Male 3",  
				"a_m_m_soucent_04",//"South Central Male 4",  
				"a_m_o_soucent_01",//"South Central Old Male",  
				"a_m_o_soucent_02",//"South Central Old Male 2",  
				"a_m_o_soucent_03",//"South Central Old Male 3",  
				"a_m_y_soucent_01",//"South Central Young Male",  
				"a_m_y_soucent_02",//"South Central Young Male 2",  
				"a_m_y_soucent_03",//"South Central Young Male 3", 
				"a_m_m_tourist_01"//"Tourist Male",  
			};

			Mod_Data::PrePed_05 = PrePeSet_05;
			Write_ini(sPedList05, Mod_Data::PrePed_05);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_05);

		const std::string sPedList06 = DirCustPeds + "/Buisness.ini";
		Mod_Data::PrePed_06 = Read_ini(sPedList06);
		if (Mod_Data::PrePed_06.size() == 0)
		{
			const std::vector<std::string> PrePeSet_06 = {
				"g_m_m_casrn_01",//"Casino Guests?",  
				"a_f_m_bevhills_01",//"Beverly Hills Female",  
				"a_f_m_bevhills_02",//"Beverly Hills Female 2", 
				"a_f_m_business_02",//"Business Female 2",  
				"a_f_y_business_01",//"Business Young Female",  
				"a_f_y_business_02",//"Business Young Female 2",  
				"a_f_y_business_03",//"Business Young Female 3",  
				"a_f_y_business_04",//"Business Young Female 4",  
				"a_f_y_femaleagent",//"Female Agent",  
				"a_m_y_busicas_01",//"Business Casual",  
				"a_m_m_business_01",//"Business Male",  
				"a_m_y_business_01",//"Business Young Male",  
				"a_m_y_business_02",//"Business Young Male 2",  
				"a_m_y_business_03",//"Business Young Male 3",  
				"a_m_m_prolhost_01"//"Prologue Host Male",  
			};

			Mod_Data::PrePed_06 = PrePeSet_06;
			Write_ini(sPedList06, Mod_Data::PrePed_06);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_06);

		const std::string sPedList07 = DirCustPeds + "/BodyBuilders.ini";
		Mod_Data::PrePed_07 = Read_ini(sPedList07);
		if (Mod_Data::PrePed_07.size() == 0)
		{
			const std::vector<std::string> PrePeSet_07 = {
				"a_f_m_bodybuild_01",//"Bodybuilder Female",  
				"a_m_y_musclbeac_01",//"Beach Muscle Male",  
				"a_m_y_musclbeac_02"//"Beach Muscle Male 2", 
			};

			Mod_Data::PrePed_07 = PrePeSet_07;
			Write_ini(sPedList07, Mod_Data::PrePed_07);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_07);

		const std::string sPedList08 = DirCustPeds + "/Joggers.ini";
		Mod_Data::PrePed_08 = Read_ini(sPedList08);
		if (Mod_Data::PrePed_08.size() == 0)
		{
			const std::vector<std::string> PrePeSet_08 = {
				"a_f_y_fitness_01",//"Fitness Female",  
				"a_f_y_fitness_02",//"Fitness Female 2",  
				"a_f_y_runner_01",//"Jogger Female",
				"a_f_y_tennis_01",//"Tennis Player Female",  
				"a_m_y_runner_01",//"Jogger Male",  
				"a_m_y_runner_02"//"Jogger Male 2", 
			};

			Mod_Data::PrePed_08 = PrePeSet_08;
			Write_ini(sPedList08, Mod_Data::PrePed_08);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_08);

		const std::string sPedList09 = DirCustPeds + "/Golfer.ini";
		Mod_Data::PrePed_09 = Read_ini(sPedList09);
		if (Mod_Data::PrePed_09.size() == 0)
		{
			const std::vector<std::string> PrePeSet_09 = {
				"a_f_y_golfer_01",//"Golfer Young Female",  
				"a_m_m_golfer_01",//"Golfer Male",  
				"a_m_y_golfer_01"//"Golfer Young Male",  
			};

			Mod_Data::PrePed_09 = PrePeSet_09;
			Write_ini(sPedList09, Mod_Data::PrePed_09);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_09);

		const std::string sPedList10 = DirCustPeds + "/Hiker.ini";
		Mod_Data::PrePed_10 = Read_ini(sPedList10);
		if (Mod_Data::PrePed_10.size() == 0)
		{
			const std::vector<std::string> PrePeSet_10 = {
				"a_f_y_hiker_01",//"Hiker Female",  
				"a_m_y_hiker_01"//"Hiker Male",  
			};

			Mod_Data::PrePed_10 = PrePeSet_10;
			Write_ini(sPedList10, Mod_Data::PrePed_10);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_10);

		const std::string sPedList11 = DirCustPeds + "/MethodAct.ini";
		Mod_Data::PrePed_11 = Read_ini(sPedList11);
		if (Mod_Data::PrePed_11.size() == 0)
		{
			const std::vector<std::string> PrePeSet_11 = {
				"a_f_y_juggalo_01",//"Juggalo Female",  
				"a_m_y_juggalo_01",//"Juggalo Male", 
				"a_f_y_rurmeth_01",//"Rural Meth Addict Female",  
				"a_m_m_rurmeth_01",//"Rural Meth Addict Male",  
				"a_f_m_salton_01",//"Salton Female",  
				"a_f_o_salton_01",//"Salton Old Female", 
				"a_m_m_farmer_01",//"Farmer", 
				"a_m_m_hillbilly_01",//"Hillbilly Male",  
				"a_m_m_hillbilly_02",//"Hillbilly Male 2",  
				"a_m_y_methhead_01"//"Meth Addict",  
			};

			Mod_Data::PrePed_11 = PrePeSet_11;
			Write_ini(sPedList11, Mod_Data::PrePed_11);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_11);

		const std::string sPedList12 = DirCustPeds + "/Rural.ini";
		Mod_Data::PrePed_12 = Read_ini(sPedList12);
		if (Mod_Data::PrePed_12.size() == 0)
		{
			const std::vector<std::string> PrePeSet_12 = {
				"a_m_m_salton_01",//"Salton Male",  
				"a_m_m_salton_02",//"Salton Male 2",  
				"a_m_m_salton_03",//"Salton Male 3",  
				"a_m_m_salton_04",//"Salton Male 4",  
				"a_m_o_salton_01",//"Salton Old Male",  
				"a_m_y_salton_01",//"Salton Young Male",  
				"s_m_m_cntrybar_01"//"Bartender (Rural)",
			};

			Mod_Data::PrePed_12 = PrePeSet_12;
			Write_ini(sPedList12, Mod_Data::PrePed_12);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_12);

		const std::string sPedList13 = DirCustPeds + "/Cycleist.ini";
		Mod_Data::PrePed_13 = Read_ini(sPedList13);
		if (Mod_Data::PrePed_13.size() == 0)
		{
			const std::vector<std::string> PrePeSet_13 = {
				"a_f_y_skater_01",//"Skater Female",  
				"a_m_y_cyclist_01",//"Cyclist Male",  
				"a_m_y_dhill_01",//"Downhill Cyclist", 
				"a_m_y_roadcyc_01",//"Road Cyclist",  
				"a_m_y_skater_01",//"Skater Young Male",  
				"a_m_y_skater_02",//"Skater Young Male 2",  
				"a_m_m_tennis_01"//"Tennis Player Male",  
			};

			Mod_Data::PrePed_13 = PrePeSet_13;
			Write_ini(sPedList13, Mod_Data::PrePed_13);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_13);

		const std::string sPedList14 = DirCustPeds + "/LLGBQWXYZ.ini";
		Mod_Data::PrePed_14 = Read_ini(sPedList14);
		if (Mod_Data::PrePed_14.size() == 0)
		{
			const std::vector<std::string> PrePeSet_14 = {
				"a_m_y_gay_01",//"Gay Male",  
				"a_m_y_gay_02",//"Gay Male 2", 
				"a_m_m_tranvest_01",//"Transvestite Male",  
				"a_m_m_tranvest_02"//"Transvestite Male 2", 
			};

			Mod_Data::PrePed_14 = PrePeSet_14;
			Write_ini(sPedList14, Mod_Data::PrePed_14);
		}
		else
			Remove_blanks(&Mod_Data::PrePed_14);
	}
	
	bool SnowOnGround = false;

	void WeatherReport(int wet)
	{
		if (wet == -1)
		{
			if (Mod_Data::CanSnow)
				wet = LessRandomInt("RanWeatherWinter", 10, 13);
			else
				wet = LessRandomInt("RanWeatherSummer", 1, 9);
		}

		if (wet == 1)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("EXTRASUNNY");
		else if (wet == 2)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("CLEAR");
		else if (wet == 3)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("CLOUDS");
		else if (wet == 4)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("SMOG");
		else if (wet == 4)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("FOGGY");
		else if (wet == 5)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("OVERCAST");
		else if (wet == 6)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("RAIN");
		else if (wet == 7)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("THUNDER");
		else if (wet == 8)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("CLEARING");
		else if (wet == 9)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("NEUTRAL");
		else if (wet == 10)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("SNOW");
		else if (wet == 11)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("BLIZZARD");
		else if (wet == 12)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("SNOWLIGHT");
		else if (wet == 13)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("XMAS");

		if (Mod_Data::CanSnow)
		{
			if (!SnowOnGround)
			{
				AccessLetItSnowType(true);
				//Write_ini(sRaceSnowOn, Snows);
				SnowOnGround = true;
			}
		}
		else
		{
			if (SnowOnGround)
			{
				AccessLetItSnowType(false);
				//Write_ini(sRaceSnowOff, Snows);
				SnowOnGround = false;

			}
		}
	}
	void RandomWeatherTime()
	{
		WeatherReport(-1);

		int Times = LessRandomInt("RanTimes", 0, 23);
		TIME::SET_CLOCK_TIME(Times, 0, 0);
	}
}

namespace Mod_Maths
{
	const std::vector<std::string> MainLandIPLs = {
		"xm_bunkerentrance_door",
		"xm_hatch_01_cutscene",
		"xm_hatch_02_cutscene",
		"xm_hatch_03_cutscene",
		"xm_hatch_04_cutscene",
		"xm_hatch_06_cutscene",
		"xm_hatch_07_cutscene",
		"xm_hatch_08_cutscene",
		"xm_hatch_09_cutscene",
		"xm_hatch_10_cutscene",
		"xm_hatch_closed",
		"xm_hatches_terrain",
		"xm_hatches_terrain_lod",
		"xm_mpchristmasadditions",
		"xm_siloentranceclosed_x17",

		"gr_case10_bunkerclosed",
		"gr_case9_bunkerclosed",
		"gr_case3_bunkerclosed",
		"gr_case0_bunkerclosed",
		"gr_case1_bunkerclosed",
		"gr_case2_bunkerclosed",
		"gr_case5_bunkerclosed",
		"gr_case7_bunkerclosed",
		"gr_case11_bunkerclosed",
		"gr_case6_bunkerclosed",
		"gr_case4_bunkerclosed",

		"vw_casino_billboard_lod",
		"vw_casino_billboard_lod(1)",
		"vw_casino_billboard",
		"hei_dlc_windows_casino_lod",
		"hei_dlc_windows_casino",
		"hei_dlc_casino_door_lod",
		"hei_dlc_casino_door",
		"hei_dlc_casino_aircon_lod",
		"hei_dlc_casino_aircon",

		"hei_dlc_vw_roofdoors_locked",
		"vw_ch3_additions",
		"vw_ch3_additions_long_0",
		"vw_ch3_additions_strm_0",
		"vw_dlc_casino_door",
		"vw_dlc_casino_door_lod",

		"ba_barriers_case1",
		"ba_barriers_case2",
		"ba_barriers_case3",
		"ba_barriers_case4",
		"ba_barriers_case5",
		"ba_barriers_case6",
		"ba_barriers_case7",
		"ba_barriers_case8",
		"ba_barriers_case9",
		"bkr_bi_hw1_13_int"
	};
	const std::vector<std::string> CayoPericoIPLs = {
		"h4_islandairstrip",
		"h4_islandairstrip_props",
		"h4_islandx_mansion",
		"h4_islandx_mansion_props",
		"h4_islandx_props",
		"h4_islandxdock",
		"h4_islandxdock_props",
		"h4_islandxdock_props_2",
		"h4_islandxtower",
		"h4_islandx_maindock",
		"h4_islandx_maindock_props",
		"h4_islandx_maindock_props_2",
		"h4_IslandX_Mansion_Vault",
		"h4_islandairstrip_propsb",
		"h4_islandx_barrack_props",
		"h4_islandx_checkpoint",
		"h4_islandx_checkpoint_props",
		"h4_islandx_Mansion_Office",
		"h4_islandx_Mansion_LockUp_01",
		"h4_islandx_Mansion_LockUp_02",
		"h4_islandx_Mansion_LockUp_03",
		"h4_islandairstrip_hangar_props",
		"h4_IslandX_Mansion_B",
		"h4_islandairstrip_doorsclosed",
		"h4_Underwater_Gate_Closed",
		"h4_mansion_gate_closed",
		"h4_aa_guns",
		"h4_IslandX_Mansion_GuardFence",
		"h4_IslandX_Mansion_Entrance_Fence",
		"h4_IslandX_Mansion_B_Side_Fence",
		"h4_IslandX_Mansion_Lights",
		"h4_islandxcanal_props",
		"h4_islandX_Terrain_props_06_a",
		"h4_islandX_Terrain_props_06_b",
		"h4_islandX_Terrain_props_06_c",
		"h4_islandX_Terrain_props_05_a",
		"h4_islandX_Terrain_props_05_b",
		"h4_islandX_Terrain_props_05_c",
		"h4_islandX_Terrain_props_05_d",
		"h4_islandX_Terrain_props_05_e",
		"h4_islandX_Terrain_props_05_f",
		"H4_islandx_terrain_01",
		"H4_islandx_terrain_02",
		"H4_islandx_terrain_03",
		"H4_islandx_terrain_04",
		"H4_islandx_terrain_05",
		"H4_islandx_terrain_06",
		"h4_ne_ipl_00",
		"h4_ne_ipl_01",
		"h4_ne_ipl_02",
		"h4_ne_ipl_03",
		"h4_ne_ipl_04",
		"h4_ne_ipl_05",
		"h4_ne_ipl_06",
		"h4_ne_ipl_07",
		"h4_ne_ipl_08",
		"h4_ne_ipl_09",
		"h4_nw_ipl_00",
		"h4_nw_ipl_01",
		"h4_nw_ipl_02",
		"h4_nw_ipl_03",
		"h4_nw_ipl_04",
		"h4_nw_ipl_05",
		"h4_nw_ipl_06",
		"h4_nw_ipl_07",
		"h4_nw_ipl_08",
		"h4_nw_ipl_09",
		"h4_se_ipl_00",
		"h4_se_ipl_01",
		"h4_se_ipl_02",
		"h4_se_ipl_03",
		"h4_se_ipl_04",
		"h4_se_ipl_05",
		"h4_se_ipl_06",
		"h4_se_ipl_07",
		"h4_se_ipl_08",
		"h4_se_ipl_09",
		"h4_sw_ipl_00",
		"h4_sw_ipl_01",
		"h4_sw_ipl_02",
		"h4_sw_ipl_03",
		"h4_sw_ipl_04",
		"h4_sw_ipl_05",
		"h4_sw_ipl_06",
		"h4_sw_ipl_07",
		"h4_sw_ipl_08",
		"h4_sw_ipl_09",
		"h4_islandx_mansion",
		"h4_islandxtower_veg",
		"h4_islandx_sea_mines",
		"h4_islandx",
		"h4_islandx_barrack_hatch",
		"h4_islandxdock_water_hatch",
		"h4_beach",
		"h4_beach_props",
		"h4_beach_bar_props",
		"h4_beach_props_party",
		"h4_beach_party"
	};
	const std::vector<std::string> YanktonIPLs = {
		"plg_01",
		"prologue01",
		"prologue01_lod",
		"prologue01c",
		"prologue01c_lod",
		"prologue01d",
		"prologue01d_lod",
		"prologue01e",
		"prologue01e_lod",
		"prologue01f",
		"prologue01f_lod",
		"prologue01g",
		"prologue01h",
		"prologue01h_lod",
		"prologue01i",
		"prologue01i_lod",
		"prologue01j",
		"prologue01j_lod",
		"prologue01k",
		"prologue01k_lod",
		"prologue01z",
		"prologue01z_lod",
		"plg_02",
		"prologue02",
		"prologue02_lod",
		"plg_03",
		"prologue03",
		"prologue03_lod",
		"prologue03b",
		"prologue03b_lod",
		"prologue03_grv_dug",
		"prologue03_grv_dug_lod",
		"prologue_grv_torch",
		"plg_04",
		"prologue04",
		"prologue04_lod",
		"prologue04b",
		"prologue04b_lod",
		"prologue04_cover",
		"des_protree_end",
		"des_protree_start",
		"des_protree_start_lod",
		"plg_05",
		"prologue05",
		"prologue05_lod",
		"prologue05b",
		"prologue05b_lod",
		"plg_06",
		"prologue06",
		"prologue06_lod",
		"prologue06b",
		"prologue06b_lod",
		"prologue06_int",
		"prologue06_int_lod",
		"prologue06_pannel",
		"prologue06_pannel_lod",
		"prologue_m2_door",
		"prologue_m2_door_lod",
		"plg_occl_00",
		"prologue_occl",
		"plg_rd",
		"prologuerd",
		"prologuerdb",
		"prologuerd_lod"
	};

	Vector3 NewVector3(float x, float y, float z)
	{
		Vector3 NewVec = Vector3();
		NewVec.x = x;
		NewVec.y = y;
		NewVec.z = z;

		return NewVec;
	}
	Vector3 NewVector3(Mod_Class::Vector4 pos)
	{
		return NewVector3(pos.X, pos.Y, pos.Z);
	}
	
	float GetAngle(Vector3 postion1, Vector3 postion2)
	{
		double ang = (postion1.x * postion2.x) + (postion1.y * postion2.y);
		double output = 0;
		if (ang != 0)
		{
			double ang1 = sqrt((postion1.x * 2) + (postion1.y * 2)) / ang;
			double ang2 = sqrt((postion2.x * 2) + (postion2.y * 2)) / ang;
			double output = cos(ang1 + ang2 / ang);
		}
		return (float)output;
	}
	float DistanceTo(Vector3 postion1, Vector3 postion2)
	{
		double num = postion2.x - postion1.x;
		double num2 = postion2.y - postion1.y;
		double num3 = postion2.z - postion1.z;
		return (float)sqrt(num * num + num2 * num2 + num3 * num3);
	}
	float DistanceTo(Entity entity1, Entity entity2)
	{
		Vector3 postion1 = ENTITY::GET_ENTITY_COORDS(entity1, false);
		Vector3 postion2 = ENTITY::GET_ENTITY_COORDS(entity2, false);

		return DistanceTo(postion1, postion2);
	}
	float DistanceTo(Entity entity1, Mod_Class::Vector4 entity2)
	{
		Vector3 postion1 = ENTITY::GET_ENTITY_COORDS(entity1, false);
		Vector3 postion2 = NewVector3(entity2.X, entity2.Y, entity2.Z);

		return DistanceTo(postion1, postion2);
	}
	float DistanceTo(Entity entity1, Vector3 postion2)
	{
		Vector3 postion1 = ENTITY::GET_ENTITY_COORDS(entity1, false);
		return DistanceTo(postion1, postion2);
	}
	float DistanceTo(Mod_Class::Vector4 postion1, Vector3 postion2)
	{
		double num = postion2.x - postion1.X;
		double num2 = postion2.y - postion1.Y;
		double num3 = postion2.z - postion1.Z;
		return (float)sqrt(num * num + num2 * num2 + num3 * num3);
	}
	float DistanceTo(Mod_Class::Vector4 postion1, Mod_Class::Vector4 postion2)
	{
		double num = postion2.X - postion1.X;
		double num2 = postion2.Y - postion1.Y;
		double num3 = postion2.Z - postion1.Z;
		return (float)sqrt(num * num + num2 * num2 + num3 * num3);
	}

	std::string MyZone(Vector3 pos)
	{
		char* ZName = ZONE::GET_NAME_OF_ZONE(pos.x, pos.y, pos.z);
		std::string s = ZName;
		return s;
	}
	std::string MyZone(Mod_Class::Vector4 pos)
	{
		return MyZone(NewVector3(pos.X, pos.Y, pos.Z));
	}

	Vector3 MyWayPoint()
	{
		return UI::GET_BLIP_INFO_ID_COORD(UI::GET_FIRST_BLIP_INFO_ID(8));
	}
	Vector3 EntPosition(Entity ent)
	{
		return ENTITY::GET_ENTITY_COORDS(ent, 0);
	}
	Vector3 PlayerPosi()
	{
		return EntPosition(PLAYER::PLAYER_PED_ID());
	}
	Vector3 RightOfEntity(Entity ent)
	{
		Vector3 Pos = ENTITY::GET_ENTITY_ROTATION(ent, 00);
		const double PI = 3.14259;
		double num = cos((double)Pos.y * (PI / 180.0));
		double num2 = cos((double)(0 - Pos.z) * (PI / 180.0)) * num;
		double num3 = sin((double)Pos.z * (PI / 180.0)) * num;
		double num4 = sin((double)(0 - Pos.y) * (PI / 180.0));

		Pos.x = (float)num2;
		Pos.y = (float)num3;
		Pos.z = (float)num4;

		return Pos;
	}
	Vector3 FowardOf(Entity ent, float multi, bool inFront)
	{
		Vector3 vec = ENTITY::GET_ENTITY_COORDS(ent, true);
		Vector3 FV = ENTITY::GET_ENTITY_FORWARD_VECTOR(ent);
		FV.x *= multi;
		FV.y *= multi;
		FV.z *= multi;

		if (inFront)
		{
			vec.x += FV.x;
			vec.y += FV.y;
			vec.z += FV.z;
		}
		else
		{
			vec.x -= FV.x;
			vec.y -= FV.y;
			vec.z -= FV.z;
		}

		return vec;
	}
	Vector3 RightOf(Entity ent, float multi, bool inFront)
	{
		Vector3 vec = ENTITY::GET_ENTITY_COORDS(ent, true);
		Vector3 FV = RightOfEntity(ent);
		FV.x *= multi;
		FV.y *= multi;
		FV.z *= multi;

		if (inFront)
		{
			vec.x += FV.x;
			vec.y += FV.y;
			vec.z += FV.z;
		}
		else
		{
			vec.x -= FV.x;
			vec.y -= FV.y;
			vec.z -= FV.z;
		}

		return vec;
	}

	Mod_Class::Vector4 GetPosV4(Entity ent)
	{
		Vector3 Vx = EntPosition(ent);

		return Mod_Class::Vector4(Vx.x, Vx.y, Vx.z, ENTITY::GET_ENTITY_HEADING(ent));
	}
	Mod_Class::Vector4 PlayerV4()
	{
		return GetPosV4(PLAYER::PLAYER_PED_ID());
	}
	Mod_Class::Vector4 InAreaOf(Mod_Class::Vector4  area, float minDist, float maxDist)
	{
		float X = Mod_Systems::RandomFloat(maxDist * -1, maxDist);
		float Y = Mod_Systems::RandomFloat(maxDist * -1, maxDist);

		if (X > -1.0 && X < minDist)
			X = minDist;
		else if (X < 1.0 && X > minDist * -1)
			X = minDist * -1;

		if (Y > -1.0 && Y < minDist)
			Y = minDist;
		else if (Y < 1.0 && Y > minDist * -1)
			Y = minDist * -1;

		float x = area.X + X;
		float y = area.Y + Y;
		float z = area.Z;
		float r = area.R;

		return Mod_Class::Vector4(x, y, z, r);
	}
	Mod_Class::Vector4 InAreaOf(Vector3 area, float minDist, float maxDist)
	{
		return InAreaOf(Mod_Class::Vector4(area.x, area.y, area.z, 0.0), minDist, maxDist);
	}
	Mod_Class::Vector4 NearByStreet(Mod_Class::Vector4 area)
	{
		Mod_Class::Vector4 Here = InAreaOf(area, 25.0f, 75.0f);
		Vector3 VMe = NewVector3(Here.X, Here.Y, Here.Z);
		PATHFIND::GET_SAFE_COORD_FOR_PED(Here.X, Here.Y, Here.Z, true, &VMe, 16);
		return Mod_Class::Vector4(VMe.x, VMe.y, VMe.z, 0.0f);
	}

	std::vector<Vector3> LastPoint = {};

	bool ItsTooNear(Mod_Class::Vector4 spot, float minDist)
	{
		bool ItsNear = true;		
		if ((int)LastPoint.size() > 0)
		{
			int i = 0;
			for (; i < (int)LastPoint.size(); i++)
			{
				if (DistanceTo(spot, LastPoint[i]) < minDist)
					break;
			}

			if (i == (int)LastPoint.size())
				ItsNear = false;
		}
		else
			ItsNear = false;

		return ItsNear;
	}
	void FindSpPoint(Mod_Class::Vector4* spot, const std::vector<Mod_Class::Vector4>& ListOfPlaces)
	{
		float Far = 9000.0f;
		int Near = 0;
		for (int i = 0; i < (int)ListOfPlaces.size(); i++)
		{
			float Dist = DistanceTo(ListOfPlaces[i], *spot);
			if (Dist < Far && !ItsTooNear(ListOfPlaces[i], 5.0f))
			{
				Far = Dist;
				Near = i;
			}
		}
		*spot = ListOfPlaces[Near];
	}
	Mod_Class::Vector4 FindPedSpPoint(Vector3 pos)
	{
		Mod_Class::Vector4 Location = Mod_Class::Vector4(pos);

		if (Mod_Data::Yankton_Loaded)
			FindSpPoint(&Location, Mod_Data::Yankton);
		else if (Mod_Data::Cayo_Loaded)
			FindSpPoint(&Location, Mod_Data::CayoSpPoint);
		else
			FindSpPoint(&Location, Mod_Data::SpPoint);

		LastPoint.push_back(NewVector3(Location));
		if (LastPoint.size() > 10)
			LastPoint.erase(LastPoint.begin());

		return Location;
	}

	bool NotTheSame(Mod_Class::Vector4 postion1, Mod_Class::Vector4 postion2)
	{
		bool bTrue = false;

		if (postion1.X != postion2.X)
			bTrue = true;

		if (postion1.Y != postion2.Y)
			bTrue = true;

		if (postion1.Z != postion2.Z)
			bTrue = true;

		if (postion1.R != postion2.R)
			bTrue = true;

		return bTrue;
	}
	float GroundHight(Vector3 postion)
	{
		float GHight = postion.z;
		GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(postion.x, postion.y, postion.z, &GHight, 1);
		return GHight;
	}

	const std::vector<Vector3> landSand = {
	 NewVector3(225.8934, 2841.527, 200.0402),
	 NewVector3(796.0992, 3011.926, 90.13193),
	 NewVector3(1495.307, 3187.998, 41.04951),
	 NewVector3(1655.049, 3249.205, 41.21964),
	 NewVector3(1561.392, 3160.818, 41.1649),
	 NewVector3(1334.507, 2924.953, 98.35621),
	 NewVector3(798.5253, 2388.362, 282.331),
	 NewVector3(413.3483, 2034.074, 425.4946),
	 NewVector3(-175.5016, 1448.899, 598.845),
	 NewVector3(-349.6658, -187.2563, 398.4032)
	};
	const std::vector<Vector3> landLS = {
		 NewVector3(-1002.727, -1650.774, 134.2087),
		 NewVector3(-1193.304, -1941.04, 59.51603),
		 NewVector3(-1571.467, -2617.15, 14.57554),
		 NewVector3(-1612.011, -2789.524, 14.62421),
		 NewVector3(-1532.074, -2835.987, 14.58676),
		 NewVector3(-991.79, -3147.605, 90.8317),
		 NewVector3(-440.5424, -3123.56, 232.0305),
		 NewVector3(-88.80471, -2403.97, 234.262),
		 NewVector3(-18.7144, -1591.593, 351.0859),
		 NewVector3(29.53166, 219.7558, 581.6113),
		 NewVector3(-169.9742, 1746.14, 484.2034)
	};
	
	std::vector<Vector3> BuildFlightPath(Vector3 start)
	{
		float f1 = DistanceTo(start, landSand[0]);
		float f2 = DistanceTo(start, landLS[0]);

		if (f1 < f2)
			return landSand;
		else
			return landLS;
	}

	bool YanktonIPL()
	{
		Mod_Systems::LoggerLight("YankLoad == " + std::to_string(Mod_Data::Yankton_Loaded));
		bool Failed = false;
		if (Mod_Data::Yankton_Loaded)
		{
			invoke<Void>(0x9BAE5AD2508DF078, false);
			invoke<Void>(0x9133955F1A2DA957, false);
			invoke<Void>(0x9BAE5AD2508DF078, false);

			for (int i = 0; i < YanktonIPLs.size(); i++)
			{
				STREAMING::REMOVE_IPL((LPSTR)YanktonIPLs[i].c_str());
				WAIT(1);
			}
			if (Mod_Data::GotPlayZero)
				Mod_Systems::Delete_ini(ZeroYank);
			Mod_Data::Yankton_Loaded = false;
		}
		else
		{
			invoke<Void>(0x9BAE5AD2508DF078, false);
			invoke<Void>(0x9133955F1A2DA957, true);

			std::vector<std::string> PzTest = {};

			for (int i = 0; i < YanktonIPLs.size(); i++)
			{
				STREAMING::REQUEST_IPL((LPSTR)YanktonIPLs[i].c_str());
				WAIT(1);
				if (!STREAMING::IS_IPL_ACTIVE((LPSTR)YanktonIPLs[i].c_str()))
					Failed = true;
			}
			if (Mod_Data::GotPlayZero)
				Mod_Systems::Write_ini(ZeroYank, PzTest);
			Mod_Data::Yankton_Loaded = true;
		}

		return Failed;
	}
	bool CayoPericoIPL()
	{
		Mod_Systems::LoggerLight("CayoPericoIPL == " + std::to_string(Mod_Data::Cayo_Loaded));
		bool Failed = false;
		if (Mod_Data::Cayo_Loaded)
		{
			invoke<Void>(0x9A9D1BA639675CF1, "HeistIsland", 0);
			invoke<Void>(0x5E1460624D194A38, 0);

			invoke<Void>(0xF74B1FFA4A15FBEA, 0);
			invoke<Void>(0x53797676AD34A9AA, 1);

			for (int i = 0; i < CayoPericoIPLs.size(); i++)
			{
				if (STREAMING::IS_IPL_ACTIVE((LPSTR)CayoPericoIPLs[i].c_str()))
					STREAMING::REMOVE_IPL((LPSTR)CayoPericoIPLs[i].c_str());
				WAIT(1);
			}

			GAMEPLAY::_ENABLE_MP_DLC_MAPS(0);

			for (int i = 0; i < MainLandIPLs.size(); i++)
			{
				if (!STREAMING::IS_IPL_ACTIVE((LPSTR)MainLandIPLs[i].c_str()))
					STREAMING::REQUEST_IPL((LPSTR)MainLandIPLs[i].c_str());
			}

			if (Mod_Data::GotPlayZero)
				Mod_Systems::Delete_ini(ZeroCayo);
			Mod_Data::Cayo_Loaded = false;
		}
		else
		{
			invoke<Void>(0x9BAE5AD2508DF078, 1);


			for (int i = 0; i < MainLandIPLs.size(); i++)
			{
				if (STREAMING::IS_IPL_ACTIVE((LPSTR)MainLandIPLs[i].c_str()))
					STREAMING::REMOVE_IPL((LPSTR)MainLandIPLs[i].c_str());
			}

			GAMEPLAY::_ENABLE_MP_DLC_MAPS(1);
			DLC2::_LOAD_MP_DLC_MAPS();

			invoke<Void>(0x9A9D1BA639675CF1, "HeistIsland", 1);
			invoke<Void>(0x5E1460624D194A38, 1);

			invoke<Void>(0xF74B1FFA4A15FBEA, 1);
			invoke<Void>(0x53797676AD34A9AA, 0);

			invoke<Void>(0xF8DEE0A5600CBB93, 1);

			std::vector<std::string> PzTest = {};

			for (int i = 0; i < CayoPericoIPLs.size(); i++)
			{
				if (!STREAMING::IS_IPL_ACTIVE((LPSTR)CayoPericoIPLs[i].c_str()))
					STREAMING::REQUEST_IPL((LPSTR)CayoPericoIPLs[i].c_str());
				WAIT(1);
				if (!STREAMING::IS_IPL_ACTIVE((LPSTR)CayoPericoIPLs[i].c_str()))
					Failed = true;
			}

			if (Mod_Data::GotPlayZero)
				Mod_Systems::Write_ini(ZeroCayo, PzTest);

			Mod_Data::Cayo_Loaded = true;
		}
		
		return Failed;
	}

	void AnyPreActives(int select, bool mainLand)
	{
		if (Mod_Data::Meth_Act)
		{
			Mod_Data::Meth_Act = false;
			Mod_Entitys::MethEdd(Mod_Data::Meth_Act);
		}

		if (Mod_Data::Deputize)
		{
			Mod_Data::Deputize = false;
			Mod_Entitys::PoliceAcadamy(Mod_Data::Deputize);
		}

		if (mainLand)
		{
			if (Mod_Data::Cayo_Loaded && select != 25)
			{
				CayoPericoIPL();
				Mod_Entitys::CayoAudio();
			}
			else if (Mod_Data::Yankton_Loaded && select != 24)
				YanktonIPL();
		}
	}
}

namespace Mod_Entitys
{
	int AddRelationship(const std::string& name)
	{
		Hash hash = -1;
		PED::ADD_RELATIONSHIP_GROUP((LPSTR)name.c_str(), &hash);

		return hash;
	}
	Hash GetRelationship()
	{
		return PED::GET_PED_RELATIONSHIP_GROUP_HASH(PLAYER::PLAYER_PED_ID());
	}
	void RelGroupMember(Ped peddy, Hash group)
	{
		PED::SET_PED_RELATIONSHIP_GROUP_HASH(peddy, group);
	}
	void SetRelBetween_Gp(Hash group1, Hash group2, int relation)
	{
		PED::SET_RELATIONSHIP_BETWEEN_GROUPS(relation, group1, group2);
		PED::SET_RELATIONSHIP_BETWEEN_GROUPS(relation, group2, group1);
	}
	void SetRelationType(bool friendly)
	{
		if (friendly)
		{
			SetRelBetween_Gp(Mod_Data::GP_Player, Mod_Data::Gp_Follow, 0);
			SetRelBetween_Gp(Mod_Data::Gp_Follow, Mod_Data::Gp_Friend, 1);
			SetRelBetween_Gp(Mod_Data::GP_Attack, Mod_Data::Gp_Follow, 5);
			SetRelBetween_Gp(Mod_Data::GP_Mental, Mod_Data::Gp_Follow, 5);
			SetRelBetween_Gp(Mod_Data::GP_Player, Mod_Data::Gp_Friend, 2);
			SetRelBetween_Gp(Mod_Data::GP_Attack, Mod_Data::Gp_Friend, 5);
			SetRelBetween_Gp(Mod_Data::GP_Player, Mod_Data::GP_Attack, 5);
			SetRelBetween_Gp(Mod_Data::GP_Mental, Mod_Data::Gp_Friend, 5);
			SetRelBetween_Gp(Mod_Data::GP_Attack, Mod_Data::GP_Mental, 5);
			SetRelBetween_Gp(Mod_Data::GP_Player, Mod_Data::GP_Mental, 5);

			PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, Mod_Data::GP_Mental, Mod_Data::GP_Mental);
		}
		else
		{
			SetRelBetween_Gp(Mod_Data::GP_Player, Mod_Data::Gp_Follow, 2);
			SetRelBetween_Gp(Mod_Data::Gp_Follow, Mod_Data::Gp_Friend, 2);
			SetRelBetween_Gp(Mod_Data::GP_Attack, Mod_Data::Gp_Follow, 5);
			SetRelBetween_Gp(Mod_Data::GP_Mental, Mod_Data::Gp_Follow, 5);
			SetRelBetween_Gp(Mod_Data::GP_Player, Mod_Data::Gp_Friend, 2);
			SetRelBetween_Gp(Mod_Data::GP_Attack, Mod_Data::Gp_Friend, 5);
			SetRelBetween_Gp(Mod_Data::GP_Player, Mod_Data::GP_Attack, 5);
			SetRelBetween_Gp(Mod_Data::GP_Mental, Mod_Data::Gp_Friend, 5);
			SetRelBetween_Gp(Mod_Data::GP_Attack, Mod_Data::GP_Mental, 5);
			SetRelBetween_Gp(Mod_Data::GP_Player, Mod_Data::GP_Mental, 5);
		}
	}

	void MoveEntity(Entity ent, Vector3 position)
	{
		ENTITY::SET_ENTITY_COORDS(ent, position.x, position.y, position.z, 1, 0, 0, 1);
	}
	void MoveEntity(Entity ent, Mod_Class::Vector4 position)
	{
		ENTITY::SET_ENTITY_COORDS(ent, position.X, position.Y, position.Z, 1, 0, 0, 1);
		ENTITY::SET_ENTITY_HEADING(ent, position.R);
	}
	void StayOnGround(Vehicle vic)
	{
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vic);
	}

	int GetPedOverlayValues(int overlay)
	{
		return PED::_GET_NUM_HEAD_OVERLAY_VALUES(overlay);
	}
	int GetPedOverlay(Ped peddy, int overlay)
	{
		return PED::_GET_PED_HEAD_OVERLAY_VALUE(peddy, overlay);
	}

	std::vector<int> RandVehModsist()
	{
		std::vector<int> RandMods = {};

		for (int i = 0; i < 67; i++)
			RandMods.push_back(-1);

		return RandMods;
	}
	Prop BuildProps(const std::string& propName, Vector3 pos, Vector3 rot, bool push, bool frozen)
	{
		Mod_Systems::LoggerLight("BuildProps == " + propName);
		Prop Plop = OBJECT::CREATE_OBJECT(Mod_Systems::MyHashKey(propName), pos.x, pos.y, pos.z, 1, 1, 1);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Plop, 1, 1);
		ENTITY::SET_ENTITY_COORDS(Plop, pos.x, pos.y, pos.z, 0, 0, 0, 1);
		ENTITY::SET_ENTITY_ROTATION(Plop, rot.x, rot.y, rot.z, 2, 1);
		if (push)
			ENTITY::APPLY_FORCE_TO_ENTITY(Plop, 1, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1, 1, 1, 1, 1, 1);
		else if (frozen)
			ENTITY::FREEZE_ENTITY_POSITION(Plop, true);
		Mod_Data::Prop_List.push_back(Plop);
		return Plop;
	}
	Prop BuildProps(const std::string& propName, Mod_Class::Vector4 pos, bool push, bool frozen)
	{
		return BuildProps(propName, Mod_Maths::NewVector3(pos.X, pos.Y, pos.Z), Mod_Maths::NewVector3(0.0f, 0.0f, pos.R), push, frozen);
	}

	void EraseBlip(Blip blippy)
	{
		if (blippy != NULL)
		{
			if ((bool)UI::DOES_BLIP_EXIST(blippy))
				UI::REMOVE_BLIP(&blippy);
		}
	}
	void ClearAllPeds()
	{
		for (int i = 0; i < (int)Mod_Data::Ped_List.size(); i++)
		{
			Entity E = Mod_Data::Ped_List[i];
			if (ENTITY::DOES_ENTITY_EXIST(E))
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&E);
		}
		Mod_Data::Ped_List.clear();
		Mod_Data::CayDancers.clear();
	}
	void ClearAllEntitys(bool andPeds)
	{
		for (int i = 0; i < (int)Mod_Data::Prop_List.size(); i++)
		{
			Prop Pops = Mod_Data::Prop_List[i];
			if (ENTITY::DOES_ENTITY_EXIST(Pops))
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&Pops);
		}
		Mod_Data::Prop_List.clear();

		for (int i = 0; i < (int)Mod_Data::Vehicle_List.size(); i++)
		{
			Vehicle Vic = Mod_Data::Vehicle_List[i];
			if (ENTITY::DOES_ENTITY_EXIST(Vic))
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&Vic);
		}
		Mod_Data::Vehicle_List.clear();

		if (andPeds)
			ClearAllPeds();
	}

	const std::vector<Mod_Class::VehBlips> VehBlips = {
		Mod_Class::VehBlips("BUFFALO4",825),
		Mod_Class::VehBlips("CHAMPION",824),
		Mod_Class::VehBlips("DEITY",823),
		Mod_Class::VehBlips("GRANGER2",821),
		Mod_Class::VehBlips("JUBILEE",820),
		Mod_Class::VehBlips("PATRIOT3",818),
		Mod_Class::VehBlips("CRUSADER",800),
		Mod_Class::VehBlips("SLAMVAN2",799),
		Mod_Class::VehBlips("SLAMVAN3", 799),
		Mod_Class::VehBlips("VALKYRIE", 759),
		Mod_Class::VehBlips("VALKYRIE2", 759),
		Mod_Class::VehBlips("SQUADDIE", 757),
		Mod_Class::VehBlips("ardent", 756),///Retro Sport...       
		Mod_Class::VehBlips("cheetah2", 756),///Retro Sport...      
		Mod_Class::VehBlips("infernus2", 756),///Retro Sport...      
		Mod_Class::VehBlips("monroe", 756),///Retro Sport...      
		Mod_Class::VehBlips("stromberg", 756),///Retro Sport...      
		Mod_Class::VehBlips("torero", 756),///Retro Sport...      
		Mod_Class::VehBlips("turismo2", 756),///Retro Sport...      
		Mod_Class::VehBlips("toreador", 756),///Retro Sport...         
		Mod_Class::VehBlips("PATROLBOAT",755),
		Mod_Class::VehBlips("DINGHY5",754),
		Mod_Class::VehBlips("DINGHY5",754),
		Mod_Class::VehBlips("seasparrow2", 753),
		Mod_Class::VehBlips("barracks", 750),
		Mod_Class::VehBlips("barracks3", 750),
		Mod_Class::VehBlips("verus", 749),
		Mod_Class::VehBlips("veto2", 748),
		Mod_Class::VehBlips("veto", 747),
		Mod_Class::VehBlips("avisa", 746),
		Mod_Class::VehBlips("WINKY", 745),
		Mod_Class::VehBlips("ZHABA", 737),
		Mod_Class::VehBlips("VAGRANT", 736),
		Mod_Class::VehBlips("OUTLAW", 735),
		Mod_Class::VehBlips("everon", 734),
		Mod_Class::VehBlips("formula",726),
		Mod_Class::VehBlips("formula2",726),
		Mod_Class::VehBlips("openwheel1",726),
		Mod_Class::VehBlips("openwheel2",726),
		Mod_Class::VehBlips("STRETCH",724),
		Mod_Class::VehBlips("ZR380", 669),
		Mod_Class::VehBlips("ZR3802", 669),
		Mod_Class::VehBlips("ZR3803", 669),
		Mod_Class::VehBlips("SLAMVAN4", 668),
		Mod_Class::VehBlips("SLAMVAN5", 668),
		Mod_Class::VehBlips("SLAMVAN6", 668),
		Mod_Class::VehBlips("SCARAB", 667),
		Mod_Class::VehBlips("SCARAB2", 667),
		Mod_Class::VehBlips("SCARAB3", 667),
		Mod_Class::VehBlips("MONSTER3", 666),
		Mod_Class::VehBlips("MONSTER4", 666),
		Mod_Class::VehBlips("MONSTER5", 666),
		Mod_Class::VehBlips("ISSI4", 665),
		Mod_Class::VehBlips("ISSI5", 665),
		Mod_Class::VehBlips("ISSI6", 665),
		Mod_Class::VehBlips("IMPERATOR", 664),
		Mod_Class::VehBlips("IMPERATOR2", 664),
		Mod_Class::VehBlips("IMPERATOR3", 664),
		Mod_Class::VehBlips("IMPALER2", 663),
		Mod_Class::VehBlips("IMPALER3", 663),
		Mod_Class::VehBlips("IMPALER4", 663),
		Mod_Class::VehBlips("DOMINATOR4", 662),
		Mod_Class::VehBlips("DOMINATOR5", 662),
		Mod_Class::VehBlips("DOMINATOR6", 662),
		Mod_Class::VehBlips("CERBERUS", 660),
		Mod_Class::VehBlips("CERBERUS2", 660),
		Mod_Class::VehBlips("CERBERUS3", 660),
		Mod_Class::VehBlips("BRUTUS", 659),
		Mod_Class::VehBlips("BRUTUS2", 659),
		Mod_Class::VehBlips("BRUTUS3", 659),
		Mod_Class::VehBlips("BRUISER", 658),
		Mod_Class::VehBlips("BRUISER2", 658),
		Mod_Class::VehBlips("BRUISER3", 658),
		Mod_Class::VehBlips("STRIKEFORCE", 640),
		Mod_Class::VehBlips("OPPRESSOR2", 639),
		Mod_Class::VehBlips("SPEEDO4", 637),
		Mod_Class::VehBlips("MULE4", 636),
		Mod_Class::VehBlips("POUNDER2", 635),
		Mod_Class::VehBlips("scramjet", 634),
		Mod_Class::VehBlips("ambulance",632),
		Mod_Class::VehBlips("pbus2",631),
		Mod_Class::VehBlips("caracara",613),
		Mod_Class::VehBlips("seasparrow", 612),
		Mod_Class::VehBlips("APC", 603),
		Mod_Class::VehBlips("akula", 602),
		Mod_Class::VehBlips("insurgent", 601),
		Mod_Class::VehBlips("insurgent3", 601),
		Mod_Class::VehBlips("volatol", 600),
		Mod_Class::VehBlips("alkonost", 600),
		Mod_Class::VehBlips("KHANJALI", 598),
		Mod_Class::VehBlips("DELUXO",  596),
		Mod_Class::VehBlips("bombushka", 585),
		Mod_Class::VehBlips("seabreeze", 584),
		Mod_Class::VehBlips("STARLING", 583),
		Mod_Class::VehBlips("ROGUE", 582),
		Mod_Class::VehBlips("PYRO", 581),
		Mod_Class::VehBlips("nokota", 580),
		Mod_Class::VehBlips("MOLOTOK", 579),
		Mod_Class::VehBlips("mogul", 578),
		Mod_Class::VehBlips("microlight", 577),
		Mod_Class::VehBlips("HUNTER", 576),
		Mod_Class::VehBlips("howard", 575),
		Mod_Class::VehBlips("havok", 574),
		Mod_Class::VehBlips("tula", 573),
		Mod_Class::VehBlips("alphaz1", 572),
		Mod_Class::VehBlips("tampa3", 562),//truureted something
		Mod_Class::VehBlips("DUNE3", 561),
		Mod_Class::VehBlips("HALFTRACK", 560),
		Mod_Class::VehBlips("OPPRESSOR", 559),
		//Mod_Class::VehBlips("", 558),//something somthing turreted
		Mod_Class::VehBlips("TECHNICAL2", 534),
		Mod_Class::VehBlips("voltic2", 533),
		Mod_Class::VehBlips("wastelander", 532),
		Mod_Class::VehBlips("DUNE4", 531),
		Mod_Class::VehBlips("DUNE5", 531),
		Mod_Class::VehBlips("RUINER2", 530),
		Mod_Class::VehBlips("PHANTOM2", 528),
		Mod_Class::VehBlips("hakuchou",522),//ModSportsBike
		Mod_Class::VehBlips("hakuchou2",522),//ModSportsBike
		Mod_Class::VehBlips("shotaro",522),//ModSportsBike
		Mod_Class::VehBlips("pbus",513),//BusssAny
		Mod_Class::VehBlips("blazer",512),//QuadAny
		Mod_Class::VehBlips("blazer2",512),//QuadAny
		Mod_Class::VehBlips("blazer3",512),//QuadAny
		Mod_Class::VehBlips("blazer4",512),//QuadAny
		Mod_Class::VehBlips("blazer5",512),//QuadAny
		Mod_Class::VehBlips("cargobob", 481),
		Mod_Class::VehBlips("cargobob2", 481),
		Mod_Class::VehBlips("cargobob3", 481),
		Mod_Class::VehBlips("cargobob4", 481),
		Mod_Class::VehBlips("armytanker", 479),//Trailler Box
		Mod_Class::VehBlips("armytrailer", 479),//Trailler Box
		Mod_Class::VehBlips("baletrailer", 479),//Trailler Box
		Mod_Class::VehBlips("boattrailer", 479),//Trailler Box
		Mod_Class::VehBlips("docktrailer", 479),//Trailler Box
		Mod_Class::VehBlips("freighttrailer", 479),//Trailler Box
		Mod_Class::VehBlips("graintrailer", 479),//Trailler Box
		Mod_Class::VehBlips("tr2", 479),//Trailler Box
		Mod_Class::VehBlips("tr3", 479),//Trailler Box
		Mod_Class::VehBlips("tr4", 479),//Trailler Box
		Mod_Class::VehBlips("trflat", 479),//Trailler Box
		Mod_Class::VehBlips("tvtrailer", 479),//Trailler Box
		Mod_Class::VehBlips("tanker", 479),//Trailler Box
		Mod_Class::VehBlips("tanker2", 479),//Trailler Box
		Mod_Class::VehBlips("trailerlarge", 479),//Trailler Box
		Mod_Class::VehBlips("trailerlogs", 479),//Trailler Box
		Mod_Class::VehBlips("trailersmall", 479),//Trailler Box
		Mod_Class::VehBlips("tanker", 479),//Trailler Box
		Mod_Class::VehBlips("trailers", 479),//Trailler Box
		Mod_Class::VehBlips("trailers2", 479),//Trailler Box
		Mod_Class::VehBlips("trailers3", 479),//Trailler Box
		Mod_Class::VehBlips("trailers4", 479),//Trailler Box
		Mod_Class::VehBlips("barracks2", 477),//Truck any---not intrucks
		Mod_Class::VehBlips("scrap", 477),//Truck any---not intrucks
		Mod_Class::VehBlips("towtruck", 477),//Truck any---not intrucks
		Mod_Class::VehBlips("rallytruck", 477),//Truck any---not intrucks
		Mod_Class::VehBlips("brickade", 477),//Truck any---not intrucks
		Mod_Class::VehBlips("firetruk",477),
		Mod_Class::VehBlips("seashark", 471),//Seashark
		Mod_Class::VehBlips("seashark2", 471),//Seashark
		Mod_Class::VehBlips("seashark3", 471),//Seashark
		Mod_Class::VehBlips("limo2", 460),
		Mod_Class::VehBlips("technical", 426),
		Mod_Class::VehBlips("technical3", 426),
		Mod_Class::VehBlips("RHINO", 421),
		Mod_Class::VehBlips("marquis",410),
		Mod_Class::VehBlips("avarus",348),//lost bike
		Mod_Class::VehBlips("chimera",348),//lost bike
		Mod_Class::VehBlips("cliffhanger",348),//lost bike
		Mod_Class::VehBlips("daemon",348),//lost bike
		Mod_Class::VehBlips("daemon2",348),//lost bike
		Mod_Class::VehBlips("gargoyle",348),//lost bike
		Mod_Class::VehBlips("hexer",348),//lost bike
		Mod_Class::VehBlips("innovation",348),//lost bike
		Mod_Class::VehBlips("ratbike",348),//lost bike
		Mod_Class::VehBlips("sanctus",348),//lost bike
		Mod_Class::VehBlips("wolfsbane",348),//lost bike
		Mod_Class::VehBlips("zombiea",348),//lost bike
		Mod_Class::VehBlips("zombieb",348),//lost bike
		Mod_Class::VehBlips("trash",318),
		Mod_Class::VehBlips("trash2",318),
		Mod_Class::VehBlips("jet",307),
		Mod_Class::VehBlips("luxor",307),
		Mod_Class::VehBlips("luxor2",307),
		Mod_Class::VehBlips("miljet",307),
		Mod_Class::VehBlips("nimbus",307),
		Mod_Class::VehBlips("shamal",307),
		Mod_Class::VehBlips("vestra",307),
		Mod_Class::VehBlips("velum",251),
		Mod_Class::VehBlips("velum2",251),
		Mod_Class::VehBlips("stunt",251),
		Mod_Class::VehBlips("mammatus",251),
		Mod_Class::VehBlips("duster",251),
		Mod_Class::VehBlips("dodo",251),
		Mod_Class::VehBlips("cuban800",251),
		Mod_Class::VehBlips("taxi",198),
		Mod_Class::VehBlips("dune",147),
		Mod_Class::VehBlips("stockade",67)
	};
	
	int OhMyBlip(Vehicle vic)
	{
		Mod_Systems::LoggerLight("OhMyBlip");

		int iBeLip = 0;
		if (vic != NULL)
		{
			int iVehClass = VEHICLE::GET_VEHICLE_CLASS(vic);

			if (iVehClass == 14)
				iBeLip = 427;
			else if (iVehClass == 15)
				iBeLip = 64;
			else if (iVehClass == 8)
				iBeLip = 226;
			else if (iVehClass == 16)
				iBeLip = 424;
			else if (iVehClass == 12)
				iBeLip = 616;
			else if (iVehClass == 20)//mule
				iBeLip = 477;
			else if (iVehClass == 10)//trucks
				iBeLip = 477;
			else if (iVehClass == 17)//buss
				iBeLip = 513;
			else if (iVehClass == 7)
				iBeLip = 595;
			else if (iVehClass == 6)
				iBeLip = 523;
			else if (iVehClass == 13)
				iBeLip = 376;
			else
				iBeLip = 225;


			for (int i = 0; i < VehBlips.size(); i++)
			{
				if ((bool)VEHICLE::IS_VEHICLE_MODEL(vic, Mod_Systems::MyHashKey(VehBlips[i].VehicleKey)))
					iBeLip = VehBlips[i].BlipNo;
			}
		}

		return iBeLip;
	}

	Prop FindingProps(Vector3 area, float radius, const std::string& modelHash)
	{
		return OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(area.x, area.y, area.z, radius, Mod_Systems::MyHashKey(modelHash), false, 1, 1);
	}
	Prop FindingProps(Mod_Class::Vector4 area, float radius, const std::string& modelHash)
	{
		return FindingProps(Mod_Maths::NewVector3(area.X, area.Y, area.Z), radius, modelHash);
	}

	Object AddDecals(Vector3 pos, int decalType, float width = 1.0f, float height = 1.0f, float rCoef = 0.1f, float gCoef = 0.1f, float bCoef = 0.1f, float opacity = 1.0f, float timeout = 20.0f)
	{
		return GRAPHICS::ADD_DECAL(decalType, pos.x, pos.y, pos.z, 0, 0, -1.0, 0, 1.0, 0, width, height, rCoef, gCoef, bCoef, opacity, timeout, 0, 0, 0);
	}

	const std::vector<std::string> GunnerSeat = {
		"MOGUL",
		"LIMO2", //><!-- Turreted Limo -->
		"INSURGENT2", //><!-- Insurgent Pick-Up -->
		"INSURGENT3", //><!-- Insurgent Pick-Up Custom -->
		"CARACARA", //>
		"MENACER", //>
		"TECHNICAL", //>
		"TECHNICAL2", //><!-- Technical Aqua -->
		"TECHNICAL3", //><!-- Technical Custom -->
		"HALFTRACK", //>
	};
	
	int FindUSeat(Vehicle vic)
	{
		bool bPass = true;
		for (int i = 0; i < (int)GunnerSeat.size(); i++)
		{
			if (Mod_Systems::MyHashKey(GunnerSeat[i]) == ENTITY::GET_ENTITY_MODEL(vic))
			{
				bPass = false;
				break;
			}
		}

		int Seats;
		if (bPass)
		{
			Seats = 0;
			while (Seats < VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vic))
			{
				if ((bool)VEHICLE::IS_VEHICLE_SEAT_FREE(vic, Seats))
					break;
				else
					Seats++;
			}
		}
		else
		{
			Seats = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vic);
			while (Seats > -1)
			{
				if ((bool)VEHICLE::IS_VEHICLE_SEAT_FREE(vic, Seats))
					break;
				else
					Seats--;
			}
		}

		return Seats;
	}
	void WarptoAnyVeh(Vehicle vic, Ped peddy, int seat)
	{
		Mod_Systems::LoggerLight("WarptoAnyVeh");

		PED::SET_PED_INTO_VEHICLE(peddy, vic, seat);
	}
	void GetOutVehicle(Ped peddy)
	{
		Mod_Systems::LoggerLight("-GetOutVehicle-");

		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(peddy, 0))
			AI::TASK_LEAVE_VEHICLE(peddy, PED::GET_VEHICLE_PED_IS_IN(peddy, true), 4160);
	}
	void EmptyVeh(Vehicle vic)
	{
		Mod_Systems::LoggerLight("PedActions.EmptyVeh");

		if ((bool)ENTITY::DOES_ENTITY_EXIST(vic))
		{
			int Seats = 0;
			while (Seats < VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vic))
			{
				if (!(bool)VEHICLE::IS_VEHICLE_SEAT_FREE(vic, Seats))
					GetOutVehicle(VEHICLE::GET_PED_IN_VEHICLE_SEAT(vic, Seats));
				Seats += 1;
			}
		}
	}
	bool InSameVeh(Ped peddy)
	{
		bool InSame = false;
		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(peddy, 0))
		{
			Vehicle Vic = PED::GET_VEHICLE_PED_IS_IN(peddy, true);
			if ((bool)PED::IS_PED_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), Vic, false))
				InSame = true;
		}
		return InSame;
	}

	void BlipFiler(Blip blippy, int blipType, const std::string& name, int colour)
	{
		UI::SET_BLIP_SPRITE(blippy, blipType);
		UI::SET_BLIP_AS_SHORT_RANGE(blippy, true);
		UI::SET_BLIP_CATEGORY(blippy, 2);
		UI::SET_BLIP_COLOUR(blippy, colour);

		std::string MadeName = " Player: " + name;

		if (name != "")
		{
			UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)MadeName.c_str());
			UI::END_TEXT_COMMAND_SET_BLIP_NAME(blippy);
		}
	}
	Blip PedBlimp(Blip blippy, Ped peddy, int blipType, const std::string& name, int colour, bool heading)
	{
		Mod_Systems::LoggerLight("PedBlimp, blipType == " + std::to_string(blipType) + ", name == " + name + ", colour" + std::to_string(colour));

		EraseBlip(blippy);

		Blip NewBlip = UI::ADD_BLIP_FOR_ENTITY(peddy);;

		BlipFiler(NewBlip, blipType, name, colour);
		if (heading)
			UI::_SET_BLIP_SHOW_HEADING_INDICATOR(NewBlip, true);

		return NewBlip;
	}
	Blip LocalBlip(Blip blippy, Mod_Class::Vector4 local, int blipType, const std::string& name, int colour)
	{
		Mod_Systems::LoggerLight("BuildObjects, blipType == " + std::to_string(blipType) + ", name == " + name);

		EraseBlip(blippy);
		Blip NewBlip = UI::ADD_BLIP_FOR_COORD(local.X, local.Y, local.Z);
		BlipFiler(NewBlip, blipType, name, colour);
		return NewBlip;
	}

	const std::vector<std::string> Mk2Weaps = {
		"WEAPON_pistol_mk2",  //0xBFE256D4",---------19
		"WEAPON_snspistol_mk2",  //0x88374054",---24
		"WEAPON_revolver_mk2",  //0xCB96392F",----29
		"WEAPON_smg_mk2",  //0x78A97CD0",-----40
		"WEAPON_pumpshotgun_mk2",  //0x555AF99A",-----------47
		"WEAPON_assaultrifle_mk2",  //0x394F415C",-------57
		"WEAPON_carbinerifle_mk2",  //0xFAD1F1C9",------59
		"WEAPON_specialcarbine_mk2",  //0x969C3D67",------62
		"WEAPON_bullpuprifle_mk2",  //0x84D6FAFD",----64
		"WEAPON_combatmg_mk2",  //0xDBBD7280",------71
		"WEAPON_heavysniper_mk2",  //0xA914799",---75
		"WEAPON_marksmanrifle_mk2"  //0x6A6C02E0"--77
	};
	
	bool WeaponIsMk2(Hash weapHash)
	{
		bool b = false;
		for (int i = 0; i < Mk2Weaps.size(); i++)
		{
			if (Mod_Systems::MyHashKey(Mk2Weaps[i]) == weapHash)
				b = true;
		}

		return b;
	}

	const std::vector<Mod_Class::AnimatedActions> MaleDance01 = {
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_male^5"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_male^6"),
	};
	const std::vector<Mod_Class::AnimatedActions> MaleDance02 = {
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_male^6")
	};
	const std::vector<Mod_Class::AnimatedActions> MaleDance03 = {
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_male^6")
	};

	const std::vector<Mod_Class::AnimatedActions> FemaleDance01 = {
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_female^6")
	};
	const std::vector<Mod_Class::AnimatedActions> FemaleDance02 = {
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_female^6")
	};
	const std::vector<Mod_Class::AnimatedActions> FemaleDance03 = {
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_female^6")
	};

	bool VehicleEnter = false;

	void GetInVehicle(Ped peddy, Vehicle vic, int seat, bool clearSeat)
	{
		Mod_Systems::LoggerLight("GetInVehicle, seat == " + std::to_string(seat));

		if (clearSeat)
			GetOutVehicle(VEHICLE::GET_PED_IN_VEHICLE_SEAT(vic, seat));

		AI::TASK_ENTER_VEHICLE(peddy, vic, -1, seat, 1.0f, 1, 0);
		WAIT(500);
		while (!(bool)PED::IS_PED_IN_ANY_VEHICLE(peddy, 0))
		{
			if (Mod_Systems::PressAnyKey())
			{
				CAM::DO_SCREEN_FADE_IN(1);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(peddy);//WarptoAnyVeh(vic, peddy, seat);
				break;
			}
			WAIT(1);
		}
	}
	void PlayerEnterVeh(Vehicle vic)
	{
		VehicleEnter = true;
		int iSeats = FindUSeat(vic);
		GetInVehicle(PLAYER::PLAYER_PED_ID(), vic, iSeats, false);
		VehicleEnter = false;
	}
	
	void WalkingStyle(Ped peddy, const std::string& anim)
	{
		PED::SET_PED_MOVEMENT_CLIPSET(peddy, (LPSTR)anim.c_str(), 1.0f);
	}
	void ForceAnim(Ped peddy, const std::string& animDict, const std::string& animName, Vector3 pos, Vector3 rot)
	{
		AI::CLEAR_PED_TASKS(peddy);
		STREAMING::REQUEST_ANIM_DICT((LPSTR)animDict.c_str());
		int iFailed = Mod_Systems::InGameTime() + 5000;
		bool bFine = true;
		while (!STREAMING::HAS_ANIM_DICT_LOADED((LPSTR)animDict.c_str()))
		{
			if (iFailed < Mod_Systems::InGameTime())
			{
				bFine = false;
				break;
			}
			WAIT(1);
		}

		if (bFine)
			AI::TASK_PLAY_ANIM_ADVANCED(peddy, (LPSTR)animDict.c_str(), (LPSTR)animName.c_str(), pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, 8.0f, 0.0f, -1, 0, 0.01f, 0, 0);
		STREAMING::REMOVE_ANIM_DICT((LPSTR)animDict.c_str());
	}
	void ForceAnim(Ped peddy, const std::string& animDict, const std::string& animName, Mod_Class::Vector4 pos)
	{
		ForceAnim(peddy, animDict, animName, Mod_Maths::NewVector3(pos.X, pos.Y, pos.Z), Mod_Maths::NewVector3(0.0f, 0.0f, pos.R));
	}
	void ForceAnim(Ped peddy, Mod_Class::AnimatedActions anim, Mod_Class::Vector4 pos)
	{
		ForceAnim(peddy, anim.Libary, anim.Action, Mod_Maths::NewVector3(pos.X, pos.Y, pos.Z), Mod_Maths::NewVector3(0.0f, 0.0f, pos.R));
	}
	void ForceSenario(const std::string& senareo, Mod_Class::Vector4 pos, bool sitting)
	{
		Ped peddy = PLAYER::PLAYER_PED_ID();
		AI::TASK_START_SCENARIO_AT_POSITION(peddy, (LPSTR)senareo.c_str(), pos.X, pos.Y, pos.Z, pos.R, -1, sitting, true);
		while (true)
		{
			GVM::TopLeft(Mod_Data::RSLangMenu[188]);
			if ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
				break;
			else if (GVM::WhileButtonDown(75))
			{
				AI::CLEAR_PED_TASKS_IMMEDIATELY(peddy);
				AI::CLEAR_PED_TASKS(peddy);
				AI::STOP_ANIM_PLAYBACK(peddy, 0, 0);
				break;
			}
			WAIT(1);
		}
	}
	void AddSenario(Ped peddy, const std::string& senareo, Mod_Class::Vector4 pos)
	{
		AI::TASK_START_SCENARIO_AT_POSITION(peddy, (LPSTR)senareo.c_str(), pos.X, pos.Y, pos.Z, pos.R, -1, true, true);
	}
	void RunAnimSeq(Mod_Class::AnimList animList, Mod_Class::Vector4 pos)
	{
		int Pause = 0;
		Ped PLped = PLAYER::PLAYER_PED_ID();
		ForceAnim(PLped, animList.Start.Libary, animList.Start.Action, pos);
		CAM::DO_SCREEN_FADE_IN(1000);
		while (true)
		{
			if ((int)animList.Middle.size() > 0)
				GVM::TopLeft(Mod_Data::RSLangMenu[212]);
			else
				GVM::TopLeft(Mod_Data::RSLangMenu[188]);

			if (GVM::WhileButtonDown(75) || (bool)ENTITY::IS_ENTITY_DEAD(PLped) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
				break;
			else if (!AI::GET_IS_TASK_ACTIVE(PLped, 134) || GVM::ButtonDown(46))
			{
				if (Pause < Mod_Systems::InGameTime())
				{
					Pause = Mod_Systems::InGameTime() + 2000;
					if ((int)animList.Middle.size() > 0)
					{
						int iBe = Mod_Systems::LessRandomInt("RN_" + animList.Start.Libary, 0, (int)animList.Middle.size() - 1);
						ForceAnim(PLped, animList.Middle[iBe].Libary, animList.Middle[iBe].Action, pos);
					}
					else
						ForceAnim(PLped, animList.Start.Libary, animList.Start.Action, pos);
				}
			}
			WAIT(1);
		}
		ForceAnim(PLped, animList.End.Libary, animList.End.Action, pos);

		Pause = Mod_Systems::InGameTime() + 6000;
		while (AI::GET_IS_TASK_ACTIVE(PLped, 134))
		{
			if (Pause < Mod_Systems::InGameTime())
				break;
			WAIT(1);
		}
		WAIT(2500);
		AI::CLEAR_PED_TASKS_IMMEDIATELY(PLped);
		AI::CLEAR_PED_TASKS(PLped);
		AI::STOP_ANIM_PLAYBACK(PLped, 0, 0);
	}
	void DanceDanceDance(Ped peddy)
	{
		Mod_Class::Vector4 DanceHere = Mod_Maths::GetPosV4(peddy);
		int iRanSpeed = Mod_Systems::LessRandomInt("DanceDanceDance01", 1, 3);
		if (PED::IS_PED_MALE(peddy))
		{
			if (iRanSpeed == 1)
				ForceAnim(peddy, MaleDance01[Mod_Systems::LessRandomInt("DanceDanceM01", 0, (int)MaleDance01.size() - 1)], DanceHere);
			else if (iRanSpeed == 2)
				ForceAnim(peddy, MaleDance02[Mod_Systems::LessRandomInt("DanceDanceM02", 0, (int)MaleDance02.size() - 1)], DanceHere);
			else
				ForceAnim(peddy, MaleDance03[Mod_Systems::LessRandomInt("DanceDanceM03", 0, (int)MaleDance03.size() - 1)], DanceHere);
		}
		else
		{
			if (iRanSpeed == 1)
				ForceAnim(peddy, FemaleDance01[Mod_Systems::LessRandomInt("DanceDanceF01", 0, (int)FemaleDance01.size() - 1)], DanceHere);
			else if (iRanSpeed == 2)
				ForceAnim(peddy, FemaleDance02[Mod_Systems::LessRandomInt("DanceDanceF02", 0, (int)FemaleDance02.size() - 1)], DanceHere);
			else
				ForceAnim(peddy, FemaleDance03[Mod_Systems::LessRandomInt("DanceDanceF03", 0, (int)FemaleDance03.size() - 1)], DanceHere);
		}
	}
	void TakeAChair(Ped peddy, Mod_Class::Vector4 pos)
	{
		pos.R -= 180.0f;
		AddSenario(peddy, "PROP_HUMAN_SEAT_CHAIR", pos);
	}
	void SunningIt(Ped peddy, Mod_Class::Vector4 pos)
	{
		int iTurn = Mod_Systems::LessRandomInt("SunningIt", 1, 5);
		if (iTurn < 3)
		{
			if (PED::IS_PED_MALE(peddy))
				ForceAnim(peddy, Mod_Data::SunbathefrontM.Middle[0].Libary, Mod_Data::SunbathefrontM.Middle[0].Action, pos);
			else
				ForceAnim(peddy, Mod_Data::SunbathefrontF.Middle[0].Libary, Mod_Data::SunbathefrontF.Middle[0].Action, pos);
		}
		else
		{
			if (PED::IS_PED_MALE(peddy))
				ForceAnim(peddy, Mod_Data::SunbathebackM.Middle[0].Libary, Mod_Data::SunbathebackM.Middle[0].Action, pos);
			else
				ForceAnim(peddy, Mod_Data::SunbathebackF.Middle[0].Libary, Mod_Data::SunbathebackF.Middle[0].Action, pos);
		}
	}

	void PlayHorn(Vehicle vic, int duration)
	{
		VEHICLE::START_VEHICLE_HORN(vic, duration, Mod_Systems::MyHashKey("HELDDOWN"), 0);
	}
	int LandingGear(Vehicle vic)
	{
		//	0: Deployed
		//	1 : Closing
		//	2 : Opening
		//	3 : Retracted
		return VEHICLE::_GET_VEHICLE_LANDING_GEAR(vic);
	}
	void LandNearHeli(Ped peddy, Vehicle vic, Vector3 target)
	{
		AI::CLEAR_PED_TASKS(peddy);
		float HeliDesX = target.x;
		float HeliDesY = target.y;
		float HeliDesZ = target.z;
		float HeliSpeed = 35;
		float HeliLandArea = 10;
		Vector3 VHickPos = ENTITY::GET_ENTITY_COORDS(vic, true);
		float dx = VHickPos.x - HeliDesX;
		float dy = VHickPos.y - HeliDesY;

		float HeliDirect = GAMEPLAY::GET_HEADING_FROM_VECTOR_2D(dx, dy) - 180.00f;

		VEHICLE::_SET_VEHICLE_LANDING_GEAR(vic, 2);
		AI::TASK_HELI_MISSION(peddy, vic, 0, 0, HeliDesX, HeliDesY, HeliDesZ, 20, HeliSpeed, HeliLandArea, HeliDirect, -1, -1, -1, 32);

		//PED::SET_PED_FIRING_PATTERN(Peddy, Mod_Systems::MyHashKey("FIRING_PATTERN_BURST_FIRE_HELI"));

		PED::SET_PED_KEEP_TASK(peddy, true);
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(peddy, true);
	}
	void LandNearPlane(Ped peddy, Vehicle vic, Vector3 start, Vector3 finish)
	{
		AI::CLEAR_PED_TASKS(peddy);
		AI::TASK_PLANE_LAND(peddy, vic, start.x, start.y, start.z, finish.x, finish.y, finish.z);
		PED::SET_PED_KEEP_TASK(peddy, true);
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(peddy, true);
	}

	void WalkHere(Ped peddy, Mod_Class::Vector4 dest)
	{
		AI::CLEAR_PED_TASKS(peddy);
		AI::TASK_FOLLOW_NAV_MESH_TO_COORD(peddy, dest.X, dest.Y, dest.Z, 1.0, -1, 0.0, false, 0.0);
		PED::SET_PED_KEEP_TASK(peddy, true);
	}
	void RunHere(Ped peddy, Vector3 dest)
	{
		AI::CLEAR_PED_TASKS(peddy);
		AI::TASK_FOLLOW_NAV_MESH_TO_COORD(peddy, dest.x, dest.y, dest.z, 2.0, -1, 0.0, false, 0.0);
		PED::SET_PED_KEEP_TASK(peddy, true);
	}
	void DriveAround(Ped peddy)
	{
		AI::CLEAR_PED_TASKS(peddy);
		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(peddy, 0))
		{
			if (peddy == VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_USING(peddy), -1))
			{
				Vehicle Vick = PED::GET_VEHICLE_PED_IS_IN(peddy, false);

				AI::TASK_VEHICLE_DRIVE_WANDER(peddy, Vick, 25, 262972);
				PED::SET_PED_KEEP_TASK(peddy, true);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(peddy, true);
			}
		}

	}
	void DriveToooPed(Ped peddy, Ped target, bool runOver)
	{
		AI::CLEAR_PED_TASKS(peddy);
		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(peddy, 0))
		{
			if (peddy == VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_USING(peddy), -1))
			{
				Vector3 PlayerPos = ENTITY::GET_ENTITY_COORDS(target, true);
				Vehicle Vick = PED::GET_VEHICLE_PED_IS_IN(peddy, false);
				if (runOver)
					AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(peddy, Vick, PlayerPos.x, PlayerPos.y, PlayerPos.z, 45, 262972, 0);
				else
					AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(peddy, Vick, PlayerPos.x, PlayerPos.y, PlayerPos.z, 25, 262972, 0);

				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(peddy, true);
			}
		}
	}
	void DriveBye(Ped peddy, Ped target, int vehType)
	{
		AI::CLEAR_PED_TASKS(peddy);
		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(peddy, 0))
		{
			if (peddy == VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_USING(peddy), -1))
			{
				if ((bool)PED::IS_PED_IN_ANY_VEHICLE(target, 0))
					AI::TASK_VEHICLE_CHASE(peddy, target);
				else
					DriveToooPed(peddy, target, true);
			}

			AI::TASK_VEHICLE_SHOOT_AT_PED(peddy, target, 5);

			bool blocking = false;
			if (vehType == 6)
				blocking = true;
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(peddy, blocking);
		}
	}
	void FlyHeli(Ped peddy, Vehicle vic, Vector3 dest, float speed, float landing)
	{
		ENTITY::FREEZE_ENTITY_POSITION(vic, false);
		AI::CLEAR_PED_TASKS(peddy);
		float HeliDesX = dest.x;
		float HeliDesY = dest.y;
		float HeliDesZ = dest.z;
		float HeliSpeed = speed;
		float HeliLandArea = landing;

		Vector3 VHickPos = Mod_Maths::EntPosition(vic);

		float dx = VHickPos.x - HeliDesX;
		float dy = VHickPos.y - HeliDesY;
		float HeliDirect = GAMEPLAY::GET_HEADING_FROM_VECTOR_2D(dx, dy) - 180.00f;

		AI::TASK_HELI_MISSION(peddy, vic, 0, 0, HeliDesX, HeliDesY, HeliDesZ, 9, HeliSpeed, HeliLandArea, HeliDirect, -1, -1, -1, 0);
		PED::SET_PED_FIRING_PATTERN(peddy, Mod_Systems::MyHashKey("FIRING_PATTERN_BURST_FIRE_HELI"));
		PED::SET_PED_KEEP_TASK(peddy, true);
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(peddy, true);
	}
	void FlyPlane(Ped peddy, Vehicle vic, Vector3 dest)
	{
		float fAngle = Mod_Maths::GetAngle(ENTITY::GET_ENTITY_COORDS(vic, true), dest);
		AI::CLEAR_PED_TASKS(peddy);

		AI::TASK_PLANE_MISSION(peddy, vic, 0, 0, dest.x, dest.y, dest.z, 6, 20, 50, fAngle, 50, 1);

		PED::SET_PED_KEEP_TASK(peddy, true);
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(peddy, true);
	}
	void DriveToooDest(Ped peddy, Vector3 dest, float speed)
	{
		AI::CLEAR_PED_TASKS(peddy);
		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(peddy, 0))
		{
			Vehicle Vick = PED::GET_VEHICLE_PED_IS_IN(peddy, false);
			if (peddy == VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_USING(peddy), -1))
			{
				AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(peddy, Vick, dest.x, dest.y, dest.z, speed, 262972, 1);
				PED::SET_PED_KEEP_TASK(peddy, true);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(peddy, true);
			}
		}
	}
	void DriveDirect(Ped peddy, Vector3 dest, float speed)
	{
		AI::CLEAR_PED_TASKS(peddy);
		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(peddy, 0))
		{
			Vehicle Vick = PED::GET_VEHICLE_PED_IS_IN(peddy, false);
			if (peddy == VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_USING(peddy), -1))
			{
				AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(peddy, Vick, dest.x, dest.y, dest.z, speed, 16777216, 1);
				PED::SET_PED_KEEP_TASK(peddy, true);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(peddy, true);
			}
		}
	}

	void FightPlayer(Ped peddy, bool inVeh, int vehType)
	{
		Ped Player = PLAYER::PLAYER_PED_ID();
		PED::REMOVE_PED_FROM_GROUP(peddy);
		PED::SET_PED_RELATIONSHIP_GROUP_HASH(peddy, Mod_Data::GP_Attack);
		PED::SET_PED_FLEE_ATTRIBUTES(peddy, 0, 1);
		PED::SET_PED_COMBAT_ATTRIBUTES(peddy, 46, 1);
		if (!inVeh)
			AI::TASK_COMBAT_PED(peddy, Player, 0, 16);
		else
			DriveBye(peddy, Player, vehType);
	}
	void GreefWar(Ped peddy, Ped target)
	{
		if (target != NULL)
		{
			AI::CLEAR_PED_TASKS(peddy);
			PED::SET_PED_FLEE_ATTRIBUTES(peddy, 0, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(peddy, 46, true);

			AI::TASK_COMBAT_PED(peddy, target, 0, 16);
		}
	}
	void JogOn(const std::vector<Mod_Class::Vector4>& destList, int start)
	{
		MoveEntity(PLAYER::PLAYER_PED_ID(), destList[start]);
		while (true)
		{
			GVM::TopLeft(Mod_Data::RSLangMenu[188]);
			if (GVM::WhileButtonDown(75) || (bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
				break;
			else if (Mod_Maths::DistanceTo(PLAYER::PLAYER_PED_ID(), destList[start]) < 3.0f)
			{
				start++;
				if (start == destList.size())
					start = 0;

				RunHere(PLAYER::PLAYER_PED_ID(), Mod_Maths::NewVector3(destList[start].X, destList[start].Y, destList[start].Z));
			}
			WAIT(1);
		}
		ForceSenario("WORLD_HUMAN_JOG_STANDING", Mod_Maths::PlayerV4(), false);
		WAIT(4000);
		AI::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
	}
	void Drive_Fly_On(Ped peddy, Vehicle vic, const std::vector<Mod_Class::Vector4>& destList, bool plane, bool heli, bool playerDrives, int start)
	{
		if (plane)
			FlyPlane(peddy, vic, Mod_Maths::NewVector3(destList[start].X, destList[start].Y, destList[start].Z));
		else if (heli)
			FlyHeli(peddy, vic, Mod_Maths::NewVector3(destList[start].X, destList[start].Y, destList[start].Z), 45.0f, 5.0f);
		else
			DriveToooDest(peddy, Mod_Maths::NewVector3(destList[start].X, destList[start].Y, destList[start].Z), 25.0f);

		float fDis = 3.0f;
		if (heli || plane)
			fDis = 30.0f;
		while (true)
		{
			if (playerDrives)
			{
				GVM::TopLeft(Mod_Data::RSLangMenu[188]);
				if (GVM::WhileButtonDown(75) || (bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
					break;
			}

			if (Mod_Maths::DistanceTo(PLAYER::PLAYER_PED_ID(), vic) > 50.0f)
				break;

			if (Mod_Maths::DistanceTo(vic, destList[start]) < fDis)
			{
				start++;
				if (start == destList.size())
					start = 0;

				if (plane)
					FlyPlane(peddy, vic, Mod_Maths::NewVector3(destList[start].X, destList[start].Y, destList[start].Z));
				else if (heli)
				{
					if (destList.size() == 2)
					{
						LandNearHeli(peddy, vic, Mod_Maths::NewVector3(destList[1].X, destList[1].Y, destList[1].Z));
						break;
					}
					else
						FlyHeli(peddy, vic, Mod_Maths::NewVector3(destList[start].X, destList[start].Y, destList[start].Z), 45.0f, 5.0f);
				}
				else
					DriveToooDest(peddy, Mod_Maths::NewVector3(destList[start].X, destList[start].Y, destList[start].Z), 25.0f);
			}
			WAIT(1);
		}

		if (playerDrives)
			AI::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
	}
	void MethEdd(bool act)
	{
		if (act)
		{
			int iTenPass = 10;
			GRAPHICS::SET_TIMECYCLE_MODIFIER("DRUG_gas_huffin");
			while (!STREAMING::HAS_ANIM_SET_LOADED("move_m@drunk@moderatedrunk") || iTenPass < 0)
			{
				iTenPass -= 1;
				STREAMING::REQUEST_ANIM_SET("move_m@drunk@moderatedrunk");
				WAIT(100);
			}
			PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), "move_m@drunk@moderatedrunk", 1.00f);
		}
		else
		{
			GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
			PED::RESET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), 0.0f);
		}
	}

	void GunningIt(Ped peddy, std::vector<Mod_Class::WeaponSaver>& gunList)
	{
		Mod_Systems::LoggerLight("GunningIt GunsGunsGuns ");

		WEAPON::REMOVE_ALL_PED_WEAPONS(peddy, true);
		for (int i = 0; i < (int)gunList.size(); i++)
		{
			Hash NewWeap = Mod_Systems::MyHashKey(gunList[i].MyWeapon);
			WEAPON::GIVE_WEAPON_TO_PED(peddy, NewWeap, 0, false, true);
			WEAPON::SET_CURRENT_PED_WEAPON(peddy, NewWeap, true);
			for (int j = 0; j < (int)gunList[i].MyAddons.size(); j++)
			{
				Hash MyAdon = Mod_Systems::MyHashKey(gunList[i].MyAddons[j]);
				if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(NewWeap, MyAdon))
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(peddy, NewWeap, MyAdon);

			}
			if (WeaponIsMk2(NewWeap))
				WAIT(750);

			WEAPON::SET_AMMO_IN_CLIP(peddy, NewWeap, WEAPON::GET_MAX_AMMO_IN_CLIP(peddy, NewWeap, true));
			WEAPON::SET_PED_AMMO(peddy, NewWeap, gunList[i].Ammo);
			WEAPON::SET_PED_WEAPON_TINT_INDEX(peddy, NewWeap, gunList[i].WeapTint);
		}
		WEAPON::SET_CURRENT_PED_WEAPON(peddy, -1569615261, true);
	}
	void GunningIt(Ped peddy, int gun)
	{
		Mod_Systems::LoggerLight("GunningIt Gun == " + std::to_string(gun));

		std::vector<std::string> WeapList = {};

		if (gun == 1)
		{
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt01", 1, 17)]);//Meelee
		}
		else if (gun == 2)
		{
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt02", 18, 37)]);//HandGuns
		}
		else if (gun == 3)
		{
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt01", 1, 17)]);//Meelee
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt02", 18, 37)]);//HandGuns
		}
		else if (gun == 4)
		{
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt04", 46, 55)]);//ShotGun
		}
		else if (gun == 5)
		{
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt01", 1, 17)]);//Meelee
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt02", 18, 37)]);//HandGuns
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt07", 73, 78)]);//sniper
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt08", 79, 87)]);//Heavey
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt09", 88, 94)]);//throw
		}
		else if (gun == 6)
		{
			WeapList.push_back("WEAPON_golfclub");//golf
		}
		else if (gun == 7)
		{
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt01", 1, 17)]);//Meelee
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt03", 38, 45)]);//Smg
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt05", 56, 68)]);//riflles
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt06", 69, 72)]);//Mg
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt07", 73, 78)]);//sniper
		}
		else if (gun == 8)
		{
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt07", 73, 78)]);//sniper
		}
		else if (gun == 9)
		{
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt01", 1, 17)]);//Meelee
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt02", 18, 37)]);//HandGuns
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt03", 38, 45)]);//Smg
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt04", 46, 55)]);//ShotGun
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt05", 56, 68)]);//riflles
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt06", 69, 72)]);//Mg
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt07", 73, 78)]);//sniper
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt08", 79, 87)]);//Heavey
			WeapList.push_back(Mod_Data::Weapons_List[Mod_Systems::LessRandomInt("GunIt09", 88, 94)]);//throw
		}
		else if (gun == 10)
		{
			WeapList.push_back("WEAPON_raypistol");  //0xAF3696A1",--36
			WeapList.push_back("WEAPON_raycarbine");  //0x476BF155"--44
			WeapList.push_back("weapon_rayminigun");
		}
		else if (gun == 50)
			GunningIt(peddy, Mod_Data::Player_Weaps);

		for (int i = 0; i < WeapList.size(); i++)
			WEAPON::GIVE_WEAPON_TO_PED(peddy, Mod_Systems::MyHashKey(WeapList[i]), 9999, false, true);
	}

	void MaxOutAllModsNoWheels(Vehicle vic, int vehType)
	{
		Mod_Systems::LoggerLight("MaxOutAllModsNoWheels");

		VEHICLE::SET_VEHICLE_MOD_KIT(vic, 0);
		for (int i = 0; i < 50; i++)
		{
			int Spoilher = VEHICLE::GET_NUM_VEHICLE_MODS(vic, i);

			if (i == 18 || i == 22 || i == 23 || i == 24)
			{

			}
			else
			{
				Spoilher -= 1;
				VEHICLE::SET_VEHICLE_MOD(vic, i, Spoilher, true);
			}
		}

		if (vehType != 13 && vehType != 14 && vehType != 15 && vehType != 16)
		{
			VEHICLE::TOGGLE_VEHICLE_MOD(vic, 18, true);
			VEHICLE::TOGGLE_VEHICLE_MOD(vic, 22, true);
		}
		else if (vehType == 15 || vehType == 16)
			VEHICLE::_SET_VEHICLE_LANDING_GEAR(vic, 3);
	}
	void MakeModsNotWar(Vehicle vic, std::vector<int>* modsList)
	{
		Mod_Systems::LoggerLight("MakeModsNotWar");

		VEHICLE::SET_VEHICLE_MOD_KIT(vic, 0);

		for (int i = 0; i < modsList->size(); i++)
		{
			if (modsList->at(i) == -10)
			{

			}
			else if (i == 48)
			{
				int Spoilher = -1;
				if (modsList->at(i) == -1)
				{
					Spoilher = VEHICLE::GET_NUM_VEHICLE_MODS(vic, i) - 1;
					if (Spoilher < 1)
						Spoilher = VEHICLE::GET_VEHICLE_LIVERY_COUNT(vic) - 1;

					if (Spoilher > 0)
					{
						modsList->at(i) = Mod_Systems::RandomInt(0, Spoilher);
					}
				}

				if (Spoilher > -1 || modsList->at(i) > -1)
				{
					VEHICLE::SET_VEHICLE_LIVERY(vic, modsList->at(i));
					VEHICLE::SET_VEHICLE_MOD(vic, i, modsList->at(i), true);
				}
			}
			else if (i == 66)
			{
				if (modsList->at(i) == -1)
				{
					int CheckHere = Mod_Systems::RandomInt(0, 159);
					modsList->at(i) = CheckHere;
				}
			}
			else if (i == 67)
			{
				if (modsList->at(i) == -1)
				{
					int CheckHere = Mod_Systems::RandomInt(0, 159);
					VEHICLE::SET_VEHICLE_COLOURS(vic, modsList->at(i - 1), CheckHere);
				}
				else
				{
					VEHICLE::SET_VEHICLE_COLOURS(vic, modsList->at(i - 1), modsList->at(i));
				}
			}
			else if (modsList->at(i) == -1)
			{
				int Spoilher = VEHICLE::GET_NUM_VEHICLE_MODS(vic, i) - 1;
				if (Spoilher > 0)
				{
					int CheckHere = Mod_Systems::RandomInt(0, Spoilher);
					VEHICLE::SET_VEHICLE_MOD(vic, i, CheckHere, true);
				}
			}
			else
			{
				VEHICLE::SET_VEHICLE_MOD(vic, i, modsList->at(i), true);
			}
		}
	}

	void PoliceAcadamy(bool togg)
	{
		if (togg)
		{
			PED::SET_PED_AS_COP(PLAYER::PLAYER_PED_ID(), togg);
			//PLAYER::_0xDC64D2C53493ED12(PLAYER::PLAYER_ID());
			PED::SET_PED_RELATIONSHIP_GROUP_HASH(PLAYER::PLAYER_PED_ID(), Mod_Systems::MyHashKey("COP"));
		}
		else if (!Mod_Data::Mod_Settings.Saved_Ped && !Mod_Data::Mod_Settings.Random_Ped)
			SavedPlayer(&Mod_Data::SavedPeds[0], 50);
		PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), togg);
	}

	Mod_Class::ClothX MaleDefault = Mod_Class::ClothX("AAA_M_Epslon_0", { 0, 0, 0, 8, 104, 0, 20, 129, 15, 0, 0, 272 }, { 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0 }, { -1, -1, -1, -1, -1 }, { -1, -1, -1, -1, -1 });
	Mod_Class::ClothX FemaleDefault = Mod_Class::ClothX("AAA_F_Epsilon_0", { 21, 0, 0, 3, 111, 0, 29, 99, 6, 0, 0, 285 }, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }, { -1, -1, -1, -1, -1 }, { -1, -1, -1, -1, -1 });

	std::vector<Mod_Class::ClothX> XmasOut_M = {
		Mod_Class::ClothX("MaleFestiveWinter Pajamas", { 0, 0, -1, 1, 32, 0, 4, 0, 15, 0, 0, 52}, { 0, 0, -1, 0, 2, 0, 1, 0, 0, 0, 0, 2}, { 44, -1, -1, -1, -1}, { 1, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleFestiveThe Pudding", { 0, 0, -1, 1, 26, 0, 12, 0, 15, 0, 0, 51}, { 0, 0, -1, 0, 3, 0, 8, 0, 0, 0, 0, 2}, { 41, -1, -1, -1, -1}, {0,-1,-1, -1, -1}),
		Mod_Class::ClothX("MaleFestiveThe Elf", {0, 0, -1, 1, 26, 0, 17, 34, 15, 0, 0, 51}, { 0, 0, -1, 0, 3, 0, 0, 0, 0, 0, 0, 1}, { 42, -1, -1, -1, -1}, { 2, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleFestiveThe Claus", {0, 0, -1, 1, 3, 0, 4, 0, 15, 0, 0, 51}, { 0, 0, -1, 0, 0, 0, 4, 0, 0, 0, 0, 0}, { 40, -1, -1, -1, -1}, { 6, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleFestiveStripy Pajamas", {0, 0, -1, 1, 32, 0, 17, 0, 15, 0, 0, 52}, { 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, { 42, -1, -1, -1, -1}, { 0, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleFestiveRed Pajamas", {0, 0, -1, 1, 32, 0, 4, 34, 15, 0, 0, 52}, { 0, 0, -1, 0, 0, 0, 2, 0, 0, 0, 0, 0}, { 40, -1, -1, -1, -1}, { 3, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleFestiveFestive Pajamas", {0, 0, -1, 1, 32, 0, 4, 34, 15, 0, 0, 52}, { 0, 0, -1, 0, 3, 0, 0, 3, 0, 0, 0, 3}, { 43, -1, -1, -1, -1}, { 3, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleSanta CostumesFilthy Santa Costume", { 0, 0, -1, 61, 57, 0, 39, 0, 15, 0, 0, 116}, { 0, 0, -1, 0, 2, 0, 0, 0, 0, 0, 0, 2}, { -1, -1, -1, -1, -1}, { -1, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleSanta CostumesDirty Santa Costume", { 0, 0, -1, 50, 57, 0, 39, 0, 15, 0, 0, 116}, { 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, { -1, -1, -1, -1, -1}, { -1, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleSanta CostumesBad Santa Costume", { 0, 0, -1, 50, 57, 0, 39, 0, 15, 0, 0, 116}, { 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, { -1, -1, -1, -1, -1}, { -1, -1, -1, -1, -1})
	};
	std::vector<Mod_Class::ClothX> XmasOut_F = {
		Mod_Class::ClothX("FemaleFestiveWinter Pajamas", {0, 0, -1, 3, 31, 0, 2, 0, 3, 0, 0, 45}, { 0, 0, -1, 0, 2, 0, 5, 0, 0, 0, 0, 2}, { 43, -1, -1, -1, -1}, { 1, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleFestiveThe Pudding", {0, 0, -1, 3, 0, 0, 22, 0, 3, 0, 0, 44}, { 0, 0, -1, 0, 7, 0, 0, 0, 0, 0, 0, 2}, { 40, -1, -1, -1, -1}, { 0, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleFestiveThe Elf", {0, 0, -1, 3, 27, 0, 17, 17, 3, 0, 0, 44}, { 0, 0, -1, 0, 2, 0, 0, 0, 0, 0, 0, 1}, { 41, -1, -1, -1, -1}, { 2, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleFestiveThe Claus", {0, 0, -1, 3, 2, 0, 2, 0, 3, 0, 0, 44}, { 0, 0, -1, 0, 0, 0, 13, 0, 0, 0, 0, 0}, { 39, -1, -1, -1, -1}, { 6, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleFestiveStripy Pajamas", {0, 0, -1, 3, 31, 0, 17, 0, 3, 0, 0, 45}, { 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, { 41, -1, -1, -1, -1}, { 0, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleFestiveRed Pajamas", {0, 0, -1, 3, 31, 0, 2, 17, 3, 0, 0, 45}, { 0, 0, -1, 0, 0, 0, 13, 0, 0, 0, 0, 0}, { 39, -1, -1, -1, -1}, { 3, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleFestiveFestive Pajamas",{ 0, 0, -1, 3, 31, 0, 2, 17, 3, 0, 0, 45}, { 0, 0, -1, 0, 3, 0, 13, 2, 0, 0, 0, 3}, { 42, -1, -1, -1, -1}, { 3, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleSanta CostumesFilthy Santa Costume", { 0, 0, -1, 65, 59, 0, 40, 0, 1, 0, 0, 108}, { 0, 0, -1, 0, 2, 0, 0, 0, 2, 0, 0, 2}, { -1, -1, -1, -1, -1}, { -1, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleSanta CostumesDirty Santa Costume", { 0, 0, -1, 52, 59, 0, 40, 0, 1, 0, 0, 108}, { 0, 0, -1, 0, 1, 0, 0, 0, 2, 0, 0, 1}, { -1, -1, -1, -1, -1}, { -1, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleSanta CostumesBad Santa Costume", { 0, 0, -1, 52, 59, 0, 40, 0, 1, 0, 0, 108}, { 0, 0, -1, 0, 0, 0, 0, 0, 2, 0, 0, 0}, { -1, -1, -1, -1, -1}, { -1, -1, -1, -1, -1})
	};
	std::vector<std::string> FindCloths(Hash UserName)
	{
		Mod_Systems::LoggerLight("-FindCloths-");
		std::vector<std::string> Files = {};
		std::string OutputFolder;
		
		bool GotDir = false;
		if (UserName == MainProtags[0])//michael
		{
			OutputFolder = DirectOutfitMichael;
			if (std::filesystem::exists(OutputFolder) && std::filesystem::is_directory(OutputFolder))
				GotDir = true;
		}
		else if (UserName == MainProtags[1])//frank
		{
			OutputFolder = DirectOutfitFranklin;
			if (std::filesystem::exists(OutputFolder) && std::filesystem::is_directory(OutputFolder))
				GotDir = true;
		}
		else if (UserName == MainProtags[2])//trev
		{
			OutputFolder = DirectOutfitTrevor;
			if (std::filesystem::exists(OutputFolder) && std::filesystem::is_directory(OutputFolder))
				GotDir = true;
		}
		else if (UserName == MainProtags[3])//male
		{
			OutputFolder = DirectOutfitMale;
			if (std::filesystem::exists(OutputFolder) && std::filesystem::is_directory(OutputFolder))
				GotDir = true;
		}
		else if (UserName == MainProtags[4])//female
		{
			OutputFolder = DirectOutfitFemale;
			if (std::filesystem::exists(OutputFolder) && std::filesystem::is_directory(OutputFolder))
				GotDir = true;
		}
		else
		{
			OutputFolder = DirectOutfitFolder + "/ModHash" + std::to_string(UserName);
			if (std::filesystem::exists(OutputFolder) && std::filesystem::is_directory(OutputFolder))
				GotDir = true;
		}

		if (GotDir)
		{
			for (const auto& entry : std::filesystem::directory_iterator(OutputFolder))
				Files.push_back(entry.path().string());
		}

		return Files;
	}
	Mod_Class::ClothX LoadCloths(const std::string& file)
	{
		Mod_Systems::LoggerLight("-LoadCloths-");
		std::string Cloths = "";
		std::vector<int> ClothA = {}, ClothB = {}, ExtraA = {}, ExtraB = {};
		int intList = 0;

		std::vector<std::string> MyColect = Mod_Systems::Read_ini(file);

		for (int i = 0; i < MyColect.size(); i++)
		{
			std::string line = MyColect[i];
			if (Mod_Systems::Contains_string("Title", line))
			{
				Cloths = Mod_Systems::Remove_char61(line);
			}
			else if (Mod_Systems::Contains_string("[ClothA]", line))
			{
				intList = 1;
			}
			else if (Mod_Systems::Contains_string("[ClothB]", line))
			{
				intList = 2;
			}
			else if (Mod_Systems::Contains_string("[ExtraA]", line))
			{
				intList = 3;
			}
			else if (Mod_Systems::Contains_string("[ExtraB]", line))
			{
				intList = 4;
			}
			else if (intList == 1)
			{
				ClothA.push_back(Mod_Systems::Convert_to_int(line));
			}
			else if (intList == 2)
			{
				int iSpot = Mod_Systems::Convert_to_int(line);
				if (iSpot < 0)
					iSpot = 0;
				ClothB.push_back(iSpot);
			}
			else if (intList == 3)
			{
				ExtraA.push_back(Mod_Systems::Convert_to_int(line));
			}
			else if (intList == 4)
			{
				int iSpot = Mod_Systems::Convert_to_int(line);
				if (iSpot < 0)
					iSpot = 0;
				ExtraB.push_back(iSpot);
			}
		}

		for (int i = 4; i < (int)ExtraA.size(); i++)
			ExtraA.pop_back();

		for (int i = 4; i < (int)ExtraB.size(); i++)
			ExtraB.pop_back();

		return Mod_Class::ClothX(Cloths, ClothA, ClothB, ExtraA, ExtraB);
	}
	Mod_Class::ClothX GetCloths(bool male)
	{
		Mod_Systems::LoggerLight("-GetCloths-");

		Mod_Class::ClothX cothing = FemaleDefault;
		Hash PlayerH = MainProtags[4];
		if (male)
		{
			cothing = MaleDefault;
			PlayerH = MainProtags[3];
		}
		std::vector<std::string> Files = FindCloths(PlayerH);

		if ((int)Files.size() > 0)
		{
			int iRando = 0;
			if (male)
				iRando = Mod_Systems::LessRandomInt("Outfits_01", 0, (int)Files.size() - 1);
			else
				iRando = Mod_Systems::LessRandomInt("Outfits_02", 0, (int)Files.size() - 1);

			cothing = LoadCloths(Files[iRando]);
		}

		return cothing;
	}

	int SizeUpHairList(bool male)
	{
		if (male)
			return (int)MHairsets.size() - 1;
		else
			return (int)FHairsets.size() - 1;
	}
	Mod_Class::HairSets PickAStyle(int style, bool male)
	{
		if (male)
			return MHairsets[style];
		else
			return FHairsets[style];
	}
	Mod_Class::HairSets PickAStyle(bool male)
	{
		return PickAStyle(male, Mod_Systems::LessRandomInt("PickAStyle0" + std::to_string(male), 0, SizeUpHairList(male)));
	}
	Mod_Class::FaceBank AddFace(bool male)
	{
		int ShapeFirstID;
		int ShapeSecondID;
		if (male)
		{
			ShapeFirstID = Mod_Systems::LessRandomInt("AddFaceM01", 0, 20);
			ShapeSecondID = Mod_Systems::LessRandomInt("AddFaceM01", 0, 20);
		}
		else
		{
			ShapeFirstID = Mod_Systems::LessRandomInt("AddFaceF01", 21, 41);
			ShapeSecondID = Mod_Systems::LessRandomInt("AddFaceF01", 21, 41);
		}

		float ShapeMix = Mod_Systems::RandomFloat(-0.9, 0.9);
		float SkinMix = Mod_Systems::RandomFloat(0.9, 0.99);
		float ThirdMix = Mod_Systems::RandomFloat(-0.9, 0.9);

		return Mod_Class::FaceBank(ShapeFirstID, ShapeSecondID, ShapeMix, SkinMix, ThirdMix);
	}
	std::vector<Mod_Class::FreeOverLay> AddOverLay(bool male, bool freemode)
	{
		Mod_Systems::LoggerLight("AddOverLay");

		std::vector<Mod_Class::FreeOverLay> YourOver = {};
		if (freemode)
		{
			for (int i = 0; i < 12; i++)
			{
				int iColour = 0;
				int iChange = Mod_Systems::RandomInt(0, PED::_GET_NUM_HEAD_OVERLAY_VALUES(i));
				float fVar = Mod_Systems::RandomFloat(0.45, 0.99);

				if (i == 0)
				{
					iChange = Mod_Systems::RandomInt(0, iChange);
				}//Blemishes
				else if (i == 1)
				{
					if (male)
						iChange = Mod_Systems::RandomInt(0, iChange);
					else
						iChange = 255;
					iColour = 1;
				}//Facial Hair
				else if (i == 2)
				{
					iChange = Mod_Systems::RandomInt(0, iChange);
					iColour = 1;
				}//Eyebrows
				else if (i == 3)
				{
					iChange = 255;
				}//Ageing
				else if (i == 4)
				{
					int iFace = Mod_Systems::RandomInt(0, 50);
					if (iFace < 30)
					{
						iChange = Mod_Systems::RandomInt(0, 15);
					}
					else if (iFace < 45)
					{
						iChange = Mod_Systems::RandomInt(0, iChange);
						fVar = Mod_Systems::RandomFloat(0.85f, 0.99f);
					}
					else
						iChange = 255;
				}//Makeup
				else if (i == 5)
				{
					if (!male)
					{
						iChange = Mod_Systems::RandomInt(0, iChange);
						fVar = Mod_Systems::RandomFloat(0.15f, 0.39f);
					}
					else
						iChange = 255;
					iColour = 2;
				}//Blush
				else if (i == 6)
				{
					iChange = Mod_Systems::RandomInt(0, iChange);
				}//Complexion
				else if (i == 7)
				{
					iChange = 255;
				}//Sun Damage
				else if (i == 8)
				{
					if (!male)
						iChange = Mod_Systems::RandomInt(0, iChange);
					else
						iChange = 255;
					iColour = 2;
				}//Lipstick
				else if (i == 9)
				{
					iChange = Mod_Systems::RandomInt(0, iChange);
				}//Moles/Freckles
				else if (i == 10)
				{
					if (male)
						iChange = Mod_Systems::RandomInt(0, iChange);
					else
						iChange = 255;
					iColour = 1;
				}//Chest Hair
				else if (i == 11)
				{
					iChange = Mod_Systems::RandomInt(0, iChange);
				}//Body Blemishes

				int AddColour = -1;

				if (iColour > 0)
					AddColour = Mod_Systems::RandomInt(0, 64);

				YourOver.push_back(Mod_Class::FreeOverLay(iColour, iChange, AddColour, fVar));
			}

		}

		return YourOver;
	}
	std::vector<Mod_Class::Tattoo> AddRandTats(bool male)
	{
		Mod_Systems::LoggerLight("AddRandTats");
		std::vector<Mod_Class::Tattoo> Tatlist = {};

		if (male)
		{
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::maleTats01[Mod_Systems::RandomInt(0, (int)Mod_Data::maleTats01.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::maleTats02[Mod_Systems::RandomInt(0, (int)Mod_Data::maleTats02.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::maleTats03[Mod_Systems::RandomInt(0, (int)Mod_Data::maleTats03.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::maleTats04[Mod_Systems::RandomInt(0, (int)Mod_Data::maleTats04.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::maleTats05[Mod_Systems::RandomInt(0, (int)Mod_Data::maleTats05.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::maleTats06[Mod_Systems::RandomInt(0, (int)Mod_Data::maleTats06.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::maleTats07[Mod_Systems::RandomInt(0, (int)Mod_Data::maleTats07.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::maleTats08[Mod_Systems::RandomInt(0, (int)Mod_Data::maleTats08.size() - 1)];
				Tatlist.push_back(T);
			}
		}
		else
		{
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::femaleTats01[Mod_Systems::RandomInt(0, (int)Mod_Data::femaleTats01.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::femaleTats02[Mod_Systems::RandomInt(0, (int)Mod_Data::femaleTats02.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::femaleTats03[Mod_Systems::RandomInt(0, (int)Mod_Data::femaleTats03.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::femaleTats04[Mod_Systems::RandomInt(0, (int)Mod_Data::femaleTats04.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::femaleTats05[Mod_Systems::RandomInt(0, (int)Mod_Data::femaleTats05.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::femaleTats06[Mod_Systems::RandomInt(0, (int)Mod_Data::femaleTats06.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::femaleTats07[Mod_Systems::RandomInt(0, (int)Mod_Data::femaleTats07.size() - 1)];
				Tatlist.push_back(T);
			}
			if (Mod_Systems::RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = Mod_Data::femaleTats08[Mod_Systems::RandomInt(0, (int)Mod_Data::femaleTats08.size() - 1)];
				Tatlist.push_back(T);
			}
		}

		return Tatlist;
	}
	Mod_Class::ClothBank NewFreeModePed(int male)
	{
		if (male == 0)
		{
			bool bMale = true;
			std::string Model = "mp_m_freemode_01";
			Mod_Class::ClothX Cothing = GetCloths(bMale);
			Mod_Class::HairSets MyHair = PickAStyle(bMale);
			return Mod_Class::ClothBank("", Model, Mod_Systems::MyHashKey(Model), true, AddFace(bMale), bMale, false, MyHair, Mod_Systems::RandomInt(1, 61), Mod_Systems::RandomInt(1, 61), Mod_Systems::RandomInt(0, 10), 0, {}, AddOverLay(bMale, true), AddRandTats(bMale), std::vector<Mod_Class::ClothX>{ Cothing }, {}, 0, 0, 0, 200, 1.0f, 1.0f);
		}
		else
		{
			bool bMale = false;
			std::string Model = "mp_f_freemode_01";
			Mod_Class::ClothX Cothing = GetCloths(bMale);
			Mod_Class::HairSets MyHair = PickAStyle(bMale);
			return Mod_Class::ClothBank("", Model, Mod_Systems::MyHashKey(Model), true, AddFace(bMale), bMale, false, MyHair, Mod_Systems::RandomInt(1, 61), Mod_Systems::RandomInt(1, 61), Mod_Systems::RandomInt(0, 10), 0, {}, AddOverLay(bMale, true), AddRandTats(bMale), std::vector<Mod_Class::ClothX>{ Cothing }, {}, 0, 0, 0, 200, 1.0f, 1.0f);
		}
	}

	bool ItsChristmas;
	bool ItHalloween;

	void ThemVoices(const std::string& voice)
	{
		AUDIO::SET_AMBIENT_VOICE_NAME(PLAYER::PLAYER_PED_ID(), (LPSTR)voice.c_str());
		invoke <Void>(0x4ADA3F19BE4A6047, PLAYER::PLAYER_PED_ID());
	}
	void PullingFaces(const std::string& aniName)
	{
		PED::SET_FACIAL_IDLE_ANIM_OVERRIDE(PLAYER::PLAYER_PED_ID(), (LPSTR)aniName.c_str(), 0);
	}

	const std::vector<std::string> LsGstars = {
		"g_f_importexport_01",//"Gang Female (Import-Export)", 
		"a_f_y_eastsa_03",//"East SA Young Female 3", 
		"g_f_importexport_01",//"Import Export Female", 
		"g_m_importexport_01",//"Gang Male (Import-Export)",
		"g_m_m_armboss_01",//"Armenian Boss",  Rogers Salvage and Scrap in La Puerta.-- NON -- 
		"g_m_m_armgoon_01",//"Armenian Goon",  
		"g_m_y_armgoon_02",//"Armenian Goon 2",  
		"g_m_m_armlieut_01",//"Armenian Lieutenant",  
		"g_f_y_ballas_01",//"Ballas Female", Davis,--Families--Vagos
		"g_m_y_ballaeast_01",//"Ballas East Male",  
		"g_m_y_ballaorig_01",//"Ballas Original Male",  
		"g_m_y_ballasout_01",//"Ballas South Male", 
		"g_m_m_chiboss_01",//"Chinese Boss",   textstyle-- korean
		"g_m_m_chigoon_01",//"Chinese Goon",  
		"g_m_m_chigoon_02",//"Chinese Goon 2",  
		"g_m_m_chicold_01",//"Chinese Goon Older", 
		"g_f_y_families_01",//"Families Female",
		"g_m_y_famca_01",//"Families CA Male",  
		"g_m_y_famdnf_01",//"Families DNF Male",  
		"g_m_y_famfor_01",//"Families FOR Male", 
		"g_m_m_korboss_01",//"Korean Boss",  K-town-- Chinesse
		"g_m_y_korlieut_01",//"Korean Lieutenant",  
		"g_m_y_korean_01",//"Korean Young Male",  
		"g_m_y_korean_02",//"Korean Young Male 2", 
		"g_m_y_azteca_01",//"Azteca", 
		"g_f_y_vagos_01",//"Vagos Female",
		"a_m_y_mexthug_01",//"Mexican Thug", 
		"g_m_m_mexboss_01",//"Mexican Boss",  
		"g_m_m_mexboss_02",//"Mexican Boss 2",  
		"g_m_y_mexgang_01",//"Mexican Gang Member",  
		"g_m_y_mexgoon_01",//"Mexican Goon",  
		"g_m_y_mexgoon_02",//"Mexican Goon 2",  
		"g_m_y_mexgoon_03",//"Mexican Goon 3",  
		"g_m_y_pologoon_01",//"Polynesian Goon",  
		"g_m_y_pologoon_02",//"Polynesian Goon 2", 
		"g_m_y_salvaboss_01",//"Salvadoran Boss",  
		"g_m_y_salvagoon_01",//"Salvadoran Goon",  
		"g_m_y_salvagoon_02",//"Salvadoran Goon 2",  
		"g_m_y_salvagoon_03",//"Salvadoran Goon 3",  
		"g_f_y_lost_01",//"The Lost MC Female",  
		"g_m_y_lost_01",//"The Lost MC Male",  
		"g_m_y_lost_02",//"The Lost MC Male 2",  
		"g_m_y_lost_03",//"The Lost MC Male 3",
		"A_F_M_GenBiker_01",//
		"A_M_M_GenBiker_01",//
		"g_m_y_strpunk_01",//"Street Punk",  
		"g_m_y_strpunk_02",//"Street Punk 2",  
		"G_M_M_GenThug_01",
		"G_M_M_Goons_01"
	};
	const std::vector<std::string> Eplomes = {
		"a_f_y_epsilon_01",//"Epsilon Female",  
		"a_m_y_epsilon_01",//"Epsilon Male",  
		"a_m_y_epsilon_02",//"Epsilon Male 2", 
	};
	const std::vector<std::string> WorkinClass = { 
		"mp_f_bennymech_01",//"Benny Mechanic (Female)",	0
		"s_m_m_autoshop_01",//"Autoshop Worker",			1
		"s_m_m_autoshop_02",//"Autoshop Worker 2",			2
		"s_f_y_bartender_01",//"Bartender",					3
		"s_f_y_clubbar_01",//"Club Bartender Female",		4
		"s_m_y_barman_01",//"Barman",						5
		"s_m_y_waiter_01",//"Waiter",						6
		"s_f_y_factory_01",//"Factory Worker Female",		7
		"s_f_m_sweatshop_01",//"Sweatshop Worker",			8
		"s_f_y_sweatshop_01",//"Sweatshop Worker Young",	9
		"S_F_M_Warehouse_01",	//							10
		"S_M_M_Warehouse_01",	//							11
		"mp_m_shopkeep_01",//"Shopkeeper (Male)",			12
		"s_f_y_scrubs_01",//"Hospital Scrubs Female",		13
		"s_m_m_doctor_01",//"Doctor",						14
		"s_f_m_maid_01",//"Maid",							15
		"s_f_y_migrant_01",//"Migrant Female--cleaner",		16
		"s_m_m_migrant_01",//"Migrant Male",				17
		"mp_s_m_armoured_01",//"Armoured Van Security Male",18
		"s_m_m_armoured_01",//"Armoured Van Security",		19
		"s_m_m_armoured_02",//"Armoured Van Security 2",	20	
		"s_m_m_chemsec_01",//"Chemical Plant Security",		21
		"mp_m_securoguard_01",//"Securoserve Guard (Male)", 22
		"s_m_m_security_01",//"Security Guard",				23
		"s_m_y_autopsy_01",//"Autopsy Tech",				24			
		"s_m_m_scientist_01",//"Scientist",					25
		"g_m_m_chemwork_01",//"Chemical Plant Worker",		26
		"s_m_y_construct_01",//"construction Worker",		27
		"s_m_y_construct_02",//"construction Worker 2",		28
		"s_m_m_dockwork_01",//"Dock Worker",				29
		"s_m_y_dockwork_01",//"Dock Worker",				30
		"s_m_y_airworker",//"Air Worker Male",				31
		"s_m_y_dwservice_01",//"DW Airport Worker",			32
		"s_m_y_dwservice_02",//"DW Airport Worker 2",		33
		"s_m_y_garbage",//"Garbage Worker",					34		
		"s_m_m_gardener_01",//"Gardener",					35
		"s_m_m_lathandy_01",//"Latino Handyman Male",		36
		"s_m_m_lsmetro_01",//"LS Metro Worker Male",		37
		"s_m_m_gentransport",//"Transport Worker Male",		38
		"s_m_y_pestcont_01",//"Pest Control",				39
		"s_m_m_postal_01",//"Postal Worker Male",			40
		"s_m_m_postal_02",//"Postal Worker Male 2",			41
		"s_m_m_ups_01",//"UPS Driver",						42
		"s_m_m_ups_02",//"UPS Driver 2",					43
		"s_m_m_strvend_01",//"Street Vendor",				44
		"s_m_y_strvend_01",//"Street Vendor Young",			45
		"s_m_y_valet_01",//"Valet",							46
		"s_m_y_winclean_01"//"Window Cleaner",				47
	};

	const std::vector<std::string> MotoCrossPeds = {
		"a_m_y_motox_01",//"Motocross Biker",  
		"a_m_y_motox_02",//"Motocross Biker 2",
	};
	const std::vector<std::string> ServicePeds = {
		"s_f_y_baywatch_01",//"Baywatch Female",	0
		"s_m_y_baywatch_01",//"Baywatch Male",		1
		"s_m_y_uscg_01",//"US Coastguard",			2
		"s_m_y_cop_01",//"Cop Male",				3
		"s_f_y_cop_01",//"Cop Female",				4
		"s_m_y_hwaycop_01",//"Highway Cop",			5
		"s_f_y_ranger_01",//"Ranger Female",		6
		"s_m_y_ranger_01",//"Ranger Male",			7
		"s_f_y_sheriff_01",//"Sheriff Female",		8
		"s_m_y_sheriff_01",//"Sheriff Male",		9
		"s_m_m_fibsec_01",//"FIB Security",			10
		"s_m_y_swat_01",//"SWAT",					11
		"s_m_y_armymech_01",//"Army Mechanic",		12
		"s_m_m_ccrew_01",//"Crew Member",			13
		"s_m_y_blackops_01",//"Black Ops Soldier",	14
		"s_m_y_blackops_02",//"Black Ops Soldier 2",15
		"s_m_y_blackops_03",//"Black Ops Soldier 3",16
		"s_m_m_marine_01",//"Marine",				17
		"s_m_m_marine_02",//"Marine 2",				18
		"s_m_y_marine_01",//"Marine Young",			19	
		"s_m_y_marine_02",//"Marine Young 2",		20
		"s_m_y_marine_03",//"Marine Young 3",		21
		"s_m_m_paramedic_01",//"Paramedic",			22
		"s_m_y_fireman_01"//"Fireman Male",			23
	};
	const std::vector<std::string> PilotPeds = {
		"s_m_y_pilot_01",//"Pilot",  
		"s_m_m_pilot_02",//"Pilot 2", 
		"s_m_m_pilot_01"//"Pilot",  
	};
	const std::vector<std::string> AnimalsPeds = {
		"a_c_boar",//"a_c_boar",		0
		"a_c_cat_01",//					1
		"a_c_husky",//					2
		"a_c_poodle",//					3
		"a_c_pug",//					4
		"a_c_retriever",//				5
		"a_c_rottweiler",//				6
		"a_c_shepherd",//				7
		"a_c_westy",//					8
		"a_c_pigeon",//"a_c_pigeon" />	9
		"a_c_rat",//"a_c_rat" />		10
		"a_c_cow",//"a_c_cow" />		11
		"a_c_coyote",//"a_c_coyote" />	12
		"a_c_crow",//"a_c_crow" />		13
		"a_c_rabbit_01",//"a_c_rabbit_01" />14
		"a_c_deer",//"a_c_deer" />			15
		"a_c_hen",//"a_c_hen" />		16
		"a_c_mtlion",//"mountain lion" />17
		"a_c_pig",//"a_c_pig" />		18
		"a_c_dolphin",//"fish/sharks" />19
		"a_c_fish",//					20
		"a_c_sharkhammer",//			21
		"a_c_humpback",//				22
		"a_c_killerwhale",//			23
		"a_c_stingray",//				24
		"a_c_sharktiger",//				25
		"a_c_chickenhawk",//"a_c_chickenhawk",  26
		"a_c_cormorant",//"a_c_cormorant" />	27
		"a_c_seagull"//					28
	};
	const std::vector<std::string> YankoPPeds = {
		"csb_prologuedriver",
		"csb_prolsec",
		"cs_prolsec_02",
		"ig_prolsec_02",
		"u_f_o_prolhost_01",
		"u_f_m_promourn_01"
	};
	const std::vector<std::string> CayoPercPeds = {
		"A_C_Panther",
		"G_M_M_CartelGuards_01",
		"G_M_M_CartelGuards_02",
		"S_M_M_HighSec_04",
		"S_F_Y_BeachBarStaff_01",
		"S_M_M_DrugProcess_01",
		"S_M_M_FieldWorker_01",
		"IG_Pilot",
		"CSB_JIO",
		"CSB_JuanStrickler",
		"CSB_MJO",
		"CSB_SSS",
		"IG_ARY",
		"IG_JIO",
		"IG_MJO",
		"IG_OldRichGuy",
		"IG_SSS"
	};

	Mod_Class::ClothX GetYourTogs(Ped peddy)
	{
		Mod_Systems::LoggerLight("GetYourTogs");
		std::vector<int> ClothA = {};
		std::vector<int> ClothB = {};

		std::vector<int> ExtraA = {};
		std::vector<int> ExtraB = {};

		for (int i = 0; i < 12; i++)
		{
			int iDrawId = PED::GET_PED_DRAWABLE_VARIATION(peddy, i);
			ClothA.push_back(iDrawId);
			int iTextId = PED::GET_PED_TEXTURE_VARIATION(peddy, i);
			ClothB.push_back(iTextId);
		}

		for (int i = 0; i < 4; i++)
		{
			int iDrawId = PED::GET_PED_PROP_INDEX(peddy, i);
			ExtraA.push_back(iDrawId);
			int iTextId = PED::GET_PED_PROP_TEXTURE_INDEX(peddy, i);
			ExtraB.push_back(iTextId);
		}

		return Mod_Class::ClothX("Default", ClothA, ClothB, ExtraA, ExtraB);
	}
	Mod_Class::FaceBank FreeFaces(Ped peddy, bool free)
	{
		if (free)
		{
			HeadBlendData MyFace;
			PED::_GET_PED_HEAD_BLEND_DATA(peddy, (Any*)&MyFace);

			return Mod_Class::FaceBank(MyFace.shapeFirstID, MyFace.shapeSecondID, MyFace.shapeMix, MyFace.skinMix, MyFace.thirdMix);
		}
		else
		{
			return Mod_Class::FaceBank(0, 0, 0.0f, 0.0f, 0.0f);
		}
	}
	std::string RandomPed(int pedtype, int subType)
	{
		std::string YourPed = "s_m_y_clown_01";
		if (pedtype == 1)
			YourPed = Mod_Data::PrePed_01[Mod_Systems::LessRandomInt("RandPed_0" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_01.size() - 1)];		//Beach Peds
		else if (pedtype == 2)
			YourPed = Mod_Data::PrePed_02[Mod_Systems::LessRandomInt("RandPed_0" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_02.size() - 1)];		//Tramps
		else if (pedtype == 3)
			YourPed = Mod_Data::PrePed_03[Mod_Systems::LessRandomInt("RandPed_0" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_03.size() - 1)];		//High class
		else if (pedtype == 4)
			YourPed = Mod_Data::PrePed_04[Mod_Systems::LessRandomInt("RandPed_0" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_04.size() - 1)];		//Mid class
		else if (pedtype == 5)
			YourPed = Mod_Data::PrePed_05[Mod_Systems::LessRandomInt("RandPed_0" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_05.size() - 1)];		//Low class 
		else if (pedtype == 6)
			YourPed = Mod_Data::PrePed_06[Mod_Systems::LessRandomInt("RandPed_0" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_06.size() - 1)];		//Buisness
		else if (pedtype == 7)
			YourPed = Mod_Data::PrePed_07[Mod_Systems::LessRandomInt("RandPed_0" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_07.size() - 1)];		//Body builder
		else if (pedtype == 8)
		{
			if (subType == 1)
				YourPed = LsGstars[Mod_Systems::LessRandomInt("RandGsPed_0" + std::to_string(subType), 0, 3)];
			else if (subType == 2)
				YourPed = LsGstars[Mod_Systems::LessRandomInt("RandGsPed_0" + std::to_string(subType), 4, 7)];
			else if (subType == 3)
				YourPed = LsGstars[Mod_Systems::LessRandomInt("RandGsPed_0" + std::to_string(subType), 8, 11)];
			else if (subType == 4)
				YourPed = LsGstars[Mod_Systems::LessRandomInt("RandGsPed_0" + std::to_string(subType), 12, 15)];
			else if (subType == 5)
				YourPed = LsGstars[Mod_Systems::LessRandomInt("RandGsPed_0" + std::to_string(subType), 16, 19)];
			else if (subType == 6)
				YourPed = LsGstars[Mod_Systems::LessRandomInt("RandGsPed_0" + std::to_string(subType), 20, 23)];
			else if (subType == 7)
				YourPed = LsGstars[Mod_Systems::LessRandomInt("RandGsPed_0" + std::to_string(subType), 24, 32)];
			else if (subType == 8)
				YourPed = LsGstars[Mod_Systems::LessRandomInt("RandGsPed_0" + std::to_string(subType), 33, 34)];
			else if (subType == 9)
				YourPed = LsGstars[Mod_Systems::LessRandomInt("RandGsPed_0" + std::to_string(subType), 35, 38)];
			else if (subType == 10)
				YourPed = LsGstars[Mod_Systems::LessRandomInt("RandGsPed_" + std::to_string(subType), 39, 44)];
			else
				YourPed = LsGstars[Mod_Systems::LessRandomInt("RandGsPed_" + std::to_string(subType), 45, (int)LsGstars.size() - 1)];
		}       //GangStars--Subset
		else if (pedtype == 9)
			YourPed = Eplomes[Mod_Systems::LessRandomInt("RandPed_0" + std::to_string(pedtype), 0, (int)Eplomes.size() - 1)];			//Epslon 
		else if (pedtype == 10)
			YourPed = Mod_Data::PrePed_08[Mod_Systems::LessRandomInt("RandPed_0" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_08.size() - 1)];		//Jogger
		else if (pedtype == 11)
			YourPed = Mod_Data::PrePed_09[Mod_Systems::LessRandomInt("RandPed_0" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_09.size() - 1)];		//Golfer
		else if (pedtype == 12)
			YourPed = Mod_Data::PrePed_10[Mod_Systems::LessRandomInt("RandPed_" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_10.size() - 1)];		//Hiker
		else if (pedtype == 13)
			YourPed = Mod_Data::PrePed_11[Mod_Systems::LessRandomInt("RandPed_" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_11.size() - 1)];		//Meth
		else if (pedtype == 14)
			YourPed = Mod_Data::PrePed_12[Mod_Systems::LessRandomInt("RandPed_" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_12.size() - 1)];		//Rural 
		else if (pedtype == 15)
			YourPed = Mod_Data::PrePed_13[Mod_Systems::LessRandomInt("RandPed_" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_13.size() - 1)];		//Cycles
		else if (pedtype == 16)
			YourPed = Mod_Data::PrePed_14[Mod_Systems::LessRandomInt("RandPed_" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_14.size() - 1)];		//LGBTQWSTRVX
		else if (pedtype == 17)
			YourPed = Mod_Data::PrePed_01[Mod_Systems::LessRandomInt("RandPed_" + std::to_string(pedtype), 0, (int)Mod_Data::PrePed_01.size() - 1)];		//Pool Peds
		else if (pedtype == 18)
		{
			if (subType == 1)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_0" + std::to_string(subType), 0, 2)];
			else if (subType == 2)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_0" + std::to_string(subType), 3, 6)];
			else if (subType == 3)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_0" + std::to_string(subType), 7, 11)];
			else if (subType == 4)
				YourPed = WorkinClass[12];
			else if (subType == 5)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_0" + std::to_string(subType), 13, 14)];
			else if (subType == 6)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_0" + std::to_string(subType), 15, 17)];
			else if (subType == 7)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_0" + std::to_string(subType), 18, 20)];
			else if (subType == 8)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_0" + std::to_string(subType), 21, 23)];
			else if (subType == 9)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_0" + std::to_string(subType), 24, 25)];
			else if (subType == 10)
				YourPed = WorkinClass[26];
			else if (subType == 11)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_" + std::to_string(subType), 27, 28)];
			else if (subType == 12)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_" + std::to_string(subType), 29, 30)];
			else if (subType == 13)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_" + std::to_string(subType), 31, 33)];
			else if (subType == 14)
				YourPed = WorkinClass[34];
			else if (subType == 15)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_" + std::to_string(subType), 35, 36)];
			else if (subType == 16)
				YourPed = WorkinClass[37];
			else if (subType == 17)
				YourPed = WorkinClass[38];
			else if (subType == 18)
				YourPed = WorkinClass[39];
			else if (subType == 19)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_" + std::to_string(subType), 40, 41)];
			else if (subType == 20)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_" + std::to_string(subType), 42, 43)];
			else if (subType == 21)
				YourPed = WorkinClass[Mod_Systems::LessRandomInt("RandWkPed_" + std::to_string(subType), 44, 45)];
			else if (subType == 22)
				YourPed = WorkinClass[46];
			else
				YourPed = WorkinClass[(int)WorkinClass.size() - 1];
		}       //Workers--Subset
		else if (pedtype == 19)
			YourPed = "a_m_y_jetski_01";		//jet ski
		else if (pedtype == 20)
			YourPed = MotoCrossPeds[Mod_Systems::LessRandomInt("RandMcPed_" + std::to_string(pedtype), 0, 1)];		//Bike/ATV Male
		else if (pedtype == 21)
		{
			if (subType == 1)
				YourPed = ServicePeds[Mod_Systems::LessRandomInt("RandSvPed_0" + std::to_string(subType), 0, 1)];		//"Baywatch 
			else if (subType == 2)
				YourPed = ServicePeds[2];																	//"US Coastguard
			else if (subType == 3)
				YourPed = ServicePeds[Mod_Systems::LessRandomInt("RandSvPed_0" + std::to_string(subType), 3, 4)];		//><!--Cops
			else if (subType == 4)
				YourPed = ServicePeds[5];																	//><!-- PoliceBike
			else if (subType == 5)
				YourPed = ServicePeds[Mod_Systems::LessRandomInt("RandSvPed_0" + std::to_string(subType), 6, 7)];		//><!-- Ranger
			else if (subType == 6)
				YourPed = ServicePeds[Mod_Systems::LessRandomInt("RandSvPed_0" + std::to_string(subType), 8, 9)];		//><!-- Sherif
			else if (subType == 7)
				YourPed = ServicePeds[10];																	//><!-- fib
			else if (subType == 8)
				YourPed = ServicePeds[11];																	//><!-- swat
			else if (subType == 9)
				YourPed = ServicePeds[Mod_Systems::LessRandomInt("RandSvPed_0" + std::to_string(subType), 12, 21)];		//military
			else if (subType == 10)
				YourPed = ServicePeds[22];																	//medic
			else
				YourPed = ServicePeds[(int)ServicePeds.size() - 1];											//fireman
		}       //Services
		else if (pedtype == 22)
		{
			if (subType == 2)
				YourPed = "mp_f_helistaff_01";
			else
				YourPed = PilotPeds[Mod_Systems::LessRandomInt("RandPiPed", 0, (int)PilotPeds.size() - 1)];
		}       //Pilot
		else if (pedtype == 23)
		{
			if (subType == 1)
				YourPed = AnimalsPeds[0];
			else if (subType == 2)
				YourPed = AnimalsPeds[Mod_Systems::LessRandomInt("RandAnPed_0" + std::to_string(subType), 1, 8)];		//"Cats/dogs", 
			else if (subType == 3)
				YourPed = AnimalsPeds[9];
			else if (subType == 4)
				YourPed = AnimalsPeds[10];
			else if (subType == 5)
				YourPed = AnimalsPeds[11];
			else if (subType == 6)
				YourPed = AnimalsPeds[12];
			else if (subType == 7)
				YourPed = AnimalsPeds[13];
			else if (subType == 8)
				YourPed = AnimalsPeds[Mod_Systems::LessRandomInt("RandAnPed_0" + std::to_string(subType), 14, 15)];		//"dearRabbit", 
			else if (subType == 9)
				YourPed = AnimalsPeds[16];
			else if (subType == 10)
				YourPed = AnimalsPeds[17];
			else if (subType == 11)
				YourPed = AnimalsPeds[18];
			else if (subType == 12)
				YourPed = AnimalsPeds[Mod_Systems::LessRandomInt("RandAnPed_" + std::to_string(subType), 19, 25)];
			else if (subType == 13)
				YourPed = AnimalsPeds[26];
			else
				YourPed = AnimalsPeds[Mod_Systems::LessRandomInt("RandAnPed_" + std::to_string(subType), 27, (int)AnimalsPeds.size() - 1)];
		}       //animals
		else if (pedtype == 24)
			YourPed = YankoPPeds[Mod_Systems::LessRandomInt("RandPed_" + std::to_string(pedtype), 0, (int)YankoPPeds.size() - 1)];		//Mod_Data::Yankton
		else
		{
			if (subType == 1)
				YourPed = CayoPercPeds[0]; //A_C_Panther  
			else if (subType == 2)
				YourPed = Mod_Data::PrePed_01[Mod_Systems::LessRandomInt("RandCpPed_0" + std::to_string(subType), 0, (int)Mod_Data::PrePed_01.size() - 1)];		 //A_F_Y_Beach_02
			else if (subType == 3)
				YourPed = CayoPercPeds[Mod_Systems::LessRandomInt("RandCpPed_0" + std::to_string(subType), 1, 3)]; //Guard
			else if (subType == 4)
				YourPed = CayoPercPeds[4];  //Bar
			else if (subType == 5)
				YourPed = CayoPercPeds[Mod_Systems::LessRandomInt("RandCpPed_0" + std::to_string(subType), 5, 6)]; //worker
			else if (subType == 6)
				YourPed = CayoPercPeds[Mod_Systems::LessRandomInt("RandCpPed_0" + std::to_string(subType), 7, (int)CayoPercPeds.size() - 2)];  //pilot
			else
				YourPed = CayoPercPeds[(int)CayoPercPeds.size() - 1];

		}     //Cayo Perico


		return YourPed;
	}
	Mod_Class::ClothBank NewClothBank(const std::string& pedTitle)
	{
		bool Male = true;
		std::string Model = pedTitle;
		Mod_Class::HairSets MyHair = MHairsets[0];
		return Mod_Class::ClothBank("", Model, 0, false, AddFace(Male), Male, false, MyHair, 0, 0, 0, 0, {}, {}, {}, {}, {}, 0, 0, 0, 200, 1.0f, 1.0f);
	}
	Mod_Class::ClothBank NewClothBank(int pedtype, int subType)
	{
		return NewClothBank(RandomPed(pedtype, subType));
	}
	Mod_Class::ClothBank PlayerClothBank()
	{
		Hash pedHash = ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID());

		bool freeMode = false;
		if (pedHash == MainProtags[3] || pedHash == MainProtags[4])
			freeMode = true;
		bool male = PED::IS_PED_MALE(PLAYER::PLAYER_PED_ID());

		bool animal_Farm = false;
		if (PED::GET_PED_TYPE(PLAYER::PLAYER_PED_ID()) == 28)
			animal_Farm = true;

		return Mod_Class::ClothBank("Current", "", pedHash, freeMode, FreeFaces(PLAYER::PLAYER_PED_ID(), freeMode), male, animal_Farm, Mod_Entitys::PickAStyle(male), 0, 0, 0, 0, {}, Mod_Entitys::AddOverLay(male, freeMode), {}, { GetYourTogs(PLAYER::PLAYER_PED_ID()) }, {}, 0, 0, 0, 200, 1.0f, 1.0f);
	}

	void ApplyTats(Ped peddy, Mod_Class::ClothBank* getTats)
	{
		if (getTats != nullptr)
		{
			for (int i = 0; i < getTats->MyTattoo.size(); i++)
				PED::_APPLY_PED_OVERLAY(peddy, Mod_Systems::MyHashKey(getTats->MyTattoo[i].BaseName), Mod_Systems::MyHashKey(getTats->MyTattoo[i].TatName));
		}
	}
	void OnlineDress(Ped peddy, Mod_Class::ClothX* cloths)
	{
		PED::CLEAR_ALL_PED_PROPS(peddy);
		if (cloths != nullptr)
		{
			for (int i = 0; i < cloths->ClothA.size(); i++)
			{
				if (cloths->ClothA[i] != -10)
					PED::SET_PED_COMPONENT_VARIATION(peddy, i, cloths->ClothA[i], cloths->ClothB[i], 2);
			}

			for (int i = 0; i < cloths->ExtraA.size(); i++)
			{
				if (cloths->ExtraA[i] != -10)
					PED::SET_PED_PROP_INDEX(peddy, i, cloths->ExtraA[i], cloths->ExtraB[i], false);
			}
			
			if (cloths->Badge.TatName != "")
				PED::_APPLY_PED_OVERLAY(peddy, Mod_Systems::MyHashKey(cloths->Badge.BaseName), Mod_Systems::MyHashKey(cloths->Badge.TatName));
		}

	}
	void SetingtheHair(Ped peddy, Mod_Class::HairSets* hair)
	{
		if (hair != nullptr)
		{
			PED::SET_PED_COMPONENT_VARIATION(peddy, 2, hair->Comp, hair->Text, 2);

			if (hair->Over != -1)
				PED::_APPLY_PED_OVERLAY(peddy, hair->OverLib, hair->Over);
		}
	}
	void OnlineFaces(Ped peddy, Mod_Class::ClothBank* feats)
	{
		//****************FaceShape/Colour****************
		PED::SET_PED_HEAD_BLEND_DATA(peddy, feats->MyFaces.ShapeFirstID, feats->MyFaces.ShapeSecondID, feats->MyFaces.ShapeThirdID, feats->MyFaces.SkinFirstID, feats->MyFaces.SkinSecondID, feats->MyFaces.SkinThirdID, feats->MyFaces.ShapeMix, feats->MyFaces.SkinMix, feats->MyFaces.ThirdMix, 0);

		if (ItsChristmas)
		{
			if (feats->Male)
				OnlineDress(peddy, &XmasOut_M[Mod_Systems::LessRandomInt("Crimb01", 0, (int)XmasOut_M.size() - 1)]);
			else
				OnlineDress(peddy, &XmasOut_F[Mod_Systems::LessRandomInt("Crimb01", 0, (int)XmasOut_F.size() - 1)]);
		}
		else if (ItHalloween)
		{
			if (feats->Male)
			{
				int Rand = Mod_Systems::LessRandomInt("Hallow01", 0, 11);
				Mod_Class::ClothX Cloths = Mod_Class::ClothX("MaleArena WarSpace_Horror", { 0, 141, 0, 164, 108, 0, 33, 0, 15, 0, 0, 277 }, { 0, Rand, 0, Rand, Rand, 0, 0, 0, 0, 0, 0, Rand }, { -1, -1, -1, -1, -1 }, { -1, -1, -1, -1, -1 });
				OnlineDress(peddy, &Cloths);
			}
			else
			{
				int Rand = Mod_Systems::LessRandomInt("Hallow01", 0, 11);
				Mod_Class::ClothX Cloths = Mod_Class::ClothX("FemaleArena WarSpace_Horror", { 21, 141, 0, 205, 115, 0, 34, 0, 6, 0, 0, 290 }, { 0, Rand, 0, Rand, Rand, 0, 0, 0, 0, 0, 0, Rand }, { -1, -1, -1, -1, -1 }, { -1, -1, -1, -1, -1 });
				OnlineDress(peddy, &Cloths);
			}
		}
		else
		{
			if ((int)feats->Cothing.size() > 0 && feats->Cloth_Pick < (int)feats->Cothing.size())
			{
				Mod_Class::ClothX Cloths = feats->Cothing[feats->Cloth_Pick];
				OnlineDress(peddy, &Cloths);
			}
			else
			{
				if (feats->Male)
					OnlineDress(peddy, &MaleDefault);
				else
					OnlineDress(peddy, &FemaleDefault);
			}
		}

		Mod_Class::HairSets Hairs = feats->MyHair;
		SetingtheHair(peddy, &Hairs);

		PED::_SET_PED_HAIR_COLOR(peddy, feats->HairColour, feats->HairStreaks);
		PED::_SET_PED_EYE_COLOR(peddy, feats->EyeColour);
		//****************Face****************
		for (int i = 0; i < feats->MyOverlay.size(); i++)
		{
			PED::SET_PED_HEAD_OVERLAY(peddy, i, feats->MyOverlay[i].Overlay, feats->MyOverlay[i].OverOpc);

			if (feats->MyOverlay[i].Colour > 0)
				PED::_SET_PED_HEAD_OVERLAY_COLOR(peddy, i, feats->MyOverlay[i].Colour, feats->MyOverlay[i].OverCol, 0);
		}

		if ((int)feats->FaceScale.size() > 0)
		{
			for (int i = 0; i < (int)feats->FaceScale.size(); i++)
				PED::_SET_PED_FACE_FEATURE(peddy, i, feats->FaceScale[i]);
		}
	}

	Ped PlayerPedGen(Mod_Class::Vector4 pos, Mod_Class::ClothBank* clothBank, bool onFoot, bool isfriend)
	{
		if (clothBank != nullptr)
		{
			WAIT(100);//Can overload and cause CTD if run multiple times.

			Mod_Systems::LoggerLight("PlayerPedGen == " + clothBank->Model);
			 
			Ped NewPed = NULL;
			Hash ModelHash = Mod_Systems::MyHashKey(clothBank->Model);

			if (clothBank->Model == "mp_m_freemode_01" || clothBank->Model == "mp_f_freemode_01")
				clothBank->FreeMode = true;
			else
				clothBank->FreeMode = false;

			if (!STREAMING::IS_MODEL_VALID(ModelHash))
				ModelHash = Mod_Systems::MyHashKey("cs_chrisformage");

			STREAMING::REQUEST_MODEL(ModelHash);// Check if the model is valid
			if ((bool)STREAMING::IS_MODEL_IN_CDIMAGE(ModelHash) && (bool)STREAMING::IS_MODEL_VALID(ModelHash))
			{
				while (!STREAMING::HAS_MODEL_LOADED(ModelHash))
					WAIT(10);

				NewPed = PED::CREATE_PED(4, ModelHash, pos.X, pos.Y, pos.Z, pos.R, true, false);

				int iAccuracy = Mod_Systems::RandomInt(50, 75);
				PED::SET_PED_ACCURACY(NewPed, iAccuracy);
				PED::SET_PED_MAX_HEALTH(NewPed, 200);
				ENTITY::SET_ENTITY_HEALTH(NewPed, 200);

				AI::SET_PED_PATH_PREFER_TO_AVOID_WATER(NewPed, false);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(NewPed, 1, 1);

				PED::SET_PED_COMBAT_ABILITY(NewPed, 100);
				if (onFoot)
				{
					PED::SET_PED_CAN_SWITCH_WEAPON(NewPed, true);
					PED::SET_PED_COMBAT_MOVEMENT(NewPed, 2);
					AI::SET_PED_PATH_CAN_USE_CLIMBOVERS(NewPed, true);
					AI::SET_PED_PATH_CAN_USE_LADDERS(NewPed, true);
					AI::SET_PED_PATH_CAN_DROP_FROM_HEIGHT(NewPed, true);
					AI::SET_PED_PATH_PREFER_TO_AVOID_WATER(NewPed, false);
					PED::SET_PED_COMBAT_ATTRIBUTES(NewPed, 0, true);
					PED::SET_PED_COMBAT_ATTRIBUTES(NewPed, 1, true);
					PED::SET_PED_COMBAT_ATTRIBUTES(NewPed, 2, true);
					PED::SET_PED_COMBAT_ATTRIBUTES(NewPed, 3, true);
				}

				if (isfriend)
					RelGroupMember(NewPed, Mod_Data::Gp_Follow);
				else
					RelGroupMember(NewPed, Mod_Data::GP_Attack);

				if (clothBank->FreeMode)
					OnlineFaces(NewPed, clothBank);

				GunningIt(NewPed, -1);

				Mod_Data::Ped_List.push_back(NewPed);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ModelHash);
			}
			else
				NewPed = NULL;

			return NewPed;
		}
		else
			return NULL;
	}
	Ped PlayerPedGen(Mod_Class::Vector4 pos, int set, int subset, bool onFoot, bool isfriend)
	{
		Mod_Class::ClothBank PedBank = NewClothBank(set, subset);
		return PlayerPedGen(pos, &PedBank, onFoot, isfriend);;
	}
	Ped PlayerPedGen(Mod_Class::Vector4 pos, const std::string& pedModel, bool onFoot, bool isfriend)
	{
		Mod_Class::ClothBank PedBank = NewClothBank(pedModel);
		return PlayerPedGen(pos, &PedBank, onFoot, isfriend);
	}

	void RepoPedPlayer(Ped target)
	{
		Ped YoPlaya = PLAYER::PLAYER_PED_ID();
		PLAYER::CHANGE_PLAYER_PED(PLAYER::PLAYER_ID(), target, true, true);
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&target);

		if (PED::GET_PED_TYPE(PLAYER::PLAYER_PED_ID()) != 28)
		{
			if (Mod_Data::Mod_Settings.Random_Weapons)
				GunningIt(PLAYER::PLAYER_PED_ID(), 0);
			else
				GunningIt(PLAYER::PLAYER_PED_ID(), Mod_Data::Player_Weaps);
		}
	}
	void ChangePlayer(Hash modelHash)
	{
		Mod_Systems::LoggerLight("ChangePlayer == " + std::to_string(modelHash));

		if (!STREAMING::IS_MODEL_VALID(modelHash))
			modelHash = Mod_Systems::MyHashKey("cs_chrisformage");

		if (STREAMING::IS_MODEL_IN_CDIMAGE(modelHash) && STREAMING::IS_MODEL_VALID(modelHash))
		{
			STREAMING::REQUEST_MODEL(modelHash);
			while (!STREAMING::HAS_MODEL_LOADED(modelHash))
				WAIT(1);

			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), modelHash);

			WAIT(1000);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(modelHash);
		}
	}
	void ChangePlayer(int select, int subset, int weap)
	{
		if (weap == -1)
			weap = Mod_Systems::RandomInt(2, 10);

		WAIT(1000);
		ChangePlayer(Mod_Systems::MyHashKey(RandomPed(select, subset)));
		PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), false);

		if (PED::GET_PED_TYPE(PLAYER::PLAYER_PED_ID()) != 28)
		{
			if (Mod_Data::Mod_Settings.Random_Weapons)
				GunningIt(PLAYER::PLAYER_PED_ID(), weap);
			else
				GunningIt(PLAYER::PLAYER_PED_ID(), Mod_Data::Player_Weaps);
		}
	}
	void SavedPlayer(Mod_Class::ClothBank* clothBank, int weap)
	{
		if (clothBank != nullptr)
		{
			if (weap == -1)
				weap = Mod_Systems::RandomInt(2, 10);

			Mod_Systems::LoggerLight("SavedPlayer == " + clothBank->CharName);

			if (clothBank->ModelHash == 0)
				clothBank->ModelHash = Mod_Systems::MyHashKey(clothBank->Model);

			ChangePlayer(clothBank->ModelHash);

			if (clothBank->FreeMode)
				OnlineFaces(PLAYER::PLAYER_PED_ID(), clothBank);
			else
				OnlineDress(PLAYER::PLAYER_PED_ID(), &clothBank->Cothing[clothBank->Cloth_Pick]);

			if (clothBank->Male)
			{
				if (clothBank->Voice >= (int)VoicesMale.size())
					clothBank->Voice = 0;

				if (clothBank->Voice > 0)
					ThemVoices(VoicesMale[clothBank->Voice]);

				if (clothBank->Walkies >= (int)M_Walks.size())
					clothBank->Walkies = 0;

				if (clothBank->Walkies > 0)
					WalkingStyle(PLAYER::PLAYER_PED_ID(), M_Walks[clothBank->Walkies]);
			}
			else
			{
				if (clothBank->Voice >= (int)VoicesFemale.size())
					clothBank->Voice = 0;

				if (clothBank->Voice > 0)
					ThemVoices(VoicesFemale[clothBank->Voice]);

				if (clothBank->Walkies >= (int)F_Walks.size())
					clothBank->Walkies = 0;

				if (clothBank->Walkies > 0)
					WalkingStyle(PLAYER::PLAYER_PED_ID(), F_Walks[clothBank->Walkies]);
			}
			if (clothBank->Moods >= (int)FaceAn.size())
				clothBank->Moods = 0;

			if (clothBank->Moods > 0)
				PullingFaces(FaceAn[clothBank->Moods]);

			//****************Tattoos****************
			ApplyTats(PLAYER::PLAYER_PED_ID(), clothBank);

			if (PED::GET_PED_TYPE(PLAYER::PLAYER_PED_ID()) != 28)
			{
				if (clothBank->MyWeapons.size() > 0)
					GunningIt(PLAYER::PLAYER_PED_ID(), clothBank->MyWeapons);
				else if (Mod_Data::Mod_Settings.Random_Weapons)
					GunningIt(PLAYER::PLAYER_PED_ID(), weap);
				else
					GunningIt(PLAYER::PLAYER_PED_ID(), Mod_Data::Player_Weaps);
			}

			PED::SET_PED_MAX_HEALTH(PLAYER::PLAYER_PED_ID(), clothBank->PlHealth);
			ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), clothBank->PlHealth);
			PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), clothBank->PlRunSp);
			PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), clothBank->PlSwimSp);
		}
	}

	std::string RandVeh(int vehList, int subSet)
	{
		Mod_Systems::LoggerLight("RandVeh, vehList == " + std::to_string(vehList) + ", subSet == " + std::to_string(subSet));

		std::string VehString = "ZENTORNO";

		if (vehList == 1)
			VehString = Mod_Data::PreVeh_01[Mod_Systems::LessRandomInt("RandVeh01", 0, (int)Mod_Data::PreVeh_01.size() - 1)];//Boats
		else if (vehList == 3)
			VehString = Mod_Data::PreVeh_02[Mod_Systems::LessRandomInt("RandVeh02", 0, (int)Mod_Data::PreVeh_02.size() - 1)];//Posh
		else if (vehList == 4)
			VehString = Mod_Data::PreVeh_03[Mod_Systems::LessRandomInt("RandVeh03", 0, (int)Mod_Data::PreVeh_03.size() - 1)];//Mid
		else if (vehList == 5)
			VehString = Mod_Data::PreVeh_04[Mod_Systems::LessRandomInt("RandVeh04", 0, (int)Mod_Data::PreVeh_04.size() - 1)];//low
		else if (vehList == 6)
			VehString = "VOLATUS";
		else if (vehList == 11)
			VehString = "CADDY";
		else if (vehList == 14)
			VehString = "TRACTOR2";
		else if (vehList == 15)
		{
			if (subSet == 1)
				VehString = "TRIBIKE";      //Racer
			else if (subSet == 2)
				VehString = "SCORCHER";     //Mountain
			else if (subSet == 3)
				VehString = "BMX";      //BMX
			else
				VehString = "CRUISER";      //Cruser
		}
		else if (vehList == 18)
		{
			if (subSet == 7)
				VehString = "STOCKADE";  //"Armoured Van Security 2"); 
			else if (subSet == 8)
				VehString = "DILETTANTE2"; //"Security Guard"); 
			else if (subSet == 11)
				VehString = Mod_Data::PreVeh_05[Mod_Systems::LessRandomInt("RandVeh05", 0, (int)Mod_Data::PreVeh_05.size() - 1)];//low//"construction Worker 2"); 
			else if (subSet == 12)
				VehString = "HANDLER"; //"Dock Worker");  
			else if (subSet == 13)
				VehString = "AIRTUG";  //Airport
			else if (subSet == 14)
				VehString = "TRASH2";  //"Garbage Worker");  
			else if (subSet == 17)
				VehString = Mod_Data::PreVeh_06[Mod_Systems::LessRandomInt("RandVeh06", 0, (int)Mod_Data::PreVeh_06.size() - 1)]; //"Transport Worker Male");  
			else if (subSet == 19)
				VehString = "BOXVILLE2";  //"Postal Worker Male 2");  
			else if (subSet == 20)
				VehString = Mod_Data::PreVeh_06[Mod_Systems::LessRandomInt("RandVeh06", 0, (int)Mod_Data::PreVeh_06.size() - 1)]; //"Transport Worker Male");  
			else if (subSet == 21)
				VehString = "BOXVILLE2";  //"Postal Worker Male 2");  
		}
		else if (vehList == 19)
			VehString = "SEASHARK";
		else if (vehList == 20)
			VehString = Mod_Data::PreVeh_07[Mod_Systems::LessRandomInt("RandVeh07", 0, (int)Mod_Data::PreVeh_07.size() - 1)];//bikeAtv
		else if (vehList == 21)
		{
			if (subSet == 1)
				VehString = "BLAZER2"; //"Baywatch 
			else if (subSet == 2)
				VehString = "PREDATOR";  //"US Coastguard
			else if (subSet == 3)
				VehString = Mod_Data::PreVeh_08[Mod_Systems::LessRandomInt("RandVeh08a", 8, (int)Mod_Data::PreVeh_08.size() - 2)]; //><!--Cops
			else if (subSet == 4)
				VehString = Mod_Data::PreVeh_08[4]; //><!-- PoliceBike
			else if (subSet == 5)
				VehString = Mod_Data::PreVeh_08[5];//><!-- Ranger
			else if (subSet == 6)
				VehString = Mod_Data::PreVeh_08[Mod_Systems::LessRandomInt("RandVeh08b", 6, 7)]; //><!-- Sherif
			else if (subSet == 7)
				VehString = Mod_Data::PreVeh_08[Mod_Systems::LessRandomInt("RandVeh08b", 0, 2)];  //><!-- fib
			else if (subSet == 8)
				VehString = Mod_Data::PreVeh_08[(int)Mod_Data::PreVeh_08.size() - 1]; //><!-- swat
			else if (subSet == 9)
				VehString = Mod_Data::PreVeh_09[Mod_Systems::LessRandomInt("RandVeh09", 0, (int)Mod_Data::PreVeh_09.size() - 1)]; //military
			else if (subSet == 10)
				VehString = "AMBULANCE"; //medic
			else
				VehString = "FIRETRUK";  //fireman
		}
		else if (vehList == 22)
		{
			if (subSet == 1)
				VehString = Mod_Data::PreVeh_10[Mod_Systems::LessRandomInt("RandVeh10a", 17, (int)Mod_Data::PreVeh_10.size() - 1)];  //civilian
			else if (subSet == 2)
				VehString = Mod_Data::PreVeh_10[Mod_Systems::LessRandomInt("RandVeh10b", 0, 18)];    //milatary
			else
				VehString = Mod_Data::PreVeh_11[Mod_Systems::LessRandomInt("RandVeh11", 0, (int)Mod_Data::PreVeh_11.size() - 1)];   //helitours
		}
		else if (vehList == 24)
			VehString = Mod_Data::PreVeh_12[Mod_Systems::LessRandomInt("RandVeh12", 0, (int)Mod_Data::PreVeh_12.size() - 1)];
		else if (vehList == 50)
			VehString = "Mule";
		else //if (vehList == 25)
			VehString = Mod_Data::PreVeh_13[Mod_Systems::LessRandomInt("RandVeh13", 0, (int)Mod_Data::PreVeh_13.size() - 1)];

		return VehString;
	}
	bool IsItARealVehicle(const std::string& vehName)
	{
		Mod_Systems::LoggerLight("IsItARealVehicle, vehName == " + vehName);

		bool bIsReal = false;
		if ((bool)STREAMING::IS_MODEL_A_VEHICLE(Mod_Systems::MyHashKey(vehName)))
			bIsReal = true;

		return bIsReal;
	}
	bool HasASeat(Vehicle vic)
	{
		bool bIn = false;
		if (vic != NULL)
		{
			if (FindUSeat(vic) > -1)
				bIn = true;
		}
		return bIn;
	}

	Vehicle VehicleSpawn(Mod_Class::Veh_Set vehSet)
	{//Fix the player to drive till press buutton and fly and other stuuff
		Mod_Systems::LoggerLight("SpawnVehicle");

		Vehicle thisVeh = NULL;
		WAIT(100);
		std::string sVehModel = vehSet.Model;

		if (!IsItARealVehicle(sVehModel))
			sVehModel = "MAMBA";

		vehSet.ModelHash = Mod_Systems::MyHashKey(sVehModel);

		if ((bool)STREAMING::IS_MODEL_IN_CDIMAGE(vehSet.ModelHash) && (bool)STREAMING::IS_MODEL_A_VEHICLE(vehSet.ModelHash))
		{
			STREAMING::REQUEST_MODEL(vehSet.ModelHash);
			while (!(bool)STREAMING::HAS_MODEL_LOADED(vehSet.ModelHash))
				WAIT(1);

			thisVeh = VEHICLE::CREATE_VEHICLE(vehSet.ModelHash, vehSet.SpawnPoint.X, vehSet.SpawnPoint.Y, vehSet.SpawnPoint.Z, vehSet.SpawnPoint.R, true, true);

			if (vehSet.IsHeli || vehSet.IsPlane)
			{
				int iClass = VEHICLE::GET_VEHICLE_CLASS(thisVeh);
				MaxOutAllModsNoWheels(thisVeh, iClass);
			}
			else
			{
				std::vector<int> Modup = RandVehModsist();
				MakeModsNotWar(thisVeh, &Modup);
			}

			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(thisVeh, 1, 1);

			Ped DesDriver = NULL;

			int iSeating = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(thisVeh);

			if (!vehSet.PlayerDriver && vehSet.PlayerInVeh && iSeating == 0)
			{
				vehSet.PlayerDriver = true;
				vehSet.FillVeh = false;
			}

			if (vehSet.PlayerDriver)
			{
				MoveEntity(PLAYER::PLAYER_PED_ID(), vehSet.SpawnPoint);
				DesDriver = PLAYER::PLAYER_PED_ID();
				WarptoAnyVeh(thisVeh, DesDriver, -1);
			}

			if (vehSet.FillVeh)
			{
				int iStart = 0;

				if (!vehSet.PlayerDriver)
				{
					DesDriver = PlayerPedGen(vehSet.SpawnPoint, vehSet.Select, vehSet.SubSet, false, vehSet.bFriend);
					WarptoAnyVeh(thisVeh, DesDriver, -1);

					if (vehSet.PlayerInVeh)
					{
						MoveEntity(PLAYER::PLAYER_PED_ID(), vehSet.SpawnPoint);
						WarptoAnyVeh(thisVeh, PLAYER::PLAYER_PED_ID(), 0);
						iStart++;
					}
				}

				for (int i = iStart; i < iSeating; i++)
				{
					Mod_Systems::LoggerLight("Fill Vehicle with peds");
					Ped CarPed = PlayerPedGen(vehSet.SpawnPoint, vehSet.Select, vehSet.SubSet, false, vehSet.bFriend);
					WarptoAnyVeh(thisVeh, CarPed, i);
				}
			}

			if (vehSet.DriveTo.size() > 1)
			{
				Drive_Fly_On(DesDriver, thisVeh, vehSet.DriveTo, vehSet.IsPlane, vehSet.IsHeli, vehSet.PlayerDriver, vehSet.RanDriveTo);
			}

			Mod_Data::Vehicle_List.push_back(thisVeh);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehSet.ModelHash);
		}
		else
			thisVeh = NULL;

		return thisVeh;
	}

	void CollectPeds(std::vector<Ped>* pedList)
	{
		const int PED_ARR_SIZE = 1024;
		Ped Pedds[PED_ARR_SIZE];
		int Pedcount = worldGetAllPeds(Pedds, PED_ARR_SIZE);

		for (int i = 0; i < Pedcount; i++)
		{
			Ped Peddy = Pedds[i];
			if (Peddy != NULL && ENTITY::DOES_ENTITY_EXIST(Peddy))
			{
				if (!ENTITY::IS_ENTITY_A_MISSION_ENTITY(Peddy))
					pedList->push_back(Peddy);
			}
		}
	}
	Ped NearByPed(Mod_Class::Vector4 area, float areaMin, float areaMax)
	{
		Ped Peddy = NULL;

		Ped PlayerPed = PLAYER::PLAYER_PED_ID();

		const int PED_ARR_SIZE = 1024;
		Ped Pedds[PED_ARR_SIZE];
		int Pedcount = worldGetAllPeds(Pedds, PED_ARR_SIZE);
		std::vector<Ped> NpcList = {};
		std::vector<Ped> AnimalList = {};

		for (int i = 0; i < Pedcount; i++)
		{
			if (Pedds[i] != NULL && ENTITY::DOES_ENTITY_EXIST(Pedds[i]))
			{
				if (!ENTITY::IS_ENTITY_A_MISSION_ENTITY(Pedds[i]) && Mod_Maths::DistanceTo(area, Mod_Maths::EntPosition(Pedds[i])) > areaMin && Mod_Maths::DistanceTo(area, Mod_Maths::EntPosition(Pedds[i])) < areaMax)
				{
					if (PED::GET_PED_TYPE(Pedds[i]) == 28)
						AnimalList.push_back(Pedds[i]);
					else
						NpcList.push_back(Pedds[i]);
				}
			}
		}

		for (int i = 0; i < (int)NpcList.size(); i++)
		{
			Peddy = NpcList[i];

			if (ENTITY::DOES_ENTITY_EXIST(Peddy))
			{
				if (Peddy != PlayerPed && !(bool)ENTITY::IS_ENTITY_DEAD(Peddy) && Mod_Maths::EntPosition(Peddy).z > -10)
				{
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Peddy, 1, 1);
					break;
				}
			}
		}

		if (Peddy == NULL)
		{
			for (int i = 0; i < (int)AnimalList.size(); i++)
			{
				Ped Peddy = AnimalList[i];
				if (ENTITY::DOES_ENTITY_EXIST(Peddy))
				{
					if (Peddy != PlayerPed && !(bool)ENTITY::IS_ENTITY_DEAD(Peddy))
					{
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Peddy, 1, 1);
						break;
					}
				}
			}
		}
		
		return Peddy;
	}

	void WatchDeath()
	{
		Mod_Systems::LoggerLight("WatchDeath");

		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("respawn_controller");
		GAMEPLAY::IGNORE_NEXT_RESTART(true);
		GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN(true);
		GAMEPLAY::SET_FADE_OUT_AFTER_DEATH(false);

		WAIT(500);

		while (true)
		{
			CAM::DO_SCREEN_FADE_IN(1);
			if (Mod_Systems::PressAnyKey())
				break;
			WAIT(1);
		}
		
		GAMEPLAY::SET_FADE_OUT_AFTER_DEATH(true);
		GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN(false);
		GAMEPLAY::_RESET_LOCALPLAYER_STATE();
	}
	void CamAction()
	{
		Vector3 Campo = Mod_Maths::PlayerPosi();
		Vector3 Camro = Mod_Maths::NewVector3(-90.00f, 0.00f, 0.00f);
		UI::DISPLAY_RADAR(false);
		Campo.z += 155.00f;
		char* CamsChar = "DEFAULT_SCRIPTED_CAMERA";
		Camera CameraObj = CAM::CREATE_CAM_WITH_PARAMS(CamsChar, Campo.x, Campo.y, Campo.z, Camro.x, Camro.y, Camro.z, 150.00f, true, 2);
		CAM::RENDER_SCRIPT_CAMS(1, 1, CameraObj, 0, 0);
		WAIT(3000);
		while (CAM::GET_CAM_COORD(CameraObj).z > Mod_Maths::PlayerPosi().z + 2.00f && !(bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()))
		{
			Campo.z -= 1.00f;
			CAM::SET_CAM_COORD((Any)CameraObj, Campo.x, Campo.y, Campo.z);
			WAIT(1);
		}
		CAM::RENDER_SCRIPT_CAMS(0, 1, 0, 0, 0);
		CAM::DESTROY_CAM(CameraObj, true);
		UI::DISPLAY_RADAR(true);
	}
	void Reicarnations()
	{
		Mod_Systems::LoggerLight("Reicarnations");

		Mod_Maths::AnyPreActives(0, false);
		Mod_Class::Vector4 DeathPlace = Mod_Maths::FindPedSpPoint(Mod_Maths::PlayerPosi());
		Ped Bob = NULL;

		if (!Mod_Data::Mod_Settings.Saved_Ped && !Mod_Data::Mod_Settings.Random_Ped && !Mod_Data::Mod_Settings.ReCurr)
			Mod_Data::Mod_Settings.ReCurr = true;

		if (!Mod_Data::Mod_Settings.ReCurr || Mod_Data::Mod_Settings.Random_Ped)
			Bob = NearByPed(DeathPlace, 35.0f, 500.0f);

		if (Mod_Settings.WatchDead)
			WatchDeath();

		while ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()))
			WAIT(100);

		if (Mod_Data::Mod_Settings.ReCurr)
			MoveEntity(PLAYER::PLAYER_PED_ID(), DeathPlace);
		else if (Mod_Data::Mod_Settings.Saved_Ped && (int)Mod_Data::SavedPeds.size() > 1)
		{
			MoveEntity(PLAYER::PLAYER_PED_ID(), DeathPlace);
			Mod_Class::ClothBank bank = Mod_Data::SavedPeds[Mod_Systems::LessRandomInt("SavedPedFind", 1, (int)Mod_Data::SavedPeds.size() - 1)];
			SavedPlayer(&bank, -1);
		}
		else
		{
			if (Bob != NULL && !Mod_Data::Yankton_Loaded && !Mod_Data::Cayo_Loaded)
				RepoPedPlayer(Bob);
			else 
			{
				if (Mod_Data::Yankton_Loaded)
					ChangePlayer(24, 0, 5);
				else if (Mod_Data::Cayo_Loaded)
					ChangePlayer(25, 3, 4);
				else
					ChangePlayer(4, 0, 1);

				MoveEntity(PLAYER::PLAYER_PED_ID(), DeathPlace);
			}
		}

		Mod_Systems::RandomWeatherTime();
		Mod_Systems::Play_wav(Mod_Data::Ahhhh);
		CAM::DO_SCREEN_FADE_IN(1500);
		CamAction();

		while (!(bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()))
		{
			WAIT(1000);
			break;
		}

		ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, true);
	}
	
	const std::vector<std::string> fluids = {
		"scr_solomon3",
		"scr_trev4_747_blood_splash",
		"cut_trevor1",
		"cs_trev1_blood_pool",
	};
	
	void CayoAudio()
	{
		if (Mod_Data::Cayo_Loaded)
		{
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_01_left", true);
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_02_right", true);
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_03_reverb", true);
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_04_reverb", true);
		}
		else
		{
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_01_left", false);
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_02_right", false);
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_03_reverb", false);
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_04_reverb", false);
		}
	}
	void CayoPartay()
	{
		const std::vector<Mod_Class::Vector4> CayoPartays = {
			Mod_Class::Vector4(4894.263f, -4913.141f, 3.36446f, 0.0f),     //Dance Rad == 5    00
			Mod_Class::Vector4(4890.318f, -4923.923f, 3.368097f, 0.0f),    //Dance Rad == 8    01
			Mod_Class::Vector4(4900.574f, -4923.098f, 3.36113f, 0.0f),     //Sit  Rad == 3     02
			Mod_Class::Vector4(4883.7f, -4916.323f, 3.368711f, 0.0f),      //Sit  Rad == 3     03
			Mod_Class::Vector4(4888.34f, -4933.511f, 3.367885f, 0.0f),     //Sit  Rad == 3     04
			Mod_Class::Vector4(4882.221f, -4933.872f, 3.37767f, 0.0f),     //Sit  Rad == 3     05
			Mod_Class::Vector4(4897.382f, -4938.688f, 3.362702f, 0.0f),    //Sit  Rad == 3     06
			Mod_Class::Vector4(4901.941f, -4935.71f, 3.363577f, 0.0f),     //Sit  Rad == 3     07
			Mod_Class::Vector4(4908.562f, -4934.384f, 3.367695f, 0.0f)     //Sit  Rad == 3	   08
		};

		const std::vector<Mod_Class::Vector4> CayoLay = {
			Mod_Class::Vector4(4878.054f, -4948.04f, 3.556281f, 91.67182f),
			Mod_Class::Vector4(4875.837f, -4950.161f, 3.629188f, 351.4073f),
			Mod_Class::Vector4(4874.032f, -4947.307f, 3.575044f, 242.7412f),
			Mod_Class::Vector4(4876.772f, -4946.251f, 3.520398f, 146.6341f),
			Mod_Class::Vector4(4872.481f, -4911.394f, 3.003824f, 294.576f),
			Mod_Class::Vector4(4872.82f, -4917.226f, 2.915241f,271.9123f),
			Mod_Class::Vector4(4871.187f, -4917.283f, 2.847157f,341.5042f),
			Mod_Class::Vector4(4871.44f, -4910.393f, 2.946956f, 288.3906f),
			Mod_Class::Vector4(4872.479f, -4911.321f, 3.003426f ,119.555f),
			Mod_Class::Vector4(4866.439f, -4906.744f, 2.577915f,106.9248f),
			Mod_Class::Vector4(4867.695f, -4910.954f, 2.650635f, 110.5905f),
			Mod_Class::Vector4(4867.171f, -4909.43f, 2.605493f ,101.497f),
			Mod_Class::Vector4(4868.493f, -4913.752f, 2.716372f, 283.9765f),
			Mod_Class::Vector4(4869.915f, -4921.263f, 2.879118f ,278.9364f),
			Mod_Class::Vector4(4868.144f, -4943.559f, 2.709443f,246.9356f),
			Mod_Class::Vector4(4862.854f, -4956.314f, 2.491656f, 64.97399f),
			Mod_Class::Vector4(4863.502f, -4955.183f, 2.544171f,78.42456f)
		};

		int iRan = Mod_Systems::RandomInt(4, 7);
		for (int i = 0; i < iRan; i++)
		{
			Mod_Class::Vector4 vDance = Mod_Maths::InAreaOf(CayoPartays[0], 2.0f, 5.0f);
			Ped Dancer = PlayerPedGen(vDance, 1, 0, true, true);
			Mod_Data::CayDancers.push_back(Dancer);
			DanceDanceDance(Dancer);
		}

		iRan = Mod_Systems::RandomInt(7, 13);

		for (int i = 0; i < iRan; i++)
		{
			Mod_Class::Vector4 vDance = Mod_Maths::InAreaOf(CayoPartays[1], 2.0f, 8.0f);
			Ped Dancer = PlayerPedGen(vDance, 1, 0, true, true);
			Mod_Data::CayDancers.push_back(Dancer);
			DanceDanceDance(Dancer);
		}

		for (int i = 2; i < CayoPartays.size(); i++)
		{
			Entity Chair = NULL;
			Chair = FindingProps(CayoPartays[i], 3.0f, "h4_prop_h4_couch_01a");

			if (Chair == NULL)
				Chair = FindingProps(CayoPartays[i], 3.0f, "h4_prop_h4_chair_01a");

			if (Chair != NULL)
			{
				ENTITY::FREEZE_ENTITY_POSITION(Chair, true);
				Mod_Class::Vector4 SunPos = Mod_Maths::GetPosV4(Chair);
				Ped Sitter = PlayerPedGen(SunPos, 1, 0, true, true);
				TakeAChair(Sitter, SunPos);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			Ped SunS = PlayerPedGen(CayoLay[i], 1, 0, true, true);
			SunningIt(SunS, CayoLay[i]);
		}

		for (int i = 4; i < CayoLay.size(); i++)
		{
			if (Mod_Systems::RandomInt(0, 20) < 10)
			{
				Ped SunS = PlayerPedGen(CayoLay[i], 1, 0, true, true);
				SunningIt(SunS, CayoLay[i]);
			}
		}

		Ped Dj = PlayerPedGen(Mod_Class::Vector4(4893.571f, -4905.296f, 3.481121f, 192.4766f), "IG_SSS", true, true);
		DanceDanceDance(Dj);
		Ped Bar = PlayerPedGen(Mod_Class::Vector4(4902.647f, -4943.707f, 3.392626f, 46.24336f), "S_F_Y_BeachBarStaff_01", true, true);
		DanceDanceDance(Bar);

		CayoAudio();
	}
}