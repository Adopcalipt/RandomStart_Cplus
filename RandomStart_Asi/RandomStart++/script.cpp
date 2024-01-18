/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2015
		--Modified By Adoppocalipt 2023--
*/


#include "script.h"
#include "ModSystems.h"

using namespace Mod_Data;
using namespace Mod_Systems;
using namespace UiSystem;
using namespace Locations;
using namespace EntityActions;

#include <string>
#include <vector>
#include <iostream>

#pragma warning(disable : 4244 4305) // double <-> float conversions

void PedditorMenu(Mod_Class::ClothBank* thisPed, int Main_Char, int iScale, float screenHeightScaleFactor);

bool Mod_Load = true;
std::string MainChar = "player_zero";
std::string FunChar01 = "player_one";
std::string FunChar02 = "player_two";
std::string FunChar03 = "mp_m_freemode_01";
std::string FunChar04 = "mp_f_freemode_01";

std::vector<Hash> MainProtags;
const std::vector<std::string> MultC = {
	"~r~", // Red
	"~b~", // Blue
	"~g~", // Green
	"~y~", // Yellow
	"~p~", // Purple
	"~o~" // Orange
};
std::vector<int> CheckScenarios()
{
    LoggerLight("CheckScenarios");
    std::vector<int> RanSenaro = {};

	if (Mod_Settings.BeachPed)
        RanSenaro.push_back(1);
    if (Mod_Settings.Tramps)
        RanSenaro.push_back(2);
    if (Mod_Settings.Highclass)
        RanSenaro.push_back(3);
    if (Mod_Settings.Midclass)
        RanSenaro.push_back(4);
    if (Mod_Settings.Lowclass)
        RanSenaro.push_back(5);
    if (Mod_Settings.Business)
        RanSenaro.push_back(6);
    if (Mod_Settings.Bodybuilder)
        RanSenaro.push_back(7);
    if (Mod_Settings.GangStars)
        RanSenaro.push_back(8);
    if (Mod_Settings.Epsilon)
        RanSenaro.push_back(9);
    if (Mod_Settings.Jogger)
        RanSenaro.push_back(10);
    if (Mod_Settings.Golfer)
        RanSenaro.push_back(11);
    if (Mod_Settings.Hiker)
        RanSenaro.push_back(12);
    if (Mod_Settings.Methaddict)
        RanSenaro.push_back(13);
    if (Mod_Settings.Rural)
        RanSenaro.push_back(14);
    if (Mod_Settings.Cyclist)
        RanSenaro.push_back(15);
    if (Mod_Settings.LGBTWXYZ)
        RanSenaro.push_back(16);
    if (Mod_Settings.PoolPeds)
        RanSenaro.push_back(17);
    if (Mod_Settings.Workers)
        RanSenaro.push_back(18);
    if (Mod_Settings.Jetski)
        RanSenaro.push_back(19);
    if (Mod_Settings.BikeATV)
        RanSenaro.push_back(20);
    if (Mod_Settings.Services)
        RanSenaro.push_back(21);
    if (Mod_Settings.Pilot)
        RanSenaro.push_back(22);
    if (Mod_Settings.Animals)
        RanSenaro.push_back(23);
    if (Mod_Settings.Yankton)
        RanSenaro.push_back(24);
    if (Mod_Settings.Cayo)
        RanSenaro.push_back(25);

    LoggerLight("CheckScenarios == " + std::to_string(RanSenaro.size()));
	return RanSenaro;
}
Mod_Class::ClothX GetYourTogs(Ped Peddy)
{
    LoggerLight("GetYourTogs");
    std::vector<int> ClothA = {};
    std::vector<int> ClothB = {};

    std::vector<int> ExtraA = {};
    std::vector<int> ExtraB = {};

    for (int i = 0; i < 12; i++)
    {
        int iDrawId = PED::GET_PED_DRAWABLE_VARIATION(Peddy, i);
        ClothA.push_back(iDrawId);
        int iTextId = PED::GET_PED_TEXTURE_VARIATION(Peddy, i);
        ClothB.push_back(iTextId);
    }

    for (int i = 0; i < 8; i++)
    {
        int iDrawId = PED::GET_PED_PROP_INDEX(Peddy, i);
        ExtraA.push_back(iDrawId);
        int iTextId = PED::GET_PED_PROP_TEXTURE_INDEX(Peddy, i);
        ExtraB.push_back(iTextId);
    }

    return Mod_Class::ClothX("Default", ClothA, ClothB, ExtraA, ExtraB);
}
Mod_Class::FaceBank FreeFaces(Ped Peddy, bool bFree)
{
    if (bFree)
    {
        HeadBlendData MyFace;
        PED::_GET_PED_HEAD_BLEND_DATA(Peddy, (Any*)&MyFace);

        return Mod_Class::FaceBank(MyFace.shapeFirstID, MyFace.shapeSecondID, MyFace.shapeMix, MyFace.skinMix, MyFace.thirdMix);
    }
    else
    {
        return Mod_Class::FaceBank(0, 0, 0.0f, 0.0f, 0.0f);
    }
}
int YourCharIs()
{
    Hash H1 = ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID());
    int YourChar = 0;
    if (H1 == MainProtags[0])
        YourChar = 1;//Michal
    else if (H1 == MainProtags[1])
        YourChar = 2;//Frank
    else if (H1 == MainProtags[2])
        YourChar = 3;//Trevor
    else if (H1 == MainProtags[3])
        YourChar = 4;//FreeMale
    else if (H1 == MainProtags[4])
        YourChar = 5;//FreeFemale
    return YourChar;
}

bool InTheSlamer = false;
Entity Excape[3] = { NULL,NULL,NULL };

void AccessAllAreas(bool togg)
{
    if (togg)
    {
        GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("restrictedareas");
        GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_armybase");
        GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_lossantosintl");
    }
    else
    {
        InTheSlamer = false;
        Excape[0] = NULL; Excape[1] = NULL; Excape[2] = NULL;
        PLAYER::SET_DISPATCH_COPS_FOR_PLAYER(PLAYER::PLAYER_ID(), true);
        SCRIPT::REQUEST_SCRIPT("restrictedareas");
        SCRIPT::REQUEST_SCRIPT("re_armybase");
        SCRIPT::REQUEST_SCRIPT("re_lossantosintl");
    }
    PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), togg);

    BackStagePass = togg;
}
void PrisonBreak()
{
    if (Excape[0] != NULL || Excape[1] != NULL || Excape[2] != NULL)
    {
        if (DistanceTo(Excape[0], PLAYER::PLAYER_PED_ID()) < 5.0f)
        {
            UiSystem::TopLeft(RSLangMenu[191]);
            if (Mod_Systems::WhileButtonDown(75, true))
            {
                CAM::DO_SCREEN_FADE_OUT(1);
                WAIT(1000);
                MoveEntity(PLAYER::PLAYER_PED_ID(), Mod_Class::Vector4(1240.87f, -3239.173f, 6.028764f, 274.899f));
                CAM::DO_SCREEN_FADE_IN(1000);
                ClearAllEntitys(true);
                AccessAllAreas(false);
            }
        }
        else if (DistanceTo(Excape[1], PLAYER::PLAYER_PED_ID()) < 5.0f)
        {
            UiSystem::TopLeft(RSLangMenu[192]);
            if (Mod_Systems::WhileButtonDown(75, true))
            {
                CAM::DO_SCREEN_FADE_OUT(1);
                WAIT(1000);
                Mod_Class::Vector4 Ppos = Mod_Class::Vector4(-352.8036f, -1553.918f, 26.20481f, 179.4799f);
                MoveEntity(PLAYER::PLAYER_PED_ID(), Ppos);
                RunAnimSeq(Mod_Class::AnimList(Mod_Class::AnimatedActions("switch@trevor@scares_tramp", "trev_scares_tramp_idle_tramp"), Mod_Class::AnimatedActions("switch@trevor@scares_tramp", "trev_scares_tramp_exit_tramp"), {}), Ppos);
                ClearAllEntitys(true);
                AccessAllAreas(false);
            }
        }
        else if (DistanceTo(Excape[2], PLAYER::PLAYER_PED_ID()) < 30.0f)
        {
            ClearAllEntitys(true);
            AccessAllAreas(false);
        }
    }
}
void InRestrictedArea()
{
    PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, 0);
    PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
    PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), true);
    PLAYER::SET_DISPATCH_COPS_FOR_PLAYER(PLAYER::PLAYER_ID(), false);
    GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prison");
    GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_armybase");
    GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_lossantosintl");
    AUDIO::STOP_ALARM("PRISON_ALARMS", 0);
    AUDIO::CLEAR_AMBIENT_ZONE_STATE((Any*)"AZ_COUNTRYSIDE_PRISON_01_ANNOUNCER_GENERAL", 0);
    AUDIO::CLEAR_AMBIENT_ZONE_STATE((Any*)"AZ_COUNTRYSIDE_PRISON_01_ANNOUNCER_WARNING", 0);
    if (InTheSlamer)
        PrisonBreak();
}

void Reposesion()
{
    int ScrollTime = 0;
    int Selecta = -1;
    Ped YoPlaya = PLAYER::PLAYER_PED_ID();
    std::vector<Ped> NearPeds = CollectPeds(-1);
    std::vector<Vector3> PedsPos = {};
    for (int i = 0; i < NearPeds.size(); i++)
    {
        ENTITY::SET_ENTITY_AS_MISSION_ENTITY(NearPeds[i], 1, 1);
        PedsPos.push_back(EntPosition(NearPeds[i]));
    }
    LoggerLight("Reposesion NearPeds == " + std::to_string((int)NearPeds.size()));

    if ((int)NearPeds.size() > 0)
    {
        ScrollTime = InGameTime() + 150;

        while (true)
        {
            WAIT(1);

            if (Selecta >= (int)NearPeds.size())
                break;

            TopLeft(RSLangMenu[211]);

            if (ScrollTime < InGameTime())
            {
                bool bEnt, bDel, bRight, bEsc;
                get_button_state(&bEnt, &bDel, NULL, NULL, NULL, &bRight, &bEsc);

                if (bDel || ButtonDown(45, true) || bEsc || ButtonDown(199, false))
                {
                    Selecta = (int)NearPeds.size();
                    break;
                }
                else if (bEnt || ButtonDown(21, true))
                {
                    if (Selecta > -1 && Selecta < (int)NearPeds.size())
                    {
                        RepoPedPlayer(NearPeds[Selecta]);
                        ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&NearPeds[Selecta]);
                        break;
                    }
                }
                else if (bRight || ButtonDown(46, true))
                {
                    ScrollTime = InGameTime() + 150;
                    if (Selecta > -1)
                        MoveEntity(NearPeds[Selecta], PedsPos[Selecta]);
                    Selecta++;

                    if (Selecta < (int)NearPeds.size())
                        MoveEntity(NearPeds[Selecta], FowardOf(YoPlaya, 2.0f, true));
                }
            }
        }

        for (int i = 0; i < NearPeds.size(); i++)
        {
            if (i != Selecta)
            {
                MoveEntity(NearPeds[i], PedsPos[i]);
                ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&NearPeds[i]);
            }
        }
    }

}

bool DeadOrArestCheck = true;
void DeathAndArrest(bool yaDeed)
{
    LoggerLight("DeathAndArrest");

    if (yaDeed)
    {
        if (Mod_Settings.Reincarnate)
            Reicarnations();
        else if (Mod_Settings.Random_Ped || Mod_Settings.Saved_Ped)
        {
            if (Mod_Settings.Funeral)
            {
                while ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()))
                    WAIT(1);

                WAIT(2000);

                SavedPlayer(&SavedPeds[0], -1);

                AnyPreActives(0, true);
                CAM::DO_SCREEN_FADE_IN(1000);

                Prop Coffin = BuildProps("prop_coffin_01", Mod_Class::Vector4(-278.3422f, 2844.4617f, 53.1f, -30.6686f), false, true);

                Ped Priest = PlayerPedGen(Mod_Class::Vector4(-276.5638f, 2844.45f, 53.75225f, 134.9461f), "ig_priest", true, true);
                PED::SET_PED_FLEE_ATTRIBUTES(Priest, 0, true);
                AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Priest, true);
                ForceAnim(Priest, "amb@world_human_bum_standing@depressed@base", "base", Mod_Class::Vector4(-276.5638f, 2844.45f, 53.75225f, 134.9461f));
                Ped Morn01 = PlayerPedGen(Mod_Class::Vector4(-281.5462f, 2844.153f, 54.07914f, 279.358f), FunChar01, true, true);
                PED::SET_PED_FLEE_ATTRIBUTES(Morn01, 0, true);
                AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Morn01, true);
                ForceAnim(Morn01, "amb@world_human_bum_standing@depressed@base", "base", Mod_Class::Vector4(-281.5462f, 2844.153f, 54.07914f, 279.358f));
                Ped Morn02 = PlayerPedGen(Mod_Class::Vector4(-276.7029f, 2841.419f, 53.96595f, 29.87679f), FunChar02, true, true);
                PED::SET_PED_FLEE_ATTRIBUTES(Morn02, 0, true);
                AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Morn02, true);
                ForceAnim(Morn02, "amb@world_human_bum_standing@depressed@base", "base", Mod_Class::Vector4(-276.7029f, 2841.419f, 53.96595f, 29.87679f));
                MoveEntity(PLAYER::PLAYER_PED_ID(), Mod_Class::Vector4(-281.0132f, 2840.851f, 54.34494f, 320.0452f));
                WAIT(10000);
                ClearAllEntitys(true);
            }
            else
            {
                while ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()))
                    WAIT(1);

                AnyPreActives(0, true);
                WAIT(2000);
                CAM::DO_SCREEN_FADE_IN(1000);
            }
        }
        else
        {
            while ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()))
                WAIT(1);

            AnyPreActives(0, true);
            WAIT(2000);
            CAM::DO_SCREEN_FADE_IN(1000);
        }
    }
    else
    {
        if (Mod_Settings.Prison)
        {
            while ((bool)PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
                WAIT(100);

            AnyPreActives(0, true);

            Excape[0] = (Entity)VehicleSpawn(Mod_Class::Veh_Set("mule", true, false, false, false, false, 50, 0, Mod_Class::Vector4(1638.30933f, 2598.91235f, 45.7980385f, -90.483223f), {}));

            Excape[1] = (Entity)BuildProps("prop_bin_14b", Mod_Class::Vector4(1689.59119f, 2541.75879f, 44.5688019f, 0.343875527f), false, true);

            Excape[2] = (Entity)BuildProps("prop_billboard_01", Mod_Class::Vector4(1816.44531f, 2561.75342f, 35.9052734f, 137.27359f), false, true);
            BuildProps("prop_scafold_08a", Mod_Class::Vector4(1805.90271f, 2557.1521f, 44.5995445f, -93.2685471f), false, true);
            BuildProps("prop_scafold_frame1a", Mod_Class::Vector4(1806.40466f, 2565.1394f, 44.5535889f, -90.8649368f), false, true);
            BuildProps("prop_scafold_frame1a", Mod_Class::Vector4(1806.39429f, 2565.16406f, 47.5116577f, -94.7868576f), false, true);
            BuildProps("prop_scafold_frame1a", Mod_Class::Vector4(1806.36267f, 2565.12549f, 50.5853157f, -93.2752533f), false, true);
            BuildProps("prop_billboard_10", NewVector3(1801.08032f, 2565.73584f, 55.1660233f), NewVector3(90.0f, -14.5189629f, 0.0f), false, true);
            BuildProps("prop_scafold_08a", Mod_Class::Vector4(1793.73547f, 2558.6228f, 44.5651245f, -100.426994f), false, true);
            BuildProps("prop_scafold_frame1a", Mod_Class::Vector4(1795.18201f, 2566.43213f, 44.535038f, -100.323944f), false, true);
            BuildProps("prop_scafold_frame1a", Mod_Class::Vector4(1795.18201f, 2566.43213f, 47.4849854f, -100.323936f), false, true);
            BuildProps("prop_scafold_frame1a", Mod_Class::Vector4(1795.18201f, 2566.43213f, 50.5544701f, -100.323929f), false, true);

            WAIT(2000);
            CAM::DO_SCREEN_FADE_IN(1000);

            InTheSlamer = true;
            AccessAllAreas(true);

            MoveEntity(PLAYER::PLAYER_PED_ID(), Mod_Class::Vector4(1658.052f, 2543.221f, 45.56487f, 320.0452f));
        }
        else
        {
            while ((bool)PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
                WAIT(100);

            AnyPreActives(0, true);
            WAIT(2000);
            CAM::DO_SCREEN_FADE_IN(1000);
        }
    }

    DeadOrArestCheck = true;
}

bool GotClutter = false;
const std::vector<std::string> TrampSigns = {
    "prop_beggers_sign_01", "prop_beggers_sign_02", "prop_beggers_sign_03", "prop_beggers_sign_04" 
};
void RandomLocation(int iSelect)
{
    LoggerLight("RandomLocation iSelect == " + std::to_string(iSelect));

    PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, 0);
    PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);

    CAM::DO_SCREEN_FADE_OUT(1);
    SideAdviceNote();
    ClearAllEntitys(true);
    AnyPreActives(iSelect, true);

    bool FuVec = false;
    bool IplFail = false;
    bool Plane = false;
    bool Heli = false;
    bool PlayerInVeh = true;
    bool PlayerDrives = true;
    bool FillVeh = false;

    std::string NSPMLaunch = "";
    std::vector<Mod_Class::Vector4> MultiSpot = {};
    Mod_Class::Vector4 MySpot = Mod_Class::Vector4(0.0f, 0.0f, 0.0f, 0.0f);
    Mod_Class::FubarVectors MySpotFu = Mod_Class::FubarVectors(0, Mod_Class::Vector4(0, 0, 0, 0), Mod_Class::Vector4(0, 0, 0, 0),"", 0);

    int Action = 0;    //1-DriveVeh  2-Sunbath  3-TrampSign  4-TrampSleap  5-MuscleBeach  6-GangWars  7-Jogger  8-EnterVeh  9-Meth  10-Gardener  11-Dancing  12-Sitting  15+-NSPM
    int WeaponSet = 0;
    int SubSet = -1;
    int Seat = -1;
    int RanDriveTo = -1;

    if (iSelect == 1)
    {
        TIME::SET_CLOCK_TIME(12,0,0);
        WeatherReport(1);

        if (LessRandomInt("RandomDriver", 1, 4) < 2)
            PlayerDrives = false;

        FillVeh = true;

        if (LessRandomInt("RandomLocations01", 1, 4) < 2)
        {
            MultiSpot.push_back(BeachBoat[LessRandomInt("RandomLocations01a", 0, (int)BeachBoat.size() - 1)]);
            MultiSpot.push_back(BeachBoat[LessRandomInt("RandomLocations01a", 0, (int)BeachBoat.size() - 1)]);
            Action = 1;
        }
        else
        {
            int iMultiStop = LessRandomInt("RandomLocations01b", 0, (int)BeachLay.size() - 1);
            Mod_Class::Vector4 Vpos = BeachLay[iMultiStop];
            MultiSpot.push_back(Vpos);

            for (int i = 0; i < (int)BeachLay.size(); i++)
            {
                if (DistanceTo(Vpos, BeachLay[i]) < 10.0f && i != iMultiStop)
                    MultiSpot.push_back(BeachLay[i]);
            }
            Action = 2;
        }
    }                 //Beach Ped
    else if (iSelect == 2)
    {
        int iW = 6;
        if (CanSnow)
            iW = 11;

        WeatherReport(iW);

        if (LessRandomInt("RandomLocations02", 1, 4) < 2)
        {
            TIME::SET_CLOCK_TIME(12, 0, 0);
            MySpot = TrampSign[LessRandomInt("RandomLocations02a", 0, (int)TrampSign.size() - 1)];
            Action = 3;
        }           //HoldSign Tramp
        else
        {
            TIME::SET_CLOCK_TIME(3, 0, 0);
            MySpot = TrampSleap[LessRandomInt("RandomLocations02b", 0, (int)TrampSleap.size() - 1)];
            Action = 4;
        }
      
        WeaponSet = 1;
    }            //Tramps
    else if (iSelect == 3)
    {
        TIME::SET_CLOCK_TIME(12, 0, 0);
        WeatherReport(1);
        Action = 8;
        MySpotFu = HighClass[LessRandomInt("RandomLocations03", 0, (int)HighClass.size() - 1)];
        WeaponSet = 2;
    }            //High class
    else if (iSelect == 4)
    {
        RandomWeatherTime(); 
        Action = 8;
        MySpotFu = MidClass[LessRandomInt("RandomLocations04", 0, (int)MidClass.size() - 1)];
        WeaponSet = 3;
    }            //Mid class
    else if (iSelect == 5)
    {
        int iW = 6;
        if (CanSnow)
            iW = 11;

        WeatherReport(iW);

        Action = 8;
        MySpotFu = LowClass[LessRandomInt("RandomLocations05", 0, (int)LowClass.size() - 1)];
        WeaponSet = 3;
    }            //Low class
    else if (iSelect == 6)
    {
        RandomWeatherTime();

        if (LessRandomInt("RandomLocations06", 1, 4) < 2)
        {
            MySpot = Buisness[LessRandomInt("RandomLocations06a", 0, (int)Buisness.size() - 1)];
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else
        {
            int iRanLand = LessRandomInt("RandomLocations06b", 1, 5);
            if (iRanLand == 1)
                MultiSpot = BuisnessHeli01;
            else if (iRanLand == 2)
                MultiSpot = BuisnessHeli02;
            else if (iRanLand == 3)
                MultiSpot = BuisnessHeli03;
            else if (iRanLand == 4)
                MultiSpot = BuisnessHeli04;
            else if (iRanLand == 5)
                MultiSpot = BuisnessHeli05;

            Heli = true;
            PlayerDrives = false;
            FillVeh = true;
            PlayerInVeh = true;
            Action = 1;
        }
        SubSet = 1;
    }            //Buisness
    else if (iSelect == 7)
    {
        TIME::SET_CLOCK_TIME(12, 0, 0);
        WeatherReport(1);

        SubSet = LessRandomInt("RandomLocations07", 0, (int)BodyBeach.size() - 1);
        MySpot = BodyBeach[SubSet];
        Action = 5;
    }            //Body builder
    else if (iSelect == 8)
    {
        RandomWeatherTime();
        SubSet = LessRandomInt("RandomLocations08", 1, 11);
        Action = 6;
        WeaponSet = 9;
    }            //GangStars             
    else if (iSelect == 9)
    {
        RandomWeatherTime();
        MySpot = Epslon[LessRandomInt("RandomLocations09", 0, (int)Epslon.size() - 1)];
        MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
    }            //Epslon
    else if (iSelect == 10)
    {
        RandomWeatherTime();
        SubSet = LessRandomInt("RandomLocations10", 1, 30);
        Action = 7;
    }           //Jogger
    else if (iSelect == 11)
    {
        TIME::SET_CLOCK_TIME(12, 0, 0);
        WeatherReport(1);

        if (LessRandomInt("RandomLocations11", 1, 4) < 2)
        {
            MultiSpot = GolfCaddy;
            FillVeh = true;
            RanDriveTo = LessRandomInt("RandomLocations11b", 0, (int)GolfCaddy.size() -1);
            Action = 1;
        }
        else
        {
            MySpot = GolfTee[LessRandomInt("RandomLocations11a", 0, (int)GolfTee.size() - 1)];
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        WeaponSet = 6;
    }           //Golf
    else if (iSelect == 12)
    {
        TIME::SET_CLOCK_TIME(12, 0, 0);
        WeatherReport(1);

        MySpot = Hiker[LessRandomInt("RandomLocations12", 0, (int)Hiker.size() - 1)];
        MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
    }           //Hiker
    else if (iSelect == 13)
    {
        RandomWeatherTime();
        MySpot = MethodActing[LessRandomInt("RandomLocations13", 0, (int)MethodActing.size() - 1)];
        Action = 9;
        WeaponSet = 1;
    }           //Meth
    else if (iSelect == 14)
    {
        RandomWeatherTime();
        if (LessRandomInt("RandomLocations12", 1, 4) < 2)
        {
            MySpot = FarmingVeh[LessRandomInt("RandomLocations14a", 0, (int)FarmingVeh.size() - 1)];
            Action = 1;
        }
        else
        {
            MySpot = Farming[LessRandomInt("RandomLocations14b", 0, (int)Farming.size() - 1)];
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        WeaponSet = 4;
    }           //Rural
    else if (iSelect == 15)
    {
        TIME::SET_CLOCK_TIME(12, 0, 0);
        WeatherReport(1);
        SubSet = LessRandomInt("RandomLocations13", 1, 4);
        if (SubSet == 1)
            MultiSpot = CycleRacer;      //Racer
        else if (SubSet == 2)
            MultiSpot = CycleMountain;      //Mountain
        else if (SubSet == 3)
            MultiSpot = CycleBMX;      //BMX
        else
            MultiSpot = CycleCruser;      //Cruser

        RanDriveTo = LessRandomInt("RandomLocations13a", 0, (int)MultiSpot.size() - 1);
        Action = 1;
    }           //Cycles
    else if (iSelect == 16)
    {
        TIME::SET_CLOCK_TIME(21, 0, 0);
        MySpot = LGBQWXYZ[LessRandomInt("RandomLocations16", 0, (int)LGBQWXYZ.size() - 1)];
        MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
    }           //LGBTWXYZ
    else if (iSelect == 17)
    {
        TIME::SET_CLOCK_TIME(12, 0, 0);
        WeatherReport(1);
        if (LessRandomInt("RandomLocations17", 0, 4) < 2)
        {
            MySpot = PoolPlace[LessRandomInt("RandomLocations17a", 0, (int)PoolPlace.size() - 1)];
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else
        {
            MySpot = BeachLounger[LessRandomInt("RandomLocations17b", 0, (int)BeachLounger.size() - 1)];
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot); 
            WAIT(1000);
            Action = 12;
        }
    }           //Pool Peds   
    else if (iSelect == 18)
    {
        RandomWeatherTime();

        SubSet = LessRandomInt("RandomLocations18", 1, 23);
        if (SubSet == 1)
        {
            MySpot = Worker_Autoshop[LessRandomInt("RandomLocations18a", 0, (int)Worker_Autoshop.size() - 1)];//"Autoshop Worker 2"); 
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else if (SubSet == 2)
        {
            MySpot = Worker_Waiter[LessRandomInt("RandomLocations18b", 0, (int)Worker_Waiter.size() - 1)];//"Waiter") ; 
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else if (SubSet == 3)
        {
            MySpot = Worker_Sweatshop[LessRandomInt("RandomLocations18c", 0, (int)Worker_Sweatshop.size() - 1)];//"Sweatshop Worker  
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else if (SubSet == 4)
        {
            MySpot = Worker_Shopkeeper[LessRandomInt("RandomLocations18d", 0, (int)Worker_Shopkeeper.size() - 1)];//"Shopkeeper (Male)"); 
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else if (SubSet == 5)
        {
            MySpot = Worker_Doctor[LessRandomInt("RandomLocations18e", 0, (int)Worker_Doctor.size() - 1)];//"Doctor"); 
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else if (SubSet == 6)
        {
            MySpot = Worker_Maid[LessRandomInt("RandomLocations18f", 0, (int)Worker_Maid.size() - 1)];//"Maid
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else if (SubSet == 7)
        {
            if (NSPM_Include)
            {
                NSPMLaunch = "" + GetDir() + "/Scripts/NSPM/RequestGroupS.txt";
                MySpot = GroupSixStarts[LessRandomInt("RandomLocations18g1", 0, (int)GroupSixStarts.size() - 1)];
            }
            else
            {
                MySpot = Worker_Security[LessRandomInt("RandomLocations18g", 0, (int)Worker_Security.size() - 1)];
                FillVeh = true;
            }
            Action = 1;
        }       //"Armoured Van Security 2"); 
        else if (SubSet == 8)
        {
            MySpot = Worker_Guard[LessRandomInt("RandomLocations18h", 0, (int)Worker_Guard.size() - 1)];
            FillVeh = true;
            Action = 1;
        }       //"Security Guard"); 
        else if (SubSet == 9)
        {
            MySpot = Worker_Scientist[LessRandomInt("RandomLocations18i", 0, (int)Worker_Scientist.size() - 1)];//"Scientist");  
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else if (SubSet == 10)
        {
            MySpot = Worker_Chemical[LessRandomInt("RandomLocations18j", 0, (int)Worker_Chemical.size() - 1)]; //"Chemical Plant Worker");  
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else if (SubSet == 11)
        {
            MySpot = Worker_Construct[LessRandomInt("RandomLocations18k", 0, (int)Worker_Construct.size() - 1)];
            Action = 1;
        }       //"construction Worker 2"); 
        else if (SubSet == 12)
        {
            MySpot = Worker_Dock[LessRandomInt("RandomLocations18l", 0, (int)Worker_Dock.size() - 1)];
            Action = 1;
        }       //"Dock Worker");  
        else if (SubSet == 13)
        {
            MySpot = Worker_Airport[LessRandomInt("RandomLocations18m", 0, (int)Worker_Airport.size() - 1)];
            Action = 1;
            AccessAllAreas(true);
        }       //Airport
        else if (SubSet == 14)
        {
            MySpot = Mod_Class::Vector4(-304.5138f, -1544.802f, 25.85103f, 154.0407f);
            PlayerDrives = false;
            Seat = 2;
            Action = 13;
        }       //"Garbage Worker");  
        else if (SubSet == 15)
        {
            MySpot = Worker_Handyman[LessRandomInt("RandomLocations18n", 0, (int)Worker_Handyman.size() - 1)];
            Action = 10;
        }       //"Latino Handyman Male"); 
        else if (SubSet == 16)
        {
            MySpot = Worker_Metro[LessRandomInt("RandomLocations18o", 0, (int)Worker_Metro.size() - 1)];//"LS Metro Worker Male");  
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else if (SubSet == 17)
        {
            MySpot = Worker_Transport[LessRandomInt("RandomLocations18p", 0, (int)Worker_Transport.size() - 1)];
            Action = 1;
        }       //"Transport Worker Male");  
        else if (SubSet == 18)
        {
            MySpot = Mod_Class::Vector4(139.4768f, -3103.723f, 5.89631f, 353.8674f);//"Pest Control");  
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else if (SubSet == 19)
        {
            MySpot = Worker_Postal[LessRandomInt("RandomLocations18q", 0, (int)Worker_Postal.size() - 1)];
            Action = 1;
        }       //"Postal Worker Male 2");  
        else if (SubSet == 20)
        {
            if (NSPM_Include)
            {
                NSPMLaunch = "" + GetDir() + "/Scripts/NSPM/RequestDelivery.txt";
                MySpot = DeliveryStarts[LessRandomInt("RandomLocations18r1", 0, (int)DeliveryStarts.size() - 1)];
            }
            else
            {
                MySpot = Worker_UPS[LessRandomInt("RandomLocations18r", 0, (int)Worker_UPS.size() - 1)];
            }
            Action = 1;
        }       //"UPS Driver 2");
        else if (SubSet == 21)
        {
            MySpot = Worker_Vendor[LessRandomInt("RandomLocations18s", 0, (int)Worker_Vendor.size() - 1)];//"Street Vendor Young");  
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }
        else if (SubSet == 22)
        {
            if (NSPM_Include)
            {
                TIME::SET_CLOCK_TIME(18, 0, 0);
                NSPMLaunch = "" + GetDir() + "/Scripts/NSPM/RequestValey.txt";
                MySpot = Mod_Class::Vector4(935.7204f, 46.89984f, 80.09576f, 125.0f);
                MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
                WriteFile(NSPMLaunch, std::vector<std::string>{"blank"});
            }
            else
                MySpot = Mod_Class::Vector4(927.10f, 52.47f, 80.09f, 53.27f);
        }       //"Valet");  
        else
        {
            MySpot = Worker_Window[LessRandomInt("RandomLocations18t", 0, (int)Worker_Window.size() - 1)];//"Window Cleaner");
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }

    }           //Workers  
    else if (iSelect == 19)
    {
        TIME::SET_CLOCK_TIME(12, 0, 0);
        WeatherReport(1);

        MySpot = JetSki[LessRandomInt("RandomLocations19", 0, (int)JetSki.size() - 1)];
        Action = 1;
    }           //jet ski Male                  
    else if (iSelect == 20)
    {
        TIME::SET_CLOCK_TIME(12, 0, 0);
        WeatherReport(1);

        SubSet = LessRandomInt("RandomLocations20", 1, 4);
        if (SubSet == 1)
            MultiSpot = OffRoadRace01;
        else if (SubSet == 2)
            MultiSpot = OffRoadRace02;
        else if (SubSet == 3)
            MultiSpot = OffRoadRace03;
        else
            MultiSpot = OffRoadRace04;
        Action = 1;

        RanDriveTo = LessRandomInt("RandomLocations20a", 0, (int)MultiSpot.size() - 1);
    }           //Bike/ATV Male
    else if (iSelect == 21)
    {
        RandomWeatherTime();

        SubSet = LessRandomInt("RandomLocations21", 1, 11);

        if (SubSet == 1)
        {
            TIME::SET_CLOCK_TIME(12, 0, 0);
            WeatherReport(1);

            MySpot = Service_Baywatch[LessRandomInt("RandomLocations21a", 0, (int)Service_Baywatch.size() - 1)];
            Action = 1;
            if (NSPM_Include)
            {
                NSPMLaunch = "" + GetDir() + "/Scripts/NSPM/RequestSharks.txt";
                WriteFile(NSPMLaunch, std::vector<std::string>{"blank"});
            }
            WeaponSet = 1;
        }            //"Baywatch 
        else if (SubSet == 2)
        {
            MySpot = Service_Coastguard[LessRandomInt("RandomLocations21b", 0, (int)Service_Coastguard.size() - 1)];
            FillVeh = true;
            Deputize = true;
            Action = 1;
        }       //"US Coastguard
        else if (SubSet == 3)
        {
            MultiSpot = CopsOnPatrol;
            //MySpot = Service_Cops[LessRandomInt("RandomLocations21c", 0, (int)Service_Cops.size() - 1)];
            RanDriveTo = LessRandomInt("RandomLocations20a", 0, (int)MultiSpot.size() - 1);
            FillVeh = true;
            Deputize = true;
            PlayerDrives = false;
            Action = 1;
        }       //><!--Cops
        else if (SubSet == 4)
        {
            MySpot = Service_CopsBike[LessRandomInt("RandomLocations21d", 0, (int)Service_CopsBike.size() - 1)];
            Deputize = true;
            Action = 1;
        }       //><!-- PoliceBike
        else if (SubSet == 5)
        {
            MultiSpot = RangersOnPatrol;
            //MySpot = Service_CopsRanger[LessRandomInt("RandomLocations21e", 0, (int)Service_CopsRanger.size() - 1)];
            RanDriveTo = LessRandomInt("RandomLocations20a", 0, (int)MultiSpot.size() - 1);
            FillVeh = true;
            Deputize = true;
            PlayerDrives = false;
            Action = 1;
        }       //><!-- Ranger
        else if (SubSet == 6)
        {
            MultiSpot = CopsOnPatrol;
            //MySpot = Service_Sherif[LessRandomInt("RandomLocations21f", 0, (int)Service_Sherif.size() - 1)];
            RanDriveTo = LessRandomInt("RandomLocations20a", 0, (int)MultiSpot.size() - 1);
            FillVeh = true;
            Deputize = true;
            PlayerDrives = false;
            Action = 1;
        }       //><!-- Sherif
        else if (SubSet == 7)
        {
            MySpot = Service_Fib[LessRandomInt("RandomLocations21g", 0, (int)Service_Fib.size() - 1)];
            FillVeh = true;
            Deputize = true;
            Action = 1;
        }       //><!-- fib
        else if (SubSet == 8)
        {
            MySpot = Service_Swat[LessRandomInt("RandomLocations21h", 0, (int)Service_Swat.size() - 1)];
            FillVeh = true;
            Deputize = true;
            Action = 1;
        }       //><!-- swat
        else if (SubSet == 9)
        {
            MySpot = Service_Military[LessRandomInt("RandomLocations21i", 0, (int)Service_Military.size() - 1)];
            FillVeh = true;
            Deputize = true;
            Action = 1;
            AccessAllAreas(true);
        }       //military
        else if (SubSet == 10)
        {
            if (NSPM_Include)
            {
                NSPMLaunch = "" + GetDir() + "/Scripts/NSPM/RequestMedic.txt";
                MySpot = AmbulanceStarts[LessRandomInt("RandomLocations21j2", 0, (int)AmbulanceStarts.size() - 1)];

            }
            else
                MySpot = Service_Medic[LessRandomInt("RandomLocations21j", 0, (int)Service_Medic.size() - 1)];

            Action = 1;
        }      //medic
        else
        {
            if (NSPM_Include)
            {
                NSPMLaunch = "" + GetDir() + "/Scripts/NSPM/RequestFire.txt";
                MySpot = FireStarts[LessRandomInt("RandomLocations21k1", 0, (int)FireStarts.size() - 1)];
            }
            else
            {
                MySpot = Service_Fireman[LessRandomInt("RandomLocations21k", 0, (int)Service_Fireman.size() - 1)];
                FillVeh = true;
            }
            Action = 1;
            
            Deputize = true;
        }      //fireman
    }           //Services 
    else if (iSelect == 22)
    {
        RandomWeatherTime();

        SubSet = LessRandomInt("RandomLocations22", 1, 4);

        if (SubSet == 1)
        {
            MultiSpot.push_back(Flight_Civi[LessRandomInt("RandomLocations22a", 0, (int)Flight_Civi.size() - 1)]);
            MultiSpot.push_back(Mod_Class::Vector4(-2352.11f, 2274.94f, 1500.0f, 0.0f));
            Plane = true;
            FillVeh = true;
            Action = 1;
        }       //civilian
        else if (SubSet == 2)
        {
            MultiSpot.push_back(Flight_Milatary[LessRandomInt("RandomLocations22b", 0, (int)Flight_Milatary.size() - 1)]);
            MultiSpot.push_back(Mod_Class::Vector4(-2352.11f, 2274.94f, 1500.0f, 0.0f));
            Plane = true;
            FillVeh = true;
            Action = 1;
        }       //milatary
        else if (SubSet == 3)
        {
            MultiSpot = Flight_HeliPerto;
            Heli = true;
            FillVeh = true;
            Action = 1;
            RanDriveTo = LessRandomInt("RandomLocations22c", 0, (int)MultiSpot.size() - 1);
        }       //helitours
        else
        {
            MultiSpot = Flight_HeliPaleto;
            Heli = true;
            FillVeh = true;
            Action = 1;
            RanDriveTo = LessRandomInt("RandomLocations22d", 0, (int)MultiSpot.size() - 1);
        }      //PaletoHeli
    }           //Pilot
    else if (iSelect == 23)
    {
        RandomWeatherTime();

        if (!Mod_Settings.Random_Ped || Mod_Settings.Saved_Ped)
            SubSet = LessRandomInt("RandomLocations23a", 1, 11);
        else
            SubSet = LessRandomInt("RandomLocations23b", 1, 14);

        if (SubSet == 1)
            MySpot = Animals_Boar[LessRandomInt("RandomLocations23c", 0, (int)Animals_Boar.size() - 1)];//a_c_boar
        else if (SubSet == 2)
            MySpot = Animals_CatsDogs[LessRandomInt("RandomLocations23d", 0, (int)Animals_CatsDogs.size() - 1)];//cats/dogs
        else if (SubSet == 3)
            MySpot = Animals_Pigeon[LessRandomInt("RandomLocations23e", 0, (int)Animals_Pigeon.size() - 1)];//a_c_pigeon
        else if (SubSet == 4)
            MySpot = Animals_Rat[LessRandomInt("RandomLocations23f", 0, (int)Animals_Rat.size() - 1)];//a_c_rat
        else if (SubSet == 5)
            MySpot = Animals_Cow[LessRandomInt("RandomLocations23g", 0, (int)Animals_Cow.size() - 1)];//a_c_cow
        else if (SubSet == 6)
            MySpot = Animals_Coyote[LessRandomInt("RandomLocations23h", 0, (int)Animals_Coyote.size() - 1)];//a_c_coyote
        else if (SubSet == 7)
            MySpot = Animals_Crow[LessRandomInt("RandomLocations23i", 0, (int)Animals_Crow.size() - 1)];//a_c_crow
        else if (SubSet == 8)
            MySpot = Animals_DeerRabit[LessRandomInt("RandomLocations23j", 0, (int)Animals_DeerRabit.size() - 1)];//a_c_deer/a_c_rabbit_01
        else if (SubSet == 9)
            MySpot = Animals_Hen[LessRandomInt("RandomLocations23k", 0, (int)Animals_Hen.size() - 1)];//a_c_hen                
        else if (SubSet == 10)
            MySpot = Animals_Lion[LessRandomInt("RandomLocations23l", 0, (int)Animals_Lion.size() - 1)];//a_c_mtlion-mountain lion
        else if (SubSet == 11)
            MySpot = Animals_Pig[LessRandomInt("RandomLocations23m", 0, (int)Animals_Pig.size() - 1)];//a_c_pig
        else if (SubSet == 12)
            MySpot = Animals_Fish[LessRandomInt("RandomLocations23n", 0, (int)Animals_Fish.size() - 1)];//Fish/sharks
        else if (SubSet == 13)
            MySpot = Animals_Hawk[LessRandomInt("RandomLocations23o", 0, (int)Animals_Hawk.size() - 1)];//a_c_chickenhawk
        else
            MySpot = Animals_Corm[LessRandomInt("RandomLocations23p", 0, (int)Animals_Corm.size() - 1)];//a_c_cormorant

        MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
    }           //Animals
    else if (iSelect == 24)
    {
        WeatherReport(RandomInt(10, 13));

        if (LessRandomInt("RandomLocations24", 1, 4) < 2)
            MySpot = Yankton[LessRandomInt("RandomLocations24a", 0, (int)Yankton.size() - 1)];
        else
        {
            MySpot = YanktonVeh[LessRandomInt("RandomLocations24b", 0, (int)YanktonVeh.size() - 1)];
            Action = 1;
        }
        WeaponSet = 5;

        if (!Yankton_Loaded)
            IplFail = YanktonIPL();
        if (!IplFail)
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
    }           //North Yankton
    else if (iSelect == 25)
    {
        TIME::SET_CLOCK_TIME(12, 0, 0);
        WeatherReport(1);

        SubSet = LessRandomInt("RandomLocations25", 1, 6);
        if (SubSet == 1)
        {
            MySpot = Mod_Class::Vector4(4979.349f, -5764.603f, 20.87796f, 45.00f);//A_C_Panther
        }
        else if (SubSet == 2)
        {
            MySpot = Cayo_Beach[LessRandomInt("RandomLocations25a", 0, (int)Cayo_Beach.size() - 1)];
            Action = 11;
        }       //A_F_Y_Beach_02
        else if (SubSet == 3)
        {
            if (LessRandomInt("RandomLocations31", 1, 4) < 2)
                MySpot = Cayo_Guard[LessRandomInt("RandomLocations25b", 0, (int)Cayo_Guard.size() - 1)];
            else
            {
                MySpot = Cayo_GuardVeh[LessRandomInt("RandomLocations25c", 0, (int)Cayo_GuardVeh.size() - 1)];
                Action = 1;
            }
            WeaponSet = 5;
        }       //Guard
        else if (SubSet == 4)
            MySpot = Mod_Class::Vector4(4904.958f, -4941.593f, 3.378354f, 37.49379f); //Bar
        else if (SubSet == 5)
            MySpot = Cayo_Workers[LessRandomInt("RandomLocations25d", 0, (int)Cayo_Workers.size() - 1)];//worker
        else if (SubSet == 6)
        {
            MySpot = Mod_Class::Vector4(4499.6f, -4523.962f, 4.412367f, 276.4212f);
            Action = 12;
        }       //pilot
        else
            MySpot = Mod_Class::Vector4(4877.928f, -4488.06f, 26.93383f, 7.88381f);//randomOther??


        if (!Cayo_Loaded)
            IplFail = CayoPericoIPL();

        if (!IplFail)
        {
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            EntityActions::CayoPartay();
        }
    }                              //Cayo Perico

    LoggerLight("RandomLocation SubSet == " + std::to_string(SubSet));

    if (IplFail)
        RandomLocation(1);
    else
    {
        int MySaved = -1;

        if (Mod_Settings.Random_Ped)
            ChangePlayer(iSelect, SubSet, WeaponSet);
        else if (Mod_Settings.Saved_Ped && (int)SavedPeds.size() > 1)
        {
            MySaved = LessRandomInt("SavedPedFind", 1, (int)SavedPeds.size() - 1);
            SavedPlayer(&SavedPeds[MySaved], WeaponSet);
        }

        if (MySaved != -1)
        {
            if (SavedPeds[MySaved].Animal_Farm)
            {
                Action = 0;
                Deputize = false;
                if (!Yankton_Loaded && !Cayo_Loaded)
                    MoveEntity(PLAYER::PLAYER_PED_ID(), Animals_Boar[LessRandomInt("RandomLocations23c", 0, (int)Animals_Boar.size() - 1)]);
            }
        }

        if (Deputize)
           PoliceAcadamy(Deputize);

        if (Action == 1)
        {
            CAM::DO_SCREEN_FADE_IN(4000);
            Vehicle Vbob = NULL;
            std::string Car = RandVeh(iSelect, SubSet);
            Mod_Class::Veh_Set MyVehSet = Mod_Class::Veh_Set(Car, Plane, Heli, PlayerInVeh, PlayerDrives, FillVeh, iSelect, SubSet, MySpot, { });
            if (MultiSpot.size() > 1)
            {

                MyVehSet.SpawnPoint = MultiSpot[0];
                MyVehSet.DriveTo = MultiSpot;
                if (RanDriveTo != -1)
                {
                    MyVehSet.RanDriveTo = RanDriveTo;
                    if (RanDriveTo == 0)
                        MyVehSet.SpawnPoint = MultiSpot[(int)MultiSpot.size() - 1];
                    else
                        MyVehSet.SpawnPoint = MultiSpot[RanDriveTo - 1];
                }

                Vbob = VehicleSpawn(MyVehSet);
            }
            else
                Vbob = VehicleSpawn(MyVehSet);

            if (PlayerDrives && Vbob != NULL)
                VEHICLE::_0xCFD778E7904C255E((Any)Vbob);

            if (NSPMLaunch != "")
                WriteFile(NSPMLaunch, std::vector<std::string>{ std::to_string((int)Vbob)});

            GotClutter = true;

        }//DriveVeh
        else if (Action == 2)
        {
            CAM::DO_SCREEN_FADE_IN(4000);
            if ((int)MultiSpot.size() > 1)
            {
                bool btrue = true;
                for (int i = 1; i < (int)MultiSpot.size(); i++)
                {
                    btrue = !btrue;
                    Ped Peddy = PlayerPedGen(MultiSpot[i], iSelect, SubSet, true, true);
                    SunningIt(Peddy, MultiSpot[i]);
                }
            }

            MoveEntity(PLAYER::PLAYER_PED_ID(), MultiSpot[0]);

            int iPose = LessRandomInt("RandsAction2", 0, 20);
            if (iPose < 10)
            {
                if (PED::IS_PED_MALE(PLAYER::PLAYER_PED_ID()))
                    RunAnimSeq(SunbathebackM, MultiSpot[0]);
                else
                    RunAnimSeq(SunbathebackF, MultiSpot[0]);
            }
            else
            {
                if (PED::IS_PED_MALE(PLAYER::PLAYER_PED_ID()))
                    RunAnimSeq(SunbathefrontM, MultiSpot[0]);
                else
                    RunAnimSeq(SunbathefrontF, MultiSpot[0]);
            }

            GotClutter = true;
        }//SunBath
        else if (Action == 3)
        {
            CAM::DO_SCREEN_FADE_IN(4000);
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            GAMEPLAY::POPULATE_NOW();
            Prop Sign = BuildProps(TrampSigns[LessRandomInt("TrampSign", 0, (int)TrampSigns.size() - 1)], MySpot, false, false);
            ENTITY::ATTACH_ENTITY_TO_ENTITY(Sign, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), 28422), 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, false, false, true, false, 2, true);
            RunAnimSeq(Mod_Class::AnimList(Mod_Class::AnimatedActions("amb@lo_res_idles@", "world_human_bum_freeway_lo_res_base"), Mod_Class::AnimatedActions("amb@prop_human_bum_bin@exit", "exit"), {}), MySpot);
            ENTITY::DETACH_ENTITY(Sign, 0, 0);
            ClearAllEntitys(false);
            //dettachsign
        }//TrampSign
        else if (Action == 4)
        {
            CAM::DO_SCREEN_FADE_IN(4000);
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            GAMEPLAY::POPULATE_NOW();
            RunAnimSeq(Mod_Class::AnimList(Mod_Class::AnimatedActions("switch@trevor@scares_tramp", "trev_scares_tramp_idle_tramp"), Mod_Class::AnimatedActions("switch@trevor@scares_tramp", "trev_scares_tramp_exit_tramp"), {}), MySpot);
        }//TrampSleap
        else if (Action == 5)
        {
            CAM::DO_SCREEN_FADE_IN(4000);
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            PED::SET_PED_SWEAT(PLAYER::PLAYER_PED_ID(), 99.0f);
            GAMEPLAY::POPULATE_NOW();
            if (SubSet == 0)
                ForceSenario("PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", MySpot, true);
            else if (SubSet < 3)
                ForceSenario("PROP_HUMAN_MUSCLE_CHIN_UPS", MySpot, false);
            else
            {
                int iPose = LessRandomInt("RandsAction5", 0, 30);
                if (iPose < 10)
                    RunAnimSeq(SitUps, MySpot);
                else if (iPose < 20)
                    ForceSenario("WORLD_HUMAN_MUSCLE_FREE_WEIGHTS", MySpot, false);
                else
                    RunAnimSeq(PushUps, MySpot);
            }
        }
        else if (Action == 6)
        {
            CAM::DO_SCREEN_FADE_IN(4000);

            if (SubSet == 1)
            {
                Mod_Class::Vector4 GangstarDriveFrom = Mod_Class::Vector4(-305.226f, 274.3028f, 87.31434f, 19.96654f);//veh end
                Mod_Class::Vector4 GangstarDriveTo = Mod_Class::Vector4(-302.166f, 317.6619f, 92.68359f, 0.0f);//veh end

                std::vector<Mod_Class::Vector4> GStars = {
                    Mod_Class::Vector4(-272.6266f, 325.0637f, 93.25459f, 102.7661f),
                    Mod_Class::Vector4(-281.3045f, 324.4917f, 93.26128f, 109.3759f),
                    Mod_Class::Vector4(-275.9741f, 324.7222f, 93.27049f, 185.5619f),
                    Mod_Class::Vector4(-274.2349f, 312.5389f, 93.25461f, 61.95487f),
                    Mod_Class::Vector4(-284.3914f, 311.4577f, 93.25461f, 11.21089f)//peds
                };           //Import Ex-- West Vine wood-- Vs. Polynesian.

                for (int i = 0; i < (int)GStars.size(); i++)
                    PlayerPedGen(GStars[i], iSelect, SubSet, true, true);

                VehicleSpawn(Mod_Class::Veh_Set("VIRGO2", false, false, true, true, true, iSelect, SubSet, Mod_Class::Vector4(-286.2027f, 311.9702f, 92.69145f, 358.9505f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("CHINO2", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(-282.5865f, 324.6772f, 92.68803f, 183.9263f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("FACTION3", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(-274.7456f, 324.9384f, 92.69529f, 179.5375f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("BUCCANEER2", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(-275.7558f, 312.8728f, 92.68794f, 19.96654f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("MINIVAN2", false, false, false, false, true, iSelect, 8, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                VehicleSpawn(Att);
            }           //Import Ex-- West Vine wood-- Vs. Polynesian.
            else if (SubSet == 2)
            {
                Mod_Class::Vector4 GangstarDriveFrom = Mod_Class::Vector4(-390.9916f, -1693.444f, 18.16406f, 151.6561f);//veh end
                Mod_Class::Vector4 GangstarDriveTo = Mod_Class::Vector4(-450.5249f, -1704.782f, 18.8604f, 0.0f);//veh end
                std::vector<Mod_Class::Vector4> GStars = {
                    Mod_Class::Vector4(-450.9772f, -1725.333f, 18.68914f, 276.2404f),
                    Mod_Class::Vector4(-449.4881f, -1724.789f, 18.68327f, 110.7676f),
                    Mod_Class::Vector4(-417.3922f, -1702.755f, 19.50922f, 110.1307f),
                    Mod_Class::Vector4(-469.3246f, -1701.666f, 18.65455f, 288.1841f),
                    Mod_Class::Vector4(-467.9238f, -1696.069f, 18.82708f, 167.8869f) //peds
                };           //Armenian -- Rogers Salvage and Scrap in La Puerta.-- Vs Police 

                for (int i = 0; i < (int)GStars.size(); i++)
                    PlayerPedGen(GStars[i], iSelect, SubSet, true, true);

                VehicleSpawn(Mod_Class::Veh_Set("SULTAN", false, false, true, true, true, iSelect, SubSet, Mod_Class::Vector4(-458.0122f, -1719.43f, 18.08753f, 336.3535f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("FORKLIFT", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(-424.3365f, -1688.027f, 18.49347f, 162.8363f), {}));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("FBI2", false, false, false, false, true, 21, 9, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                VehicleSpawn(Att);
            }           //Armenian -- Rogers Salvage and Scrap in La Puerta.-- Vs Police 
            else if (SubSet == 3)
            {
                Mod_Class::Vector4 GangstarDriveFrom = Mod_Class::Vector4(94.26853f, -1859.033f, 23.66001f, 141.1448f);//veh end
                Mod_Class::Vector4 GangstarDriveTo = Mod_Class::Vector4(-450.5249f, -1704.782f, 18.8604f, 0.0f);//veh end
                std::vector<Mod_Class::Vector4> GStars = {
                    Mod_Class::Vector4(115.3598f, -1947.014f, 20.60158f, 217.1962f),
                    Mod_Class::Vector4(115.2621f, -1944.061f, 20.63267f, 322.8773f),
                    Mod_Class::Vector4(116.2385f, -1942.619f, 20.60547f, 129.2276f),
                    Mod_Class::Vector4(117.9724f, -1940.25f, 20.62111f, 106.1278f),
                    Mod_Class::Vector4(118.3578f, -1939.102f, 20.64555f, 88.98208f) //peds
                };           //Ballas-- Davis, Vs --Families 

                for (int i = 0; i < (int)GStars.size(); i++)
                    PlayerPedGen(GStars[i], iSelect, SubSet, true, true);

                VehicleSpawn(Mod_Class::Veh_Set("EMPEROR", false, false, true, true, true, iSelect, SubSet, Mod_Class::Vector4(100.9958f, -1929.075f, 19.88203f, 160.4151f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("PEYOTE", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(113.7581f, -1939.326f, 19.91485f, 116.716f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("MANANA", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(106.8031f, -1949.032f, 19.91415f, 15.96025f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("VOODOO", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(97.78821f, -1944.386f, 19.94981f, 312.7894f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("BALLER", false, false, false, false, true, iSelect, 5, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                VehicleSpawn(Att);

                Hash ThisGp = MyHashKey("AMBIENT_GANG_BALLAS");
                SetRelBetween_Gp(&ThisGp, &GP_Player, 0);
            }           //Ballas-- Davis, Vs --Families 
            else if (SubSet == 4)
            {
                Mod_Class::Vector4 GangstarDriveFrom = Mod_Class::Vector4(452.4408f, -682.1255f, 27.24649f, 192.9981f);//veh end
                Mod_Class::Vector4 GangstarDriveTo = Mod_Class::Vector4(-450.5249f, -1704.782f, 18.8604f, 0.0f);//veh end
                std::vector<Mod_Class::Vector4> GStars = {
                    Mod_Class::Vector4(458.827f, -737.6528f, 27.35774f, 332.2838f),
                    Mod_Class::Vector4(463.1091f, -739.5256f, 27.36115f, 167.9439f),
                    Mod_Class::Vector4(462.527f, -742.2394f, 27.3605f, 21.53196f),
                    Mod_Class::Vector4(461.8431f, -734.8542f, 27.35998f, 132.3374f),
                    Mod_Class::Vector4(466.5947f, -730.8536f, 27.36218f, 101.3915f)//peds
                };           //Chinese textile city, Vs-- korean

                for (int i = 0; i < (int)GStars.size(); i++)
                    PlayerPedGen(GStars[i], iSelect, SubSet, true, true);

                MoveEntity(PLAYER::PLAYER_PED_ID(), Mod_Class::Vector4(458.5448f, -735.9688f, 27.35763f, 204.9358f));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("BURRITO", false, false, false, false, true, iSelect, 6, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                VehicleSpawn(Att);
            }           //Chinese textile city, Vs-- korean
            else if (SubSet == 5)
            {
                Mod_Class::Vector4 GangstarDriveFrom = Mod_Class::Vector4(-301.5466f, -1441.86f, 30.96148f, 273.4159f);//veh end
                Mod_Class::Vector4 GangstarDriveTo = Mod_Class::Vector4(-450.5249f, -1704.782f, 18.8604f, 0.0f);//veh end
                std::vector<Mod_Class::Vector4> GStars = {
                    Mod_Class::Vector4(-225.4482f, -1490.504f, 31.45079f, 310.6292f),
                    Mod_Class::Vector4(-222.5614f, -1488.412f, 31.2943f, 228.3047f),
                    Mod_Class::Vector4(-221.2482f, -1488.211f, 31.29151f, 102.181f),
                    Mod_Class::Vector4(-221.4105f, -1490.208f, 31.28293f, 17.52296f),
                    Mod_Class::Vector4(-223.3837f, -1490.498f, 31.28734f, 336.8165f)//peds
                };           //Families --Strawberry--Chamberlain Hills, Vs  Ballas

                for (int i = 0; i < (int)GStars.size(); i++)
                    PlayerPedGen(GStars[i], iSelect, SubSet, true, true);

                VehicleSpawn(Mod_Class::Veh_Set("BALLER", false, false, true, true, true, iSelect, SubSet, Mod_Class::Vector4(-224.047f, -1487.307f, 30.99617f, 140.3711f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("TORNADO2", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(-218.7061f, -1491.246f, 30.95563f, 139.3282f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("BALLER", false, false, false, false, true, iSelect, 3, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                VehicleSpawn(Att);

                Hash ThisGp = MyHashKey("AMBIENT_GANG_FAMILY");
                SetRelBetween_Gp(&ThisGp, &GP_Player, 0);
            }           //Families --Strawberry--Chamberlain Hills, Vs  Ballas
            else if (SubSet == 6)
            {
                Mod_Class::Vector4 GangstarDriveFrom = Mod_Class::Vector4(-696.5001f, -1061.766f, 14.30107f, 125.0344f);//veh end
                Mod_Class::Vector4 GangstarDriveTo = Mod_Class::Vector4(-450.5249f, -1704.782f, 18.8604f, 0.0f);//veh end
                std::vector<Mod_Class::Vector4> GStars = {
                    Mod_Class::Vector4(-742.5094f, -1041.155f, 12.51869f, 12.97545f),
                    Mod_Class::Vector4(-739.5043f, -1040.927f, 12.5031f, 68.58642f),
                    Mod_Class::Vector4(-741.374f, -1040.158f, 12.54656f, 143.1764f),
                    Mod_Class::Vector4(-743.769f, -1047.43f, 12.28089f, 341.5395f),
                    Mod_Class::Vector4(-744.7137f, -1045.582f, 12.3123f, 312.4333f) //peds
                };            //Korean --K-town, Vs Chinesse

                for (int i = 0; i < (int)GStars.size(); i++)
                    PlayerPedGen(GStars[i], iSelect, SubSet, true, true);

                VehicleSpawn(Mod_Class::Veh_Set("KURUMA", false, false, true, true, true, iSelect, SubSet, Mod_Class::Vector4(-755.6411f, -1035.036f, 12.59574f, 118.859f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("ELEGY", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(-737.267f, -1032.804f, 12.42186f, 299.1285f), { }));
                VehicleSpawn(Mod_Class::Veh_Set("FUTO", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(-751.9888f, -1041.709f, 12.31588f, 116.6273f), { }));
                VehicleSpawn(Mod_Class::Veh_Set("FUTO", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(-741.7025f, -1045.407f, 12.05153f, 23.04387f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("BALLER", false, false, false, false, true, iSelect, 4, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                VehicleSpawn(Att);
            }            //Korean --K-town, Vs Chinesse
            else if (SubSet == 7)
            {
                Mod_Class::Vector4 GangstarDriveFrom = Mod_Class::Vector4(274.7089f, -2033.892f, 18.23305f, 316.9213f);//veh end
                Mod_Class::Vector4 GangstarDriveTo = Mod_Class::Vector4(-450.5249f, -1704.782f, 18.8604f, 0.0f);//veh end
                std::vector<Mod_Class::Vector4> GStars = {
                    Mod_Class::Vector4(333.0477f, -2041.747f, 20.9505f, 78.31051f),
                    Mod_Class::Vector4(335.6685f, -2038.63f, 21.16848f, 175.0418f),
                    Mod_Class::Vector4(337.3491f, -2039.961f, 21.20797f, 143.0706f),
                    Mod_Class::Vector4(337.0323f, -2041.932f, 21.12964f, 29.95985f),
                    Mod_Class::Vector4(334.4699f, -2041.716f, 21.02297f, 251.7424f) //peds
                };           //Mexican --Rancho--Central Cypress Flats, Vs Salvadoran

                for (int i = 0; i < (int)GStars.size(); i++)
                    PlayerPedGen(GStars[i], iSelect, SubSet, true, true);

                VehicleSpawn(Mod_Class::Veh_Set("ELEGY", false, false, true, true, true, iSelect, SubSet, Mod_Class::Vector4(323.1364f, -2023.899f, 20.57834f, 143.4038f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("FUTO", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(320.1991f, -2034.714f, 20.33097f, 323.2342f), { }));
                VehicleSpawn(Mod_Class::Veh_Set("KURUMA", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(329.5031f, -2030.321f, 20.78702f, 141.8689f), { }));
                VehicleSpawn(Mod_Class::Veh_Set("Z190", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(336.029f, -2037.448f, 20.90948f, 90.30424f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("RUMPO3", false, false, false, false, true, iSelect, 9, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                VehicleSpawn(Att);

                Hash ThisGp = MyHashKey("AMBIENT_GANG_MEXICAN");
                SetRelBetween_Gp(&ThisGp, &GP_Player, 0);
            }           //Mexican --Rancho--Central Cypress Flats, Vs Salvadoran
            else if (SubSet == 8)
            {
                Mod_Class::Vector4 GangstarDriveFrom = Mod_Class::Vector4(-773.9064f, 5511.155f, 34.17496f, 28.73141f);//veh end
                Mod_Class::Vector4 GangstarDriveTo = Mod_Class::Vector4(-450.5249f, -1704.782f, 18.8604f, 0.0f);//veh end
                std::vector<Mod_Class::Vector4> GStars = {
                    Mod_Class::Vector4(-750.9026f, 5539.973f, 33.48567f, 47.66533f),
                    Mod_Class::Vector4(-753.6173f, 5539.024f, 33.48567f, 354.5756f),
                    Mod_Class::Vector4(-755.5646f, 5540.3f, 33.48567f, 315.5447f),
                    Mod_Class::Vector4(-753.6513f, 5542.839f, 33.48567f, 170.8908f),
                    Mod_Class::Vector4(-750.5474f, 5542.514f, 33.48567f, 125.0001f)//peds
                };           //Polynesian -- ? -- Lost

                for (int i = 0; i < (int)GStars.size(); i++)
                    PlayerPedGen(GStars[i], iSelect, SubSet, true, true);

                VehicleSpawn(Mod_Class::Veh_Set("PANTO", false, false, true, true, true, iSelect, SubSet, Mod_Class::Vector4(-753.3419f, 5531.84f, 33.00214f, 31.34572f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("RHAPSODY", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(-747.302f, 5535.622f, 33.00214f, 28.5319f), { }));
                VehicleSpawn(Mod_Class::Veh_Set("BRIOSO", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(-759.3707f, 5547.82f, 33.00235f, 177.4559f), { }));
                VehicleSpawn(Mod_Class::Veh_Set("BLISTA3", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(-752.3031f, 5547.335f, 33.00233f, 177.423f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("SLAMVAN2", false, false, false, false, true, iSelect, 10, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                VehicleSpawn(Att);
            }           //Polynesian -- ? -- Lost
            else if (SubSet == 9)
            {
                Mod_Class::Vector4 GangstarDriveFrom = Mod_Class::Vector4(1223.305f, -1684.305f, 39.15781f, 115.6373f);//veh end
                Mod_Class::Vector4 GangstarDriveTo = Mod_Class::Vector4(-450.5249f, -1704.782f, 18.8604f, 0.0f);//veh end
                std::vector<Mod_Class::Vector4> GStars = {
                    Mod_Class::Vector4(1161.041f, -1646.738f, 36.91954f, 48.9831f),
                    Mod_Class::Vector4(1160.423f, -1644.621f, 36.92954f, 161.1805f),
                    Mod_Class::Vector4(1158.195f, -1645.382f, 36.93469f, 227.3338f),
                    Mod_Class::Vector4(1158.133f, -1647.429f, 36.91374f, 299.3054f),
                    Mod_Class::Vector4(1159.598f, -1648.531f, 36.91959f, 17.60314f)//peds
                };           //"Salvadoran --El Burro Heights--Vespucci Beach(night)--East Vinewood Drain Canal, Vs Mexican

                for (int i = 0; i < (int)GStars.size(); i++)
                    PlayerPedGen(GStars[i], iSelect, SubSet, true, true);

                VehicleSpawn(Mod_Class::Veh_Set("MANANA", false, false, true, true, true, iSelect, SubSet, Mod_Class::Vector4(1166.919f, -1643.647f, 36.44419f, 177.7492f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("REBEL", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(1154.781f, -1657.428f, 36.08745f, 116.5546f), { }));
                VehicleSpawn(Mod_Class::Veh_Set("PEYOTE", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(1157.266f, -1661.953f, 36.12128f, 117.0901f), { }));
                VehicleSpawn(Mod_Class::Veh_Set("TORNADO2", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(1153.491f, -1650.302f, 36.03091f, 28.40678f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("RUMPO3", false, false, false, false, true, iSelect, 7, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                VehicleSpawn(Att);

                Hash ThisGp = MyHashKey("AMBIENT_GANG_SALVA");
                SetRelBetween_Gp(&ThisGp, &GP_Player, 0);
            }           //"Salvadoran --El Burro Heights--Vespucci Beach(night)--East Vinewood Drain Canal, Vs Mexican
            else if (SubSet == 10)
            {
                Mod_Class::Vector4 GangstarDriveFrom = Mod_Class::Vector4(961.9417f, -137.4299f, 73.6806f, 322.8134f);//veh end
                Mod_Class::Vector4 GangstarDriveTo = Mod_Class::Vector4(-450.5249f, -1704.782f, 18.8604f, 0.0f);//veh end
                std::vector<Mod_Class::Vector4> GStars = {
                    Mod_Class::Vector4(975.9936f, -126.8484f, 74.16551f, 348.0559f),
                    Mod_Class::Vector4(977.2745f, -124.7848f, 74.1376f, 214.7823f),
                    Mod_Class::Vector4(963.3976f, -123.7268f, 74.35315f, 338.3762f),
                    Mod_Class::Vector4(968.5342f, -118.6646f, 74.35315f, 121.6418f),
                    Mod_Class::Vector4(974.248f, -113.7502f, 74.35315f, 90.07847f)//peds
                };           //Lost ... Vs Impex

                for (int i = 0; i < (int)GStars.size(); i++)
                    PlayerPedGen(GStars[i], iSelect, SubSet, true, true);

                VehicleSpawn(Mod_Class::Veh_Set("DAEMON2", false, false, true, true, true, iSelect, SubSet, Mod_Class::Vector4(981.2489f, -128.9782f, 73.09866f, 63.50796f), {}));
                VehicleSpawn(Mod_Class::Veh_Set("GARGOYLE", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(965.4485f, -119.1682f, 73.82195f, 216.7741f), { }));
                VehicleSpawn(Mod_Class::Veh_Set("CLIFFHANGER", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(971.0372f, -115.0153f, 73.82298f, 218.4778f), { }));
                VehicleSpawn(Mod_Class::Veh_Set("DAEMON", false, false, false, false, true, iSelect, SubSet, Mod_Class::Vector4(979.4431f, -133.8394f, 72.97166f, 62.28038f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("MOONBEAM2", false, false, false, false, true, iSelect, 1, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                VehicleSpawn(Att);

                Hash ThisGp = MyHashKey("AMBIENT_GANG_LOST");
                SetRelBetween_Gp(&ThisGp, &GP_Player, 0);
            }           //Lost ... Vs Impex
            else if (SubSet == 11)
            {
                std::vector<Mod_Class::Vector4> GStars = {
                    Mod_Class::Vector4(83.97136f, 260.0858f, 108.9136f, 154.9512f),
                    Mod_Class::Vector4(1581.418f, 6453.026f, 25.31714f, 152.6169f),
                    Mod_Class::Vector4(-1189.455f, -877.1514f, 13.6739f, 32.68035f),
                    Mod_Class::Vector4(-1550.502f, -439.1086f, 40.51901f, 222.9146f),
                    Mod_Class::Vector4(-593.3647f, -863.3263f, 25.92446f, 17.25182f),
                    Mod_Class::Vector4(-1175.367f, -1267.867f, 6.164357f, 135.6286f),
                    Mod_Class::Vector4(-856.694f, -1140.941f, 6.942525f, 218.6946f),
                    Mod_Class::Vector4(-136.9821f, -260.9609f, 42.97683f, 243.6652f),
                    Mod_Class::Vector4(1137.357f, -960.7468f, 47.58101f, 329.7662f),
                    Mod_Class::Vector4(104.028f, -1421.119f, 29.30048f, 301.8356f),
                    Mod_Class::Vector4(-189.5329f, -1430.544f, 31.51664f, 59.90533f),
                    Mod_Class::Vector4(3.255534f, -1605.107f, 29.27947f, 64.94491f),
                    Mod_Class::Vector4(281.5654f, -1515.604f, 29.29159f, 242.0782f)
                };           //Street Punk-- Vs Old Ladys
                int iLocate = LessRandomInt("RandomLocations08Sub11", 0, (int)GStars.size() - 1);

                MoveEntity(PLAYER::PLAYER_PED_ID(), GStars[iLocate]);
                WAIT(1000);

                std::vector<std::string> OldD = {
                    "a_f_o_soucent_01",               //"South Central Old Female", 
                    "a_f_o_soucent_02",               //"South Central Old Female 2",
                    "a_f_o_indian_01",               //"Indian Old Female", 
                    "a_f_o_genstreet_01",               //"General Street Old Female", 
                    "a_f_o_ktown_01"               //"Korean Old Female", 
                };

                for (int i = 0; i < 4; i++)
                {
                    int iGran = LessRandomInt("GranSub11", 0, (int)OldD.size() - 1);
                    Mod_Class::ClothBank Cbank = Mod_Class::ClothBank("", OldD[iGran], -1, false, AddFace(false), false, false, Mod_Class::HairSets(0, 0, "H_FMM_0_0", "Close Shave", -1, -1), 0, 0, 0, 0, {}, {}, {}, {}, "");
                    Ped Deary = PlayerPedGen(Locations::NearByStreet(GStars[iLocate]), &Cbank, true, false);
                    FightPlayer(Deary, false, 0);
                    WEAPON::REMOVE_ALL_PED_WEAPONS(Deary, false);
                    GunningIt(Deary, 1);
                }
            }           //Street Punk-- Vs Old Ladys
            
            GotClutter = true;
        }       //GangStar--Fixup..
        else if (Action == 7)
        {
            CAM::DO_SCREEN_FADE_IN(4000);
            PED::SET_PED_SWEAT(PLAYER::PLAYER_PED_ID(), 99.0f);
            if (SubSet == 1)
                JogOn(Jogger01, RandomInt(0, (int)Jogger01.size() - 1));
            else if (SubSet == 2)
                JogOn(Jogger02, RandomInt(0, (int)Jogger02.size() - 1));
            else if (SubSet == 3)
                JogOn(Jogger03, RandomInt(0, (int)Jogger03.size() - 1));
            else if (SubSet == 4)
                JogOn(Jogger04, RandomInt(0, (int)Jogger04.size() - 1));
            else if (SubSet == 5)
                JogOn(Jogger05, RandomInt(0, (int)Jogger05.size() - 1));
            else if (SubSet == 6)
                JogOn(Jogger06, RandomInt(0, (int)Jogger06.size() - 1));
            else if (SubSet == 7)
                JogOn(Jogger07, RandomInt(0, (int)Jogger07.size() - 1));
            else if (SubSet == 8)
                JogOn(Jogger08, RandomInt(0, (int)Jogger08.size() - 1));
            else if (SubSet == 9)
                JogOn(Jogger09, RandomInt(0, (int)Jogger09.size() - 1));
            else if (SubSet == 10)
                JogOn(Jogger10, RandomInt(0, (int)Jogger10.size() - 1));
            else if (SubSet == 11)
                JogOn(Jogger11, RandomInt(0, (int)Jogger11.size() - 1));
            else if (SubSet == 12)
                JogOn(Jogger12, RandomInt(0, (int)Jogger12.size() - 1));
            else if (SubSet == 13)
                JogOn(Jogger13, RandomInt(0, (int)Jogger13.size() - 1));
            else if (SubSet == 14)
                JogOn(Jogger14, RandomInt(0, (int)Jogger14.size() - 1));
            else if (SubSet == 15)
                JogOn(Jogger15, RandomInt(0, (int)Jogger15.size() - 1));
            else if (SubSet == 16)
                JogOn(Jogger16, RandomInt(0, (int)Jogger16.size() - 1));
            else if (SubSet == 17)
                JogOn(Jogger17, RandomInt(0, (int)Jogger17.size() - 1));
            else if (SubSet == 18)
                JogOn(Jogger18, RandomInt(0, (int)Jogger18.size() - 1));
            else if (SubSet == 19)
                JogOn(Jogger19, RandomInt(0, (int)Jogger19.size() - 1));
            else if (SubSet == 20)
                JogOn(Jogger20, RandomInt(0, (int)Jogger20.size() - 1));
            else if (SubSet == 21)
                JogOn(Jogger21, RandomInt(0, (int)Jogger21.size() - 1));
            else if (SubSet == 22)
                JogOn(Jogger22, RandomInt(0, (int)Jogger22.size() - 1));
            else if (SubSet == 23)
                JogOn(Jogger23, RandomInt(0, (int)Jogger23.size() - 1));
            else if (SubSet == 24)
                JogOn(Jogger24, RandomInt(0, (int)Jogger24.size() - 1));
            else if (SubSet == 25)
                JogOn(Jogger25, RandomInt(0, (int)Jogger25.size() - 1));
            else if (SubSet == 26)
                JogOn(Jogger26, RandomInt(0, (int)Jogger26.size() - 1));
            else if (SubSet == 27)
                JogOn(Jogger27, RandomInt(0, (int)Jogger27.size() - 1));
            else if (SubSet == 28)
                JogOn(Jogger28, RandomInt(0, (int)Jogger28.size() - 1));
            else if (SubSet == 29)
                JogOn(Jogger29, RandomInt(0, (int)Jogger29.size() - 1));
            else
                JogOn(Jogger30, RandomInt(0, (int)Jogger30.size() - 1));
        }       //JogOn
        else if (Action == 8)
        {
            std::string Car = RandVeh(iSelect, SubSet);
            Vehicle Vic = VehicleSpawn(Mod_Class::Veh_Set(Car, false, false, false, false, false, iSelect, SubSet, MySpotFu.Car, { }));
            int iPose = LessRandomInt("RandsAction8", 0, 20);
            if (iPose < 10)
            {
                int iStart = 0;
                int iSeating = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(Vic);

                for (int i = iStart; i < iSeating; i++)
                {
                    LoggerLight("Fill Vehicle with peds");
                    Ped CarPed = PlayerPedGen(MySpotFu.Car, iSelect, SubSet, false, true);
                    // Wtf Is this doing here????---SavedPlayer(&SavedPeds[MySaved], WeaponSet);
                    PED::SET_PED_CAN_BE_DRAGGED_OUT(CarPed, false);
                    WarptoAnyVeh(Vic, CarPed, i);
                }
            }
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpotFu.Ped);
            WAIT(1000);
            CAM::DO_SCREEN_FADE_IN(1000);
            GetInVehicle(PLAYER::PLAYER_PED_ID(), Vic, Seat, true);
            WAIT(1000);
            GotClutter = true;
        }       //EnterVehicle
        else if (Action == 9)
        {
            RandomWeatherTime();
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            Meth_Act = true;
            MethEdd(Meth_Act);
            CAM::DO_SCREEN_FADE_IN(1000);
        }      //MethActing
        else if (Action == 10)
        {
            CAM::DO_SCREEN_FADE_IN(4000);
            MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            ForceSenario("WORLD_HUMAN_GARDENER_PLANT", MySpot, false);
        }
        else if (Action == 11)
        {
            CAM::DO_SCREEN_FADE_IN(1000);

        }      //Dancing
        else if (Action == 12)
        {
            WAIT(1000);
            CAM::DO_SCREEN_FADE_IN(4000);
            std::vector<std::string> Hashes = {
                "prop_patio_lounger1",
                "prop_patio_lounger_2",
                "prop_patio_lounger_3"
            };
            Entity SunL = NULL; 
            int i = 0;
            for (; i < (int)Hashes.size(); i++)
            {
                SunL = FindingProps(MySpot, 20.0f, Hashes[i]);
                if (SunL != NULL)
                    break;
            }

            if (SunL != NULL)
            {
                ENTITY::FREEZE_ENTITY_POSITION(SunL, true);
                Mod_Class::Vector4 SunPos = Locations::GetPosV4(SunL);
                Ped outPed = NearByPed(SunPos, false, 0.0f, 1.50f);

                if (outPed != NULL)
                    AI::TASK_REACT_AND_FLEE_PED(outPed, PLAYER::PLAYER_PED_ID());

                if (i == 0)
                {
                    Vector3 VPos = Locations::FowardOf(SunL, 0.255f, false);
                    SunPos.X = VPos.x;
                    SunPos.Y = VPos.y;
                }
                else if (i == 1)
                {
                    Vector3 VPos = Locations::FowardOf(SunL, 0.255f, true);
                    SunPos.X = VPos.x;
                    SunPos.Y = VPos.y;
                    SunPos.Z += 0.16f;
                }
                SunPos.R -= 180.0f;
                SunPos.Z += 0.32f;
                ForceSenario("PROP_HUMAN_SEAT_SUNLOUNGER", SunPos, true);
            }
        }     //Sitting-SunLounger
        else if (Action == 13)
        {
            CAM::DO_SCREEN_FADE_IN(4000);
            Vehicle Vbob = NULL;
            std::string Car = RandVeh(iSelect, SubSet);
            Mod_Class::Veh_Set MyVehSet = Mod_Class::Veh_Set(Car, Plane, Heli, PlayerInVeh, PlayerDrives, FillVeh, iSelect, SubSet, MySpot, { });
            Vbob = VehicleSpawn(MyVehSet);

            int iSeating = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(Vbob);

            for (int i = -1; i < iSeating - 1; i++)
            {
                LoggerLight("Fill Vehicle with peds");
                Ped CarPed = PlayerPedGen(MySpot, iSelect, SubSet, false, true);
                PED::SET_PED_CAN_BE_DRAGGED_OUT(CarPed, false);
                WarptoAnyVeh(Vbob, CarPed, i);
            }
            WarptoAnyVeh(Vbob, PLAYER::PLAYER_PED_ID(), iSeating - 1);
            CAM::DO_SCREEN_FADE_IN(1000);
            AI::TASK_VEHICLE_DRIVE_WANDER(VEHICLE::GET_PED_IN_VEHICLE_SEAT(Vbob, -1), Vbob, 12.0f, 1);

            GotClutter = true;
        }
        else
            CAM::DO_SCREEN_FADE_IN(1000);
    }
}
void RandomStart(bool Bypass)
{
    LoggerLight("RandomStart");

    int PickPlace = -1;
    if ((int)Avalable_Scenarios.size() == 0)
    {
        Avalable_Scenarios = CheckScenarios();
        if ((int)Avalable_Scenarios.size() != 0)
        {
            int ListSpot = RandomInt(0, (int)Avalable_Scenarios.size() - 1);
            PickPlace = Avalable_Scenarios[ListSpot];
            Avalable_Scenarios.erase(Avalable_Scenarios.begin() + ListSpot);
        }
    }
    else
    {
        int ListSpot = RandomInt(0, (int)Avalable_Scenarios.size() - 1);
        PickPlace = Avalable_Scenarios[ListSpot];
        Avalable_Scenarios.erase(Avalable_Scenarios.begin() + ListSpot);
    }

    LoggerLight("PickPlace == " + std::to_string(PickPlace));
    CAM::DO_SCREEN_FADE_OUT(1000);
    WAIT(1000);

    if (PickPlace != -1 && Mod_Settings.Auto_Run)
        Bypass = true;
    else if (!Bypass)
    {
        if (Mod_Settings.Saved_Ped && (int)SavedPeds.size() > 1)
        {
            Mod_Class::ClothBank bank = SavedPeds[LessRandomInt("SavedPedFind", 1, (int)SavedPeds.size() - 1)];
            SavedPlayer(&bank, -1);
        }
        CAM::DO_SCREEN_FADE_IN(4000);
    }

    if (Bypass)
        RandomLocation(PickPlace);
}

void KeyCapture()
{
    Mod_Data::Mod_Settings.MenuKey = FindKeyBinds(false);
    if (Mod_Data::Mod_Settings.MenuKey == -1)
        Mod_Data::Mod_Settings.MenuKey = 55;

    WAIT(2000);
}
void ControlerCapture()
{
    Mod_Data::Mod_Settings.ControlA = FindKeyBinds(true);
    Mod_Data::Mod_Settings.ControlB = FindKeyBinds(true);

    if (Mod_Data::Mod_Settings.ControlA != -1 && Mod_Data::Mod_Settings.ControlB != -1)
        Mod_Data::Mod_Settings.ControlSupport = true;

    WAIT(2000);
}
void WeaponCapture()
{
    Player_Weaps.clear();
    std::string weapon = "";
    int ammo = 0;
    for (int i = 0; i < (int)Weapons_List.size(); i++)
    {
        weapon = Weapons_List[i];
        if (WEAPON::HAS_PED_GOT_WEAPON(PLAYER::PLAYER_PED_ID(), MyHashKey(weapon), false))
        {
            ammo = WEAPON::GET_AMMO_IN_PED_WEAPON(PLAYER::PLAYER_PED_ID(), MyHashKey(weapon));

            std::vector<std::string> myAddons = {};
            for (int j = 0; j < (int)WeapAdd_List.size(); j++)
            {
                if (WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(PLAYER::PLAYER_PED_ID(), MyHashKey(weapon), MyHashKey(WeapAdd_List[j])))
                    myAddons.push_back(WeapAdd_List[j]);
            }
            Player_Weaps.push_back(Mod_Class::WeaponSaver(weapon, myAddons, ammo));
        }
    }
    SaveMyWeaps();
}

void SetWeatherDate()
{
    CanSnow = false;
    std::string Today = TimeDate();
    if (StringContains("Jan", Today) && Mod_Settings.SnowMonths.Jan)
        CanSnow = true;
    else if (StringContains("Feb", Today) && Mod_Settings.SnowMonths.Feb)
        CanSnow = true;
    else if (StringContains("Mar", Today) && Mod_Settings.SnowMonths.Mar)
        CanSnow = true;
    else if (StringContains("Apr", Today) && Mod_Settings.SnowMonths.Apr)
        CanSnow = true;
    else if (StringContains("May", Today) && Mod_Settings.SnowMonths.May)
        CanSnow = true;
    else if (StringContains("Jun", Today) && Mod_Settings.SnowMonths.Jun)
        CanSnow = true;
    else if (StringContains("Jul", Today) && Mod_Settings.SnowMonths.Jul)
        CanSnow = true;
    else if (StringContains("Aug", Today) && Mod_Settings.SnowMonths.Aug)
        CanSnow = true;
    else if (StringContains("Sep", Today) && Mod_Settings.SnowMonths.Sep)
        CanSnow = true;
    else if (StringContains("Oct", Today) && Mod_Settings.SnowMonths.Oct)
        CanSnow = true;
    else if (StringContains("Nov", Today) && Mod_Settings.SnowMonths.Nov)
        CanSnow = true;
    else if (StringContains("Dec", Today) && Mod_Settings.SnowMonths.Dec)
        CanSnow = true;
}
void LoadinData()
{
    LoggerLight("LoadinData");
    FindSettings(&Mod_Settings);
    MainProtags = { MyHashKey(MainChar), MyHashKey(FunChar01), MyHashKey(FunChar02), MyHashKey(FunChar03), MyHashKey(FunChar04) };
	GP_Player = GetRelationship();
	FollowMe = PED::GET_PED_GROUP_INDEX(PLAYER::PLAYER_PED_ID());// PED::CREATE_GROUP(0);
	Gp_Friend = AddRelationship("FrendlyNPCs");
	GP_Attack = AddRelationship("AttackNPCs");
	Gp_Follow = AddRelationship("FollowerNPCs");
	GP_Mental = AddRelationship("MentalNPCs");
	SetRelationType(true);

    int iAm = YourCharIs();
    if (iAm == 1)
    {
        MainChar = "player_zero";
        FunChar01 = "player_two";
        FunChar02 = "player_one";
        Mod_Class::ClothBank MyNewBank = Mod_Class::ClothBank("Michael", "player_zero", MyHashKey("player_zero"), false, FreeFaces(PLAYER::PLAYER_PED_ID(), false), true, false, PickAStyle(true), 0, 0, 0, 0, AddOverLay(true, false), {}, { GetYourTogs(PLAYER::PLAYER_PED_ID()) }, {}, "");
        SavedPeds.push_back(MyNewBank);

    }//Michal
    else if (iAm == 3)
    {
        MainChar = "player_two";
        FunChar01 = "player_one";
        FunChar02 = "player_zero";
        Mod_Class::ClothBank MyNewBank = Mod_Class::ClothBank("Trevor", "player_two", MyHashKey("player_two"), false, FreeFaces(PLAYER::PLAYER_PED_ID(), false), true, false, PickAStyle(true), 0, 0, 0, 0, AddOverLay(true, false), {}, { GetYourTogs(PLAYER::PLAYER_PED_ID()) }, {}, "");
        SavedPeds.push_back(MyNewBank);
    }//Trevor
    else
    {
        MainChar = "player_one";
        FunChar01 = "player_two";
        FunChar02 = "player_zero";
        Mod_Class::ClothBank MyNewBank = Mod_Class::ClothBank("Franklin", "player_one", MyHashKey("player_one"), false, FreeFaces(PLAYER::PLAYER_PED_ID(), false), true, false, PickAStyle(true), 0, 0, 0, 0, AddOverLay(true, false), {}, { GetYourTogs(PLAYER::PLAYER_PED_ID()) }, {}, "");
        SavedPeds.push_back(MyNewBank);
    }//Frank

	LoadSavedPeds();

	Disable_RL = CanRandondomizeStart();
    NSPM_Include = FileExists(GetDir() + "/Scripts/NSPM/Settings/NSPMach.NSPM");
    Ahhhh = GetDir() + "/RandomStart/heavenly_choir.wav";
    std::string BannerLoc = GetDir() + "/RandomStart/RandomStartBanner@256x64.png";
    MyBannerPng = createTexture(BannerLoc.c_str());
	BottomLeft("" + MultC[LessRandomInt("LoadinData01", 0, 5)] + "Random Start " + MultC[LessRandomInt("LoadinData01", 0, 5)] + "1.21" + MultC[LessRandomInt("LoadinData01", 0, 5)] + " by" + MultC[LessRandomInt("LoadinData01", 0, 5)] + " Adopcalipt " + MultC[LessRandomInt("LoadinData01", 0, 5)] + "Loaded" + MultC[LessRandomInt("LoadinData01", 0, 5)] + ".");
    
    if (FileExists(GetDir() + "/PlayerZero++.asi"))
        GotPlayZero = true;

    LoadLang();

    if (First_Load)
        WeaponCapture();

    SetWeatherDate();

    if (Mod_Settings.Auto_Run)
        RandomStart(false);
}
void UpdateSavedClothBanks()
{
    for (int i = 1; i < (int)SavedPeds.size(); i++)
        SaveClothBank(&SavedPeds[i]);
}

bool MenuOpen = false;
int Menu_IndexI = -1;
int Menu_IndexII = -1;
int Menu_IndexIII = -1;

const std::vector<std::string> VoicesMale = {
                "Default",
            "ANDY_MOON", //B51D1921", //3038583073", //"1256384223
            "ANTON", //ED9B229C", //3986367132", //"308600164
            "AVI", //EF7A6BDE", //4017777630", //"277189666
            "AGENCYJANITOR", //5288D370", //1384698736", //1384698736
            "AIRCRAFT_WARNING_MALE_01", //A65A6402", //2790941698", //"1504025598
            "AIRDUMMER", //798D01B5", //2039284149", //2039284149
            "AIRGUITARIST", //A1D7351A", //2715235610", //"1579731686
            "AIRPIANIST", //B98B1513", //3112899859", //"1182067437
            "AIRPORT_PA_MALE", //4BA3E2F7", //1269031671", //1269031671
            "ALIENS", //EB86F769", //3951490921", //"343476375
            "AMMUCITY", //D4503291", //3562025617", //"732941679
            "APT_BEAST", //14F37BC9", //351501257", //351501257
            "BALLASOG", //AAE4ECF8", //2867129592", //"1427837704
            "BANK", //3A15DB98", //974511000", //974511000
            "BANKWM1", //CED9042B", //3470328875", //"824638421
            "BANKWM2", //9C9B9FB1", //2627444657", //"1667522639
            "BAYGOR", //7BF7A5D6", //2079827414", //2079827414
            "BENNY", //F1EB2693", //4058719891", //"236247405
            "BEVERLY", //79D862EA", //2044224234", //2044224234
            "BIKE_MECHANIC", //573287EB", //1462929387", //1462929387
            "BILLBINDER", //4E43F344", //1313076036", //1313076036
            "BJPILOT_CANAL", //B75951F4", //3076084212", //"1218883084
            "BJPILOT_TRAIN", //0FACABE0", //262974432", //262974432
            "BRAD", //57360243", //1463157315", //1463157315
            "BREATHING_FRANKLIN_01", //777E9106", //2004783366", //2004783366
            "BREATHING_MICHAEL_01", //CAB2CFFB", //3400716283", //"894251013
            "BREATHING_TEST_01", //D75E8754", //3613296468", //"681670828
            "BREATHING_TREVOR_01", //18092047", //403251271", //403251271
            "BUSINESSMAN", //3ECBA7BD", //1053534141", //1053534141
            "CASEY", //908C67DC", //2425120732", //"1869846564
            "CHAR_INTRO_FRANKLIN_01", //420FF5A0", //1108342176", //1108342176
            "CHAR_INTRO_MICHAEL_01", //E4A08B92", //3835726738", //"459240558
            "CHAR_INTRO_TREVOR_01", //8F52758F", //2404545935", //"1890421361
            "CHEF", //BF59CC9A", //3210333338", //"1084633958
            "CHENG", //65BBBE48", //1706802760", //1706802760
            "CLETUS", //9B00816A", //2600501610", //"1694465686
            "CLINTON", //2B502F45", //726675269", //726675269
            "CLOWNS", //D8088180", //3624436096", //"670531200
            "COOK", //5673232D", //1450386221", //1450386221
            "DAVE", //B1F68A9D", //2985724573", //"1309242723
            "DOM", //BBF2D511", //3153253649", //"1141713647
            "EDDIE", //C5FB1FF5", //3321569269", //"973398027
            "EXECPA_MALE", //0C5C69CC", //207382988", //207382988
            "EXT1HELIPILOT", //EF004581", //4009772417", //"285194879
            "FACILITY_ANNOUNCER", //A9F8234D", //2851611469", //"1443355827
            "FLOYD", //5E69D958", //1583995224", //1583995224
            "FM", //FFE20CE1", //4293004513", //"1962783
            "FM_TH", //2640742C", //641758252", //641758252
            "GARDENER", //4260B7F4", //1113634804", //1113634804
            "GAYMILITARY", //212EBC3B", //556710971", //556710971
            "GERALD", //07DCC381", //131908481", //131908481
            "GROOM", //4A735AF1", //1249073905", //1249073905
            "GUSTAVO", //E5A7195C", //3852933468", //"442033828
            "HAO", //5F91F8AE", //1603401902", //1603401902
            "HEISTMANAGER", //3F3FAB0F", //1061137167", //1061137167
            "HUGH", //F4EE78A9", //4109269161", //"185698135
            "IMPOTENT_RAGE", //BE080ED8", //3188199128", //"1106768168
            "INFERNUS", //18F25AC7", //418536135", //418536135
            "JEROME", //D982DA50", //3649231440", //"645735856
            "JESSE", //916BB095", //2439753877", //"1855213419
            "JIMMY_DRUNK", //43C1EB55", //1136782165", //1136782165
            "JIMMY_NORMAL", //95810242", //2508259906", //"1786707390
            "JOE", //07CC375A", //130824026", //130824026
            "JOSEF", //F63ED80C", //4131313676", //"163653620
            "JOSH", //F4DDE967", //4108183911", //"186783385
            "KARIM", //DB158746", //3675621190", //"619346106
            "KARL", //D29BCDFD", //3533426173", //"761541123
            "LAMAR", //EA22BC4D", //3928144973", //"366822323
            "LAMAR_1_NORMAL", //35FE7226", //905867814", //905867814
            "LAMAR_2_NORMAL", //25068D1D", //621186333", //621186333
            "LAMAR_DRUNK", //648A554F", //1686787407", //1686787407
            "LAMAR_NORMAL", //9D861581", //2642810241", //"1652157055
            "LESTER", //8DB38846", //2377353286", //"1917614010
            "LIENGINEER", //BD5D1E88", //3176996488", //"1117970808
            "LIENGINEER2", //3A58B62B", //978892331", //978892331
            "LI_GEORGE_01", //F22854E3", //4062729443", //"232237853
            "LI_LOBBY_01", //3DB175B5", //1035040181", //1035040181
            "LI_MALE_01", //9CF88EB5", //2633535157", //"1661432139
            "LI_MALE_02", //AAB22A28", //2863802920", //"1431164376
            "MALE_STRIP_DJ_WHITE", //54825131", //1417826609", //1417826609
            "MANI", //9A9B1CC9", //2593856713", //"1701110583
            "MELVIN", //558B495C", //1435191644", //1435191644
            "MELVINSCIENTIST", //E90C6953", //3909904723", //"385062573
            "MIME", //5B25DA1F", //1529207327", //1529207327
            "MISTERK", //FF37663A", //4281820730", //"13146566
            "MPCT", //FF02D40E", //4278375438", //"16591858
            "MP_RESIDENT", //844127A9", //2218862505", //"2076104791
            "NERVOUSRON", //20251950", //539302224", //539302224
            "NIGEL", //F95E18F2", //4183693554", //"111273742
            "NIGHT_OUT_MALE_01", //41EC4175", //1106002293", //1106002293
            "NIGHT_OUT_MALE_02", //C428C5EC", //3291006444", //"1003960852
            "NORM", //AE21D168", //2921451880", //"1373515416
            "NO_VOICE", //87BFF09A", //2277503130", //"2017464166
            "PACKIE", //B8791A2F", //3094944303", //"1200022993
            "PACKIE_AI_NORM_PART1_BOOTH", //E0D1A809", //3771836425", //"523130871
            "PANIC_WALLA", //14DEB561", //350139745", //350139745
            "PIER_ANNOUNCE_MALE", //9567A0E1", //2506596577", //"1788370719
            "PIER_FOLEY", //58EA9491", //1491768465", //1491768465
            "PRISONER", //7EA26372", //2124571506", //2124571506
            "PRISON_ANNOUNCER", //9BEE7F20", //2616098592", //"1678868704
            "PRISON_TANNOY", //E5DCB564", //3856446820", //"438520476
            "REDOCASTRO", //CED55457", //3470087255", //"824880041
            "REDR1DRUNK1", //4184DA81", //1099225729", //1099225729
            "REDR1DRUNK1_AI_DRUNK", //2B10FBD7", //722533335", //722533335
            "REDR2DRUNKM", //51408669", //1363183209", //1363183209
            "REHH2HIKER", //92977683", //2459399811", //"1835567485
            "REHH3HIPSTER", //C0147C2B", //3222567979", //"1072399317
            "SECUROMECH", //9C7CE8C0", //2625431744", //"1669535552
            "SHOPASSISTANT", //53912D70", //1402023280", //1402023280
            "SIMEON", //82816017", //2189516823", //"2105450473
            "SOL1ACTOR", //4B0CAD83", //1259122051", //1259122051
            "SPACE_RANGER", //21D80107", //567804167", //567804167
            "STEVE", //CE95B9A9", //3465918889", //"829048407
            "STRETCH", //8B13F083", //2333339779", //"1961627517
            "SUBWAY_ANNOUNCER", //1C2F9BF2", //472882162", //472882162
            "TOM", //97CBE769", //2546722665", //"1748244631
            "TRANSLATOR", //EAC3FECB", //3938713291", //"356254005
            "VULTURES", //18219991", //404855185", //404855185
            "WADE", //7DD049A4", //2110802340", //2110802340
            "WHISTLINGJANITOR", //168D3E8E", //378355342", //378355342
            "YACHTCAPTAIN", //71C9A806", //1909041158", //1909041158
            "ZOMBIE", //22666A99", //577137305", //577137305
            "BTL_DAVE_PVG",
            "HS4_RAMPA_PVG",
            "HS4_ANDME_PVG",
            "HS4_ADAM_PVG",
            "HS4_PTRAX_PVG",
            "HS4_MOODY_PVG",
            "HS4_PRODUCER_PVG",
            "HS4_POOH_PVG",
            "HS4_BUSINESS_PVG",
            "HS4_CELEB1_PVG",
            "HS4_GUSTAVO_PVG",
            "HS4_PAVEL_PVG",
            "HS4_ELRUBIO_PVG",
            "HS4_MIGUEL_PVG",
            "HS4_ENTRYPILOT1_PVG",
            "HS4_OLDRICHGUY_PVG",
            "MALE_CLUB_R2PVG",
            "MALE_GENERICCHEAPWORKER_LATINO_PVG",
            "HS4_BODYGUARD1_PVG",
            "IGUARD_PVG",
            "AFFLUENT_SUBURBAN_MALE_01", //85FA12FF", //2247758591", //"2047208705
            "AFFLUENT_SUBURBAN_MALE_02", //A4394F7D", //2755219325", //"1539747971
            "A_M_M_AFRIAMER_01_BLACK_FULL_01", //43367BD1", //1127644113", //1127644113
            "A_M_M_BEACH_01_BLACK_MINI_01", //D01013F6", //3490714614", //"804252682
            "A_M_M_BEACH_01_LATINO_FULL_01", //26669A41", //644258369", //644258369
            "A_M_M_BEACH_01_LATINO_MINI_01", //FB444157", //4215554391", //"79412905
            "A_M_M_BEACH_01_WHITE_FULL_01", //30CB4589", //818627977", //818627977
            "A_M_M_BEACH_01_WHITE_MINI_02", //A8E033BD", //2833265597", //"1461701699
            "A_M_M_BEACH_02_BLACK_FULL_01", //BCACE696", //3165447830", //"1129519466
            "A_M_M_BEACH_02_WHITE_FULL_01", //E8314D57", //3895545175", //"399422121
            "A_M_M_BEACH_02_WHITE_MINI_01", //AE3CFC05", //2923232261", //"1371735035
            "A_M_M_BEACH_02_WHITE_MINI_02", //4717ADD8", //1192734168", //1192734168
            "A_M_M_BEVHILLS_01_BLACK_FULL_01", //457F9C3D", //1165990973", //1165990973
            "A_M_M_BEVHILLS_01_BLACK_MINI_01", //29323F4A", //691158858", //691158858
            "A_M_M_BevHills_01_WHITE_FULL_01", //DBCAE12A", //3687506218", //"607461078
            "A_M_M_BEVHILLS_01_WHITE_MINI_01", //D19FFBCA", //3516922826", //"778044470
            "A_M_M_BEVHILLS_02_BLACK_FULL_01", //5370D897", //1399904407", //1399904407
            "A_M_M_BEVHILLS_02_BLACK_MINI_01", //25983C23", //630733859", //630733859
            "A_M_M_BEVHILLS_02_WHITE_FULL_01", //6BB97FD6", //1807318998", //1807318998
            "A_M_M_BEVHILLS_02_WHITE_MINI_01", //B509F09C", //3037327516", //"1257639780
            "A_M_M_BUSINESS_01_BLACK_FULL_01", //4F3C06EB", //1329333995", //1329333995
            "A_M_M_BUSINESS_01_BLACK_MINI_01", //9C4ACF39", //2622148409", //"1672818887
            "A_M_M_BUSINESS_01_WHITE_FULL_01", //CE2B65BC", //3458950588", //"836016708
            "A_M_M_BUSINESS_01_WHITE_MINI_01", //F3AD48DE", //4088219870", //"206747426
            "A_M_M_EASTSA_01_LATINO_FULL_01", //BE01DD94", //3187793300", //"1107173996
            "A_M_M_EASTSA_01_LATINO_MINI_01", //6BF8BF2C", //1811463980", //1811463980
            "A_M_M_EASTSA_02_LATINO_FULL_01", //9CB34BA8", //2628996008", //"1665971288
            "A_M_M_EASTSA_02_LATINO_MINI_01", //CDF2AD27", //3455233319", //"839733977
            "A_M_M_FARMER_01_WHITE_MINI_01", //24689D1A", //610835738", //610835738
            "A_M_M_FARMER_01_WHITE_MINI_02", //4ED1F1EC", //1322381804", //1322381804
            "A_M_M_FARMER_01_WHITE_MINI_03", //F7F4C433", //4160013363", //"134953933
            "A_M_M_FATLATIN_01_LATINO_FULL_01", //2F04A30B", //788833035", //788833035
            "A_M_M_FATLATIN_01_LATINO_MINI_01", //4AED8689", //1257080457", //1257080457
            "A_M_M_GENERICMALE_01_WHITE_MINI_01", //13EFDE7E", //334487166", //334487166
            "A_M_M_GENERICMALE_01_WHITE_MINI_02", //221A7AD3", //572160723", //572160723
            "A_M_M_GENERICMALE_01_WHITE_MINI_03", //5AA26BD6", //1520593878", //1520593878
            "A_M_M_GENERICMALE_01_WHITE_MINI_04", //FD0AB0B4", //4245336244", //"49631052
            "A_M_M_GENFAT_01_LATINO_FULL_01", //E53DAB11", //3846023953", //"448943343
            "A_M_M_GENFAT_01_LATINO_MINI_01", //4C00FC14", //1275132948", //1275132948
            "A_M_M_GOLFER_01_BLACK_FULL_01", //65B984D1", //1706656977", //1706656977
            "A_M_M_GOLFER_01_WHITE_FULL_01", //57DD2744", //1474111300", //1474111300
            "A_M_M_GOLFER_01_WHITE_MINI_01", //CA82D279", //3397571193", //"897396103
            "A_M_M_HASJEW_01_WHITE_MINI_01", //31B413DD", //833885149", //833885149
            "A_M_M_HILLBILLY_01_WHITE_MINI_01", //342FA137", //875536695", //875536695
            "A_M_M_HILLBILLY_01_WHITE_MINI_02", //EEB2964E", //4004681294", //"290286002
            "A_M_M_HILLBILLY_01_WHITE_MINI_03", //62B97E4A", //1656323658", //1656323658
            "A_M_M_HILLBILLY_02_WHITE_MINI_01", //9E428A7D", //2655160957", //"1639806339
            "A_M_M_HILLBILLY_02_WHITE_MINI_02", //ACECA7D1", //2901190609", //"1393776687
            "A_M_M_HILLBILLY_02_WHITE_MINI_03", //7A9EC332", //2057225010", //2057225010
            "A_M_M_HILLBILLY_02_WHITE_MINI_04", //14C3777D", //348354429", //348354429
            "A_M_M_INDIAN_01_INDIAN_MINI_01", //0D92701D", //227700765", //227700765
            "A_M_M_KTOWN_01_KOREAN_FULL_01", //CEB967A9", //3468257193", //"826710103
            "A_M_M_KTOWN_01_KOREAN_MINI_01", //9D5568DD", //2639620317", //"1655346979
            "A_M_M_MALIBU_01_BLACK_FULL_01", //704A0828", //1883899944", //1883899944
            "A_M_M_MALIBU_01_LATINO_FULL_01", //C446CD11", //3292974353", //"1001992943
            "A_M_M_MALIBU_01_LATINO_MINI_01", //23A05D0D", //597712141", //597712141
            "A_M_M_MALIBU_01_WHITE_FULL_01", //ABCCBA7C", //2882321020", //"1412646276
            "A_M_M_MALIBU_01_WHITE_MINI_01", //B71E2A9D", //3072207517", //"1222759779
            "A_M_M_POLYNESIAN_01_POLYNESIAN_FULL_01", //68887F5A", //1753775962", //1753775962
            "A_M_M_POLYNESIAN_01_POLYNESIAN_MINI_01", //CDB20C91", //3450997905", //"843969391
            "A_M_M_SALTON_01_WHITE_FULL_01", //C4B4C301", //3300180737", //"994786559
            "A_M_M_SALTON_02_WHITE_FULL_01", //AAD2C80E", //2865940494", //"1429026802
            "A_M_M_SALTON_02_WHITE_MINI_01", //47C9EC4A", //1204415562", //1204415562
            "A_M_M_SALTON_02_WHITE_MINI_02", //6D9837E6", //1838692326", //1838692326
            "A_M_M_SKATER_01_BLACK_FULL_01", //256B9C01", //627809281", //627809281
            "A_M_M_SKATER_01_WHITE_FULL_01", //011E5DF9", //18767353", //18767353
            "A_M_M_SKATER_01_WHITE_MINI_01", //990DB923", //2567813411", //"1727153885
            "A_M_M_SKIDROW_01_BLACK_FULL_01", //A9B4316E", //2847158638", //"1447808658
            "A_M_M_SOCENLAT_01_LATINO_FULL_01", //06291B43", //103357251", //103357251
            "A_M_M_SOCENLAT_01_LATINO_MINI_01", //E9A5A98F", //3919948175", //"375019121
            "A_M_M_SOUCENT_01_BLACK_FULL_01", //15D5484D", //366299213", //366299213
            "A_M_M_SOUCENT_02_BLACK_FULL_01", //465792F9", //1180144377", //1180144377
            "A_M_M_SOUCENT_03_BLACK_FULL_01", //19DD2A37", //433924663", //433924663
            "A_M_M_SOUCENT_04_BLACK_FULL_01", //3712F629", //923989545", //923989545
            "A_M_M_SOUCENT_04_BLACK_MINI_01", //7BDBD27A", //2078003834", //2078003834
            "A_M_M_STLAT_02_LATINO_FULL_01", //27BC1008", //666636296", //666636296
            "A_M_M_TENNIS_01_BLACK_MINI_01", //74745D9B", //1953783195", //1953783195
            "A_M_M_TENNIS_01_WHITE_MINI_01", //A7AD9A25", //2813172261", //"1481795035
            "A_M_M_TOURIST_01_WHITE_MINI_01", //4B87E962", //1267198306", //1267198306
            "A_M_M_TRAMPBEAC_01_BLACK_FULL_01", //126F2EEF", //309276399", //309276399
            "A_M_M_TRAMP_01_BLACK_FULL_01", //EBC7775E", //3955717982", //"339249314
            "A_M_M_TRAMP_01_BLACK_MINI_01", //7924B380", //2032448384", //2032448384
            "A_M_M_TRANVEST_01_WHITE_MINI_01", //98921800", //2559711232", //"1735256064
            "A_M_M_TRANVEST_02_LATINO_FULL_01", //659F48E4", //1704937700", //1704937700
            "A_M_M_TRANVEST_02_LATINO_MINI_01", //F9BFF521", //4190106913", //"104860383
            "A_M_O_BEACH_01_WHITE_FULL_01", //7FBF0F4A", //2143227722", //2143227722
            "A_M_O_BEACH_01_WHITE_MINI_01", //B21E181B", //2988316699", //"1306650597
            "A_M_O_GENSTREET_01_WHITE_FULL_01", //BB6B9D57", //3144392023", //"1150575273
            "A_M_O_GENSTREET_01_WHITE_MINI_01", //10EE4E6A", //284053098", //284053098
            "A_M_O_SALTON_01_WHITE_FULL_01", //5DBB7560", //1572566368", //1572566368
            "A_M_O_SALTON_01_WHITE_MINI_01", //AEA39902", //2929957122", //"1365010174
            "A_M_O_SOUCENT_01_BLACK_FULL_01", //8F45DF82", //2403721090", //"1891246206
            "A_M_O_SOUCENT_02_BLACK_FULL_01", //C195B582", //3247814018", //"1047153278
            "A_M_O_SOUCENT_03_BLACK_FULL_01", //9CE751AB", //2632405419", //"1662561877
            "A_M_O_TRAMP_01_BLACK_FULL_01", //ABAB17E1", //2880116705", //"1414850591
            "A_M_Y_BEACHVESP_01_CHINESE_FULL_01", //D5130E1F", //3574795807", //"720171489
            "A_M_Y_BEACHVESP_01_CHINESE_MINI_01", //B0C6E699", //2965825177", //"1329142119
            "A_M_Y_BEACHVESP_01_LATINO_MINI_01", //3F13D91C", //1058265372", //1058265372
            "A_M_Y_BEACHVESP_01_WHITE_FULL_01", //3CE0CB56", //1021365078", //1021365078
            "A_M_Y_BEACHVESP_01_WHITE_MINI_01", //AAD5FF3F", //2866151231", //"1428816065
            "A_M_Y_BEACHVESP_02_WHITE_FULL_01", //4C19F4DE", //1276769502", //1276769502
            "A_M_Y_BEACHVESP_02_WHITE_MINI_01", //7F7BB4CC", //2138813644", //2138813644
            "A_M_Y_BEACH_01_CHINESE_FULL_01", //14611348", //341906248", //341906248
            "A_M_Y_BEACH_01_CHINESE_MINI_01", //6A55B403", //1784001539", //1784001539
            "A_M_Y_BEACH_01_WHITE_FULL_01", //1C2149A7", //471943591", //471943591
            "A_M_Y_BEACH_01_WHITE_MINI_01", //912C1ADE", //2435586782", //"1859380514
            "A_M_Y_BEACH_02_LATINO_FULL_01", //DBF1B32E", //3690050350", //"604916946
            "A_M_Y_BEACH_02_WHITE_FULL_01", //0B3E6275", //188637813", //188637813
            "A_M_Y_BEACH_03_BLACK_FULL_01", //18519A78", //408001144", //408001144
            "A_M_Y_BEACH_03_BLACK_MINI_01", //5C219040", //1545703488", //1545703488
            "A_M_Y_BEACH_03_WHITE_FULL_01", //187DBBE4", //410893284", //410893284
            "A_M_Y_BEVHILLS_01_BLACK_FULL_01", //BB7823E2", //3145212898", //"1149754398
            "A_M_Y_BevHills_01_WHITE_FULL_01", //FBF34319", //4227023641", //"67943655
            "A_M_Y_BEVHILLS_01_WHITE_MINI_01", //7C5C68C5", //2086430917", //2086430917
            "A_M_Y_BevHills_02_Black_FULL_01", //7FDB40A6", //2145075366", //2145075366
            "A_M_Y_BEVHILLS_02_WHITE_FULL_01", //D4FC2A78", //3573295736", //"721671560
            "A_M_Y_BEVHILLS_02_WHITE_MINI_01", //E24573FE", //3796202494", //"498764802
            "A_M_Y_BUSICAS_01_WHITE_MINI_01", //AE353C51", //2922724433", //"1372242863
            "A_M_Y_BUSINESS_01_BLACK_FULL_01", //14EA502A", //350900266", //350900266
            "A_M_Y_BUSINESS_01_BLACK_MINI_01", //3EE0C0FD", //1054916861", //1054916861
            "A_M_Y_BUSINESS_01_CHINESE_FULL_01", //2AF37A7A", //720599674", //720599674
            "A_M_Y_BUSINESS_01_CHINESE_MINI_01", //BBE9D5F6", //3152664054", //"1142303242
            "A_M_Y_BUSINESS_01_WHITE_FULL_01", //A3B29220", //2746389024", //"1548578272
            "A_M_Y_BUSINESS_01_WHITE_MINI_02", //D5230A76", //3575843446", //"719123850
            "A_M_Y_BUSINESS_02_BLACK_FULL_01", //455E1156", //1163792726", //1163792726
            "A_M_Y_BUSINESS_02_BLACK_MINI_01", //728E84E0", //1921942752", //1921942752
            "A_M_Y_BUSINESS_02_WHITE_FULL_01", //21BD5DCB", //566058443", //566058443
            "A_M_Y_BUSINESS_02_WHITE_MINI_01", //DF04F10C", //3741643020", //"553324276
            "A_M_Y_BUSINESS_02_WHITE_MINI_02", //D1405583", //3510654339", //"784312957
            "A_M_Y_BUSINESS_03_BLACK_FULL_01", //63CAEDDD", //1674243549", //1674243549
            "A_M_Y_BUSINESS_03_WHITE_MINI_01", //5161018C", //1365311884", //1365311884
            "A_M_Y_DOWNTOWN_01_BLACK_FULL_01", //5C59E524", //1549395236", //1549395236
            "A_M_Y_EASTSA_01_LATINO_FULL_01", //4D091B2B", //1292442411", //1292442411
            "A_M_Y_EASTSA_01_LATINO_MINI_01", //90006FB0", //2415947696", //"1879019600
            "A_M_Y_EASTSA_02_LATINO_FULL_01", //71EFEA69", //1911548521", //1911548521
            "A_M_Y_EPSILON_01_BLACK_FULL_01", //3C737DA3", //1014201763", //1014201763
            "A_M_Y_EPSILON_01_KOREAN_FULL_01", //C5901506", //3314554118", //"980413178
            "A_M_Y_EPSILON_01_WHITE_FULL_01", //8B5E6BA1", //2338220961", //"1956746335
            "A_M_Y_EPSILON_02_WHITE_MINI_01", //5929B31B", //1495905051", //1495905051
            "A_M_Y_GAY_01_BLACK_FULL_01", //D66B6510", //3597362448", //"697604848
            "A_M_Y_GAY_01_LATINO_FULL_01", //56EA4F8A", //1458196362", //1458196362
            "A_M_Y_GAY_02_WHITE_MINI_01", //F31D141C", //4078769180", //"216198116
            "A_M_Y_GENSTREET_01_CHINESE_FULL_01", //FBD60609", //4225107465", //"69859831
            "A_M_Y_GENSTREET_01_CHINESE_MINI_01", //68B1C2E6", //1756480230", //1756480230
            "A_M_Y_GenStreet_01_White_FULL_01", //CCC8E124", //3435716900", //"859250396
            "A_M_Y_GENSTREET_01_WHITE_MINI_01", //0EA63482", //245773442", //245773442
            "A_M_Y_GENSTREET_02_BLACK_FULL_01", //A05521B9", //2689933753", //"1605033543
            "A_M_Y_GENSTREET_02_LATINO_FULL_01", //8A23EC00", //2317609984", //"1977357312
            "A_M_Y_GENSTREET_02_LATINO_MINI_01", //71BDAFD1", //1908256721", //1908256721
            "A_M_Y_GOLFER_01_WHITE_FULL_01", //DB7324F1", //3681756401", //"613210895
            "A_M_Y_GOLFER_01_WHITE_MINI_01", //0F36AC80", //255241344", //255241344
            "A_M_Y_HASJEW_01_WHITE_MINI_01", //C4E78448", //3303507016", //"991460280
            "A_M_Y_HIPPY_01_WHITE_FULL_01", //72E9121E", //1927877150", //1927877150
            "A_M_Y_HIPPY_01_WHITE_MINI_01", //A92E6392", //2838389650", //"1456577646
            "A_M_Y_HIPSTER_01_BLACK_FULL_01", //4D67AAB4", //1298639540", //1298639540
            "A_M_Y_HIPSTER_01_WHITE_FULL_01", //93896827", //2475255847", //"1819711449
            "A_M_Y_HIPSTER_01_WHITE_MINI_01", //B4EB0EBF", //3035303615", //"1259663681
            "A_M_Y_HIPSTER_02_WHITE_FULL_01", //742FB44D", //1949283405", //1949283405
            "A_M_Y_HIPSTER_02_WHITE_MINI_01", //521933C3", //1377383363", //1377383363
            "A_M_Y_HIPSTER_03_WHITE_FULL_01", //E694D959", //3868514649", //"426452647
            "A_M_Y_HIPSTER_03_WHITE_MINI_01", //B22C563F", //2989250111", //"1305717185
            "A_M_Y_KTOWN_01_KOREAN_FULL_01", //285D1B2F", //677190447", //677190447
            "A_M_Y_KTOWN_01_KOREAN_MINI_01", //D97AF207", //3648713223", //"646254073
            "A_M_Y_KTOWN_02_KOREAN_FULL_01", //7B3CEC0F", //2067590159", //2067590159
            "A_M_Y_KTOWN_02_KOREAN_MINI_01", //77B4E675", //2008344181", //2008344181
            "A_M_Y_LATINO_01_LATINO_MINI_01", //26ED66AF", //653092527", //653092527
            "A_M_Y_LATINO_01_LATINO_MINI_02", //C2429D5B", //3259145563", //"1035821733
            "A_M_Y_MEXTHUG_01_LATINO_FULL_01", //5756D257", //1465307735", //1465307735
            "A_M_Y_MUSCLBEAC_01_BLACK_FULL_01", //C1B61E52", //3249938002", //"1045029294
            "A_M_Y_MUSCLBEAC_01_WHITE_FULL_01", //0225E2F9", //36037369", //36037369
            "A_M_Y_MUSCLBEAC_01_WHITE_MINI_01", //977DC3C1", //2541601729", //"1753365567
            "A_M_Y_MUSCLBEAC_02_CHINESE_FULL_01", //A6F52D1E", //2801085726", //"1493881570
            "A_M_Y_MUSCLBEAC_02_LATINO_FULL_01", //67CCA113", //1741463827", //1741463827
            "A_M_Y_POLYNESIAN_01_POLYNESIAN_FULL_01", //121DA55B", //303932763", //303932763
            "A_M_Y_RACER_01_WHITE_MINI_01", //F64541B5", //4131733941", //"163233355
            "A_M_Y_ROLLERCOASTER_01_MINI_01", //7DB0EDFB", //2108747259", //2108747259
            "A_M_Y_ROLLERCOASTER_01_MINI_02", //678FC1B9", //1737474489", //1737474489
            "A_M_Y_ROLLERCOASTER_01_MINI_03", //A3F33A7F", //2750626431", //"1544340865
            "A_M_Y_ROLLERCOASTER_01_MINI_04", //962B9EF0", //2519441136", //"1775526160
            "A_M_Y_RUNNER_01_WHITE_FULL_01", //F85796B7", //4166489783", //"128477513
            "A_M_Y_RUNNER_01_WHITE_MINI_01", //6816D078", //1746325624", //1746325624
            "A_M_Y_SALTON_01_WHITE_MINI_01", //488C6273", //1217159795", //1217159795
            "A_M_Y_SALTON_01_WHITE_MINI_02", //5E6F8E25", //1584369189", //1584369189
            "A_M_Y_SKATER_01_WHITE_FULL_01", //1E6F76CB", //510621387", //510621387
            "A_M_Y_SKATER_01_WHITE_MINI_01", //41386857", //1094215767", //1094215767
            "A_M_Y_SKATER_02_BLACK_FULL_01", //46B9D99F", //1186584991", //1186584991
            "A_M_Y_SOUCENT_01_BLACK_FULL_01", //7ADB7C56", //2061204566", //2061204566
            "A_M_Y_SOUCENT_02_BLACK_FULL_01", //BA7414D7", //3128169687", //"1166797609
            "A_M_Y_SOUCENT_03_BLACK_FULL_01", //997A83C0", //2574943168", //"1720024128
            "A_M_Y_SOUCENT_04_BLACK_FULL_01", //97BA1740", //2545555264", //"1749412032
            "A_M_Y_SOUCENT_04_BLACK_MINI_01", //E3DE23A6", //3822986150", //"471981146
            "A_M_Y_STBLA_01_BLACK_FULL_01", //80372D5A", //2151099738", //"2143867558
            "A_M_Y_STBLA_02_BLACK_FULL_01", //B77F38D5", //3078568149", //"1216399147
            "A_M_Y_STLAT_01_LATINO_FULL_01", //AF739934", //2943588660", //"1351378636
            "A_M_Y_STLAT_01_LATINO_MINI_01", //CDC7408D", //3452387469", //"842579827
            "A_M_Y_STWHI_01_WHITE_FULL_01", //51843C65", //1367620709", //1367620709
            "A_M_Y_STWHI_01_WHITE_MINI_01", //283E7635", //675182133", //675182133
            "A_M_Y_STWHI_02_WHITE_FULL_01", //32F459E7", //854874599", //854874599
            "A_M_Y_STWHI_02_WHITE_MINI_01", //D94A1B14", //3645512468", //"649454828
            "A_M_Y_SUNBATHE_01_BLACK_FULL_01", //523A66C3", //1379559107", //1379559107
            "A_M_Y_SUNBATHE_01_WHITE_FULL_01", //0CEA2526", //216671526", //216671526
            "A_M_Y_SUNBATHE_01_WHITE_MINI_01", //C31ADD04", //3273317636", //"1021649660
            "A_M_Y_TRIATHLON_01_MINI_01", //55B488C4", //1437894852", //1437894852
            "A_M_Y_TRIATHLON_01_MINI_02", //87746C43", //2272554051", //"2022413245
            "A_M_Y_TRIATHLON_01_MINI_03", //BB49D3ED", //3142177773", //"1152789523
            "A_M_Y_TRIATHLON_01_MINI_04", //ED26B7A6", //3978737574", //"316229722
            "A_M_Y_VINEWOOD_01_BLACK_FULL_01", //8567F85C", //2238183516", //"2056783780
            "A_M_Y_VINEWOOD_01_BLACK_MINI_01", //0C746F67", //208957287", //208957287
            "A_M_Y_VINEWOOD_02_WHITE_FULL_01", //0A626D28", //174222632", //174222632
            "A_M_Y_VINEWOOD_02_WHITE_MINI_01", //C370059E", //3278898590", //"1016068706
            "A_M_Y_Vinewood_03_Latino_FULL_01", //F450D2AC", //4098937516", //"196029780
            "A_M_Y_VINEWOOD_03_LATINO_MINI_01", //9FDD31FF", //2682073599", //"1612893697
            "A_M_Y_VINEWOOD_03_WHITE_FULL_01", //852D3A8F", //2234333839", //"2060633457
            "A_M_Y_VINEWOOD_03_WHITE_MINI_01", //3A84F91E", //981793054", //981793054
            "A_M_Y_VINEWOOD_04_WHITE_FULL_01", //77B21017", //2008158231", //2008158231
            "A_M_Y_VINEWOOD_04_WHITE_MINI_01", //99DA0ADA", //2581203674", //"1713763622
            "G_M_M_ARMBOSS_01_WHITE_ARMENIAN_MINI_01", //F840ABA3", //4164987811", //"129979485
            "G_M_M_ARMBOSS_01_WHITE_ARMENIAN_MINI_02", //DD7F7641", //3716118081", //"578849215
            "G_M_M_ARMLIEUT_01_WHITE_ARMENIAN_MINI_01", //9B88EB80", //2609441664", //"1685525632
            "G_M_M_ARMLIEUT_01_WHITE_ARMENIAN_MINI_02", //8BCF4C0D", //2345618445", //"1949348851
            "G_M_M_CHIBOSS_01_CHINESE_MINI_01", //FD2B8068", //4247486568", //"47480728
            "G_M_M_CHIBOSS_01_CHINESE_MINI_02", //6EF5E41B", //1861608475", //1861608475
            "G_M_M_CHIGOON_01_CHINESE_MINI_01", //E8CB59DD", //3905640925", //"389326371
            "G_M_M_CHIGOON_01_CHINESE_MINI_02", //F8FCFA40", //4177328704", //"117638592
            "G_M_M_CHIGOON_02_CHINESE_MINI_01", //93D6B240", //2480321088", //"1814646208
            "G_M_M_CHIGOON_02_CHINESE_MINI_02", //2138CD06", //557370630", //557370630
            "G_M_M_KORBOSS_01_KOREAN_MINI_01", //049ADD23", //77258019", //77258019
            "G_M_M_KORBOSS_01_KOREAN_MINI_02", //9DB98F56", //2646183766", //"1648783530
            "G_M_M_MEXBOSS_01_LATINO_MINI_01", //121AC997", //303745431", //303745431
            "G_M_M_MEXBOSS_01_LATINO_MINI_02", //A86BF63B", //2825647675", //"1469319621
            "G_M_M_MEXBOSS_02_LATINO_MINI_01", //FCB3B4DF", //4239635679", //"55331617
            "G_M_M_MEXBOSS_02_LATINO_MINI_02", //59FC6F6F", //1509715823", //1509715823
            "G_M_M_X17_RSO_01", //7B4E71E9", //2068738537", //2068738537
            "G_M_M_X17_RSO_02", //0518057E", //85460350", //85460350
            "G_M_M_X17_RSO_03", //16232794", //371402644", //371402644
            "G_M_M_X17_RSO_04", //09AF0EA8", //162467496", //162467496
            "G_M_Y_ARMGOON_02_WHITE_ARMENIAN_MINI_01", //F98339EA", //4186126826", //"108840470
            "G_M_Y_ARMGOON_02_WHITE_ARMENIAN_MINI_02", //91C4EA6B", //2445601387", //"1849365909
            "G_M_Y_BALLAEAST_01_BLACK_FULL_01", //9CFAAA5C", //2633673308", //"1661293988
            "G_M_Y_BALLAEAST_01_BLACK_FULL_02", //8F2D0EC1", //2402094785", //"1892872511
            "G_M_Y_BALLAEAST_01_BLACK_MINI_01", //2C0FCD9F", //739233183", //739233183
            "G_M_Y_BALLAEAST_01_BLACK_MINI_02", //D5BE20F9", //3586007289", //"708960007
            "G_M_Y_BALLAEAST_01_BLACK_MINI_03", //C77B8474", //3346760820", //"948206476
            "G_M_Y_BALLAORIG_01_BLACK_FULL_01", //F0D6A527", //4040598823", //"254368473
            "G_M_Y_BALLAORIG_01_BLACK_FULL_02", //DF4101FC", //3745579516", //"549387780
            "G_M_Y_BALLAORIG_01_BLACK_MINI_01", //719C62A9", //1906074281", //1906074281
            "G_M_Y_BALLAORIG_01_BLACK_MINI_02", //AD1BD9A7", //2904283559", //"1390683737
            "G_M_Y_BALLAORIG_01_BLACK_MINI_03", //925BA427", //2455479335", //"1839487961
            "G_M_Y_BALLASOUT_01_BLACK_FULL_01", //60B320B0", //1622352048", //1622352048
            "G_M_Y_BALLASOUT_01_BLACK_FULL_02", //2A5033EB", //709899243", //709899243
            "G_M_Y_BALLASOUT_01_BLACK_MINI_01", //6ED150A0", //1859211424", //1859211424
            "G_M_Y_BALLASOUT_01_BLACK_MINI_02", //A00D3317", //2685219607", //"1609747689
            "G_M_Y_BALLASOUT_01_BLACK_MINI_03", //BE746FE5", //3195301861", //"1099665435
            "G_M_Y_FAMCA_01_BLACK_FULL_01", //3F299AE9", //1059691241", //1059691241
            "G_M_Y_FAMCA_01_BLACK_FULL_02", //51573F44", //1364672324", //1364672324
            "G_M_Y_FAMCA_01_BLACK_MINI_01", //D991FA9F", //3650222751", //"644744545
            "G_M_Y_FAMCA_01_BLACK_MINI_02", //6B6D9E58", //1802346072", //1802346072
            "G_M_Y_FAMCA_01_BLACK_MINI_03", //0658D3F8", //106484728", //106484728
            "G_M_Y_FAMDNF_01_BLACK_FULL_01", //5F8F7FB9", //1603239865", //1603239865
            "G_M_Y_FAMDNF_01_BLACK_FULL_02", //B271257B", //2993759611", //"1301207685
            "G_M_Y_FAMDNF_01_BLACK_MINI_01", //BA8A1C11", //3129613329", //"1165353967
            "G_M_Y_FAMDNF_01_BLACK_MINI_02", //28A77842", //682063938", //682063938
            "G_M_Y_FAMDNF_01_BLACK_MINI_03", //D2384B6D", //3526904685", //"768062611
            "G_M_Y_FAMFOR_01_BLACK_FULL_01", //4D505739", //1297110841", //1297110841
            "G_M_Y_FAMFOR_01_BLACK_FULL_02", //7FEB3C3E", //2146122814", //2146122814
            "G_M_Y_FAMFOR_01_BLACK_MINI_01", //FA83BCD1", //4202937553", //"92029743
            "G_M_Y_FAMFOR_01_BLACK_MINI_02", //4721560B", //1193367051", //1193367051
            "G_M_Y_FAMFOR_01_BLACK_MINI_03", //56CEF566", //1456403814", //1456403814
            "G_M_Y_KOREAN_01_KOREAN_MINI_01", //3975B100", //964014336", //964014336
            "G_M_Y_KOREAN_01_KOREAN_MINI_02", //0F585CC6", //257449158", //257449158
            "G_M_Y_KOREAN_02_KOREAN_MINI_01", //E1E0349F", //3789567135", //"505400161
            "G_M_Y_KOREAN_02_KOREAN_MINI_02", //D41A1913", //3558480147", //"736487149
            "G_M_Y_KORLIEUT_01_KOREAN_MINI_01", //6B9A636E", //1805280110", //1805280110
            "G_M_Y_KORLIEUT_01_KOREAN_MINI_02", //2116CE64", //555142756", //555142756
            "G_M_Y_LATINO01_LATINO_MINI_02", //215F60FC", //559898876", //559898876
            "G_M_Y_LOST_01_BLACK_FULL_01", //BD922FD5", //3180474325", //"1114492971
            "G_M_Y_LOST_01_BLACK_FULL_02", //06D7C263", //114803299", //114803299
            "G_M_Y_LOST_01_BLACK_MINI_01", //D03903FA", //3493397498", //"801569798
            "G_M_Y_LOST_01_BLACK_MINI_02", //0154E631", //22341169", //22341169
            "G_M_Y_LOST_01_BLACK_MINI_03", //2ADE3943", //719206723", //719206723
            "G_M_Y_LOST_01_WHITE_FULL_01", //A29BB240", //2728112704", //"1566854592
            "G_M_Y_LOST_01_WHITE_MINI_01", //0477B521", //74954017", //74954017
            "G_M_Y_LOST_01_WHITE_MINI_02", //D6005837", //3590346807", //"704620489
            "G_M_Y_LOST_02_LATINO_FULL_01", //93D0C3D0", //2479932368", //"1815034928
            "G_M_Y_LOST_02_LATINO_FULL_02", //DD9DD769", //3718109033", //"576858263
            "G_M_Y_LOST_02_LATINO_MINI_01", //B4A96868", //3031001192", //"1263966104
            "G_M_Y_LOST_02_LATINO_MINI_02", //C34E85B2", //3276703154", //"1018264142
            "G_M_Y_LOST_02_LATINO_MINI_03", //D1C5229F", //3519357599", //"775609697
            "G_M_Y_LOST_02_WHITE_FULL_01", //552D4F23", //1429032739", //1429032739
            "G_M_Y_LOST_02_WHITE_MINI_01", //AC382220", //2889359904", //"1405607392
            "G_M_Y_LOST_02_WHITE_MINI_02", //302D2A08", //808266248", //808266248
            "G_M_Y_LOST_03_WHITE_FULL_01", //269A2029", //647634985", //647634985
            "G_M_Y_LOST_03_WHITE_MINI_02", //19793B32", //427375410", //427375410
            "G_M_Y_LOST_03_WHITE_MINI_03", //6C55606D", //1817534573", //1817534573
            "G_M_Y_MEXGOON_01_LATINO_MINI_01", //57C1000E", //1472266254", //1472266254
            "G_M_Y_MEXGOON_01_LATINO_MINI_02", //4F90EFAA", //1334898602", //1334898602
            "G_M_Y_MEXGOON_02_LATINO_MINI_01", //B00D3337", //2953655095", //"1341312201
            "G_M_Y_MEXGOON_02_LATINO_MINI_02", //6A4227A2", //1782720418", //1782720418
            "G_M_Y_MEXGOON_03_LATINO_MINI_01", //36640278", //912523896", //912523896
            "G_M_Y_MEXGOON_03_LATINO_MINI_02", //45EBA187", //1173070215", //1173070215
            "G_M_Y_POLOGOON_01_LATINO_MINI_01", //D1389B20", //3510147872", //"784819424
            "G_M_Y_POLOGOON_01_LATINO_MINI_02", //DBFFB0AE", //3690967214", //"604000082
            "G_M_Y_SALVABOSS_01_SALVADORIAN_MINI_01", //083FF1D1", //138408401", //138408401
            "G_M_Y_SALVABOSS_01_SALVADORIAN_MINI_02", //FB1D578C", //4213004172", //"81963124
            "G_M_Y_SALVAGOON_01_SALVADORIAN_MINI_01", //0E2D970B", //237868811", //237868811
            "G_M_Y_SALVAGOON_01_SALVADORIAN_MINI_02", //C9228CF6", //3374484726", //"920482570
            "G_M_Y_SALVAGOON_01_SALVADORIAN_MINI_03", //D6DD286B", //3604818027", //"690149269
            "G_M_Y_SALVAGOON_02_SALVADORIAN_MINI_01", //38FB557B", //955995515", //955995515
            "G_M_Y_SalvaGoon_02_SALVADORIAN_MINI_02", //2B1E39C1", //723401153", //723401153
            "G_M_Y_SALVAGOON_02_SALVADORIAN_MINI_03", //1C639C4C", //476290124", //476290124
            "G_M_Y_SALVAGOON_03_SALVADORIAN_MINI_01", //B2F150B6", //3002159286", //"1292808010
            "G_M_Y_SALVAGOON_03_SALVADORIAN_MINI_02", //50C88C62", //1355320418", //1355320418
            "G_M_Y_SalvaGoon_03_SALVADORIAN_MINI_03", //61092CDF", //1627991263", //1627991263
            "G_M_Y_STREETPUNK02_BLACK_MINI_04", //5E2969AE", //1579772334", //1579772334
            "G_M_Y_STREETPUNK_01_BLACK_MINI_01", //A5364DA4", //2771799460", //"1523167836
            "G_M_Y_STREETPUNK_01_BLACK_MINI_02", //7AD978EB", //2061072619", //2061072619
            "G_M_Y_STREETPUNK_01_BLACK_MINI_03", //4A3417A1", //1244927905", //1244927905
            "G_M_Y_STREETPUNK_02_BLACK_MINI_01", //4C3FB5C7", //1279243719", //1279243719
            "G_M_Y_STREETPUNK_02_BLACK_MINI_02", //658FE867", //1703929959", //1703929959
            "G_M_Y_STREETPUNK_02_BLACK_MINI_03", //58794E3A", //1484344890", //1484344890
            "G_M_Y_X17_AGUARD_01", //0FC95A0C", //264854028", //264854028
            "G_M_Y_X17_AGUARD_02", //1AEC7052", //451702866", //451702866
            "G_M_Y_X17_AGUARD_03", //ED3E94F7", //3980301559", //"314665737
            "G_M_Y_X17_AGUARD_04", //71369CE9", //1899404521", //1899404521
            "G_M_Y_X17_AGUARD_05", //7B64B145", //2070196549", //2070196549
            "CONSTRUCTION_SITE_MALE_01", //C285BFCA", //3263545290", //"1031422006
            "CONSTRUCTION_SITE_MALE_02", //3572A596", //896705942", //896705942
            "CONSTRUCTION_SITE_MALE_03", //82A1C003", //2191638531", //"2103328765
            "CONSTRUCTION_SITE_MALE_04", //93CE625C", //2479776348", //"1815190948
            "BAILBOND1JUMPER", //6909D3CC", //1762251724", //1762251724
            "BAILBOND2JUMPER", //8C257BBD", //2351266749", //"1943700547
            "BAILBOND3JUMPER", //2E2EF1F8", //774828536", //774828536
            "BAILBOND4JUMPER", //643A0559", //1681524057", //1681524057
            "BARRY", //A9058E54", //2835713620", //"1459253676
            "BARRY_01_ALIEN_A", //82BA2086", //2193236102", //"2101731194
            "BARRY_01_ALIEN_B", //7494843B", //1955890235", //1955890235
            "BARRY_01_ALIEN_C", //F06D7BEB", //4033706987", //"261260309
            "BARRY_02_CLOWN_A", //7929F21D", //2032792093", //2032792093
            "BARRY_02_CLOWN_B", //66F4CDB3", //1727319475", //1727319475
            "BARRY_02_CLOWN_C", //9E16BBF6", //2652290038", //"1642677258
            "HOSTAGEBF1", //D5D22CA5", //3587320997", //"707646299
            "HOSTAGEBM1", //E8CB2CFF", //3905629439", //"389337857
            "HOSTAGEWF1", //8632FA43", //2251487811", //"2043479485
            "HOSTAGEWF2", //99952107", //2576687367", //"1718279929
            "HOSTAGEWM1", //5779B631", //1467594289", //1467594289
            "HOSTAGEWM2", //9F53C5E4", //2673067492", //"1621899804
            "FRANKLIN_1_NORMAL", //D603B047", //3590565959", //"704401337
            "FRANKLIN_2_NORMAL", //9F8D1B67", //2676824935", //"1618142361
            "FRANKLIN_3_NORMAL", //FA7C388C", //4202444940", //"92522356
            "FRANKLIN_ANGRY", //D227A0A9", //3525812393", //"769154903
            "FRANKLIN_DRUNK", //E6EFD5C5", //3874477509", //"420489787
            "FRANKLIN_NORMAL", //64CCE782", //1691150210", //1691150210
            "MICHAEL_1_NORMAL", //78BECF39", //2025770809", //2025770809
            "MICHAEL_2_NORMAL", //568D3564", //1452094820", //1452094820
            "MICHAEL_3_NORMAL", //FBC7F7B9", //4224186297", //"70780999
            "MICHAEL_ANGRY", //973C5F18", //2537316120", //"1757651176
            "MICHAEL_DRUNK", //DEBBCFA7", //3736850343", //"558116953
            "MICHAEL_NORMAL", //C46897D1", //3295188945", //"999778351
            "MP_M_SHOPKEEP_01_CHINESE_MINI_01", //D36AF9E4", //3547003364", //"747963932
            "MP_M_SHOPKEEP_01_LATINO_MINI_01", //0592C339", //93504313", //93504313
            "MP_M_SHOPKEEP_01_PAKISTANI_MINI_01", //25364924", //624314660", //624314660
            "PAIN_FRANKLIN_01", //2003420C", //537084428", //537084428
            "PAIN_FRANKLIN_02", //EBF4D9F0", //3958692336", //"336274960
            "PAIN_FRANKLIN_03", //1DA7BD55", //497532245", //497532245
            "PAIN_FRANKLIN_04", //C5B08D68", //3316682088", //"978285208
            "PAIN_MALE_MIXED_01", //0A14C671", //169133681", //169133681
            "PAIN_MALE_MIXED_02", //A251F75D", //2723280733", //"1571686563
            "PAIN_MALE_MIXED_03", //700712C8", //1879511752", //1879511752
            "PAIN_MALE_MIXED_04", //86A03FFA", //2258649082", //"2036318214
            "PAIN_MALE_MIXED_05", //5124548F", //1361335439", //1361335439
            "PAIN_MALE_MIXED_06", //B25B96FC", //2992346876", //"1302620420
            "PAIN_MALE_MIXED_07", //BC96AB72", //3163990898", //"1130976398
            "PAIN_MALE_MIXED_08", //8DA5CD91", //2376453521", //"1918513775
            "PAIN_MALE_MIXED_09", //97EBE21D", //2548818461", //"1746148835
            "PAIN_MALE_NORMAL_01", //E3B792BC", //3820458684", //"474508612
            "PAIN_MALE_NORMAL_02", //145573EB", //341144555", //341144555
            "PAIN_MALE_NORMAL_03", //E296906E", //3801518190", //"493449106
            "PAIN_MALE_NORMAL_04", //B7C53ACC", //3083156172", //"1211811124
            "PAIN_MALE_NORMAL_05", //09F45F29", //167010089", //167010089
            "PAIN_MALE_NORMAL_06", //CB49E1D5", //3410616789", //"884350507
            "PAIN_MALE_TOUGH_01", //ACC806D0", //2898790096", //"1396177200
            "PAIN_MALE_TOUGH_02", //DB33E3A7", //3677610919", //"617356377
            "PAIN_MALE_TOUGH_03", //90FF4F3B", //2432651067", //"1862316229
            "PAIN_MALE_TOUGH_04", //BF202B80", //3206556544", //"1088410752
            "PAIN_MALE_TOUGH_05", //F397946E", //4086797422", //"208169874
            "PAIN_MALE_WEAK_01", //22C36EE8", //583233256", //583233256
            "PAIN_MALE_WEAK_02", //B05B0A1D", //2958756381", //"1336210915
            "PAIN_MALE_WEAK_03", //D62355AD", //3592639917", //"702327379
            "PAIN_MALE_WEAK_04", //E61CF5A0", //3860657568", //"434309728
            "PAIN_MICHAEL_01", //E657BAA9", //3864509097", //"430458199
            "PAIN_MICHAEL_02", //D8151E24", //3625262628", //"669704668
            "PAIN_MICHAEL_03", //3436D666", //876009062", //876009062
            "PAIN_MICHAEL_04", //66EB3BD2", //1726692306", //1726692306
            "PAIN_PLAYER_TEST_01", //F38B2CC2", //4085984450", //"208982846
            "PAIN_PLAYER_TEST_02", //E161886F", //3781265519", //"513701777
            "PAIN_PLAYER_TEST_03", //576C746B", //1466725483", //1466725483
            "PAIN_TEST_01", //F5655828", //4117059624", //"177907672
            "PAIN_TEST_02", //FC1C6596", //4229719446", //"65247850
            "PAIN_TEST_03", //172E9BA2", //388930466", //388930466
            "PAIN_TREVOR_01", //21261ADB", //556145371", //556145371
            "PAIN_TREVOR_02", //32DCBE48", //853327432", //853327432
            "PAIN_TREVOR_03", //3DAED3EC", //1034867692", //1034867692
            "PAIN_TREVOR_04", //4F427713", //1329755923", //1329755923
            "S_M_M_AMMUCOUNTRY_01_WHITE_01", //14AE106F", //346951791", //346951791
            "S_M_M_AMMUCOUNTRY_WHITE_MINI_01", //B6A5CF41", //3064319809", //"1230647487
            "S_M_M_AUTOSHOP_01_WHITE_01", //B97E410A", //3112059146", //"1182908150
            "S_M_M_BOUNCER_01_BLACK_FULL_01", //5CF368B8", //1559455928", //1559455928
            "S_M_M_BOUNCER_01_LATINO_FULL_01", //57B91BD3", //1471749075", //1471749075
            "S_M_M_BOUNCER_LATINO_FULL_01", //66E1CE62", //1726074466", //1726074466
            "S_M_M_CIASEC_01_BLACK_MINI_01", //797CD9E6", //2038225382", //2038225382
            "S_M_M_CIASEC_01_BLACK_MINI_02", //F6AED44C", //4138652748", //"156314548
            "S_M_M_CIASEC_01_WHITE_MINI_01", //7DB88D9D", //2109246877", //2109246877
            "S_M_M_CIASEC_01_WHITE_MINI_02", //AF77F11B", //2943873307", //"1351093989
            "S_M_M_FIBOFFICE_01_BLACK_MINI_01", //DEA5CD64", //3735407972", //"559559324
            "S_M_M_FIBOFFICE_01_BLACK_MINI_02", //F0C0F19A", //4039176602", //"255790694
            "S_M_M_FIBOFFICE_01_LATINO_MINI_01", //655117C7", //1699813319", //1699813319
            "S_M_M_FIBOFFICE_01_LATINO_MINI_02", //938DF440", //2475553856", //"1819413440
            "S_M_M_FIBOFFICE_01_WHITE_MINI_01", //0AC9249C", //180954268", //180954268
            "S_M_M_FIBOFFICE_01_WHITE_MINI_02", //FE040B12", //4261677842", //"33289454
            "S_M_M_GENERICCHEAPWORKER_01_LATINO_MINI_01", //90328A79", //2419231353", //"1875735943
            "S_M_M_GENERICCHEAPWORKER_01_LATINO_MINI_02", //D9249C5C", //3643055196", //"651912100
            "S_M_M_GENERICCHEAPWORKER_01_LATINO_MINI_03", //EBDDC1CE", //3957178830", //"337788466
            "S_M_M_GENERICCHEAPWORKER_01_LATINO_MINI_04", //635D30CB", //1667051723", //1667051723
            "S_M_M_GENERICMARINE_01_LATINO_MINI_01", //24A78E34", //614960692", //614960692
            "S_M_M_GENERICMARINE_01_LATINO_MINI_02", //8F6E63C0", //2406376384", //"1888590912
            "S_M_M_GENERICMECHANIC_01_BLACK_MINI_01", //229CDFDF", //580706271", //580706271
            "S_M_M_GENERICMECHANIC_01_BLACK_MINI_02", //09392D18", //154742040", //154742040
            "S_M_M_GENERICPOSTWORKER_01_BLACK_MINI_01", //10C0CBFD", //281070589", //281070589
            "S_M_M_GENERICPOSTWORKER_01_BLACK_MINI_02", //FC16A2A9", //4229341865", //"65625431
            "S_M_M_GENERICPOSTWORKER_01_WHITE_MINI_01", //D2C75726", //3536279334", //"758687962
            "S_M_M_GENERICPOSTWORKER_01_WHITE_MINI_02", //DC906AB8", //3700452024", //"594515272
            "S_M_M_GENERICSECURITY_01_BLACK_MINI_01", //3D1D46D3", //1025328851", //1025328851
            "S_M_M_GENERICSECURITY_01_BLACK_MINI_02", //565A794D", //1448769869", //1448769869
            "S_M_M_GENERICSECURITY_01_BLACK_MINI_03", //9162EF15", //2439180053", //"1855787243
            "S_M_M_GENERICSECURITY_01_LATINO_MINI_01", //B5910C1D", //3046181917", //"1248785379
            "S_M_M_GENERICSECURITY_01_LATINO_MINI_02", //97D1D09F", //2547110047", //"1747857249
            "S_M_M_GENERICSECURITY_01_WHITE_MINI_01", //5D4BE0A9", //1565253801", //1565253801
            "S_M_M_GENERICSECURITY_01_WHITE_MINI_02", //4FE145D4", //1340163540", //1340163540
            "S_M_M_GENERICSECURITY_01_WHITE_MINI_03", //66DDF3D9", //1725821913", //1725821913
            "S_M_M_HAIRDRESSER_01_BLACK_MINI_01", //594BCB86", //1498139526", //1498139526
            "S_M_M_HAIRDRESS_01_BLACK_01", //7E2CBE66", //2116861542", //2116861542
            "S_M_M_PARAMEDIC_01_BLACK_MINI_01", //1DE649B3", //501631411", //501631411
            "S_M_M_PARAMEDIC_01_LATINO_MINI_01", //43261273", //1126568563", //1126568563
            "S_M_M_PARAMEDIC_01_WHITE_MINI_01", //54925FD6", //1418878934", //1418878934
            "S_M_M_PILOT_01_BLACK_FULL_01", //3DAC41B0", //1034699184", //1034699184
            "S_M_M_PILOT_01_BLACK_FULL_02", //4F73E53F", //1332995391", //1332995391
            "S_M_M_PILOT_01_WHITE_FULL_01", //BC0F504A", //3155120202", //"1139847094
            "S_M_M_PILOT_01_WHITE_FULL_02", //A9A32B72", //2846042994", //"1448924302
            "S_M_M_TRUCKER_01_BLACK_FULL_01", //D940A3BC", //3644892092", //"650075204
            "S_M_M_TRUCKER_01_WHITE_FULL_01", //3CA3269A", //1017325210", //1017325210
            "S_M_M_TRUCKER_01_WHITE_FULL_02", //0B4743DF", //189219807", //189219807
            "S_M_Y_AIRWORKER_BLACK_FULL_01", //90ECCFDC", //2431438812", //"1863528484
            "S_M_Y_AIRWORKER_BLACK_FULL_02", //9EAF6B61", //2662296417", //"1632670879
            "S_M_Y_AIRWORKER_LATINO_FULL_01", //0D981AB3", //228072115", //228072115
            "S_M_Y_AIRWORKER_LATINO_FULL_02", //234F4621", //592397857", //592397857
            "S_M_Y_AMMUCITY_01_WHITE_01", //5C7526F0", //1551181552", //1551181552
            "S_M_Y_AMMUCITY_01_WHITE_MINI_01", //20C18390", //549553040", //549553040
            "S_M_Y_BAYWATCH_01_BLACK_FULL_01", //CD79387C", //3447273596", //"847693700
            "S_M_Y_BAYWATCH_01_BLACK_FULL_02", //E32263CE", //3810681806", //"484285490
            "S_M_Y_BAYWATCH_01_WHITE_FULL_01", //BAB6D724", //3132544804", //"1162422492
            "S_M_Y_BAYWATCH_01_WHITE_FULL_02", //1EA89F06", //514367238", //514367238
            "S_M_Y_BLACKOPS_01_BLACK_MINI_01", //BBE7E188", //3152535944", //"1142431352
            "S_M_Y_BLACKOPS_01_BLACK_MINI_02", //DDB7A52B", //3719800107", //"575167189
            "S_M_Y_BLACKOPS_01_WHITE_MINI_01", //65B98207", //1706656263", //1706656263
            "S_M_Y_BLACKOPS_01_WHITE_MINI_02", //D7FFE692", //3623872146", //"671095150
            "S_M_Y_BLACKOPS_02_LATINO_MINI_01", //4214AE9E", //1108651678", //1108651678
            "S_M_Y_BLACKOPS_02_LATINO_MINI_02", //13E2520A", //333599242", //333599242
            "S_M_Y_BLACKOPS_02_WHITE_MINI_01", //C3A6E830", //3282495536", //"1012471760
            "S_M_Y_BUSBOY_01_WHITE_MINI_01", //C847EAA9", //3360156329", //"934810967
            "S_M_Y_COP_01_BLACK_FULL_01", //DD72FE87", //3715300999", //"579666297
            "S_M_Y_COP_01_BLACK_FULL_02", //C7B3D309", //3350450953", //"944516343
            "S_M_Y_COP_01_BLACK_MINI_01", //EF2409AE", //4012116398", //"282850898
            "S_M_Y_COP_01_BLACK_MINI_02", //00CDAD01", //13479169", //13479169
            "S_M_Y_COP_01_BLACK_MINI_03", //4A804065", //1249919077", //1249919077
            "S_M_Y_COP_01_BLACK_MINI_04", //5C34E3CE", //1546970062", //1546970062
            "S_M_Y_COP_01_WHITE_FULL_01", //6F38027D", //1865941629", //1865941629
            "S_M_Y_COP_01_WHITE_FULL_02", //360C1026", //906760230", //906760230
            "S_M_Y_COP_01_WHITE_MINI_01", //BA399207", //3124335111", //"1170632185
            "S_M_Y_COP_01_WHITE_MINI_02", //CBEB356A", //3421189482", //"873777814
            "S_M_Y_COP_01_WHITE_MINI_03", //DDB458FC", //3719583996", //"575383300
            "S_M_Y_COP_01_WHITE_MINI_04", //EF5EFC51", //4015979601", //"278987695
            "S_M_Y_FIREMAN_01_LATINO_FULL_01", //71549C50", //1901370448", //1901370448
            "S_M_Y_FIREMAN_01_LATINO_FULL_02", //7C0BB1BE", //2081141182", //2081141182
            "S_M_Y_FIREMAN_01_WHITE_FULL_01", //0094A96A", //9742698", //9742698
            "S_M_Y_FIREMAN_01_WHITE_FULL_02", //80DB29FD", //2161846781", //"2133120515
            "S_M_Y_GENERICCHEAPWORKER_01_BLACK_MINI_01", //09FD9FD3", //167616467", //167616467
            "S_M_Y_GENERICCHEAPWORKER_01_BLACK_MINI_02", //37D07B78", //936409976", //936409976
            "S_M_Y_GENERICCHEAPWORKER_01_WHITE_MINI_01", //3869CBA7", //946457511", //946457511
            "S_M_Y_GENERICMARINE_01_BLACK_MINI_01", //17F5909B", //401969307", //401969307
            "S_M_Y_GENERICMARINE_01_BLACK_MINI_02", //0E947DD1", //244612561", //244612561
            "S_M_Y_GENERICMARINE_01_WHITE_MINI_01", //55FDC164", //1442693476", //1442693476
            "S_M_Y_GENERICMARINE_01_WHITE_MINI_02", //08BBA6E1", //146515681", //146515681
            "S_M_Y_GENERICWORKER_01_BLACK_MINI_01", //0A3A301F", //171585567", //171585567
            "S_M_Y_GENERICWORKER_01_BLACK_MINI_02", //60D0DD4B", //1624300875", //1624300875
            "S_M_Y_GENERICWORKER_01_LATINO_MINI_01", //86640419", //2254701593", //"2040265703
            "S_M_Y_GENERICWORKER_01_LATINO_MINI_02", //F4AC60AC", //4104937644", //"190029652
            "S_M_Y_GENERICWORKER_01_WHITE_01", //129AD4A3", //312136867", //312136867
            "S_M_Y_GENERICWORKER_01_WHITE_MINI_01", //E8727D7D", //3899817341", //"395149955
            "S_M_Y_GENERICWORKER_01_WHITE_MINI_02", //B23310FF", //2989691135", //"1305276161
            "S_M_Y_HWAYCOP_01_BLACK_FULL_01", //DC403AA7", //3695196839", //"599770457
            "S_M_Y_HWAYCOP_01_BLACK_FULL_02", //11AAA57B", //296396155", //296396155
            "S_M_Y_HWAYCOP_01_WHITE_FULL_01", //F332D786", //4080195462", //"214771834
            "S_M_Y_HWAYCOP_01_WHITE_FULL_02", //0384F82A", //59045930", //59045930
            "S_M_Y_MCOP_01_WHITE_MINI_01", //7A44FB56", //2051341142", //2051341142
            "S_M_Y_MCOP_01_WHITE_MINI_02", //670ED4EA", //1729025258", //1729025258
            "S_M_Y_MCOP_01_WHITE_MINI_03", //54D0306D", //1422930029", //1422930029
            "S_M_Y_MCOP_01_WHITE_MINI_04", //B361ED8F", //3009539471", //"1285427825
            "S_M_Y_MCOP_01_WHITE_MINI_05", //0F8FA5E9", //261072361", //261072361
            "S_M_Y_MCOP_01_WHITE_MINI_06", //FFE50694", //4293199508", //"1767788
            "S_M_Y_RANGER_01_LATINO_FULL_01", //94EBCA6B", //2498480747", //"1796486549
            "S_M_Y_RANGER_01_WHITE_FULL_01", //9723C55B", //2535703899", //"1759263397
            "S_M_Y_SHERIFF_01_WHITE_FULL_01", //A1C8B88A", //2714286218", //"1580681078
            "S_M_Y_SHERIFF_01_WHITE_FULL_02", //939F1C37", //2476678199", //"1818289097
            "S_M_Y_SHOP_MASK_WHITE_MINI_01", //03AAB8B0", //61520048", //61520048
            "S_M_Y_SWAT_01_WHITE_FULL_01", //BA960340", //3130393408", //"1164573888
            "S_M_Y_SWAT_01_WHITE_FULL_02", //E55E58D0", //3848165584", //"446801712
            "S_M_Y_SWAT_01_WHITE_FULL_03", //F324745C", //4079252572", //"215714724
            "S_M_Y_SWAT_01_WHITE_FULL_04", //0236127F", //37098111", //37098111
            "U_M_Y_TATTOO_01_WHITE_MINI_01", //956C178D", //2506889101", //"1788078195
            "TAXIALONZO", //A0B07846", //2695919686", //"1599047610
            "TAXIBRUCE", //1E0A9C18", //504011800", //504011800
            "TAXICLYDE", //90992C60", //2425957472", //"1869009824
            "TAXIDARREN", //2C1A5202", //739922434", //739922434
            "TAXIDERRICK", //2D71435C", //762397532", //762397532
            "TAXIDOM", //9DA9FDB5", //2645163445", //"1649803851
            "TAXIFELIPE", //E66D1B66", //3865910118", //"429057178
            "TAXIGANGM", //08AC318A", //145502602", //145502602
            "TAXIJAMES", //A8A8F64E", //2829645390", //"1465321906
            "TAXIKWAK", //58B68A9D", //1488358045", //1488358045
            "TAXIOJCOP1", //5883C603", //1485030915", //1485030915
            "TAXIOTIS", //A0B868F9", //2696440057", //"1598527239
            "TAXIPAULIE", //05437D58", //88309080", //88309080
            "TAXIWALTER", //1A43E0E1", //440656097", //440656097
            "TEST_VOICE", //62883B8C", //1653095308", //1653095308
            "TREVOR_1_NORMAL", //3AD6D338", //987157304", //987157304
            "TREVOR_2_NORMAL", //CB2DDB29", //3408780073", //"886187223
            "TREVOR_3_NORMAL", //4697A021", //1184342049", //1184342049
            "TREVOR_ANGRY", //0953FCF8", //156499192", //156499192
            "TREVOR_DRUNK", //EA0CA87A", //3926698106", //"368269190
            "TREVOR_NORMAL", //4072CC77", //1081265271", //1081265271
            "VB_LIFEGUARD_01", //6B6161EE", //1801544174", //1801544174
            "VB_MALE_01", //AC519660", //2891028064", //"1403939232
            "VB_MALE_02", //B5E5A988", //3051727240", //"1243240056
            "VB_MALE_03", //3A03B192", //973320594", //973320594
            "WAVELOAD_PAIN_FRANKLIN", //33F65FC3", //871784387", //871784387
            "WAVELOAD_PAIN_MALE", //804C18BB", //2152470715", //"2142496581
            "WAVELOAD_PAIN_MICHAEL", //6531A692", //1697752722", //1697752722
            "WAVELOAD_PAIN_TREVOR" //0CF83E9F", //217595551", //217595551
};
const std::vector<std::string> VoicesFemale = {
                "Default",
            "ABIGAIL", //073DD899", //121493657", //121493657
            "AIRPORT_PA_FEMALE", //80D0944F", //2161153103", //"2133814193
            "AMANDA_DRUNK", //5C0B144D", //1544229965", //1544229965
            "AMANDA_NORMAL", //EC6C9072", //3966537842", //"328429454
            "CHASTITY", //9B4468A9", //2604951721", //"1690015575
            "CHASTITY_MP", //4E0041AA", //1308639658", //1308639658
            "CST4ACTRESS", //6A8C4C84", //1787579524", //1787579524
            "DARYL", //10088962", //268994914", //268994914
            "DENISE", //860AA79A", //2248845210", //"2046122086
            "EXECPA_FEMALE", //B6FB2A37", //3069913655", //"1225053641
            "GIRL1", //9ABA4CB8", //2595900600", //"1699066696
            "GIRL2", //C38C1E5B", //3280739931", //"1014227365
            "GRIFF", //03DD4948", //64833864", //64833864
            "FUFU", //ED8EA575", //3985548661", //"309418635
            "FUFU_MP", //4EA343CA", //1319322570", //1319322570
            "JANE", //893E74D0", //2302571728", //"1992395568
            "JANET", //8498F40B", //2224616459", //"2070350837
            "JULIET", //27AD5D38", //665673016", //665673016
            "KAREN", //FBF9CDB2", //4227452338", //"67514958
            "KIDNAPPEDFEMALE", //064DC6E9", //105760489", //105760489
            "LACEY", //29CAB776", //701151094", //701151094
            "LI_FEMALE_01", //E58E5187", //3851309447", //"443657849
            "LOSTKIDNAPGIRL", //7D8F4F88", //2106544008", //2106544008
            "MAID", //015EE6C7", //22996679", //22996679
            "MARNIE", //5FA82CAC", //1604857004", //1604857004
            "MARYANN", //9FEEF145", //2683236677", //"1611730619
            "MAUDE", //1AE32960", //451094880", //451094880
            "MRSTHORNHILL", //C6DE44C8", //3336455368", //"958511928
            "NIKKI", //47F4D564", //1207227748", //1207227748
            "NIKKI_MP", //11515E1F", //290545183", //290545183
            "PAIGE", //C2515320", //3260109600", //"1034857696
            "PAMELA_DRAKE", //714E62B7", //1900962487", //1900962487
            "PATRICIA", //D22B34C3", //3526046915", //"768920381
            "PEACH", //FE7FCDEA", //4269788650", //"25178646
            "PIER_ANNOUNCE_FEMALE", //3AB5E64D", //984999501", //984999501
            "REHH5BRIDE", //923B42A5", //2453357221", //"1841610075
            "REHOMGIRL", //745E2A7D", //1952328317", //1952328317
            "REPRI1LOST", //4E9991FE", //1318687230", //1318687230
            "SAPPHIRE", //74F8F352", //1962472274", //1962472274
            "TALINA", //ED031790", //3976402832", //"318564464
            "TAXIGANGGIRL1", //E2228087", //3793911943", //"501055353
            "TAXIGANGGIRL2", //F7E3AC09", //4158893065", //"136074231
            "TAXIKEYLA", //23ACB127", //598520103", //598520103
            "TAXILIZ", //C8B6AC99", //3367414937", //"927552359
            "TAXIMIRANDA", //97A199A8", //2543950248", //"1751017048
            "TONYA", //FCB43161", //4239667553", //"55299743
            "TRACEY", //5A7D2459", //1518150745", //1518150745
            "VB_FEMALE_01", //CB2136C8", //3407951560", //"887015736
            "VB_FEMALE_02", //E4EA6A5A", //3840567898", //"454399398
            "VB_FEMALE_03", //B1510330", //2974876464", //"1320090832
            "VB_FEMALE_04", //C397A7BD", //3281495997", //"1013471299
            "WAVELOAD_PAIN_FEMALE", //332128AB", //857811115", //857811115
            "WFSTEWARDESS", //84EDE1BF", //2230182335", //"2064784961
            "HS4_KAYLEE_PVG",
            "HS4_JACKIE_PVG",
            "FEMALE_CLUB_R2PVG",
            "BTL_CONNIE_PVG",
            "AFFLUENT_SUBURBAN_FEMALE_01", //FF4D4698", //4283254424", //"11712872
            "AFFLUENT_SUBURBAN_FEMALE_02", //12836D04", //310603012", //310603012
            "AFFLUENT_SUBURBAN_FEMALE_03", //DC6000BE", //3697279166", //"597688130
            "AFFLUENT_SUBURBAN_FEMALE_04", //EE1AA433", //3994723379", //"300243917
            "AFFLUENT_SUBURBAN_FEMALE_05", //A47190DE", //2758906078", //"1536061218
            "AFFLUENT_SUBURBAN_FEMALE_06", //B62C3453", //3056350291", //"1238617005
            "AIRCRAFT_WARNING_FEMALE_01", //85A08F9C", //2241892252", //"2053075044
            "A_F_M_BEACH_01_WHITE_FULL_01", //6B996380", //1805214592", //1805214592
            "A_F_M_BEACH_01_WHITE_MINI_01", //139EA948", //329165128", //329165128
            "A_F_M_BEVHILLS_01_WHITE_FULL_01", //00A8641D", //11035677", //11035677
            "A_F_M_BEVHILLS_01_WHITE_MINI_01", //3E0995AE", //1040815534", //1040815534
            "A_F_M_BEVHILLS_01_WHITE_MINI_02", //4ABAAF10", //1253748496", //1253748496
            "A_F_M_BEVHILLS_02_BLACK_FULL_01", //8455F5F0", //2220226032", //"2074741264
            "A_F_M_BEVHILLS_02_BLACK_MINI_01", //466B8D2A", //1181453610", //1181453610
            "A_F_M_BEVHILLS_02_WHITE_FULL_01", //B228C501", //2989016321", //"1305950975
            "A_F_M_BEVHILLS_02_WHITE_FULL_02", //CC76F99D", //3430349213", //"864618083
            "A_F_M_BEVHILLS_02_WHITE_MINI_01", //3FD63057", //1071001687", //1071001687
            "A_F_M_BODYBUILD_01_BLACK_FULL_01", //4B0E89BF", //1259243967", //1259243967
            "A_F_M_BODYBUILD_01_BLACK_MINI_01", //23D791B0", //601330096", //601330096
            "A_F_M_BODYBUILD_01_WHITE_FULL_01", //8773ADD6", //2272505302", //"2022461994
            "A_F_M_BODYBUILD_01_WHITE_MINI_01", //B902AA3A", //3103959610", //"1191007686
            "A_F_M_BUSINESS_02_WHITE_MINI_01", //9C4AD53A", //2622149946", //"1672817350
            "A_F_M_DOWNTOWN_01_BLACK_FULL_01", //0AA25C8F", //178412687", //178412687
            "A_F_M_EASTSA_01_LATINO_FULL_01", //0ACC23F9", //181150713", //181150713
            "A_F_M_EASTSA_01_LATINO_MINI_01", //CE348715", //3459548949", //"835418347
            "A_F_M_EASTSA_02_LATINO_FULL_01", //0AA30167", //178454887", //178454887
            "A_F_M_EASTSA_02_LATINO_MINI_01", //721CC9FF", //1914489343", //1914489343
            "A_F_M_FATWHITE_01_WHITE_FULL_01", //D2158D79", //3524627833", //"770339463
            "A_F_M_FATWHITE_01_WHITE_MINI_01", //59E595EB", //1508218347", //1508218347
            "A_F_M_KTOWN_01_KOREAN_FULL_01", //D77777E6", //3614930918", //"680036378
            "A_F_M_KTOWN_01_KOREAN_MINI_01", //AF6FB9B1", //2943334833", //"1351632463
            "A_F_M_KTOWN_02_CHINESE_MINI_01", //C533C983", //3308505475", //"986461821
            "A_F_M_KTOWN_02_KOREAN_FULL_01", //D8CD3773", //3637327731", //"657639565
            "A_F_M_SALTON_01_WHITE_FULL_01", //89DA8A2E", //2312800814", //"1982166482
            "A_F_M_SALTON_01_WHITE_FULL_02", //9C052E83", //2617585283", //"1677382013
            "A_F_M_SALTON_01_WHITE_FULL_03", //A66E4355", //2792244053", //"1502723243
            "A_F_M_SALTON_01_WHITE_MINI_01", //8701705E", //2265018462", //"2029948834
            "A_F_M_SALTON_01_WHITE_MINI_02", //7DC35DE2", //2109955554", //2109955554
            "A_F_M_SALTON_01_WHITE_MINI_03", //6675AF47", //1718988615", //1718988615
            "A_F_M_SKIDROW_01_BLACK_FULL_01", //A7C0DE51", //2814434897", //"1480532399
            "A_F_M_SKIDROW_01_BLACK_MINI_01", //443E6FBE", //1144942526", //1144942526
            "A_F_M_SKIDROW_01_WHITE_FULL_01", //F8F30014", //4176674836", //"118292460
            "A_F_M_SKIDROW_01_WHITE_MINI_01", //705684C4", //1884718276", //1884718276
            "A_F_M_SOUCENT_01_BLACK_FULL_01", //4E0DA806", //1309517830", //1309517830
            "A_F_M_SOUCENT_02_BLACK_FULL_01", //C725E5CC", //3341149644", //"953817652
            "A_F_M_TOURIST_01_WHITE_MINI_01", //25365382", //624317314", //624317314
            "A_F_M_TRAMPBEAC_01_BLACK_FULL_01", //F091AF03", //4036079363", //"258887933
            "A_F_M_TRAMPBEAC_01_BLACK_MINI_01", //DE24211D", //3726909725", //"568057571
            "A_F_M_TRAMPBEAC_01_WHITE_FULL_01", //8D34DFCC", //2369052620", //"1925914676
            "A_F_M_TRAMP_01_WHITE_FULL_01", //D05841FA", //3495444986", //"799522310
            "A_F_M_TRAMP_01_WHITE_MINI_01", //55CE3CCC", //1439579340", //1439579340
            "A_F_O_GENSTREET_01_WHITE_MINI_01", //482D1EC8", //1210916552", //1210916552
            "A_F_O_INDIAN_01_INDIAN_MINI_01", //8755E8CA", //2270554314", //"2024412982
            "A_F_O_KTOWN_01_KOREAN_FULL_01", //DBE7871F", //3689383711", //"605583585
            "A_F_O_KTOWN_01_KOREAN_MINI_01", //F94EAEEB", //4182683371", //"112283925
            "A_F_O_SALTON_01_WHITE_FULL_01", //F79EEC05", //4154387461", //"140579835
            "A_F_O_SALTON_01_WHITE_MINI_01", //FCBC6F1F", //4240207647", //"54759649
            "A_F_O_SOUCENT_01_BLACK_FULL_01", //3439D3C2", //876204994", //876204994
            "A_F_O_SOUCENT_02_BLACK_FULL_01", //F27CEF94", //4068274068", //"226693228
            "A_F_Y_BEACH_01_BLACK_MINI_01", //4B79AF9D", //1266266013", //1266266013
            "A_F_Y_BEACH_01_WHITE_FULL_01", //2BCAB282", //734704258", //734704258
            "A_F_Y_BEACH_01_WHITE_MINI_01", //13609A3C", //325098044", //325098044
            "A_F_Y_BEACH_BLACK_FULL_01", //0422CC2C", //69389356", //69389356
            "A_F_Y_BEVHILLS_01_WHITE_FULL_01", //E7099D21", //3876166945", //"418800351
            "A_F_Y_BEVHILLS_01_WHITE_MINI_01", //D2C133B9", //3535877049", //"759090247
            "A_F_Y_BEVHILLS_02_WHITE_FULL_01", //F700AB54", //4144016212", //"150951084
            "A_F_Y_BEVHILLS_02_WHITE_MINI_01", //AA4B2212", //2857050642", //"1437916654
            "A_F_Y_BEVHILLS_02_WHITE_MINI_02", //7E1BC9B0", //2115750320", //2115750320
            "A_F_Y_BEVHILLS_03_WHITE_FULL_01", //8558FF3F", //2237202239", //"2057765057
            "A_F_Y_BEVHILLS_03_WHITE_MINI_01", //D17E6765", //3514722149", //"780245147
            "A_F_Y_BEVHILLS_04_WHITE_FULL_01", //B91127EB", //3104909291", //"1190058005
            "A_F_Y_BEVHILLS_04_WHITE_MINI_01", //9A251230", //2586120752", //"1708846544
            "A_F_Y_BUSINESS_01_WHITE_FULL_01", //A3D0C7CD", //2748368845", //"1546598451
            "A_F_Y_BUSINESS_01_WHITE_MINI_01", //87816F13", //2273406739", //"2021560557
            "A_F_Y_BUSINESS_01_WHITE_MINI_02", //188B9125", //411799845", //411799845
            "A_F_Y_BUSINESS_02_WHITE_FULL_01", //4CC300E2", //1287848162", //1287848162
            "A_F_Y_BUSINESS_02_WHITE_MINI_01", //94B7537B", //2495042427", //"1799924869
            "A_F_Y_BUSINESS_03_CHINESE_FULL_01", //7D9DD020", //2107494432", //2107494432
            "A_F_Y_BUSINESS_03_CHINESE_MINI_01", //D41AE44A", //3558532170", //"736435126
            "A_F_Y_BUSINESS_03_LATINO_FULL_01", //420377DE", //1107523550", //1107523550
            "A_F_Y_BUSINESS_04_BLACK_FULL_01", //26D1F656", //651294294", //651294294
            "A_F_Y_BUSINESS_04_BLACK_MINI_01", //97D8B312", //2547561234", //"1747406062
            "A_F_Y_BUSINESS_04_WHITE_MINI_01", //BE6FAE2C", //3194990124", //"1099977172
            "A_F_Y_EASTSA_01_LATINO_FULL_01", //3CB71B34", //1018633012", //1018633012
            "A_F_Y_EASTSA_01_LATINO_MINI_01", //D3A7F87F", //3551000703", //"743966593
            "A_F_Y_EASTSA_02_WHITE_FULL_01", //3DDC0236", //1037828662", //1037828662
            "A_F_Y_EASTSA_03_LATINO_FULL_01", //C801D0E0", //3355562208", //"939405088
            "A_F_Y_EASTSA_03_LATINO_MINI_01", //38E9E4FC", //954852604", //954852604
            "A_F_Y_EPSILON_01_WHITE_MINI_01", //1B66BF81", //459718529", //459718529
            "A_F_Y_FITNESS_01_WHITE_FULL_01", //7639B49D", //1983493277", //1983493277
            "A_F_Y_FITNESS_01_WHITE_MINI_01", //E2D732E6", //3805754086", //"489213210
            "A_F_Y_FITNESS_02_BLACK_FULL_01", //851B5376", //2233160566", //"2061806730
            "A_F_Y_FITNESS_02_BLACK_MINI_01", //27C40170", //667156848", //667156848
            "A_F_Y_FITNESS_02_WHITE_FULL_01", //BF9CB8C8", //3214719176", //"1080248120
            "A_F_Y_FITNESS_02_WHITE_MINI_01", //A105E3A0", //2701517728", //"1593449568
            "A_F_Y_Golfer_01_WHITE_FULL_01", //B81316C5", //3088258757", //"1206708539
            "A_F_Y_Golfer_01_WHITE_MINI_01", //5F5BFB44", //1599863620", //1599863620
            "A_F_Y_HIKER_01_WHITE_FULL_01", //BB0A674E", //3138021198", //"1156946098
            "A_F_Y_HIKER_01_WHITE_MINI_01", //C8CAFB5E", //3368745822", //"926221474
            "A_F_Y_HIPSTER_01_WHITE_FULL_01", //A24D58EA", //2722978026", //"1571989270
            "A_F_Y_HIPSTER_01_WHITE_MINI_01", //92D2202A", //2463244330", //"1831722966
            "A_F_Y_HIPSTER_02_WHITE_FULL_01", //83EA9D79", //2213191033", //"2081776263
            "A_F_Y_HIPSTER_02_WHITE_MINI_01", //41543F56", //1096040278", //1096040278
            "A_F_Y_HIPSTER_02_WHITE_MINI_02", //2F6F9B8D", //795843469", //795843469
            "A_F_Y_HIPSTER_03_WHITE_FULL_01", //ADED3C9F", //2918005919", //"1376961377
            "A_F_Y_HIPSTER_03_WHITE_MINI_01", //F824C1C7", //4163158471", //"131808825
            "A_F_Y_HIPSTER_03_WHITE_MINI_02", //E95A2432", //3914998834", //"379968462
            "A_F_Y_HIPSTER_04_WHITE_FULL_01", //3141C876", //826394742", //826394742
            "A_F_Y_HIPSTER_04_WHITE_MINI_01", //6B08FBA6", //1795750822", //1795750822
            "A_F_Y_HIPSTER_04_WHITE_MINI_02", //3BDF1D53", //1004477779", //1004477779
            "A_F_Y_INDIAN_01_INDIAN_MINI_01", //AD0551E1", //2902807009", //"1392160287
            "A_F_Y_INDIAN_01_INDIAN_MINI_02", //BF49F66A", //3209295466", //"1085671830
            "A_F_Y_ROLLERCOASTER_01_MINI_01", //5470D900", //1416681728", //1416681728
            "A_F_Y_ROLLERCOASTER_01_MINI_02", //4295B54A", //1117107530", //1117107530
            "A_F_Y_ROLLERCOASTER_01_MINI_03", //C2393483", //3258528899", //"1036438397
            "A_F_Y_ROLLERCOASTER_01_MINI_04", //B015903C", //2954203196", //"1340764100
            "A_F_Y_SKATER_01_WHITE_FULL_01", //52D929F1", //1389963761", //1389963761
            "A_F_Y_SKATER_01_WHITE_MINI_01", //6E55B81F", //1851111455", //1851111455
            "A_F_Y_SOUCENT_01_BLACK_FULL_01", //A0FDDA5B", //2700991067", //"1593976229
            "A_F_Y_SOUCENT_02_BLACK_FULL_01", //DB96A76C", //3684083564", //"610883732
            "A_F_Y_SOUCENT_03_LATINO_FULL_01", //AA71DF24", //2859589412", //"1435377884
            "A_F_Y_SOUCENT_03_LATINO_MINI_01", //656710BE", //1701253310", //1701253310
            "A_F_Y_TENNIS_01_BLACK_MINI_01", //B602DF7D", //3053641597", //"1241325699
            "A_F_Y_TENNIS_01_WHITE_MINI_01", //434E2C2C", //1129196588", //1129196588
            "A_F_Y_TOURIST_01_BLACK_FULL_01", //ECA3EB4D", //3970165581", //"324801715
            "A_F_Y_TOURIST_01_BLACK_MINI_01", //A3713FCD", //2742108109", //"1552859187
            "A_F_Y_TOURIST_01_LATINO_FULL_01", //D6F2B12F", //3606229295", //"688738001
            "A_F_Y_TOURIST_01_LATINO_MINI_01", //122F5483", //305091715", //305091715
            "A_F_Y_TOURIST_01_WHITE_FULL_01", //DBEFEC5C", //3689933916", //"605033380
            "A_F_Y_TOURIST_01_WHITE_MINI_01", //216BE906", //560720134", //560720134
            "A_F_Y_TOURIST_02_WHITE_MINI_01", //0D6F398A", //225393034", //225393034
            "A_F_Y_VINEWOOD_01_WHITE_FULL_01", //2AF2EF5B", //720564059", //720564059
            "A_F_Y_VINEWOOD_01_WHITE_MINI_01", //23A74DCA", //598166986", //598166986
            "A_F_Y_VINEWOOD_02_WHITE_FULL_01", //3A311C01", //976296961", //976296961
            "A_F_Y_VINEWOOD_02_WHITE_MINI_01", //191A5AF2", //421157618", //421157618
            "A_F_Y_Vinewood_03_Chinese_FULL_01", //E632B0F0", //3862081776", //"432885520
            "A_F_Y_VINEWOOD_03_CHINESE_MINI_01", //3512D951", //890427729", //890427729
            "A_F_Y_VINEWOOD_04_WHITE_FULL_01", //20C68AC8", //549882568", //549882568
            "A_F_Y_VINEWOOD_04_WHITE_MINI_01", //12763C39", //309738553", //309738553
            "A_F_Y_VINEWOOD_04_WHITE_MINI_02", //C8CB28E4", //3368757476", //"926209820
            "G_F_Y_BALLAS_01_BLACK_MINI_01", //15BB1C9C", //364584092", //364584092
            "G_F_Y_BALLAS_01_BLACK_MINI_02", //17F72114", //402071828", //402071828
            "G_F_Y_BALLAS_01_BLACK_MINI_03", //1D7F2C2C", //494873644", //494873644
            "G_F_Y_BALLAS_01_BLACK_MINI_04", //403F71AC", //1077899692", //1077899692
            "G_F_Y_FAMILIES_01_BLACK_MINI_01", //4D341506", //1295258886", //1295258886
            "G_F_Y_FAMILIES_01_BLACK_MINI_02", //69F34E84", //1777553028", //1777553028
            "G_F_Y_FAMILIES_01_BLACK_MINI_03", //B0B85C0D", //2964872205", //"1330095091
            "G_F_Y_FAMILIES_01_BLACK_MINI_04", //5B7DB199", //1534964121", //1534964121
            "G_F_Y_FAMILIES_01_BLACK_MINI_05", //85658568", //2238023016", //"2056944280
            "G_F_Y_FAMILIES_01_BLACK_MINI_06", //BFA0F9DE", //3214997982", //"1079969314
            "G_F_Y_VAGOS_01_LATINO_MINI_01", //0320E887", //52488327", //52488327
            "G_F_Y_VAGOS_01_LATINO_MINI_02", //D6930F6C", //3599961964", //"695005332
            "G_F_Y_VAGOS_01_LATINO_MINI_03", //7E0BDE5F", //2114707039", //2114707039
            "G_F_Y_VAGOS_01_LATINO_MINI_04", //8854F2F1", //2287268593", //"2007698703
            "NIGHT_OUT_FEMALE_01", //33A0908D", //866160781", //866160781
            "NIGHT_OUT_FEMALE_02", //49EBBD23", //1240186147", //1240186147
            "NIGHT_OUT_FEMALE_03", //831EAF88", //2199826312", //"2095140984
            "NIGHT_OUT_FEMALE_04", //A56CF424", //2775381028", //"1519586268
            "PAIN_FEMALE_01", //40F0B1B8", //1089515960", //1089515960
            "PAIN_FEMALE_02", //D828602D", //3626524717", //"668442579
            "PAIN_FEMALE_NORMAL_01", //6EF36D3C", //1861446972", //1861446972
            "PAIN_FEMALE_NORMAL_02", //5CECC92F", //1559021871", //1559021871
            "PAIN_FEMALE_NORMAL_03", //8AA3249B", //2325947547", //"1969019749
            "PAIN_FEMALE_NORMAL_04", //78878064", //2022146148", //2022146148
            "PAIN_FEMALE_NORMAL_05", //2629DBA6", //640277414", //640277414
            "PAIN_FEMALE_NORMAL_06", //0BF1A736", //200386358", //200386358
            "PAIN_FEMALE_NORMAL_07", //41699229", //1097437737", //1097437737
            "PAIN_FEMALE_NORMAL_08", //374E7DEF", //927890927", //927890927
            "PAIN_FEMALE_NORMAL_09", //DCDE4910", //3705555216", //"589412080
            "PAIN_FEMALE_NORMAL_10", //966B3B23", //2523609891", //"1771357405
            "PAIN_FEMALE_NORMAL_11", //343976BD", //876181181", //876181181
            "PAIN_FEMALE_NORMAL_12", //21EAD220", //569037344", //569037344
            "PAIN_FEMALE_TEST_01", //95928372", //2509407090", //"1785560206
            "PAIN_FEMALE_TEST_02", //AAE0AE0E", //2866851342", //"1428115954
            "PAIN_FEMALE_TEST_03", //B89E4989", //3097381257", //"1197586039
            "S_F_M_FEMBARBER_BLACK_MINI_01", //4B82A928", //1266854184", //1266854184
            "S_F_M_GENERICCHEAPWORKER_01_LATINO_MINI_01", //E085EF87", //3766873991", //"528093305
            "S_F_M_GENERICCHEAPWORKER_01_LATINO_MINI_02", //EA440303", //3930325763", //"364641533
            "S_F_M_GENERICCHEAPWORKER_01_LATINO_MINI_03", //51565112", //1364611346", //1364611346
            "S_F_M_PONSEN_01_BLACK_01", //B60A191B", //3054115099", //"1240852197
            "S_F_M_SHOP_HIGH_WHITE_MINI_01", //AD7E25AA", //2910725546", //"1384241750
            "S_F_Y_AIRHOSTESS_01_BLACK_FULL_01", //50B140C7", //1353793735", //1353793735
            "S_F_Y_AIRHOSTESS_01_BLACK_FULL_02", //D0FFC16E", //3506422126", //"788545170
            "S_F_Y_AIRHOSTESS_01_WHITE_FULL_01", //090B4CD4", //151735508", //151735508
            "S_F_Y_AIRHOSTESS_01_WHITE_FULL_02", //E1B67E2B", //3786833451", //"508133845
            "S_F_Y_BAYWATCH_01_BLACK_FULL_01", //F33860E9", //4080558313", //"214408983
            "S_F_Y_BAYWATCH_01_BLACK_FULL_02", //880F0A98", //2282687128", //"2012280168
            "S_F_Y_BAYWATCH_01_WHITE_FULL_01", //26DECE02", //652135938", //652135938
            "S_F_Y_BAYWATCH_01_WHITE_FULL_02", //35226A89", //891447945", //891447945
            "S_F_Y_Cop_01_BLACK_FULL_01", //EFB0FA91", //4021353105", //"273614191
            "S_F_Y_COP_01_BLACK_FULL_02", //62A6E07B", //1655103611", //1655103611
            "S_F_Y_COP_01_WHITE_FULL_01", //EB73C44F", //3950232655", //"344734641
            "S_F_Y_COP_01_WHITE_FULL_02", //F9C560F2", //4190462194", //"104505102
            "S_F_Y_GENERICCHEAPWORKER_01_BLACK_MINI_01", //44ACE464", //1152181348", //1152181348
            "S_F_Y_GENERICCHEAPWORKER_01_BLACK_MINI_02", //3707C91A", //923257114", //923257114
            "S_F_Y_GENERICCHEAPWORKER_01_LATINO_MINI_01", //A135DE73", //2704662131", //"1590305165
            "S_F_Y_GENERICCHEAPWORKER_01_LATINO_MINI_02", //CF08BA18", //3473455640", //"821511656
            "S_F_Y_GENERICCHEAPWORKER_01_LATINO_MINI_03", //BC269454", //3156644948", //"1138322348
            "S_F_Y_GENERICCHEAPWORKER_01_LATINO_MINI_04", //EB8E7323", //3951981347", //"342985949
            "S_F_Y_GENERICCHEAPWORKER_01_WHITE_MINI_01", //E5EAA67A", //3857360506", //"437606790
            "S_F_Y_GENERICCHEAPWORKER_01_WHITE_MINI_02", //39B64E08", //968248840", //968248840
            "S_F_Y_HOOKER_01_WHITE_FULL_01", //18B73C7E", //414661758", //414661758
            "S_F_Y_HOOKER_01_WHITE_FULL_02", //66F658FB", //1727420667", //1727420667
            "S_F_Y_HOOKER_01_WHITE_FULL_03", //75E576D9", //1977972441", //1977972441
            "S_F_Y_HOOKER_02_WHITE_FULL_01", //77BE674B", //2008966987", //2008966987
            "S_F_Y_HOOKER_02_WHITE_FULL_02", //09978AFF", //160926463", //160926463
            "S_F_Y_HOOKER_02_WHITE_FULL_03", //1B382E40", //456666688", //456666688
            "S_F_Y_HOOKER_03_BLACK_FULL_01", //875814D6", //2270696662", //"2024270634
            "S_F_Y_HOOKER_03_BLACK_FULL_03", //129DAB5F", //312322911", //312322911
            "S_F_Y_PECKER_01_WHITE_01", //6B019062", //1795264610", //1795264610
            "S_F_Y_RANGER_01_WHITE_MINI_01", //47A85382", //1202213762", //1202213762
            "S_F_Y_SHOP_LOW_WHITE_MINI_01", //ED77E493", //3984057491", //"310909805
            "S_F_Y_SHOP_MID_WHITE_MINI_01" //77B47F14", //2008317716", //2008317716
};

const std::vector<std::string> PedComposList= { RSLangMenu[127], RSLangMenu[128], RSLangMenu[129], RSLangMenu[130], RSLangMenu[131], RSLangMenu[132], RSLangMenu[133], RSLangMenu[134], RSLangMenu[135], RSLangMenu[136], RSLangMenu[137], RSLangMenu[138] };
const std::vector<std::string> PedPropsList = { RSLangMenu[139], RSLangMenu[140], RSLangMenu[141], RSLangMenu[142] };
const std::vector<std::string> PedTatsProList = { RSLangMenu[143], RSLangMenu[144], RSLangMenu[145], RSLangMenu[146], RSLangMenu[147], RSLangMenu[148] };
const std::vector<std::string> PedTatsFreeList = { RSLangMenu[149],RSLangMenu[150],RSLangMenu[151],RSLangMenu[144], RSLangMenu[145], RSLangMenu[146], RSLangMenu[147], RSLangMenu[148] };
const std::vector<std::string> PedFaceFeat = { RSLangMenu[152],RSLangMenu[153],RSLangMenu[154],RSLangMenu[155],RSLangMenu[156],RSLangMenu[157],RSLangMenu[158],RSLangMenu[159],RSLangMenu[160],RSLangMenu[161],RSLangMenu[162],RSLangMenu[163],RSLangMenu[164],RSLangMenu[165],RSLangMenu[166],RSLangMenu[167],RSLangMenu[168],RSLangMenu[169],RSLangMenu[170],RSLangMenu[171] };
const std::vector<std::string> PedOversList = { RSLangMenu[172],RSLangMenu[173],RSLangMenu[174],RSLangMenu[175],RSLangMenu[176],RSLangMenu[177],RSLangMenu[178],RSLangMenu[179],RSLangMenu[180],RSLangMenu[181],RSLangMenu[182],RSLangMenu[183],RSLangMenu[184] };

void PeditorMenu_Parenting(Mod_Class::ClothBank* Outfit, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("PeditorMenu_Parenting");
    MenuOpen = true;
    Ped Peddy = PLAYER::PLAYER_PED_ID();
    int ShapeMix = (int)(Outfit->MyFaces.ShapeMix * 100);
    int SkinMix = (int)(Outfit->MyFaces.SkinMix * 100);
    int ThirdMix = (int)(Outfit->MyFaces.ThirdMix * 100);

    std::vector<Mod_Class::MeunFields> PedCompOut = {

        Mod_Class::MeunFields(RSLangMenu[122], "", false, true, 0, 45, Outfit->MyFaces.ShapeFirstID),
        Mod_Class::MeunFields(RSLangMenu[123], "", false, true, 0, 45, Outfit->MyFaces.ShapeSecondID),
        Mod_Class::MeunFields(RSLangMenu[124], "", false, true, 0, 100, ShapeMix),
        Mod_Class::MeunFields(RSLangMenu[125], "", false, true, 0, 100, SkinMix),
        Mod_Class::MeunFields(RSLangMenu[126], "", false, true, 0, 100, ThirdMix)
    };


    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 5, false, PedCompOut);
    myMenu.waitTime = InGameTime() + 150;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 1;
            break;
        }
        else if (myMenu._Activate)
        {
            myMenu.Menu_Form[myMenu.Index].Current = 0;

            if (myMenu.Index == 0)
            {
                Outfit->MyFaces.ShapeFirstID = 0;
                Outfit->MyFaces.ShapeThirdID = 0;
                Outfit->MyFaces.SkinFirstID = 0;
                Outfit->MyFaces.SkinThirdID = 0;
            }
            else if (myMenu.Index == 1)
            {
                Outfit->MyFaces.ShapeSecondID = 0;
                Outfit->MyFaces.SkinSecondID = 0;
            }
            else if (myMenu.Index == 2)
                Outfit->MyFaces.ShapeMix = 0.0f;
            else if (myMenu.Index == 3)
                Outfit->MyFaces.SkinMix = 0.0f;
            else if (myMenu.Index == 4)
                Outfit->MyFaces.ThirdMix = 0.0f;

            PED::SET_PED_HEAD_BLEND_DATA(Peddy, Outfit->MyFaces.ShapeFirstID, Outfit->MyFaces.ShapeSecondID, Outfit->MyFaces.ShapeThirdID, Outfit->MyFaces.SkinFirstID, Outfit->MyFaces.SkinSecondID, Outfit->MyFaces.SkinThirdID, Outfit->MyFaces.ShapeMix, Outfit->MyFaces.SkinMix, Outfit->MyFaces.ThirdMix, 0);
        }
        else if (myMenu._Left || myMenu._Right)
        {
            if (myMenu.Index == 0)
            {
                Outfit->MyFaces.ShapeFirstID = myMenu.Menu_Form[myMenu.Index].Current;
                Outfit->MyFaces.ShapeThirdID = myMenu.Menu_Form[myMenu.Index].Current;
                Outfit->MyFaces.SkinFirstID = myMenu.Menu_Form[myMenu.Index].Current;
                Outfit->MyFaces.SkinThirdID = myMenu.Menu_Form[myMenu.Index].Current;
            }
            else if (myMenu.Index == 1)
            {
                Outfit->MyFaces.ShapeSecondID = myMenu.Menu_Form[myMenu.Index].Current;
                Outfit->MyFaces.SkinSecondID = myMenu.Menu_Form[myMenu.Index].Current;
            }
            else
            {
                float fEat = myMenu.Menu_Form[myMenu.Index].Current;

                if (fEat != 0)
                    fEat /= 100;


                else if (myMenu.Index == 2)
                    Outfit->MyFaces.ShapeMix = fEat;
                else if (myMenu.Index == 3)
                    Outfit->MyFaces.SkinMix = fEat;
                else if (myMenu.Index == 4)
                    Outfit->MyFaces.ThirdMix = fEat;

            }

            PED::SET_PED_HEAD_BLEND_DATA(Peddy, Outfit->MyFaces.ShapeFirstID, Outfit->MyFaces.ShapeSecondID, Outfit->MyFaces.ShapeThirdID, Outfit->MyFaces.SkinFirstID, Outfit->MyFaces.SkinSecondID, Outfit->MyFaces.SkinThirdID, Outfit->MyFaces.ShapeMix, Outfit->MyFaces.SkinMix, Outfit->MyFaces.ThirdMix, 0);
        }
    }
    MenuOpen = false;
}
void PeditorMenu_FaceShape(Mod_Class::ClothBank* Outfit, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("PedCompMenu");
    MenuOpen = true;
    int iTotal = 0;
    int iColour = -1;

    if (Outfit->FaceScale.size() == 0)
    {
        for (int i = 0; i < PedFaceFeat.size(); i++)
            Outfit->FaceScale.push_back(0.0f);
    }

    Ped Peddy = PLAYER::PLAYER_PED_ID();
    std::vector<Mod_Class::MeunFields> PedCompOut = {};

    for (int i = 0; i < PedFaceFeat.size(); i++)
        PedCompOut.push_back(Mod_Class::MeunFields(PedFaceFeat[i], "", false, true, -100, 100, 0));

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 7, true, PedCompOut);
    myMenu.waitTime = InGameTime() + 150;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 1;
            break;
        }
        else if (myMenu._Activate)
        {
            myMenu.Menu_Form[myMenu.Index].Current = 0;

            Outfit->FaceScale[myMenu.Index] = 0.0f;
            PED::_SET_PED_FACE_FEATURE(PLAYER::PLAYER_PED_ID(), myMenu.Index, Outfit->FaceScale[myMenu.Index]);
        }
        else if (myMenu._Left || myMenu._Right)
        {
            float fEat = myMenu.Menu_Form[myMenu.Index].Current;
            if (fEat != 0)
                fEat /= 100;
            Outfit->FaceScale[myMenu.Index] = fEat;
            PED::_SET_PED_FACE_FEATURE(PLAYER::PLAYER_PED_ID(), myMenu.Index, Outfit->FaceScale[myMenu.Index]);
        }
    }
    MenuOpen = false;
}
void PeditorMenu_FaceFeatsList(int iComp, int iTotal, int iColour, Mod_Class::ClothBank* Outfit, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("PeditorMenu_FaceFeatsList");
    MenuOpen = true;

    int iOPC = (int)(Outfit->MyOverlay[iComp].OverOpc * 100);
    int iNums = 2;
    std::vector<Mod_Class::MeunFields> PedCompOut = {
        Mod_Class::MeunFields(RSLangMenu[117], PedOversList[iComp], false, true, -1, iTotal, Outfit->MyOverlay[iComp].Overlay),
        Mod_Class::MeunFields(RSLangMenu[120], PedOversList[iComp], false, true, 0, 100, iOPC),
    };
    if (iColour != -1)
    {
        PedCompOut.push_back(Mod_Class::MeunFields(RSLangMenu[121], PedOversList[iComp], false, true, 0, 62, Outfit->MyOverlay[iComp].OverCol));
        iNums++;
    }

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, iNums, false, PedCompOut);
    myMenu.waitTime = InGameTime() + 150;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 4;
            break;
        }
        else if (myMenu._Activate)
        {
            myMenu.Menu_Form[myMenu.Index].Current = 0;

            if (iComp == 1)
                iColour = 1;//Facial Hair
            else if (iComp == 2)
                iColour = 1;//Eyebrows
            else if (iComp == 5)
                iColour = 2;//Blush
            else if (iComp == 8)
                iColour = 2;//Lipstick
            else if (iComp == 10)
                iColour = 1;//Chest Hair

            if (myMenu.Index == 0)
            {
                int iChange = myMenu.Menu_Form[myMenu.Index].Current;
                if (iChange == -1)
                    iChange = 255;
                Outfit->MyOverlay[iComp].Overlay = iChange;
            }
            else if (myMenu.Index == 1)
            {
                float fVar = myMenu.Menu_Form[myMenu.Index].Current;
                if (fVar != 0)
                    fVar /= 100;
                Outfit->MyOverlay[iComp].OverOpc = fVar;
            }
            else if (myMenu.Index == 2)
                Outfit->MyOverlay[iComp].OverCol = myMenu.Menu_Form[myMenu.Index].Current;

            Ped Pedx = PLAYER::PLAYER_PED_ID();

            PED::SET_PED_HEAD_OVERLAY(Pedx, iComp, Outfit->MyOverlay[iComp].Overlay, Outfit->MyOverlay[iComp].OverOpc);

            if (iColour != -1)
                PED::_SET_PED_HEAD_OVERLAY_COLOR(Pedx, iComp, iColour, Outfit->MyOverlay[iComp].OverCol, 0);
        }
        else if (myMenu._Left || myMenu._Right)
        {
            if (iComp == 1)
                iColour = 1;//Facial Hair
            else if (iComp == 2)
                iColour = 1;//Eyebrows
            else if (iComp == 5)
                iColour = 2;//Blush
            else if (iComp == 8)
                iColour = 2;//Lipstick
            else if (iComp == 10)
                iColour = 1;//Chest Hair

            if (myMenu.Index == 0)
            {
                int iChange = myMenu.Menu_Form[myMenu.Index].Current;
                if (iChange == -1)
                    iChange = 255;
                Outfit->MyOverlay[iComp].Overlay = iChange;
            }
            else if (myMenu.Index == 1)
            {
                float fVar = myMenu.Menu_Form[myMenu.Index].Current;
                if (fVar > 0)
                    fVar /= 100;
                Outfit->MyOverlay[iComp].OverOpc = fVar;
            }
            else if (myMenu.Index == 2)
                Outfit->MyOverlay[iComp].OverCol = myMenu.Menu_Form[myMenu.Index].Current;

            Ped Pedx = PLAYER::PLAYER_PED_ID();

            PED::SET_PED_HEAD_OVERLAY(Pedx, iComp, Outfit->MyOverlay[iComp].Overlay, Outfit->MyOverlay[iComp].OverOpc);

            if (iColour != -1)
                PED::_SET_PED_HEAD_OVERLAY_COLOR(Pedx, iComp, iColour, Outfit->MyOverlay[iComp].OverCol, 0);
        }
    }
    MenuOpen = false;
}
void PeditorMenu_FaceFeats(Mod_Class::ClothBank* Outfit, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("PeditorMenu_FaceFeats");
    MenuOpen = true;
    int iTotal = 0;
    int iColour = -1;

    Ped Peddy = PLAYER::PLAYER_PED_ID();
    std::vector<Mod_Class::MeunFields> PedCompOut = {};

    for (int i = 0; i < (int)PedOversList.size(); i++)
        PedCompOut.push_back(Mod_Class::MeunFields(PedOversList[i], "Select " + PedOversList[i], false, false, -1, GetPedOverlayValues(i), GetPedOverlay(Peddy, i)));

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 7, true, PedCompOut);
    myMenu.waitTime = InGameTime() + 150;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 1;
            break;
        }
        else if (myMenu._Activate)
        {
            if (myMenu.Index == 1 || myMenu.Index == 2 || myMenu.Index == 10)
                iColour = 1;
            else if (myMenu.Index == 5 || myMenu.Index == 8)
                iColour = 2;

            iTotal = myMenu.Menu_Form[myMenu.Index].Max;


            Menu_Index = 12;
            Menu_IndexI = myMenu.Index;
            Menu_IndexII = iTotal;
            Menu_IndexIII = iColour;

            break;
        }
    }

    MenuOpen = false;
}

std::vector<Mod_Class::Tattoo> TattoosList(int iPed, int iZone)
{
    LoggerLight("TattoosList, iPed == " + std::to_string(iPed) + ", iZone == " + std::to_string(iZone));

    bool bEmpty = false;
    std::vector<Mod_Class::Tattoo> TatList = {};

    if (iPed == 1)
    {
        if (iZone == 0)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_018", "Impotent Rage"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_014", "Chinese Dragon"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_008", "Trinity Knot"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_004", "Lucky"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_020", "Way of the Gun"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_017", "Whiskey Life"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_015", "Flaming Shamrock"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_006", "Eagle and Serpent"));
        }//TORSO
        else if (iZone == 1)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_003", "The Rose of My Heart"));
        }//HEAD
        else if (iZone == 2)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_019", "Dragon"));//     
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_012", "Faith"));//   
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_010", "Lady M"));//   
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_009", "Lucky Celtic Dogs"));//  
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_007", "Mermaid"));//       
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_000", "Mandy"));//    
        }//LEFT ARM 
        else if (iZone == 3)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_016", "Michael and Amanda"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_013", "Flower Mural"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_005", "Virgin Mary"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_001", "Family is Forever"));
        }//RIGHT ARM
        else if (iZone == 4)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_002", "Smoking Dagger"));
        }//LEFT LEG
        else
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_011", "Tiki Pinup "));
        }//RIGHT LEG
    }// Michael
    else if (iPed == 2)
    {
        if (iZone == 0)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_038", "Angel of Los Santos"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_010", "Grace and Power"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_004", "Dragon"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_039", "Impotent Rage"));//   
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_037", "Los Santos Bills"));// 
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_036", "These Streets"));//    
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_035", "Families"));//      
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_032", "LS Flames"));//  
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_031", "Fam 4 Life"));//   
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_030", "Families Symbol"));//      
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_029", "FAM Power"));//    
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_028", "Flaming Cross"));//  
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_021", "Chamberlain Families LS"));//  
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_020", "LS Heart "));//   
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_018", "Families Kings"));//  
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_011", "Forum4Life"));//      
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_000", "Chamberlain"));//     
            //Not in List
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_025", "Skull on the Cross"));//    
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_024", "Skull and Dragon"));
        }//TORSO
        else if (iZone == 1)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_022", "Chamberlain Families"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_005", "Faith"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_034", "LS Bold"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_033", "LS Script"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_014", "F King"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_013", "F Crown "));
        }//HEAD
        else if (iZone == 2)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_019", "FAMILIES"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_017", "Lion"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_016", "Dragon Mural"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_007", "Serpent Skull"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_001", "Brotherhood"));
        }//LEFT ARM
        else if (iZone == 3)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_023", "Fiery Dragon"));//    
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_012", "Oriental Mural"));//    
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_009", "Chop"));//    
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_008", "Mother"));//    
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_006", "Serpents"));//    
        }//RIGHT ARM
        else if (iZone == 4)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_027", "Hottie"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_015", "The Warrior"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_002", "Dragons"));
        }//LEFT LEG
        else
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_026", "Trust No One"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_003", "Melting Skull"));
        }//RIGHT LEG
    }// Franklin
    else if (iPed == 3)
    {
        if (iZone == 0)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_032", "Lucky"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_031", "Unzipped"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_026", "Skulls and Rose"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_022", "Chinese Dragon"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_033", "Impotent Rage"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_030", "Fuck Cops"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_029", "Smiley"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_028", "Ace"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_027", "Piggy"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_023", "Monster Pups"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_021", "Stone Cross"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_015", "Tweaker"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_013", "Betraying Scroll"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_012", "Eye Catcher"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_006", "Blackjack"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_004", "Evil Clown"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_000", "Imperial Douche"));
        }//TORSO
        else if (iZone == 1)
        {
            bEmpty = true;
        }//HEAD
        else if (iZone == 2)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_024", "Grim Reaper Smoking Gun"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_018", "Dope Skull"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_017", "The Wages of Sin"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_016", "Dragon and Dagger"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_003", "Zodiac Skull"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_001", "R.I.P Michael"));
        }//LEFT ARM
        else if (iZone == 3)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_020", "Indian Ram"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_014", "Muertos"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_010", "Flaming Skull"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_009", "Broken Skull"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_008", "Dagger"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_007", "Tribal"));
        }//RIGHT ARM
        else if (iZone == 4)
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_011", "Serpant Skull"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_002", "Grim Reaper"));
        }//LEFT LEG
        else
        {
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_025", "Freedom"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_019", "Flaming Scorpion"));
            TatList.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_005", "Love to Hate"));
        }//RIGHT LEG
    }// Trevor
    else if (iPed == 4)
    {
        if (iZone == 0)
        {
            TatList = maleTats01;
        }//BACK
        else if (iZone == 1)
        {
            TatList = maleTats02;
        }//CHEST
        else if (iZone == 2)
        {
            TatList = maleTats03;
        }//STOMACH
        else if (iZone == 3)
        {
            TatList = maleTats04;
            //Not On the TatlIst     ...                            
        }//HEAD
        else if (iZone == 4)
        {
            TatList = maleTats05;
        }//LEFT ARM
        else if (iZone == 5)
        {
            TatList = maleTats06;
        }//RIGHT ARM
        else if (iZone == 6)
        {
            TatList = maleTats07;
        }//LEFT LEG
        else
        {
            TatList = maleTats08;
        }//RIGHT LEG
    }// FreeMale
    else if (iPed == 5)
    {
        if (iZone == 0)
        {
            TatList = femaleTats01;
        }//BACK
        else if (iZone == 1)
        {
            TatList = femaleTats02;
        }//CHEST
        else if (iZone == 2)
        {
            TatList = femaleTats03;
        }//STOMACH
        else if (iZone == 3)
        {
            TatList = femaleTats04;
        }//HEAD
        else if (iZone == 4)
        {
            TatList = femaleTats05;
        }//LEFT ARM
        else if (iZone == 5)
        {
            TatList = femaleTats06;
        }//RIGHT ARM
        else if (iZone == 6)
        {
            TatList = femaleTats07;
        }//LEFT LEG
        else
        {
            TatList = femaleTats08;
        }//RIGHT LEG
    }// FreeFemale

    if (bEmpty)
        TatList.push_back(Mod_Class::Tattoo("", "", "No Tattoos Available"));

    return TatList;
}
void PeditorMenu_TattooParList(Mod_Class::ClothBank* Outfit, int Main_Char, int iSelect, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("TattooParListMenu");
    MenuOpen = true;
    std::vector<Mod_Class::MeunFields> PedCompOut = {};

    std::vector<Mod_Class::Tattoo> myTattoosList = TattoosList(Main_Char, iSelect);;

    for (int i = 0; i < (int)myTattoosList.size(); i++)
    {
        int iGotit = 0;
        for (int j = 0; j < (int)Outfit->MyTattoo.size(); j++)
        {
            if (Outfit->MyTattoo[j].TatName == myTattoosList[i].TatName)
                iGotit = 1;
               
        }
        PedCompOut.push_back(Mod_Class::MeunFields(myTattoosList[i].Name, "", true, false, 0, 1, iGotit));

    }

    bool MoreThan = true;
    int iCountU = 7;
    if ((int)myTattoosList.size() < 7)
    {
        MoreThan = false;
        iCountU = (int)myTattoosList.size();
    }

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, iCountU, MoreThan, PedCompOut);
    myMenu.waitTime = InGameTime() + 150;

    int iPosChange = 0;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 3;
            break;
        }
        else if (myMenu._Activate || myMenu._Left || myMenu._Right)
        {
            bool Add = true;
            for (int i = 0; i < (int)Outfit->MyTattoo.size(); i++)
            {
                if (Outfit->MyTattoo[i].TatName == myTattoosList[myMenu.Index].TatName)
                {
                    Add = false;
                    Outfit->MyTattoo.erase(Outfit->MyTattoo.begin() + i);
                    myMenu.Menu_Form[myMenu.Index].Current = 0;
                }
            }
            if (Add)
                Outfit->MyTattoo.push_back(myTattoosList[myMenu.Index]);

            PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
            ApplyTats(PLAYER::PLAYER_PED_ID(), Outfit);
        }
        else if (iPosChange != myMenu.Index)
        {
            iPosChange = myMenu.Index;
            PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
            PED::_APPLY_PED_OVERLAY(PLAYER::PLAYER_PED_ID(), MyHashKey(myTattoosList[myMenu.Index].BaseName), MyHashKey(myTattoosList[myMenu.Index].TatName));
        }
    }

    PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
    ApplyTats(PLAYER::PLAYER_PED_ID(), Outfit);
    MenuOpen = false;

}
void PeditorMenu_TattooPar(Mod_Class::ClothBank* Outfit, int Main_Char, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("TattooParMenu");
    MenuOpen = true;
    std::vector<Mod_Class::MeunFields> PedCompOut = {};
    bool Loopy = true;
    int Counter = 7;

    if (Main_Char == 1 || Main_Char == 2 || Main_Char == 3)
    {
        for (int i = 0; i < PedTatsProList.size(); i++)
            PedCompOut.push_back(Mod_Class::MeunFields(PedTatsProList[i], "", false, false, 0, 1, 0));

        Loopy = false;
        Counter = 6;
    }
    else
    {
        for (int i = 0; i < PedTatsFreeList.size(); i++)
            PedCompOut.push_back(Mod_Class::MeunFields(PedTatsFreeList[i], "", false, false, 0, 1, 0));
    }


    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, Counter, Loopy, PedCompOut);
    myMenu.waitTime = InGameTime() + 150;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 1;
            break;
        }
        else if (myMenu._Activate)
        {
            Menu_Index = 11;
            Menu_IndexI = myMenu.Index;
            break;
        }
    }
    MenuOpen = false;
}

int TshirtLabel(int CharName)
{
    if (CharName == 1)
        return 0;
    else if (CharName == 2)
        return 0;
    else if (CharName == 3)
        return 0;
    else if (CharName == 4)
        return (int)MaleTshirt.size() - 1;
    else if (CharName == 5)
        return (int)FemaleTshirt.size() - 1;
    else
        return 0;
}
void PeditorMenu_PropList(int Comp, Mod_Class::ClothBank* Outfit, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("PedPropList");
    MenuOpen = true;
    int DrawVar = PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), Comp);
    int TextVar = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), Comp, Outfit->Cothing[Outfit->Cloth_Pick].ClothA[Comp]);

    std::vector<Mod_Class::MeunFields> PedCompOut = {
        Mod_Class::MeunFields(RSLangMenu[117], PedPropsList[Comp], false, true, -1, DrawVar, Outfit->Cothing[Outfit->Cloth_Pick].ExtraA[Comp]),
        Mod_Class::MeunFields(RSLangMenu[118], PedPropsList[Comp], false, true, 0, TextVar, Outfit->Cothing[Outfit->Cloth_Pick].ExtraB[Comp])
    };

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 2, false, PedCompOut);
    myMenu.waitTime = InGameTime() + 150;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 8;
            break;
        }
        else if (myMenu._Activate)
        {
            if (myMenu.Index == 0)
            {
                myMenu.Menu_Form[0].Current = 0;
                myMenu.Menu_Form[1].Current = 0;
                TextVar = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), Comp, myMenu.Menu_Form[0].Current);
                PedCompOut[1].Max = TextVar;
            }
            else
                myMenu.Menu_Form[1].Current = 0;

            Outfit->Cothing[Outfit->Cloth_Pick].ExtraA[Comp] = myMenu.Menu_Form[0].Current;
            Outfit->Cothing[Outfit->Cloth_Pick].ExtraB[Comp] = myMenu.Menu_Form[1].Current;

            if (Outfit->Cothing[Outfit->Cloth_Pick].ExtraA[Comp] == -1)
                PED::CLEAR_ALL_PED_PROPS(PLAYER::PLAYER_PED_ID());
            else
                PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), Comp, Outfit->Cothing[Outfit->Cloth_Pick].ExtraA[Comp], Outfit->Cothing[Outfit->Cloth_Pick].ExtraB[Comp], false);
        }
        else if (myMenu._Left || myMenu._Right)
        {
            if (myMenu.Index == 0)
            {
                TextVar = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), Comp, myMenu.Menu_Form[0].Current);
                PedCompOut[1].Max = TextVar;
                myMenu.Menu_Form[1].Current = 0;
            }
            Outfit->Cothing[Outfit->Cloth_Pick].ExtraA[Comp] = myMenu.Menu_Form[0].Current;
            Outfit->Cothing[Outfit->Cloth_Pick].ExtraB[Comp] = myMenu.Menu_Form[1].Current;

            if (Outfit->Cothing[Outfit->Cloth_Pick].ExtraA[Comp] == -1)
                PED::CLEAR_ALL_PED_PROPS(PLAYER::PLAYER_PED_ID());
            else
                PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), Comp, Outfit->Cothing[Outfit->Cloth_Pick].ExtraA[Comp], Outfit->Cothing[Outfit->Cloth_Pick].ExtraB[Comp], false);
        }
    }
    MenuOpen = false;
}
void PeditorMenu_PedProp(Mod_Class::ClothBank* Outfit, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("PedPropMenu");
    MenuOpen = true;
    std::vector<Mod_Class::MeunFields> PedCompOut = {};
    //Mod_Class::ClothX Outfit = GetYourTogs(PLAYER::PLAYER_PED_ID());

    for (int i = 0; i < PedPropsList.size(); i++)
        PedCompOut.push_back(Mod_Class::MeunFields(PedPropsList[i], "", false, false, 0, 1, 0));

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 4, false, PedCompOut);
    myMenu.waitTime = InGameTime() + 150;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 2;
            break;
        }
        else if (myMenu._Activate)
        {
            Menu_Index = 10;
            Menu_IndexI = myMenu.Index;
            break;

        }
    }
    MenuOpen = false;
}
void PeditorMenu_CompList(int Comp, Mod_Class::ClothBank* Outfit, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("PedCompList");
    MenuOpen = true;
    int iTake = 0;
    if (Comp == 6)
        iTake = 2;
    int DrawVar = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), Comp) - iTake;
    int TextVar = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), Comp, Outfit->Cothing[Outfit->Cloth_Pick].ClothA[Comp]);

    std::vector<Mod_Class::MeunFields> PedCompOut = {
        Mod_Class::MeunFields(RSLangMenu[117], PedComposList[Comp], false, true, -1, DrawVar, Outfit->Cothing[Outfit->Cloth_Pick].ClothA[Comp]),
        Mod_Class::MeunFields(RSLangMenu[118], PedComposList[Comp], false, true, 0, TextVar, Outfit->Cothing[Outfit->Cloth_Pick].ClothB[Comp])
    };

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 2, false, PedCompOut);
    myMenu.waitTime = InGameTime() + 150;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 7;
            break;
        }
        else if (myMenu._Activate)
        {
            if (myMenu.Index == 0)
            {
                myMenu.Menu_Form[0].Current = 0;
                myMenu.Menu_Form[1].Current = 0;
                TextVar = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), Comp, myMenu.Menu_Form[0].Current);
                PedCompOut[1].Max = TextVar;
            }
            else
                myMenu.Menu_Form[1].Current = 0;

            Outfit->Cothing[Outfit->Cloth_Pick].ClothA[Comp] = myMenu.Menu_Form[0].Current;
            Outfit->Cothing[Outfit->Cloth_Pick].ClothB[Comp] = myMenu.Menu_Form[1].Current;

            PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), Comp, Outfit->Cothing[Outfit->Cloth_Pick].ClothA[Comp], Outfit->Cothing[Outfit->Cloth_Pick].ClothB[Comp], 2);
        }
        else if (myMenu._Left || myMenu._Right)
        {
            if (myMenu.Index == 0)
            {
                TextVar = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), Comp, myMenu.Menu_Form[0].Current);
                PedCompOut[1].Max = TextVar;
                myMenu.Menu_Form[1].Current = 0;
            }
            Outfit->Cothing[Outfit->Cloth_Pick].ClothA[Comp] = myMenu.Menu_Form[0].Current;
            Outfit->Cothing[Outfit->Cloth_Pick].ClothB[Comp] = myMenu.Menu_Form[1].Current;

            PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), Comp, Outfit->Cothing[Outfit->Cloth_Pick].ClothA[Comp], Outfit->Cothing[Outfit->Cloth_Pick].ClothB[Comp], 2);
        }
    }

    MenuOpen = false;
}
void PeditorMenu_PedComp(Mod_Class::ClothBank* Outfit, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("PedCompMenu");
    MenuOpen = true;
    std::vector<Mod_Class::MeunFields> PedCompOut = {};
    //Mod_Class::ClothX Outfit = GetYourTogs(PLAYER::PLAYER_PED_ID());

    for (int i = 0; i < PedComposList.size(); i++)
        PedCompOut.push_back(Mod_Class::MeunFields(PedComposList[i], RSLangMenu[119] + PedComposList[i], false, false, 0, 1, 0));

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 7, true, PedCompOut);
    myMenu.waitTime = InGameTime() + 150;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 2;
            break;
        }
        else if (myMenu._Activate)          
        {
            Menu_Index = 9;
            Menu_IndexI = myMenu.Index;
            break;

        }
    }
    MenuOpen = false;
}
void PeditorMenu_Outfit(Mod_Class::ClothBank* thisPed, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("OutfitMenu");
    MenuOpen = true;
    std::vector<std::string> sList = {};

    if (thisPed->FreeMode)
        sList = FindCloths(thisPed->Male);

    int iSize = 4;
    int iCharType = YourCharIs();

    Mod_Class::ClothX MyCloths = thisPed->Cothing[thisPed->Cloth_Pick];

    std::vector<Mod_Class::MeunFields> M_List = {
        Mod_Class::MeunFields(RSLangMenu[109], MyCloths.Title, false, false, 0, (int)thisPed->Cothing.size() - 1, thisPed->Cloth_Pick),
        Mod_Class::MeunFields(RSLangMenu[110], RSLangMenu[111], false, false, 0, 1, 0),
        Mod_Class::MeunFields(RSLangMenu[112], RSLangMenu[113], false, false, 0, 1, 0),
        Mod_Class::MeunFields(RSLangMenu[114], RSLangMenu[115], false, false, 0, 1, 0)
    };

    if (iCharType > 3)
    {
        iSize ++;
        M_List.push_back(Mod_Class::MeunFields(RSLangMenu[193], "", false, false, 0, TshirtLabel(iCharType), 0));
    }

    if ((int)sList.size() > 0)
    {
        iSize ++;
        M_List.push_back(Mod_Class::MeunFields(RSLangMenu[116], "", false, false, 0, (int)sList.size() - 1, 0));
    }


    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, iSize, false, M_List);
    myMenu.waitTime = InGameTime() + 150;

    Menu_Index = 1;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
            break;
        else if (myMenu._Activate)
        {
            if (myMenu.Index == 1)
            {
                std::string sC = CaptureScreenText();

                if (sC != "")
                {
                    thisPed->Cloth_Pick = (int)thisPed->Cothing.size();
                    thisPed->Cothing.push_back(MyCloths);
                    thisPed->Cothing[thisPed->Cloth_Pick].Title = sC;
                    Menu_Index = 7;
                }
            }
            else if (myMenu.Index == 2)
            {
                Menu_Index = 7;
                break;
            }
            else if (myMenu.Index == 3)
            {
                Menu_Index = 8;
                break;
            }
            else if (myMenu.Index == 4)
            {
                PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
                myMenu.Menu_Form[myMenu.Index].Current = 0;
                myMenu.Menu_Form[myMenu.Index].Description = "";
                thisPed->Cothing[thisPed->Cloth_Pick].Badge.TatName = "";
                thisPed->Cothing[thisPed->Cloth_Pick].Badge.BaseName = "";
                ApplyTats(PLAYER::PLAYER_PED_ID(), thisPed);
            }
            else if (myMenu.Index == 5)
            {
                Menu_Index = 7;
                break;
            }
            else
                break;
        }
        else if (myMenu._Left || myMenu._Right)
        {
            if (myMenu.Index == 0)
            {
                if (myMenu.Menu_Form[0].Current > -1 && myMenu.Menu_Form[0].Current < thisPed->Cothing.size())
                {
                    thisPed->Cloth_Pick = myMenu.Menu_Form[0].Current;
                    myMenu.Menu_Form[0].Description = thisPed->Cothing[thisPed->Cloth_Pick].Title;
                    Mod_Class::ClothX Cloths = thisPed->Cothing[thisPed->Cloth_Pick];
                    OnlineDress(PLAYER::PLAYER_PED_ID(), &Cloths);

                    if (thisPed->FreeMode)
                    {
                        Mod_Class::HairSets Hairs = thisPed->MyHair;
                        SetingtheHair(PLAYER::PLAYER_PED_ID(), &Hairs);
                    }
                }

            }
            else if (myMenu.Index == 4)
            {
                if (iCharType == 4)
                {
                    if (myMenu.Menu_Form[myMenu.Index].Current > -1 && myMenu.Menu_Form[myMenu.Index].Current < (int)MaleTshirt.size())
                    {
                        thisPed->Cothing[thisPed->Cloth_Pick].Badge.BaseName = MaleTshirt[myMenu.Menu_Form[myMenu.Index].Current].BaseName;
                        thisPed->Cothing[thisPed->Cloth_Pick].Badge.TatName = MaleTshirt[myMenu.Menu_Form[myMenu.Index].Current].TatName;
                    }
                }
                else if (iCharType == 5)
                {
                    if (myMenu.Menu_Form[myMenu.Index].Current > -1 && myMenu.Menu_Form[myMenu.Index].Current < (int)FemaleTshirt.size())
                    {
                        thisPed->Cothing[thisPed->Cloth_Pick].Badge.BaseName = FemaleTshirt[myMenu.Menu_Form[myMenu.Index].Current].BaseName;
                        thisPed->Cothing[thisPed->Cloth_Pick].Badge.TatName = FemaleTshirt[myMenu.Menu_Form[myMenu.Index].Current].TatName;
                    }
                }

                myMenu.Menu_Form[myMenu.Index].Description = thisPed->Cothing[thisPed->Cloth_Pick].Badge.TatName;
                PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
                PED::_APPLY_PED_OVERLAY(PLAYER::PLAYER_PED_ID(), MyHashKey(thisPed->Cothing[thisPed->Cloth_Pick].Badge.BaseName), MyHashKey(thisPed->Cothing[thisPed->Cloth_Pick].Badge.TatName));
                ApplyTats(PLAYER::PLAYER_PED_ID(), thisPed);
            }
            else if (myMenu.Index == 5)
            {

                if (myMenu.Menu_Form[myMenu.Index].Current > -1 && myMenu.Menu_Form[myMenu.Index].Current < sList.size())
                {
                    MyCloths = LoadCloths(sList[myMenu.Menu_Form[myMenu.Index].Current]);
                    thisPed->Cothing[thisPed->Cloth_Pick] = MyCloths;;

                    myMenu.Menu_Form[myMenu.Index].Description = MyCloths.Title;
                    OnlineDress(PLAYER::PLAYER_PED_ID(), &MyCloths);

                    if (thisPed->FreeMode)
                    {
                        Mod_Class::HairSets Hairs = thisPed->MyHair;
                        SetingtheHair(PLAYER::PLAYER_PED_ID(), &Hairs);
                    }
                }
            }
        }
    }

    MenuOpen = false;
}

void MakinAMove(int Type, Mod_Class::AnimatedActions Anim)
{
    PED::SET_PED_ALTERNATE_MOVEMENT_ANIM(PLAYER::PLAYER_PED_ID(), Type, (LPSTR)Anim.Libary.c_str(), (LPSTR)Anim.Action.c_str(), 1.0f, true);
}
int VoiceCount(bool male)
{
    if (male)
        return (int)VoicesMale.size() - 1;
    else
        return (int)VoicesFemale.size() - 1;
}
std::string YourVoice(bool male,int inPlace)
{
    if (male)
        return VoicesMale[inPlace];
    else
        return VoicesFemale[inPlace];
}
void PeditorMenu_Other(Mod_Class::ClothBank* thisPed, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("PeditorMenu_Other");
    MenuOpen = true;

    std::vector<Mod_Class::MeunFields> M_List = {
        Mod_Class::MeunFields(RSLangMenu[87], RSLangMenu[88], false, false, 0, 0, 0),
        Mod_Class::MeunFields(RSLangMenu[89], RSLangMenu[90], false, false, 0, 0, 0),
        Mod_Class::MeunFields(RSLangMenu[104], thisPed->Voice, false, false, 0, VoiceCount(thisPed->Male), 0),
        Mod_Class::MeunFields(RSLangMenu[105], RSLangMenu[106], false, false, 0, 0, 0),
        Mod_Class::MeunFields(RSLangMenu[107], RSLangMenu[108], false, false, 0, 0, 0)
    };

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 5, false, M_List);
    myMenu.waitTime = InGameTime() + 150;

    Menu_Index = 0;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
            break;
        else if (myMenu._Activate)
        {
            if (myMenu.Index == 0)
            {
                std::string sC = CaptureScreenText();
                if (sC != "")
                    thisPed->CharName = sC;
            }
            else if (myMenu.Index == 1)
            {
                Menu_Index = 2;
                break;
            }
            else if (myMenu.Index == 2)
            {
                std::string Vo = YourVoice(thisPed->Male, myMenu.Menu_Form[myMenu.Index].Current);
                if (Vo == "Default")
                {
                    invoke <Void>(0x40CF0D12D142A9E8, PLAYER::PLAYER_PED_ID());
                    invoke <Void>(0x4ADA3F19BE4A6047, PLAYER::PLAYER_PED_ID());
                    thisPed->Voice = "";
                }
                else
                {
                    AUDIO::SET_AMBIENT_VOICE_NAME(PLAYER::PLAYER_PED_ID(), (LPSTR)Vo.c_str());
                    invoke <Void>(0x4ADA3F19BE4A6047, PLAYER::PLAYER_PED_ID());
                    thisPed->Voice = Vo;
                }
            }
            else if (myMenu.Index == 3)
            {
                if (thisPed->CharName == "")
                    thisPed->CharName = CaptureScreenText();

                UpdateSavedClothBanks();
            }
            else if (myMenu.Index == 4)
            {
                for (int i = 0; i < (int)SavedPeds.size(); i++)
                {
                    FileRemoval(GetDir() + "/RandomStart/SavedPeds/" + thisPed->CharName + ".ini");
                    if (SavedPeds[i].CharName == thisPed->CharName)
                        SavedPeds.erase(SavedPeds.begin() + i);
                }
                break;
            }
            else
                break;
        }
        else if (myMenu._Left || myMenu._Right)
        {
            if (myMenu.Index == 2)
                myMenu.Menu_Form[myMenu.Index].Description = YourVoice(thisPed->Male, myMenu.Menu_Form[myMenu.Index].Current);
        }
    }

    MenuOpen = false;
}
void PeditorMenu_MainChar(Mod_Class::ClothBank* thisPed, int Main_Char, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("PeditorMenu_MainChar");
    MenuOpen = true;
    std::string PedVoice = thisPed->Voice;

    std::vector<Mod_Class::MeunFields> M_List = {
        Mod_Class::MeunFields(RSLangMenu[87], RSLangMenu[88], false, false, 0, 0, 0),
        Mod_Class::MeunFields(RSLangMenu[89], RSLangMenu[90], false, false, 0, 0, 0),
        Mod_Class::MeunFields(RSLangMenu[91], RSLangMenu[92], false, false, 0, 0, 0),
        Mod_Class::MeunFields(RSLangMenu[104], PedVoice, false, false, 0, VoiceCount(thisPed->Male), 0),
        Mod_Class::MeunFields(RSLangMenu[105], RSLangMenu[106], false, false, 0, 0, 0),
        Mod_Class::MeunFields(RSLangMenu[107], RSLangMenu[108], false, false, 0, 0, 0)
    };

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 6, false, M_List);
    myMenu.waitTime = InGameTime() + 150;

    Menu_Index = 0;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
            break;
        else if (myMenu._Activate)
        {
            if (myMenu.Index == 0)
            {
                std::string sC = CaptureScreenText();
                if (sC != "")
                    thisPed->CharName = sC;
            }
            else if (myMenu.Index == 1)
            {
                Menu_Index = 2;
                break;
            }
            else if (myMenu.Index == 2)
            {
                Menu_Index = 3;
                break;
            }
            else if (myMenu.Index == 3)
            {
                std::string Vo = YourVoice(thisPed->Male, myMenu.Menu_Form[myMenu.Index].Current);
                if (Vo == "Default")
                {
                    invoke <Void>(0x40CF0D12D142A9E8, PLAYER::PLAYER_PED_ID());
                    invoke <Void>(0x4ADA3F19BE4A6047, PLAYER::PLAYER_PED_ID());
                    thisPed->Voice = "";
                }
                else
                {
                    AUDIO::SET_AMBIENT_VOICE_NAME(PLAYER::PLAYER_PED_ID(), (LPSTR)Vo.c_str());
                    invoke <Void>(0x4ADA3F19BE4A6047, PLAYER::PLAYER_PED_ID());
                    thisPed->Voice = Vo;
                }
            }
            else if (myMenu.Index == 4)
            {
                if (thisPed->CharName == "")
                    thisPed->CharName = CaptureScreenText();

                UpdateSavedClothBanks();
            }
            else if (myMenu.Index == 5)
            {

                for (int i = 0; i < (int)SavedPeds.size(); i++)
                {
                    if (SavedPeds[i].CharName == thisPed->CharName)
                        SavedPeds.erase(SavedPeds.begin() + i);
                    FileRemoval(GetDir() + "/RandomStart/SavedPeds/" + thisPed->CharName + ".ini");
                }
                break;
            }
            else
                break;
        }
        else if (myMenu._Left || myMenu._Right)
        {
            if (myMenu.Index == 3)
                myMenu.Menu_Form[myMenu.Index].Description = YourVoice(thisPed->Male, myMenu.Menu_Form[myMenu.Index].Current);
        }

    }
    MenuOpen = false;
}
void PeditorMenu_FreeMode(Mod_Class::ClothBank* thisPed, int Main_Char, int iScale, float screenHeightScaleFactor)
{
    LoggerLight("PeditorMenu_FreeMode");
    MenuOpen = true;

    int EyeTotal = 22;
    if (thisPed->Male)
        EyeTotal = 22;
    int iHair = 0;
    for (int i = 0; i < SizeUpHairList(thisPed->Male); i++)
    {
        if (PickAStyle(i, thisPed->Male).Name == thisPed->MyHair.Name)
        {
            iHair = i;
            break;
        }
    }
    int Voices = 0;
    for (int i = 0; i < SizeUpHairList(thisPed->Male); i++)
    {
        if (YourVoice(thisPed->Male, i) == thisPed->Voice)
        {
            Voices = i;
            break;
        }
    }

    std::vector<Mod_Class::MeunFields> M_List = {
        Mod_Class::MeunFields(RSLangMenu[87] ,RSLangMenu[88], false, false, 0, 0, 0),
        Mod_Class::MeunFields(RSLangMenu[89], RSLangMenu[90], false, false, 0, 0, 0),            //ext
        Mod_Class::MeunFields(RSLangMenu[91], RSLangMenu[92], false, false, 0, 0, 0),                    //ext
        Mod_Class::MeunFields(RSLangMenu[93], thisPed->MyHair.Name, false, true, 0, SizeUpHairList(thisPed->Male), iHair),
        Mod_Class::MeunFields(RSLangMenu[94], RSLangMenu[95], false, true, 0, EyeTotal, thisPed->EyeColour),
        Mod_Class::MeunFields(RSLangMenu[96], thisPed->MyHair.Name, false, true, 0, 61, thisPed->HairColour),
        Mod_Class::MeunFields(RSLangMenu[97], thisPed->MyHair.Name, false, true, 0, 61, thisPed->HairStreaks),
        Mod_Class::MeunFields(RSLangMenu[98], RSLangMenu[99], false, false, 0, 0, 0),                     //ext
        Mod_Class::MeunFields(RSLangMenu[100], RSLangMenu[101], false, false, 0, 0, 0),        //ext
        Mod_Class::MeunFields(RSLangMenu[102], RSLangMenu[103], false, false, 0, 0, 0),            //ext
        Mod_Class::MeunFields(RSLangMenu[104], thisPed->Voice, false, false, 0, VoiceCount(thisPed->Male), Voices),
        Mod_Class::MeunFields(RSLangMenu[105], RSLangMenu[106], false, false, 0, 0, 0),
        Mod_Class::MeunFields(RSLangMenu[107], RSLangMenu[108], false, false, 0, 0, 0)
    };

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 7, true, M_List);
    myMenu.waitTime = InGameTime() + 150;

    Menu_Index = 0;
    
    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
            break;
        else if (myMenu._Activate)
        {
            if (myMenu.Index == 0)
            {
                std::string sC = CaptureScreenText();
                if (sC != "")
                    thisPed->CharName = sC;
            }
            else if (myMenu.Index == 1)
            {
                if ((int)thisPed->Cothing.size() == 0)
                {
                    thisPed->Cloth_Pick = 0;
                    thisPed->Cothing.push_back(GetYourTogs(PLAYER::PLAYER_PED_ID()));
                }
                Menu_Index = 2;
                break;
            }
            else if (myMenu.Index == 2)
            {
                Menu_Index = 3; 
                break;
            }
            else if (myMenu.Index == 3)
            {
                myMenu.Menu_Form[myMenu.Index].Current = 0;
                Mod_Class::HairSets newHair = PickAStyle(myMenu.Menu_Form[myMenu.Index].Current, thisPed->Male);
                SetingtheHair(PLAYER::PLAYER_PED_ID(), &newHair);
                myMenu.Menu_Form[myMenu.Index].Description = newHair.Name;
                thisPed->MyHair = newHair;
            }
            else if (myMenu.Index == 4)
            {
                thisPed->EyeColour = 0;
                myMenu.Menu_Form[myMenu.Index].Current = 0;
                PED::_SET_PED_EYE_COLOR(PLAYER::PLAYER_PED_ID(), 0);
            }
            else if (myMenu.Index == 5)
            {
                thisPed->HairColour = 0;
                myMenu.Menu_Form[myMenu.Index].Current = 0;
                PED::_SET_PED_HAIR_COLOR(PLAYER::PLAYER_PED_ID(), thisPed->HairColour, thisPed->HairStreaks);
            }
            else if (myMenu.Index == 6)
            {
                thisPed->HairStreaks = 0;
                myMenu.Menu_Form[myMenu.Index].Current = 0;
                PED::_SET_PED_HAIR_COLOR(PLAYER::PLAYER_PED_ID(), thisPed->HairColour, thisPed->HairStreaks);
            }
            else if (myMenu.Index == 7)
            {
                Menu_Index = 4;
                break;
            }
            else if (myMenu.Index == 8)
            {
                Menu_Index = 5;
                break;
            }
            else if (myMenu.Index == 9)
            {
                Menu_Index = 6;
                break;
            }
            else if (myMenu.Index == 10)
            {
                std::string Vo = YourVoice(thisPed->Male, myMenu.Menu_Form[myMenu.Index].Current);
                if (Vo == "Default")
                {
                    invoke <Void>(0x40CF0D12D142A9E8, PLAYER::PLAYER_PED_ID());
                    invoke <Void>(0x4ADA3F19BE4A6047, PLAYER::PLAYER_PED_ID());
                    thisPed->Voice = "";
                }
                else
                {
                    AUDIO::SET_AMBIENT_VOICE_NAME(PLAYER::PLAYER_PED_ID(), (LPSTR)Vo.c_str());
                    invoke <Void>(0x4ADA3F19BE4A6047, PLAYER::PLAYER_PED_ID());
                    thisPed->Voice = Vo;
                }
            }
            else if (myMenu.Index == 11)
            {
                if (thisPed->CharName == "")
                    thisPed->CharName = CaptureScreenText();

                UpdateSavedClothBanks();
                break;
            }
            else if (myMenu.Index == 12)
            {
                for (int i = 0; i < (int)SavedPeds.size(); i++)
                {
                    FileRemoval(GetDir() + "/RandomStart/SavedPeds/" + thisPed->CharName + ".ini");
                    if (SavedPeds[i].CharName == thisPed->CharName)
                        SavedPeds.erase(SavedPeds.begin() + i);
                }
                break;
            }
            else
                break;
        }
        else if (myMenu._Left || myMenu._Right)
        {
            if (myMenu.Index == 3)
            {
                Mod_Class::HairSets newHair = PickAStyle(myMenu.Menu_Form[myMenu.Index].Current, thisPed->Male);
                SetingtheHair(PLAYER::PLAYER_PED_ID(), &newHair);
                myMenu.Menu_Form[myMenu.Index].Description = newHair.Name;
                thisPed->MyHair = newHair;
            }
            else if (myMenu.Index == 4)
            {
                thisPed->EyeColour = myMenu.Menu_Form[myMenu.Index].Current;
                PED::_SET_PED_EYE_COLOR(PLAYER::PLAYER_PED_ID(), thisPed->EyeColour);
            }
            else if (myMenu.Index == 5)
            {
                thisPed->HairColour = myMenu.Menu_Form[myMenu.Index].Current;
                PED::_SET_PED_HAIR_COLOR(PLAYER::PLAYER_PED_ID(), thisPed->HairColour, thisPed->HairStreaks);
            }
            else if (myMenu.Index == 6)
            {
                thisPed->HairStreaks = myMenu.Menu_Form[myMenu.Index].Current;
                PED::_SET_PED_HAIR_COLOR(PLAYER::PLAYER_PED_ID(), thisPed->HairColour, thisPed->HairStreaks);
            }
            else if (myMenu.Index == 10)
            {
                std::string Vo = YourVoice(thisPed->Male, myMenu.Menu_Form[myMenu.Index].Current);
                if (Vo == "Default")
                {
                    invoke <Void>(0x40CF0D12D142A9E8, PLAYER::PLAYER_PED_ID());
                    invoke <Void>(0x4ADA3F19BE4A6047, PLAYER::PLAYER_PED_ID());
                    thisPed->Voice = "";
                }
                else
                {
                    AUDIO::SET_AMBIENT_VOICE_NAME(PLAYER::PLAYER_PED_ID(), (LPSTR)Vo.c_str());
                    invoke <Void>(0x4ADA3F19BE4A6047, PLAYER::PLAYER_PED_ID());
                    thisPed->Voice = Vo;
                }
                myMenu.Menu_Form[myMenu.Index].Description = Vo;
            }
        }
    }
    if (myMenu._Exit)
    {
        if (thisPed->CharName == "")
            SavedPeds.pop_back();
    }
    MenuOpen = false;
}

void PedditorMenu(Mod_Class::ClothBank* thisPed)
{
    LoggerLight("PedditorMenu");

    float screenHeightScaleFactor = GRAPHICS::_GET_SCREEN_ASPECT_RATIO(true);

    std::vector<std::string> sInstBut = { RSLangMenu[0], RSLangMenu[1], RSLangMenu[2], RSLangMenu[3] };
    std::vector<int> iInstBut = { 21, 45, 189, 190 };
    int Main_Char = YourCharIs();
    int iScale = BottomRight(iInstBut, sInstBut);

    Menu_Index = 1;

    while (true)
    {
        if (Close_Menu)
            break;
        else if (Menu_Index == 1)
        {
            if (Main_Char == 1 || Main_Char == 2 || Main_Char == 3)
                PeditorMenu_MainChar(thisPed, Main_Char, iScale, screenHeightScaleFactor);
            else if (Main_Char == 4 || Main_Char == 5)
                PeditorMenu_FreeMode(thisPed, Main_Char, iScale, screenHeightScaleFactor);
            else
                PeditorMenu_Other(thisPed, iScale, screenHeightScaleFactor);
        }
        else if (Menu_Index == 2)
            PeditorMenu_Outfit(thisPed, iScale, screenHeightScaleFactor);
        else if (Menu_Index == 3)
            PeditorMenu_TattooPar(thisPed, Main_Char, iScale, screenHeightScaleFactor);
        else if (Menu_Index == 4)
            PeditorMenu_FaceFeats(thisPed, iScale, screenHeightScaleFactor);
        else if (Menu_Index == 5)
            PeditorMenu_FaceShape(thisPed, iScale, screenHeightScaleFactor);
        else if (Menu_Index == 6)
            PeditorMenu_Parenting(thisPed, iScale, screenHeightScaleFactor);
        else if (Menu_Index == 7)
            PeditorMenu_PedComp(thisPed, iScale, screenHeightScaleFactor);
        else if (Menu_Index == 8)
            PeditorMenu_PedProp(thisPed, iScale, screenHeightScaleFactor);
        else if (Menu_Index == 9)
            PeditorMenu_CompList(Menu_IndexI, thisPed, iScale, screenHeightScaleFactor);
        else if (Menu_Index == 10)
            PeditorMenu_PropList(Menu_IndexI, thisPed, iScale, screenHeightScaleFactor);
        else if (Menu_Index == 11)
            PeditorMenu_TattooParList(thisPed, Main_Char, Menu_IndexI, iScale, screenHeightScaleFactor);
        else if (Menu_Index == 12)
            PeditorMenu_FaceFeatsList(Menu_IndexI, Menu_IndexII, Menu_IndexIII, thisPed, iScale, screenHeightScaleFactor);
        else
            break;
    }
    if (thisPed->CharName != "")
        UpdateSavedClothBanks();
    CloseBaseHelpBar(iScale);
}

void SaveCurrentPed()
{
    Hash pedHash = ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID());

    bool freeMode = false;
    if (pedHash == MainProtags[3] || pedHash == MainProtags[4])
        freeMode = true;
    bool male = PED::IS_PED_MALE(PLAYER::PLAYER_PED_ID());

    bool animal_Farm = false;
    if (PED::GET_PED_TYPE(PLAYER::PLAYER_PED_ID()) == 28)
        animal_Farm = true;

    Mod_Class::ClothBank MyNewBank = Mod_Class::ClothBank("", "", pedHash, freeMode, FreeFaces(PLAYER::PLAYER_PED_ID(), freeMode), male, animal_Farm, PickAStyle(male), 0, 0, 0, 0, AddOverLay(male, freeMode), {}, { GetYourTogs(PLAYER::PLAYER_PED_ID()) }, {}, "");

    SavedPeds.push_back(MyNewBank);

    Menu_IndexI = (int)SavedPeds.size() - 1;

    Menu_Index = -1;
}
void NewRandomFreePed()
{
    Menu_IndexI = (int)SavedPeds.size();
    SavedPeds.push_back(NewFreeModePed());
    SavedPlayer(&SavedPeds[Menu_IndexI], -1);
    Menu_Index = -1;
}
void RsMenu_LoadSavePed(int iScale, float screenHeightScaleFactor)
{
    MenuOpen = true;
    LoggerLight("RsMenu_LoadSavePed");

    if ((int)SavedPeds.size() > 0)
    {
        std::vector<Mod_Class::MeunFields> PedCompOut = {};

        for (int i = 0; i < (int)SavedPeds.size(); i++)
            PedCompOut.push_back(Mod_Class::MeunFields(SavedPeds[i].CharName, RSLangMenu[86], false, false, 0, 1, 0));

        bool scroll = false;
        int iSize = 7;
        if ((int)PedCompOut.size() > 7)
            scroll = true;
        else
            iSize = (int)PedCompOut.size();

        Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, iSize, scroll, PedCompOut);
        myMenu.waitTime = InGameTime() + 150;

        Menu_Index = 0;

        while (true)
        {
            if (Close_Menu)
                break;

            MenuDisplay(&myMenu, screenHeightScaleFactor);
            GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
            WAIT(0);

            if (myMenu._Exit)
                break;
            else if (myMenu._Activate)
                break;
        }

        MenuOpen = false;
        if (!Close_Menu)
        {
            if (myMenu._Exit)
                Menu_Index = 1;
            else if (myMenu._Activate)
            {
                Menu_IndexI = myMenu.Index;
                SavedPlayer(&SavedPeds[Menu_IndexI], -1);
                Menu_Index = -1;
            }
        }
    }
    else
        Menu_Index = 1;
}
void RsMenu_SavePed(int iScale, float screenHeightScaleFactor)
{
    LoggerLight("RsMenu_SavePed");
    MenuOpen = true;
    std::vector<Mod_Class::MeunFields> M_List = {
        Mod_Class::MeunFields(RSLangMenu[78], RSLangMenu[79], false, false, 0, 0, 0),   //Ext
        Mod_Class::MeunFields(RSLangMenu[80], RSLangMenu[81], false, false, 0, 0, 0),    //Ext
        Mod_Class::MeunFields(RSLangMenu[82], RSLangMenu[83], false, false, 0, 0, 0),
        Mod_Class::MeunFields(RSLangMenu[84], RSLangMenu[85], false, false, 0, 0, 0)
    };
    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 4, false, M_List);
    myMenu.waitTime = InGameTime() + 150;

    Menu_Index = 0;

    while (true)
    {
        if (Close_Menu)
            break;
        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 1;
            break;
        }
        else if (myMenu._Activate)
            break;
    }

    MenuOpen = false;
    if (myMenu._Exit)
        Menu_Index = 1;
    else if (myMenu.Index == 0)
        Menu_Index = 5;
    else if (myMenu.Index == 1)
        Menu_Index = 6;
    else if (myMenu.Index == 2)
        Menu_Index = 7;
    else if (myMenu.Index == 3)
        Menu_Index = 100;
}
void RsMenu_ScenarioToggles(int index)
{
    if (index == 1)
        Mod_Settings.BeachPed = !Mod_Settings.BeachPed;
    else if (index == 2)
        Mod_Settings.Tramps = !Mod_Settings.Tramps;
    else if (index == 3)
        Mod_Settings.Highclass = !Mod_Settings.Highclass;
    else if (index == 4)
        Mod_Settings.Midclass = !Mod_Settings.Midclass;
    else if (index == 5)
        Mod_Settings.Lowclass = !Mod_Settings.Lowclass;
    else if (index == 6)
        Mod_Settings.Business = !Mod_Settings.Business;
    else if (index == 7)
        Mod_Settings.Bodybuilder = !Mod_Settings.Bodybuilder;
    else if (index == 8)
        Mod_Settings.GangStars = !Mod_Settings.GangStars;
    else if (index == 9)
        Mod_Settings.Epsilon = !Mod_Settings.Epsilon;
    else if (index == 10)
        Mod_Settings.Jogger = !Mod_Settings.Jogger;
    else if (index == 11)
        Mod_Settings.Golfer = !Mod_Settings.Golfer;
    else if (index == 12)
        Mod_Settings.Hiker = !Mod_Settings.Hiker;
    else if (index == 13)
        Mod_Settings.Methaddict = !Mod_Settings.Methaddict;
    else if (index == 14)
        Mod_Settings.Rural = !Mod_Settings.Rural;
    else if (index == 15)
        Mod_Settings.Cyclist = !Mod_Settings.Cyclist;
    else if (index == 16)
        Mod_Settings.LGBTWXYZ = !Mod_Settings.LGBTWXYZ;
    else if (index == 17)
        Mod_Settings.PoolPeds = !Mod_Settings.PoolPeds;
    else if (index == 18)
        Mod_Settings.Workers = !Mod_Settings.Workers;
    else if (index == 19)
        Mod_Settings.Jetski = !Mod_Settings.Jetski;
    else if (index == 20)
        Mod_Settings.BikeATV = !Mod_Settings.BikeATV;
    else if (index == 21)
        Mod_Settings.Services = !Mod_Settings.Services;
    else if (index == 22)
        Mod_Settings.Pilot = !Mod_Settings.Pilot;
    else if (index == 23)
        Mod_Settings.Animals = !Mod_Settings.Animals;
    else if (index == 24)
        Mod_Settings.Yankton = !Mod_Settings.Yankton;
    else if (index == 25)
        Mod_Settings.Cayo = !Mod_Settings.Cayo;
}
void RsMenu_Scenario(int iScale, float screenHeightScaleFactor)
{
    LoggerLight("RsMenu_Scenario");
    MenuOpen = true;
    std::vector<Mod_Class::MeunFields> M_List = {
        Mod_Class::MeunFields(RSLangMenu[8], RSLangMenu[4], false, false, 0, 1, 0),
        Mod_Class::MeunFields(RSLangMenu[28], RSLangMenu[29], true, false, 0, 1, (int)Mod_Settings.BeachPed),
        Mod_Class::MeunFields(RSLangMenu[30], RSLangMenu[31], true, false, 0, 1, (int)Mod_Settings.Tramps),
        Mod_Class::MeunFields(RSLangMenu[32], RSLangMenu[33], true, false, 0, 1, (int)Mod_Settings.Highclass),
        Mod_Class::MeunFields(RSLangMenu[34], RSLangMenu[35], true, false, 0, 1, (int)Mod_Settings.Midclass),
        Mod_Class::MeunFields(RSLangMenu[36], RSLangMenu[37], true, false, 0, 1, (int)Mod_Settings.Lowclass),
        Mod_Class::MeunFields(RSLangMenu[38], RSLangMenu[39], true, false, 0, 1, (int)Mod_Settings.Business),
        Mod_Class::MeunFields(RSLangMenu[40], RSLangMenu[41], true, false, 0, 1, (int)Mod_Settings.Bodybuilder),
        Mod_Class::MeunFields(RSLangMenu[42], RSLangMenu[43], true, false, 0, 1, (int)Mod_Settings.GangStars),
        Mod_Class::MeunFields(RSLangMenu[44], RSLangMenu[45], true, false, 0, 1, (int)Mod_Settings.Epsilon),
        Mod_Class::MeunFields(RSLangMenu[46], RSLangMenu[47], true, false, 0, 1, (int)Mod_Settings.Jogger),
        Mod_Class::MeunFields(RSLangMenu[48], RSLangMenu[49], true, false, 0, 1, (int)Mod_Settings.Golfer),
        Mod_Class::MeunFields(RSLangMenu[50], RSLangMenu[51], true, false, 0, 1, (int)Mod_Settings.Hiker),
        Mod_Class::MeunFields(RSLangMenu[52], RSLangMenu[53], true, false, 0, 1, (int)Mod_Settings.Methaddict),
        Mod_Class::MeunFields(RSLangMenu[54], RSLangMenu[55], true, false, 0, 1, (int)Mod_Settings.Rural),
        Mod_Class::MeunFields(RSLangMenu[56], RSLangMenu[57], true, false, 0, 1, (int)Mod_Settings.Cyclist),
        Mod_Class::MeunFields(RSLangMenu[58], RSLangMenu[59], true, false, 0, 1, (int)Mod_Settings.LGBTWXYZ),
        Mod_Class::MeunFields(RSLangMenu[60], RSLangMenu[61], true, false, 0, 1, (int)Mod_Settings.PoolPeds),
        Mod_Class::MeunFields(RSLangMenu[62], RSLangMenu[63], true, false, 0, 1, (int)Mod_Settings.Workers),
        Mod_Class::MeunFields(RSLangMenu[64], RSLangMenu[65], true, false, 0, 1, (int)Mod_Settings.Jetski),
        Mod_Class::MeunFields(RSLangMenu[66], RSLangMenu[67], true, false, 0, 1, (int)Mod_Settings.BikeATV),
        Mod_Class::MeunFields(RSLangMenu[68], RSLangMenu[69], true, false, 0, 1, (int)Mod_Settings.Services),
        Mod_Class::MeunFields(RSLangMenu[70], RSLangMenu[71], true, false, 0, 1, (int)Mod_Settings.Pilot),
        Mod_Class::MeunFields(RSLangMenu[72], RSLangMenu[73], true, false, 0, 1, (int)Mod_Settings.Animals),
        Mod_Class::MeunFields(RSLangMenu[74], RSLangMenu[75], true, false, 0, 1, (int)Mod_Settings.Yankton),
        Mod_Class::MeunFields(RSLangMenu[76], RSLangMenu[77], true, false, 0, 1, (int)Mod_Settings.Cayo)
    };

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 7, true, M_List);
    myMenu.waitTime = InGameTime() + 150;

    Menu_Index = 0;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 1;
            break;
        }
        else if (myMenu._Activate)
            break;
        else if (myMenu._Left || myMenu._Right)
            RsMenu_ScenarioToggles(myMenu.Index);
    }
    MenuOpen = false;

    if (myMenu._Activate)
    {
        if (myMenu.Index == 0)
            RandomStart(false);
        else
            RandomLocation(myMenu.Index);
    }
}
void RsMenu_WinterToggles(int index)
{
    if (index == 0)
        Mod_Settings.SnowMonths.Jan = !Mod_Settings.SnowMonths.Jan;
    else if (index == 1)
        Mod_Settings.SnowMonths.Feb = !Mod_Settings.SnowMonths.Feb;
    else if (index == 2)
        Mod_Settings.SnowMonths.Mar = !Mod_Settings.SnowMonths.Mar;
    else if (index == 3)
        Mod_Settings.SnowMonths.Apr = !Mod_Settings.SnowMonths.Apr;
    else if (index == 4)
        Mod_Settings.SnowMonths.May = !Mod_Settings.SnowMonths.May;
    else if (index == 5)
        Mod_Settings.SnowMonths.Jun = !Mod_Settings.SnowMonths.Jun;
    else if (index == 6)
        Mod_Settings.SnowMonths.Jul = !Mod_Settings.SnowMonths.Jul;
    else if (index == 7)
        Mod_Settings.SnowMonths.Aug = !Mod_Settings.SnowMonths.Aug;
    else if (index == 8)
        Mod_Settings.SnowMonths.Sep = !Mod_Settings.SnowMonths.Sep;
    else if (index == 9)
        Mod_Settings.SnowMonths.Oct = !Mod_Settings.SnowMonths.Oct;
    else if (index == 10)
        Mod_Settings.SnowMonths.Nov = !Mod_Settings.SnowMonths.Nov;
    else if (index == 11)
        Mod_Settings.SnowMonths.Dec = !Mod_Settings.SnowMonths.Dec;
}
void RsMenu_Winter(int iScale, float screenHeightScaleFactor)
{
    LoggerLight("RsMenu_Winter");
    MenuOpen = true;
    std::vector<Mod_Class::MeunFields> M_List = {
        Mod_Class::MeunFields(RSLangMenu[214], "", true, false, 0, 1, (int)Mod_Settings.SnowMonths.Jan),
        Mod_Class::MeunFields(RSLangMenu[215], "", true, false, 0, 1, (int)Mod_Settings.SnowMonths.Feb),
        Mod_Class::MeunFields(RSLangMenu[216], "", true, false, 0, 1, (int)Mod_Settings.SnowMonths.Mar),
        Mod_Class::MeunFields(RSLangMenu[217], "", true, false, 0, 1, (int)Mod_Settings.SnowMonths.Apr),
        Mod_Class::MeunFields(RSLangMenu[218], "", true, false, 0, 1, (int)Mod_Settings.SnowMonths.May),
        Mod_Class::MeunFields(RSLangMenu[219], "", true, false, 0, 1, (int)Mod_Settings.SnowMonths.Jun),
        Mod_Class::MeunFields(RSLangMenu[220], "", true, false, 0, 1, (int)Mod_Settings.SnowMonths.Jul),
        Mod_Class::MeunFields(RSLangMenu[221], "", true, false, 0, 1, (int)Mod_Settings.SnowMonths.Aug),
        Mod_Class::MeunFields(RSLangMenu[222], "", true, false, 0, 1, (int)Mod_Settings.SnowMonths.Sep),
        Mod_Class::MeunFields(RSLangMenu[223], "", true, false, 0, 1, (int)Mod_Settings.SnowMonths.Oct),
        Mod_Class::MeunFields(RSLangMenu[224], "", true, false, 0, 1, (int)Mod_Settings.SnowMonths.Nov),
        Mod_Class::MeunFields(RSLangMenu[225], "", true, false, 0, 1, (int)Mod_Settings.SnowMonths.Dec),
    };

    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 7, true, M_List);
    myMenu.waitTime = InGameTime() + 150;

    Menu_Index = 0;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 1;
            break;
        }
        else if (myMenu._Activate)
            RsMenu_WinterToggles(myMenu.Index);
        else if (myMenu._Left || myMenu._Right)
            RsMenu_WinterToggles(myMenu.Index);
    }
    SetWeatherDate();
    WeatherReport(-1);
    MenuOpen = false;
}
void RsMenu_KeyCapture(int iScale, float screenHeightScaleFactor)
{
    LoggerLight("RsMenu_SavePed");
    MenuOpen = true;
    std::vector<Mod_Class::MeunFields> M_List = {
        Mod_Class::MeunFields(RSLangMenu[184], RSLangMenu[185], false, false, 0, 0, 0),   //Ext
        Mod_Class::MeunFields(RSLangMenu[186], RSLangMenu[187], false, false, 0, 0, 0),    //Ext
    };
    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 2, false, M_List);
    myMenu.waitTime = InGameTime() + 150;

    Menu_Index = 0;

    while (true)
    {
        if (Close_Menu)
            break;
        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);
        WAIT(0);

        if (myMenu._Exit)
        {
            Menu_Index = 1;
            break;
        }
        else if (myMenu._Activate)
            break;
    }

    MenuOpen = false;
    if (myMenu._Exit)
        Menu_Index = 1;
    else if (myMenu._Activate)
    {
        if (myMenu.Index == 0)
            KeyCapture();
        else if (myMenu.Index == 1)
            ControlerCapture();
    }
}
void RsMenu_MainToggles(int index, Mod_Class::MeunSystem* myMenu)
{
    if (index == 2)
        Mod_Settings.Auto_Run = !Mod_Settings.Auto_Run;
    else if (index == 3)
    {
        Mod_Settings.Random_Ped = !Mod_Settings.Random_Ped;

        if (Mod_Settings.Random_Ped)
        {
            myMenu->Menu_Form[4].Current = 0;
            Mod_Settings.Saved_Ped = false;
        }
    }
    else if (index == 4)
    {
        Mod_Settings.Saved_Ped = !Mod_Settings.Saved_Ped;

        if (Mod_Settings.Saved_Ped)
        {
            myMenu->Menu_Form[3].Current = 0;
            Mod_Settings.Random_Ped = false;
        }
    }
    else if (index == 5)
    {
        Mod_Settings.Reincarnate = !Mod_Settings.Reincarnate;

        if (Mod_Settings.Reincarnate)
        {
            myMenu->Menu_Form[7].Current = 0;
            Mod_Settings.Funeral = false;
        }
    }
    else if (index == 6)
        Mod_Settings.ReCurr = !Mod_Settings.ReCurr;
    else if (index == 7)
    {
        Mod_Settings.Funeral = !Mod_Settings.Funeral;

        if (Mod_Settings.Funeral)
        {
            myMenu->Menu_Form[5].Current = 0;
            Mod_Settings.Reincarnate = false;
        }
    }
    else if (index == 8)
        Mod_Settings.Prison = !Mod_Settings.Prison;
    else if (index == 9)
        Mod_Settings.Random_Weapons = !Mod_Settings.Random_Weapons;
    else if (index == 10)
        Mod_Settings.Disable_Record_Key = !Mod_Settings.Disable_Record_Key;
}
const std::vector<std::string> TranlatesTo = {
    "English",
    "French",
    "German",
    "Italian",
    "Spanish",
    "Portuguese",
    "Polish",
    "Russian",
    "Korean",
    "Chinese",
    "Japanese",
    "Mexican",
    "ChineseSimplifyed"
};
void RsMenu_Main(int iScale, float screenHeightScaleFactor)
{
    LoggerLight("RsMenu_Main");
    MenuOpen = true;
    std::vector<Mod_Class::MeunFields> M_List = {
        Mod_Class::MeunFields(RSLangMenu[4], RSLangMenu[5], false, false, 0, 0, 0),                             //Ext
        Mod_Class::MeunFields(RSLangMenu[6], RSLangMenu[7], false, false, 0, 0, 0),                                   //Ext
        Mod_Class::MeunFields(RSLangMenu[8], RSLangMenu[9], true, false, 0, 1, (int)Mod_Settings.Auto_Run),
        Mod_Class::MeunFields(RSLangMenu[10], RSLangMenu[11], true, false, 0, 1, (int)Mod_Settings.Random_Ped),
        Mod_Class::MeunFields(RSLangMenu[12], RSLangMenu[13], true, false, 0, 1, (int)Mod_Settings.Saved_Ped),
        Mod_Class::MeunFields(RSLangMenu[14], RSLangMenu[15], true, false, 0, 1, (int)Mod_Settings.Reincarnate),
        Mod_Class::MeunFields(RSLangMenu[16], RSLangMenu[17], true, false, 0, 1, (int)Mod_Settings.ReCurr),
        Mod_Class::MeunFields(RSLangMenu[18], RSLangMenu[19], true, false, 0, 1, (int)Mod_Settings.Funeral),
        Mod_Class::MeunFields(RSLangMenu[20], RSLangMenu[21], true, false, 0, 1, (int)Mod_Settings.Prison),
        Mod_Class::MeunFields(RSLangMenu[22], RSLangMenu[23], true, false, 0, 1, (int)Mod_Settings.Random_Weapons),
        Mod_Class::MeunFields(RSLangMenu[24], RSLangMenu[25], false, false, 0, 0, 0),
        Mod_Class::MeunFields(RSLangMenu[26], RSLangMenu[27], false, false, 0, 0, 0),
        Mod_Class::MeunFields(RSLangMenu[213],RSLangMenu[226], false, false, 0, 0, 0),         //Ext
        Mod_Class::MeunFields(TranlatesTo[Mod_Settings.Lang_Set], "", false, false, 0, 0, 0)
    };
    
    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 7, true, M_List);
    myMenu.waitTime = InGameTime() + 150;

    Menu_Index = 0;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);

        WAIT(0);

        if (myMenu._Exit)
            break;
        else if (myMenu._Activate)
        {
            if (myMenu.Index == 0)
            {
                Menu_Index = 2;
                break;
            }
            else if (myMenu.Index == 1)
            {
                Menu_Index = 3;
                break;
            }
            else if (myMenu.Index == 10)
            {
                WeaponCapture();
                break;
            }
            else if (myMenu.Index == 11)
            {
                Menu_Index = 8;
                break;
            }
            else if (myMenu.Index == 12)
            {
                Menu_Index = 4;
                break;
            }
            else
            {
                bool bswitch = !(bool)myMenu.Menu_Form[myMenu.Index].Current;
                myMenu.Menu_Form[myMenu.Index].Current = (int)bswitch;
                RsMenu_MainToggles(myMenu.Index, &myMenu);
            }
        }
        else if (myMenu._Left)
        {
            if (myMenu.Index == 12)
            {
                Mod_Settings.Lang_Set--;
                if (Mod_Settings.Lang_Set < 0)
                {
                    Mod_Settings.Lang_Set = (int)TranlatesTo.size() - 1;
                    myMenu.Menu_Form[12].Title = TranlatesTo[Mod_Settings.Lang_Set];
                }
                else
                    myMenu.Menu_Form[12].Title = TranlatesTo[Mod_Settings.Lang_Set];

                LoadLang();
                Menu_Index = 1;
                break;
            }
            else
                RsMenu_MainToggles(myMenu.Index, &myMenu);
        }
        else if (myMenu._Right)
        {
            if (myMenu.Index == 12)
            {
                Mod_Settings.Lang_Set++;
                if (Mod_Settings.Lang_Set < (int)TranlatesTo.size())
                    myMenu.Menu_Form[12].Title = TranlatesTo[Mod_Settings.Lang_Set];
                else
                {
                    Mod_Settings.Lang_Set = 0;
                    myMenu.Menu_Form[12].Title = TranlatesTo[Mod_Settings.Lang_Set];
                }
                LoadLang();
                Menu_Index = 1;
                break;
            }
            else
                RsMenu_MainToggles(myMenu.Index, &myMenu);
        }
    }
    MenuOpen = false;    
}

void FindThisScale(int iSkale, float fChange, Mod_Class::MeunSystem* myMenu)
{
    if (iSkale == 0)
        myMenu->_Screen.lineWidth = fChange;
    else if (iSkale == 1)
        myMenu->_Screen.lineHeight = fChange;
    else if (iSkale == 2)
        myMenu->_Screen.lineTop = fChange;
    else if (iSkale == 3)
        myMenu->_Screen.lineTobSpace = fChange;
    else if (iSkale == 4)
        myMenu->_Screen.lineLeft = fChange;
    else if (iSkale == 5)
        myMenu->_Screen.textLeft = fChange;
    else if (iSkale == 6)
        myMenu->_Screen.tickSizeX = fChange;
    else if (iSkale == 7)
        myMenu->_Screen.tickSizeY = fChange;
    else if (iSkale == 8)
        myMenu->_Screen.tickX = fChange;
    else if (iSkale == 9)
        myMenu->_Screen.tickY = fChange;
    else if (iSkale == 10)
        myMenu->_Screen.tickMulti = fChange;
    else if (iSkale == 11)
        myMenu->_Screen.sizeX = fChange;
    else if (iSkale == 12)
        myMenu->_Screen.sizeY = fChange;
    else if (iSkale == 13)
        myMenu->_Screen.centerX = fChange;
    else if (iSkale == 14)
        myMenu->_Screen.centerY = fChange;
    else if (iSkale == 15)
        myMenu->_Screen.posX = fChange;
    else if (iSkale == 16)
        myMenu->_Screen.posY = fChange;
    else if (iSkale == 17)
        myMenu->_Screen.rotation = fChange;
    else if (iSkale == 18)
        myMenu->_Screen.red = fChange;
    else if (iSkale == 19)
        myMenu->_Screen.green = fChange;
    else if (iSkale == 20)
        myMenu->_Screen.blue = fChange;
    else if (iSkale == 21)
        myMenu->_Screen.alfa = fChange;
    else if (iSkale == 22)
        myMenu->_Screen.ArrowAlr = fChange;
    else if (iSkale == 23)
        myMenu->_Screen.ArrowBlr = fChange;
    else if (iSkale == 24)
        myMenu->_Screen.ArrowH = fChange;
    else if (iSkale == 25)
        myMenu->_Screen.Numberlr = fChange;
    else if (iSkale == 26)
        myMenu->_Screen.ArrowtickSizeX = fChange;
    else if (iSkale == 27)
        myMenu->_Screen.ArrowtickSizeY = fChange;
    else if (iSkale == 28)
        myMenu->_Screen.NumGap = fChange;
}
void SetMenuScale(int iScale, float screenHeightScaleFactor)
{
    LoggerLight("SetMenuScale");
    MenuOpen = true;
    std::vector<float> MemSacle = {
        /*lineWidth*/     288.5f,    /*lineHeight*/     5.5f,    /*lineTop*/     104.5f,    /*lineTobSpace*/     28.0f,    /*lineLeft*/     19.5f,    /*textLeft*/     6.0f,    /*tickSizeX*/     64.0f,    /*tickSizeY*/     64.0f,    /*tickX*/     383.5f,    /*tickY*/     3.6f,    /*tickMulti*/     41.4f,    /*sizeX*/     0.227f,    /*sizeY*/     0.062f,    /*centerX*/     0.5f,    /*centerY*/     0.5f,    /*posX*/     0.128f,    /*posY*/     0.092f,    /*rotation*/     0.0f,    /*red*/     1.0f,    /*green*/     1.0f,    /*blue*/     1.0f,    /*alfa*/     1.0f,    /*ArrowAlr*/     -25.0f,    /*ArrowBlr*/     13.0f,    /*ArrowH*/     3.85f,    /*Numberlr*/     260.0f,    /*ArrowtickSizeX*/     32.0f,    /*ArrowtickSizeY*/     32.0f, 9.0f
    };
    std::vector<std::string> ItemSacle = {
        "lineWidth", /*288.5f*/ "lineHeight", /*5.5f*/ "lineTop", /*104.5f*/ "lineTobSpace", /*28.0f*/ "lineLeft", /*19.5f*/ "textLeft", /*6.0f*/ "tickSizeX", /*64.0f*/ "tickSizeY", /*64.0f*/ "tickX", /*383.5f*/ "tickY", /*3.6f*/ "tickMulti", /*41.4f*/ "sizeX", /*0.227f*/ "sizeY", /*0.062f*/ "centerX", /*0.5f*/ "centerY", /*0.5f*/ "posX", /*0.128f*/ "posY", /*0.092f*/ "rotation", /*0.0f*/ "red", /*1.0f*/ "green", /*1.0f*/ "blue", /*1.0f*/ "alfa", /*1.0f*/ "ArrowAlr", /*-8.4f*/ "ArrowBlr", /*33.2f*/ "ArrowH", /*3.85f*/ "Numberlr", /*271.6f*/ "ArrowtickSizeX", /*32.0f*/ "ArrowtickSizeY", /*32.0f*/ "NumGap"
    };

    std::vector<Mod_Class::MeunFields> M_List = {};

    for (int i = 0; i < (int)MemSacle.size(); i++)
    {
        int iCon = (int)(MemSacle[i] * 10);
        M_List.push_back(Mod_Class::MeunFields(ItemSacle[i], "", false, true, -100000, 100000, iCon));
    }
    Mod_Class::MeunSystem myMenu = Mod_Class::MeunSystem(0, 7, true, M_List);
    myMenu.waitTime = InGameTime() + 150;

    Menu_Index = 0;

    while (true)
    {
        if (Close_Menu)
            break;

        MenuDisplay(&myMenu, screenHeightScaleFactor);
        GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 0);

        WAIT(0);

        if (myMenu._Exit)
            break;
        else if (myMenu._Left || myMenu._Right)
        {
            float fChange = (float)(myMenu.Menu_Form[myMenu.Index].Current / 10);
            MemSacle[myMenu.Index] = fChange;
            FindThisScale(myMenu.Index, fChange, &myMenu);
        }
    }
    for (int i = 0; i < (int)MemSacle.size(); i++)
        LoggerLight("MenuScale -- " + ItemSacle[i] + " == " + std::to_string(MemSacle[i]));
    MenuOpen = false;
}

void RandomStartMenu()
{
    LoggerLight("RandomStartMenu");

    float screenHeightScaleFactor = GRAPHICS::_GET_SCREEN_ASPECT_RATIO(true);

    std::vector<std::string> sInstBut = { RSLangMenu[0], RSLangMenu[1], RSLangMenu[2], RSLangMenu[3] };
    std::vector<int> iInstBut = { 21, 45, 189, 190 };

    int iScale = BottomRight(iInstBut, sInstBut);
    Menu_Index = 1;

    while (true)
    {
        WAIT(1);
        if (Close_Menu)
            break;

        if (Menu_Index == 1)
            RsMenu_Main(iScale, screenHeightScaleFactor);
        else if (Menu_Index == 2)
            RsMenu_Scenario(iScale, screenHeightScaleFactor);
        else if (Menu_Index == 3)
            RsMenu_SavePed(iScale, screenHeightScaleFactor);       
        else if (Menu_Index == 4)
            RsMenu_Winter(iScale, screenHeightScaleFactor);
        else if (Menu_Index == 5)
            RsMenu_LoadSavePed(iScale, screenHeightScaleFactor);
        else if (Menu_Index == 6)
            SaveCurrentPed();
        else if (Menu_Index == 7)
            NewRandomFreePed();
        else if (Menu_Index == 8)
            RsMenu_KeyCapture(iScale, screenHeightScaleFactor);
        else
            break;
    }
    CloseBaseHelpBar(iScale);
    ReBuildIni(&Mod_Settings);

    if (Menu_Index == 100)
        Reposesion();
    else if (Menu_Index == -1 && Menu_IndexI > -1 && Menu_IndexI < (int)SavedPeds.size())
        PedditorMenu(&SavedPeds[Menu_IndexI]);
}

int iWait = 0;
int ClosePhone = 0;
void RemoveWhenFar()
{
    if ((int)Vehicle_List.size() > 0)
    {
        if (DistanceTo(PlayerPosi(),EntPosition(Vehicle_List[0])) > 150.00f)
            ClearAllEntitys(true);
        GotClutter = false;
    }
    else if ((int)Ped_List.size() > 0)
    {
        if (DistanceTo(PlayerPosi(), EntPosition(Ped_List[0])) > 150.00f)
            ClearAllPeds();
        GotClutter = false;
    }
    else
        GotClutter = false;
}
Mod_Class::MeunSystem SideAdvice = Mod_Class::MeunSystem(0, 0, false, {});
const Mod_Class::Vector4 CayoDance01 = Mod_Class::Vector4(4894.263f, -4913.141f, 3.36446f, 0.0f);
const Mod_Class::Vector4 CayoDance02 = Mod_Class::Vector4(4890.318f, -4923.923f, 3.368097f, 0.0f);

bool PrivateDancer = false;
int Strictly = 0;
void StrictlyCome()
{
    if (Strictly < (int)CayDancers.size())
    {
        if ((bool)ENTITY::IS_ENTITY_DEAD(CayDancers[Strictly]))
            ClearAllPeds();
        else if (!AI::GET_IS_TASK_ACTIVE(CayDancers[Strictly], 134))
            DanceDanceDance(CayDancers[Strictly]);
        Strictly++;
    }
    else
        Strictly = 0;
}
void YouMakeMeFeal()
{
    if (PrivateDancer)
    {
        UiSystem::TopLeft(RSLangMenu[209]);
        if (Mod_Systems::WhileButtonDown(75, true))
        {
            AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
            AI::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
            AI::STOP_ANIM_PLAYBACK(PLAYER::PLAYER_PED_ID(), 0, 0);
            PrivateDancer = false;
        }
        else if (Mod_Systems::WhileButtonDown(46, true))
            DanceDanceDance(PLAYER::PLAYER_PED_ID());
    }
    else
    {
        UiSystem::TopLeft(RSLangMenu[210]);
        if (Mod_Systems::WhileButtonDown(46, true))
        {
            DanceDanceDance(PLAYER::PLAYER_PED_ID());
            PrivateDancer = true;
        }
    }
}
void SecondLoop()
{
	while (true)
	{	 
		if (!Mod_Load)
		{
            if (DeadOrArestCheck)
            {
                if ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
                {
                    Close_Menu = true;
                    DeadOrArestCheck = false;
                    if (BackStagePass)
                        AccessAllAreas(false);
                    ClearAllEntitys(false);
                    DeathAndArrest((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()));
                }
            }
            
            if (BackStagePass)
                InRestrictedArea();
            else if (Cayo_Loaded)
            {
                if (DistanceTo(PLAYER::PLAYER_PED_ID(), CayoDance01) < 90.0f)
                {
                    if ((int)CayDancers.size() > 0)
                        StrictlyCome();

                    if (DistanceTo(PLAYER::PLAYER_PED_ID(), CayoDance01) < 7.0f || DistanceTo(PLAYER::PLAYER_PED_ID(), CayoDance02) < 11.0f)
                    {
                        if (!(bool)PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
                            YouMakeMeFeal();
                    }
                }
                else if (PrivateDancer)
                {
                    AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
                    AI::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
                    AI::STOP_ANIM_PLAYBACK(PLAYER::PLAYER_PED_ID(), 0, 0);
                    PrivateDancer = false;
                }
            }
            else if (GotClutter)
                RemoveWhenFar();
		}
		WAIT(1);
	}
}
void main()
{
	while (true)
	{
		if (Mod_Load)
		{
			if (!(bool)DLC2::GET_IS_LOADING_SCREEN_ACTIVE())
			{
				LoadinData();
				Mod_Load = false;
				//BuildProps("prop_fib_3b_cover1", NewVector3(-282.8405f, 2834.9153f, 53.3622f), NewVector3(0.00f, 0.00f, 151.3774f), false, false);

			}
		}
		else
		{
            if (Disp_Advice)
            {
                if (Side_Add_Time < InGameTime())
                    Disp_Advice = false;
                else
                    UiSystem::MeunDescrition(&SideAdvice, &Disp_Pick, true);
            }

            if (!MenuOpen)
            {
                bool Key0 = false;
                Menu_Button_state(&Key0);
                if (Mod_Data::Mod_Settings.ControlSupport)
                {
                    if (ButtonDown(Mod_Data::Mod_Settings.ControlA, false) && ButtonDown(Mod_Data::Mod_Settings.ControlB, false))
                        Key0 = true;
                }
               
                if (Key0)
                {
                    CAM::DO_SCREEN_FADE_IN(1);
                    Close_Menu = false;
                    MenuOpen = true;
                    RandomStartMenu();
                }
            }
		}
        WAIT(1);
	}
}

void ScriptSecond()
{
	srand(GetTickCount());
	SecondLoop();
}
void ScriptMain()
{
	srand(GetTickCount());
	main();
}
