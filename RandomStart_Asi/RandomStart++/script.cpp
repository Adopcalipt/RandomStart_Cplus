/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2015
		--Modified By Adoppocalipt 2023--
*/

#include "script.h"
#include "keyboard.h"
#include "ModSystems.h"
#include "GtaVMenu.h"

using namespace Mod_Data;

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm> // For std::sort
#include <any>//any thing classes
#include <type_traits>//any thing classes
#include <utility>//any thing classes

//#pragma warning(disable : 4244 4305) // double <-> float conversions

bool Mod_Load = true;

std::string Mod_Vesion = "1.6";

int CustomMenuBannerPos = 0;

bool NSPM_Include = false;

std::vector<GVM::GVMSystem> Rs_MenuList = {};
void Rs_MenuStart();
void Rs_SavedPedEdit(void* obj);
void Rs_SavedWeapons(void* obj);
void Rs_Pedditor(void* obj);
void Rs_PedMenu();

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
    Mod_Systems::LoggerLight("CheckScenarios");
    std::vector<int> RanSenaro = {};

    if (Mod_Data::Mod_Settings.BeachPed)
        RanSenaro.push_back(1);
    if (Mod_Data::Mod_Settings.Tramps)
        RanSenaro.push_back(2);
    if (Mod_Data::Mod_Settings.Highclass)
        RanSenaro.push_back(3);
    if (Mod_Data::Mod_Settings.Midclass)
        RanSenaro.push_back(4);
    if (Mod_Data::Mod_Settings.Lowclass)
        RanSenaro.push_back(5);
    if (Mod_Data::Mod_Settings.Business)
        RanSenaro.push_back(6);
    if (Mod_Data::Mod_Settings.Bodybuilder)
        RanSenaro.push_back(7);
    if (Mod_Data::Mod_Settings.GangStars)
        RanSenaro.push_back(8);
    if (Mod_Data::Mod_Settings.Epsilon)
        RanSenaro.push_back(9);
    if (Mod_Data::Mod_Settings.Jogger)
        RanSenaro.push_back(10);
    if (Mod_Data::Mod_Settings.Golfer)
        RanSenaro.push_back(11);
    if (Mod_Data::Mod_Settings.Hiker)
        RanSenaro.push_back(12);
    if (Mod_Data::Mod_Settings.Methaddict)
        RanSenaro.push_back(13);
    if (Mod_Data::Mod_Settings.Rural)
        RanSenaro.push_back(14);
    if (Mod_Data::Mod_Settings.Cyclist)
        RanSenaro.push_back(15);
    if (Mod_Data::Mod_Settings.LGBTWXYZ)
        RanSenaro.push_back(16);
    if (Mod_Data::Mod_Settings.PoolPeds)
        RanSenaro.push_back(17);
    if (Mod_Data::Mod_Settings.Workers)
        RanSenaro.push_back(18);
    if (Mod_Data::Mod_Settings.Jetski)
        RanSenaro.push_back(19);
    if (Mod_Data::Mod_Settings.BikeATV)
        RanSenaro.push_back(20);
    if (Mod_Data::Mod_Settings.Services)
        RanSenaro.push_back(21);
    if (Mod_Data::Mod_Settings.Pilot)
        RanSenaro.push_back(22);
    if (Mod_Data::Mod_Settings.Animals)
        RanSenaro.push_back(23);
    if (Mod_Data::Mod_Settings.Yankton)
        RanSenaro.push_back(24);
    if (Mod_Data::Mod_Settings.Cayo)
        RanSenaro.push_back(25);

    Mod_Systems::LoggerLight("CheckScenarios == " + std::to_string(RanSenaro.size()));
    return RanSenaro;
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
Entity Excape[3] = { NULL, NULL, NULL };

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

    Mod_Data::BackStagePass = togg;
}
void PrisonBreak()
{
    if (Excape[0] != NULL || Excape[1] != NULL || Excape[2] != NULL)
    {
        if (Mod_Maths::DistanceTo(Excape[0], PLAYER::PLAYER_PED_ID()) < 5.0f)
        {
            GVM::TopLeft(Mod_Data::RSLangMenu[191]);
            if (GVM::WhileButtonDown(75))
            {
                CAM::DO_SCREEN_FADE_OUT(1);
                WAIT(1000);
                CAM::DO_SCREEN_FADE_IN(1000);
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), Mod_Class::Vector4(1240.87f, -3239.173f, 6.028764f, 274.899f));
                Mod_Entitys::ClearAllEntitys(true);
                AccessAllAreas(false);
            }
        }
        else if (Mod_Maths::DistanceTo(Excape[1], PLAYER::PLAYER_PED_ID()) < 5.0f)
        {
            GVM::TopLeft(Mod_Data::RSLangMenu[192]);
            if (GVM::WhileButtonDown(75))
            {
                CAM::DO_SCREEN_FADE_OUT(1);
                WAIT(1000);
                CAM::DO_SCREEN_FADE_IN(1000);
                Mod_Class::Vector4 Ppos = Mod_Class::Vector4(-352.8036f, -1553.918f, 26.20481f, 179.4799f);
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), Ppos);
                Mod_Entitys::RunAnimSeq(Mod_Class::AnimList(Mod_Class::AnimatedActions("switch@trevor@scares_tramp", "trev_scares_tramp_idle_tramp"), Mod_Class::AnimatedActions("switch@trevor@scares_tramp", "trev_scares_tramp_exit_tramp"), {}), Ppos);
                Mod_Entitys::ClearAllEntitys(true);
                AccessAllAreas(false);
            }
        }
        else if (Mod_Maths::DistanceTo(Excape[2], PLAYER::PLAYER_PED_ID()) < 30.0f)
        {
            Mod_Entitys::ClearAllEntitys(true);
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
    Rs_MenuList.clear();
    int ScrollTime = 0;
    int Selecta = -1;
    Ped YoPlaya = PLAYER::PLAYER_PED_ID();
    std::vector<Ped> CollectedPeds = {};
    Mod_Entitys::CollectPeds(&CollectedPeds);
    std::vector<Ped> NearPeds = {};
    std::vector<Vector3> PedsPos = {};
    for (int i = 0; i < CollectedPeds.size(); i++)
    {
        if (CollectedPeds[i] != NULL)
        {
            if (ENTITY::DOES_ENTITY_EXIST(CollectedPeds[i]))
            {
                if (Mod_Maths::DistanceTo(CollectedPeds[i], Mod_Maths::PlayerPosi()) < 125.0f)
                {
                    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(CollectedPeds[i], 1, 1);
                    PedsPos.push_back(Mod_Maths::EntPosition(CollectedPeds[i]));
                    NearPeds.push_back(CollectedPeds[i]);
                }
            }
        }
    }

    if ((int)NearPeds.size() > 0)
    {
        ScrollTime = Mod_Systems::InGameTime() + 150;

        while (true)
        {
            WAIT(1);

            if (Selecta >= (int)NearPeds.size() || (bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
                break;

            GVM::TopLeft(Mod_Data::RSLangMenu[211]);

            if (ScrollTime < Mod_Systems::InGameTime())
            {
                bool bEnt, bDel, bRight, bEsc;
                Mod_Systems::get_button_state(&bEnt, &bDel, NULL, NULL, NULL, &bRight, &bEsc);

                if (bDel || GVM::ButtonDown(45) || bEsc || GVM::ButtonDown(199))
                {
                    Selecta = (int)NearPeds.size();
                    break;
                }
                else if (bEnt || GVM::ButtonDown(21))
                {
                    if (Selecta > -1 && Selecta < (int)NearPeds.size())
                    {
                        Mod_Entitys::RepoPedPlayer(NearPeds[Selecta]);
                        ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&NearPeds[Selecta]);
                        break;
                    }
                }
                else if (bRight || GVM::ButtonDown(46))
                {
                    ScrollTime = Mod_Systems::InGameTime() + 150;
                    if (Selecta > -1 && Selecta < (int)NearPeds.size())
                        Mod_Entitys::MoveEntity(NearPeds[Selecta], PedsPos[Selecta]);
                    Selecta++;

                    if (Selecta < (int)NearPeds.size())
                        Mod_Entitys::MoveEntity(NearPeds[Selecta], Mod_Maths::FowardOf(YoPlaya, 2.0f, true));
                }
            }
        }

        for (int i = 0; i < NearPeds.size(); i++)
        {
            if (i != Selecta)
            {
                Mod_Entitys::MoveEntity(NearPeds[i], PedsPos[i]);
                ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&NearPeds[i]);
            }
        }
    }

}

bool DeadOrArestCheck = true;
void DeathAndArrest(bool yaDeed)
{
    Mod_Systems::LoggerLight("DeathAndArrest");

    if (yaDeed)
    {
        if (Mod_Data::Mod_Settings.Reincarnate)
            Mod_Entitys::Reicarnations();
        else if (Mod_Data::Mod_Settings.Random_Ped || Mod_Data::Mod_Settings.Saved_Ped)
        {
            if (Mod_Settings.WatchDead)
                Mod_Entitys::WatchDeath();

            if (Mod_Data::Mod_Settings.Funeral)
            {
                while ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()))
                    WAIT(1);

                WAIT(2000);

                Mod_Entitys::SavedPlayer(&Mod_Data::SavedPeds[0], -1);

                Mod_Maths::AnyPreActives(0, true);
                CAM::DO_SCREEN_FADE_IN(1000);

                Prop Coffin = Mod_Entitys::BuildProps("prop_coffin_01", Mod_Class::Vector4(-278.3422f, 2844.4617f, 53.1f, -30.6686f), false, true);

                Ped Priest = Mod_Entitys::PlayerPedGen(Mod_Class::Vector4(-276.5638f, 2844.45f, 53.75225f, 134.9461f), "ig_priest", true, true);
                PED::SET_PED_FLEE_ATTRIBUTES(Priest, 0, true);
                AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Priest, true);
                Mod_Entitys::ForceAnim(Priest, "amb@world_human_bum_standing@depressed@base", "base", Mod_Class::Vector4(-276.5638f, 2844.45f, 53.75225f, 134.9461f));
                Ped Morn01 = Mod_Entitys::PlayerPedGen(Mod_Class::Vector4(-281.5462f, 2844.153f, 54.07914f, 279.358f), MainChar[1], true, true);
                PED::SET_PED_FLEE_ATTRIBUTES(Morn01, 0, true);
                AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Morn01, true);
                Mod_Entitys::ForceAnim(Morn01, "amb@world_human_bum_standing@depressed@base", "base", Mod_Class::Vector4(-281.5462f, 2844.153f, 54.07914f, 279.358f));
                Ped Morn02 = Mod_Entitys::PlayerPedGen(Mod_Class::Vector4(-276.7029f, 2841.419f, 53.96595f, 29.87679f), MainChar[2], true, true);
                PED::SET_PED_FLEE_ATTRIBUTES(Morn02, 0, true);
                AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Morn02, true);
                Mod_Entitys::ForceAnim(Morn02, "amb@world_human_bum_standing@depressed@base", "base", Mod_Class::Vector4(-276.7029f, 2841.419f, 53.96595f, 29.87679f));
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), Mod_Class::Vector4(-281.0132f, 2840.851f, 54.34494f, 320.0452f));
                WAIT(10000);
                Mod_Entitys::ClearAllEntitys(true);
            }
            else
            {
                while ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()))
                    WAIT(1);

                Mod_Maths::AnyPreActives(0, true);
                WAIT(2000);
                CAM::DO_SCREEN_FADE_IN(1000);
            }
        }
        else
        {
            while ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()))
                WAIT(1);

            Mod_Maths::AnyPreActives(0, true);
            WAIT(2000);
            CAM::DO_SCREEN_FADE_IN(1000);
        }
    }
    else
    {
        if (Mod_Data::Mod_Settings.Prison)
        {
            while ((bool)PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
                WAIT(100);

            Mod_Maths::AnyPreActives(0, true);

            Excape[0] = (Entity)Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("mule", true, false, false, false, false, 50, 0, Mod_Class::Vector4(1638.30933f, 2598.91235f, 45.7980385f, -90.483223f), {}));
            Excape[1] = (Entity)Mod_Entitys::BuildProps("prop_bin_14b", Mod_Class::Vector4(1689.59119f, 2541.75879f, 44.5688019f, 0.343875527f), false, true);
            Excape[2] = (Entity)Mod_Entitys::BuildProps("prop_billboard_01", Mod_Class::Vector4(1816.44531f, 2561.75342f, 35.9052734f, 137.27359f), false, true);
 
            Mod_Entitys::BuildProps("prop_scafold_08a", Mod_Class::Vector4(1805.90271f, 2557.1521f, 44.5995445f, -93.2685471f), false, true);
            Mod_Entitys::BuildProps("prop_scafold_frame1a", Mod_Class::Vector4(1806.40466f, 2565.1394f, 44.5535889f, -90.8649368f), false, true);
            Mod_Entitys::BuildProps("prop_scafold_frame1a", Mod_Class::Vector4(1806.39429f, 2565.16406f, 47.5116577f, -94.7868576f), false, true);
            Mod_Entitys::BuildProps("prop_scafold_frame1a", Mod_Class::Vector4(1806.36267f, 2565.12549f, 50.5853157f, -93.2752533f), false, true);
            Mod_Entitys::BuildProps("prop_billboard_10", Mod_Maths::NewVector3(1801.08032f, 2565.73584f, 55.1660233f), Mod_Maths::NewVector3(90.0f, -14.5189629f, 0.0f), false, true);
            Mod_Entitys::BuildProps("prop_scafold_08a", Mod_Class::Vector4(1793.73547f, 2558.6228f, 44.5651245f, -100.426994f), false, true);
            Mod_Entitys::BuildProps("prop_scafold_frame1a", Mod_Class::Vector4(1795.18201f, 2566.43213f, 44.535038f, -100.323944f), false, true);
            Mod_Entitys::BuildProps("prop_scafold_frame1a", Mod_Class::Vector4(1795.18201f, 2566.43213f, 47.4849854f, -100.323936f), false, true);
            Mod_Entitys::BuildProps("prop_scafold_frame1a", Mod_Class::Vector4(1795.18201f, 2566.43213f, 50.5544701f, -100.323929f), false, true);

            WAIT(2000);
            CAM::DO_SCREEN_FADE_IN(1000);

            InTheSlamer = true;
            AccessAllAreas(true);

            Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), Mod_Class::Vector4(1658.052f, 2543.221f, 45.56487f, 320.0452f));
        }
        else
        {
            while ((bool)PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
                WAIT(100);

            Mod_Maths::AnyPreActives(0, true);
            WAIT(2000);
            CAM::DO_SCREEN_FADE_IN(1000);
        }
    }

    DeadOrArestCheck = true;
}

bool GotClutter = false;

void RandomLocation(int selectSen)
{
    if (selectSen < 1)
    {
        std::vector<int> NumList = CheckScenarios();
        if ((int)NumList.size() == 0 || !Mod_Data::Mod_Settings.Auto_Run)
            selectSen = 0;
        else
            selectSen = Mod_Systems::LessRandomInt("PickASenareo", NumList);
    }

    Mod_Systems::LoggerLight("RandomLocation selectSen == " + std::to_string(selectSen));

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
    Mod_Class::FubarVectors MySpotFu = Mod_Class::FubarVectors(0, Mod_Class::Vector4(0, 0, 0, 0), Mod_Class::Vector4(0, 0, 0, 0), "", 0);

    int Action = 0;    //1-DriveVeh  2-Sunbath  3-TrampSign  4-TrampSleap  5-MuscleBeach  6-GangWars  7-Jogger  8-EnterVeh  9-Meth  10-Gardener  11-Dancing  12-Sitting  15+-NSPM
    int WeaponSet = 0;
    int SubSet = -1;
    int Seat = -1;
    int RanDriveTo = -1;
    if (selectSen > 0)
    {
        Rs_MenuList.clear();
        CAM::DO_SCREEN_FADE_OUT(1);

        PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, 0);
        PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);

        Mod_Entitys::ClearAllEntitys(true);
        Mod_Maths::AnyPreActives(selectSen, true);

        if (selectSen == 1)
        {
            TIME::SET_CLOCK_TIME(12, 0, 0);
            Mod_Systems::WeatherReport(1);

            if (Mod_Systems::LessRandomInt("RandomDriver", 1, 4) < 2)
                PlayerDrives = false;

            FillVeh = true;

            if (Mod_Systems::LessRandomInt("RandomMod_Maths01", 1, 4) < 2)
            {
                MultiSpot.push_back(BeachBoat[Mod_Systems::LessRandomInt("RandomMod_Maths01a", 0, (int)BeachBoat.size() - 1)]);
                MultiSpot.push_back(BeachBoat[Mod_Systems::LessRandomInt("RandomMod_Maths01a", 0, (int)BeachBoat.size() - 1)]);
                Action = 1;
            }
            else
            {
                int iMultiStop = Mod_Systems::LessRandomInt("RandomMod_Maths01b", 0, (int)BeachLay.size() - 1);
                Mod_Class::Vector4 Vpos = BeachLay[iMultiStop];
                MultiSpot.push_back(Vpos);

                for (int i = 0; i < (int)BeachLay.size(); i++)
                {
                    if (Mod_Maths::DistanceTo(Vpos, BeachLay[i]) < 10.0f && i != iMultiStop)
                        MultiSpot.push_back(BeachLay[i]);
                }
                Action = 2;
            }
        }                 //Beach Ped
        else if (selectSen == 2)
        {
            int iW = 6;
            if (Mod_Data::CanSnow)
                iW = 11;

            Mod_Systems::WeatherReport(iW);

            if (Mod_Systems::LessRandomInt("RandomMod_Maths02", 1, 4) < 2)
            {
                TIME::SET_CLOCK_TIME(12, 0, 0);
                MySpot = TrampSign[Mod_Systems::LessRandomInt("RandomMod_Maths02a", 0, (int)TrampSign.size() - 1)];
                Action = 3;
            }           //HoldSign Tramp
            else
            {
                TIME::SET_CLOCK_TIME(3, 0, 0);
                MySpot = TrampSleap[Mod_Systems::LessRandomInt("RandomMod_Maths02b", 0, (int)TrampSleap.size() - 1)];
                Action = 4;
            }

            WeaponSet = 1;
        }            //Tramps
        else if (selectSen == 3)
        {
            TIME::SET_CLOCK_TIME(12, 0, 0);
            Mod_Systems::WeatherReport(1);
            Action = 8;
            MySpotFu = HighClass[Mod_Systems::LessRandomInt("RandomMod_Maths03", 0, (int)HighClass.size() - 1)];
            WeaponSet = 2;
        }            //High class
        else if (selectSen == 4)
        {
            Mod_Systems::RandomWeatherTime();
            Action = 8;
            MySpotFu = MidClass[Mod_Systems::LessRandomInt("RandomMod_Maths04", 0, (int)MidClass.size() - 1)];
            WeaponSet = 3;
        }            //Mid class
        else if (selectSen == 5)
        {
            int iW = 6;
            if (Mod_Data::CanSnow)
                iW = 11;

            Mod_Systems::WeatherReport(iW);

            Action = 8;
            MySpotFu = LowClass[Mod_Systems::LessRandomInt("RandomMod_Maths05", 0, (int)LowClass.size() - 1)];
            WeaponSet = 3;
        }            //Low class
        else if (selectSen == 6)
        {
            Mod_Systems::RandomWeatherTime();

            if (Mod_Systems::LessRandomInt("RandomMod_Maths06", 1, 4) < 2)
            {
                MySpot = Buisness[Mod_Systems::LessRandomInt("RandomMod_Maths06a", 0, (int)Buisness.size() - 1)];
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            else
            {
                int iRanLand = Mod_Systems::LessRandomInt("RandomMod_Maths06b", 0, (int)BuisnessHeli.size() - 1);
                Mod_Class::Vector4 Above = BuisnessHeli[iRanLand];
                Above.Z += 250.0f;
                MultiSpot = { Above , BuisnessHeli[iRanLand] };

                Heli = true;
                PlayerDrives = false;
                FillVeh = true;
                PlayerInVeh = true;
                Action = 1;
            }
            SubSet = 1;
        }            //Buisness
        else if (selectSen == 7)
        {
            TIME::SET_CLOCK_TIME(12, 0, 0);
            Mod_Systems::WeatherReport(1);

            SubSet = Mod_Systems::LessRandomInt("RandomMod_Maths07", 0, (int)BodyBeach.size() - 1);
            MySpot = BodyBeach[SubSet];
            Action = 5;
        }            //Body builder
        else if (selectSen == 8)
        {
            Mod_Systems::RandomWeatherTime();
            SubSet = Mod_Systems::LessRandomInt("RandomMod_Maths08", 1, 11);
            Action = 6;
            WeaponSet = 9;
        }            //GangStars             
        else if (selectSen == 9)
        {
            Mod_Systems::RandomWeatherTime();
            MySpot = Epslon[Mod_Systems::LessRandomInt("RandomMod_Maths09", 0, (int)Epslon.size() - 1)];
            Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }            //Epslon
        else if (selectSen == 10)
        {
            Mod_Systems::RandomWeatherTime();
            SubSet = Mod_Systems::LessRandomInt("RandomMod_Maths10", 1, 30);
            if (SubSet == 1)
                MultiSpot = Jogger01;
            else if (SubSet == 2)
                MultiSpot = Jogger02;
            else if (SubSet == 3)
                MultiSpot = Jogger03;
            else if (SubSet == 4)
                MultiSpot = Jogger04;
            else if (SubSet == 5)
                MultiSpot = Jogger05;
            else if (SubSet == 6)
                MultiSpot = Jogger06;
            else if (SubSet == 7)
                MultiSpot = Jogger07;
            else if (SubSet == 8)
                MultiSpot = Jogger08;
            else if (SubSet == 9)
                MultiSpot = Jogger09;
            else if (SubSet == 10)
                MultiSpot = Jogger10;
            else if (SubSet == 11)
                MultiSpot = Jogger11;
            else if (SubSet == 12)
                MultiSpot = Jogger12;
            else if (SubSet == 13)
                MultiSpot = Jogger13;
            else if (SubSet == 14)
                MultiSpot = Jogger14;
            else if (SubSet == 15)
                MultiSpot = Jogger15;
            else if (SubSet == 16)
                MultiSpot = Jogger16;
            else if (SubSet == 17)
                MultiSpot = Jogger17;
            else if (SubSet == 18)
                MultiSpot = Jogger18;
            else if (SubSet == 19)
                MultiSpot = Jogger19;
            else if (SubSet == 20)
                MultiSpot = Jogger20;
            else if (SubSet == 21)
                MultiSpot = Jogger21;
            else if (SubSet == 22)
                MultiSpot = Jogger22;
            else if (SubSet == 23)
                MultiSpot = Jogger23;
            else if (SubSet == 24)
                MultiSpot = Jogger24;
            else if (SubSet == 25)
                MultiSpot = Jogger25;
            else if (SubSet == 26)
                MultiSpot = Jogger26;
            else if (SubSet == 27)
                MultiSpot = Jogger27;
            else if (SubSet == 28)
                MultiSpot = Jogger28;
            else if (SubSet == 29)
                MultiSpot = Jogger29;
            else
                MultiSpot = Jogger30;

            Action = 7;
        }           //Jogger
        else if (selectSen == 11)
        {
            TIME::SET_CLOCK_TIME(12, 0, 0);
            Mod_Systems::WeatherReport(1);

            if (Mod_Systems::LessRandomInt("RandomMod_Maths11", 1, 4) < 2)
            {
                MultiSpot = GolfCaddy;
                FillVeh = true;
                RanDriveTo = Mod_Systems::LessRandomInt("RandomMod_Maths11b", 0, (int)GolfCaddy.size() - 1);
                Action = 1;
            }
            else
            {
                MySpot = GolfTee[Mod_Systems::LessRandomInt("RandomMod_Maths11a", 0, (int)GolfTee.size() - 1)];
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            WeaponSet = 6;
        }           //Golf
        else if (selectSen == 12)
        {
            TIME::SET_CLOCK_TIME(12, 0, 0);
            Mod_Systems::WeatherReport(1);

            MySpot = Hiker[Mod_Systems::LessRandomInt("RandomMod_Maths12", 0, (int)Hiker.size() - 1)];
            Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }           //Hiker
        else if (selectSen == 13)
        {
            Mod_Systems::RandomWeatherTime();
            MySpot = MethodActing[Mod_Systems::LessRandomInt("RandomMod_Maths13", 0, (int)MethodActing.size() - 1)];
            Action = 9;
            WeaponSet = 1;
        }           //Meth
        else if (selectSen == 14)
        {
            Mod_Systems::RandomWeatherTime();
            if (Mod_Systems::LessRandomInt("RandomMod_Maths12", 1, 4) < 2)
            {
                MySpot = FarmingVeh[Mod_Systems::LessRandomInt("RandomMod_Maths14a", 0, (int)FarmingVeh.size() - 1)];
                Action = 1;
            }
            else
            {
                MySpot = Farming[Mod_Systems::LessRandomInt("RandomMod_Maths14b", 0, (int)Farming.size() - 1)];
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            WeaponSet = 4;
        }           //Rural
        else if (selectSen == 15)
        {
            TIME::SET_CLOCK_TIME(12, 0, 0);
            Mod_Systems::WeatherReport(1);
            SubSet = Mod_Systems::LessRandomInt("RandomMod_Maths13", 1, 4);
            if (SubSet == 1)
                MultiSpot = CycleRacer;      //Racer
            else if (SubSet == 2)
                MultiSpot = CycleMountain;      //Mountain
            else if (SubSet == 3)
                MultiSpot = CycleBMX;      //BMX
            else
                MultiSpot = CycleCruser;      //Cruser

            RanDriveTo = Mod_Systems::LessRandomInt("RandomMod_Maths13a", 0, (int)MultiSpot.size() - 1);
            Action = 1;
        }           //Cycles
        else if (selectSen == 16)
        {
            TIME::SET_CLOCK_TIME(21, 0, 0);
            MySpot = LGBQWXYZ[Mod_Systems::LessRandomInt("RandomMod_Maths16", 0, (int)LGBQWXYZ.size() - 1)];
            Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }           //LGBTWXYZ
        else if (selectSen == 17)
        {
            TIME::SET_CLOCK_TIME(12, 0, 0);
            Mod_Systems::WeatherReport(1);
            if (Mod_Systems::LessRandomInt("RandomMod_Maths17", 0, 4) < 2)
            {
                MySpot = PoolPlace[Mod_Systems::LessRandomInt("RandomMod_Maths17a", 0, (int)PoolPlace.size() - 1)];
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            else
            {
                MySpot = BeachLounger[Mod_Systems::LessRandomInt("RandomMod_Maths17b", 0, (int)BeachLounger.size() - 1)];
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
                WAIT(1000);
                Action = 12;
            }
        }           //Pool Peds   
        else if (selectSen == 18)
        {
            Mod_Systems::RandomWeatherTime();

            SubSet = Mod_Systems::LessRandomInt("RandomMod_Maths18", 1, 23);
            if (SubSet == 1)
            {
                MySpot = Worker_Autoshop[Mod_Systems::LessRandomInt("RandomMod_Maths18a", 0, (int)Worker_Autoshop.size() - 1)];//"Autoshop Worker 2"); 
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            else if (SubSet == 2)
            {
                MySpot = Worker_Waiter[Mod_Systems::LessRandomInt("RandomMod_Maths18b", 0, (int)Worker_Waiter.size() - 1)];//"Waiter") ; 
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            else if (SubSet == 3)
            {
                MySpot = Worker_Sweatshop[Mod_Systems::LessRandomInt("RandomMod_Maths18c", 0, (int)Worker_Sweatshop.size() - 1)];//"Sweatshop Worker  
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            else if (SubSet == 4)
            {
                MySpot = Worker_Shopkeeper[Mod_Systems::LessRandomInt("RandomMod_Maths18d", 0, (int)Worker_Shopkeeper.size() - 1)];//"Shopkeeper (Male)"); 
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            else if (SubSet == 5)
            {
                MySpot = Worker_Doctor[Mod_Systems::LessRandomInt("RandomMod_Maths18e", 0, (int)Worker_Doctor.size() - 1)];//"Doctor"); 
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            else if (SubSet == 6)
            {
                MySpot = Worker_Maid[Mod_Systems::LessRandomInt("RandomMod_Maths18f", 0, (int)Worker_Maid.size() - 1)];//"Maid
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            else if (SubSet == 7)
            {
                if (NSPM_Include)
                {
                    NSPMLaunch = "" + Mod_Systems::GetDir() + "/scripts/NSPM/RequestGroupS.txt";
                    MySpot = GroupSixStarts[Mod_Systems::LessRandomInt("RandomMod_Maths18g1", 0, (int)GroupSixStarts.size() - 1)];
                }
                else
                {
                    MySpot = Worker_Security[Mod_Systems::LessRandomInt("RandomMod_Maths18g", 0, (int)Worker_Security.size() - 1)];
                    FillVeh = true;
                }
                Action = 1;
            }       //"Armoured Van Security 2"); 
            else if (SubSet == 8)
            {
                MySpot = Worker_Guard[Mod_Systems::LessRandomInt("RandomMod_Maths18h", 0, (int)Worker_Guard.size() - 1)];
                FillVeh = true;
                Action = 1;
            }       //"Security Guard"); 
            else if (SubSet == 9)
            {
                MySpot = Worker_Scientist[Mod_Systems::LessRandomInt("RandomMod_Maths18i", 0, (int)Worker_Scientist.size() - 1)];//"Scientist");  
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            else if (SubSet == 10)
            {
                MySpot = Worker_Chemical[Mod_Systems::LessRandomInt("RandomMod_Maths18j", 0, (int)Worker_Chemical.size() - 1)]; //"Chemical Plant Worker");  
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            else if (SubSet == 11)
            {
                MySpot = Worker_Construct[Mod_Systems::LessRandomInt("RandomMod_Maths18k", 0, (int)Worker_Construct.size() - 1)];
                Action = 1;
            }       //"construction Worker 2"); 
            else if (SubSet == 12)
            {
                MySpot = Worker_Dock[Mod_Systems::LessRandomInt("RandomMod_Maths18l", 0, (int)Worker_Dock.size() - 1)];
                Action = 1;
            }       //"Dock Worker");  
            else if (SubSet == 13)
            {
                MySpot = Worker_Airport[Mod_Systems::LessRandomInt("RandomMod_Maths18m", 0, (int)Worker_Airport.size() - 1)];
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
                MySpot = Worker_Handyman[Mod_Systems::LessRandomInt("RandomMod_Maths18n", 0, (int)Worker_Handyman.size() - 1)];
                Action = 10;
            }       //"Latino Handyman Male"); 
            else if (SubSet == 16)
            {
                MySpot = Worker_Metro[Mod_Systems::LessRandomInt("RandomMod_Maths18o", 0, (int)Worker_Metro.size() - 1)];//"LS Metro Worker Male");  
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            else if (SubSet == 17)
            {
                MySpot = Worker_Transport[Mod_Systems::LessRandomInt("RandomMod_Maths18p", 0, (int)Worker_Transport.size() - 1)];
                Action = 1;
            }       //"Transport Worker Male");  
            else if (SubSet == 18)
            {
                if (NSPM_Include)
                {
                    NSPMLaunch = "" + Mod_Systems::GetDir() + "/scripts/NSPM/RequestBugStart.txt";
                    MySpot = Mod_Class::Vector4(139.4768f, -3103.723f, 5.89631f, 353.8674f);//"Pest Control");  
                    Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
                }
                else
                {
                    MySpot = Mod_Class::Vector4(139.4768f, -3103.723f, 5.89631f, 353.8674f);//"Pest Control");  
                    Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
                }
            }
            else if (SubSet == 19)
            {
                MySpot = Worker_Postal[Mod_Systems::LessRandomInt("RandomMod_Maths18q", 0, (int)Worker_Postal.size() - 1)];
                Action = 1;
            }       //"Postal Worker Male 2");  
            else if (SubSet == 20)
            {
                if (NSPM_Include)
                {
                    NSPMLaunch = "" + Mod_Systems::GetDir() + "/scripts/NSPM/RequestDelivery.txt";
                    MySpot = DeliveryStarts[Mod_Systems::LessRandomInt("RandomMod_Maths18r1", 0, (int)DeliveryStarts.size() - 1)];
                }
                else
                {
                    MySpot = Worker_UPS[Mod_Systems::LessRandomInt("RandomMod_Maths18r", 0, (int)Worker_UPS.size() - 1)];
                }
                Action = 1;
            }       //"UPS Driver 2");
            else if (SubSet == 21)
            {
                MySpot = Worker_Vendor[Mod_Systems::LessRandomInt("RandomMod_Maths18s", 0, (int)Worker_Vendor.size() - 1)];//"Street Vendor Young");  
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }
            else if (SubSet == 22)
            {
                if (NSPM_Include)
                {
                    TIME::SET_CLOCK_TIME(18, 0, 0);
                    NSPMLaunch = "" + Mod_Systems::GetDir() + "/scripts/NSPM/RequestValey.txt";
                    MySpot = Mod_Class::Vector4(935.7204f, 46.89984f, 80.09576f, 125.0f);
                    Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
                    Mod_Systems::Write_ini(NSPMLaunch, std::vector<std::string>{"blank"});
                }
                else
                    MySpot = Mod_Class::Vector4(927.10f, 52.47f, 80.09f, 53.27f);
            }       //"Valet");  
            else
            {
                MySpot = Worker_Window[Mod_Systems::LessRandomInt("RandomMod_Maths18t", 0, (int)Worker_Window.size() - 1)];//"Window Cleaner");
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            }

        }           //Workers  
        else if (selectSen == 19)
        {
            TIME::SET_CLOCK_TIME(12, 0, 0);
            Mod_Systems::WeatherReport(1);

            MySpot = JetSki[Mod_Systems::LessRandomInt("RandomMod_Maths19", 0, (int)JetSki.size() - 1)];
            Action = 1;
        }           //jet ski Male                  
        else if (selectSen == 20)
        {
            TIME::SET_CLOCK_TIME(12, 0, 0);
            Mod_Systems::WeatherReport(1);

            SubSet = Mod_Systems::LessRandomInt("RandomMod_Maths20", 1, 4);
            if (SubSet == 1)
                MultiSpot = OffRoadRace01;
            else if (SubSet == 2)
                MultiSpot = OffRoadRace02;
            else if (SubSet == 3)
                MultiSpot = OffRoadRace03;
            else
                MultiSpot = OffRoadRace04;
            Action = 1;

            RanDriveTo = Mod_Systems::LessRandomInt("RandomMod_Maths20a", 0, (int)MultiSpot.size() - 1);
        }           //Bike/ATV Male
        else if (selectSen == 21)
        {
            Mod_Systems::RandomWeatherTime();

            SubSet = Mod_Systems::LessRandomInt("RandomMod_Maths21", 1, 11);

            if (SubSet == 1)
            {
                TIME::SET_CLOCK_TIME(12, 0, 0);
                Mod_Systems::WeatherReport(1);

                MySpot = Service_Baywatch[Mod_Systems::LessRandomInt("RandomMod_Maths21a", 0, (int)Service_Baywatch.size() - 1)];
                Action = 1;
                if (NSPM_Include)
                {
                    NSPMLaunch = "" + Mod_Systems::GetDir() + "/scripts/NSPM/RequestSharks.txt";
                    Mod_Systems::Write_ini(NSPMLaunch, std::vector<std::string>{"blank"});
                }
                WeaponSet = 1;
            }            //"Baywatch 
            else if (SubSet == 2)
            {
                MySpot = Service_Coastguard[Mod_Systems::LessRandomInt("RandomMod_Maths21b", 0, (int)Service_Coastguard.size() - 1)];
                FillVeh = true;
                Mod_Data::Deputize = true;
                Action = 1;
            }       //"US Coastguard
            else if (SubSet == 3)
            {
                MultiSpot = CopsOnPatrol;
                //MySpot = Service_Cops[Mod_Systems::LessRandomInt("RandomMod_Maths21c", 0, (int)Service_Cops.size() - 1)];
                RanDriveTo = Mod_Systems::LessRandomInt("RandomMod_Maths20a", 0, (int)MultiSpot.size() - 1);
                FillVeh = true;
                Mod_Data::Deputize = true;
                PlayerDrives = false;
                Action = 1;
            }       //><!--Cops
            else if (SubSet == 4)
            {
                MySpot = Service_CopsBike[Mod_Systems::LessRandomInt("RandomMod_Maths21d", 0, (int)Service_CopsBike.size() - 1)];
                Mod_Data::Deputize = true;
                Action = 1;
            }       //><!-- PoliceBike
            else if (SubSet == 5)
            {
                MultiSpot = RangersOnPatrol;
                //MySpot = Service_CopsRanger[Mod_Systems::LessRandomInt("RandomMod_Maths21e", 0, (int)Service_CopsRanger.size() - 1)];
                RanDriveTo = Mod_Systems::LessRandomInt("RandomMod_Maths20a", 0, (int)MultiSpot.size() - 1);
                FillVeh = true;
                Mod_Data::Deputize = true;
                PlayerDrives = false;
                Action = 1;
            }       //><!-- Ranger
            else if (SubSet == 6)
            {
                MultiSpot = CopsOnPatrol;
                //MySpot = Service_Sherif[Mod_Systems::LessRandomInt("RandomMod_Maths21f", 0, (int)Service_Sherif.size() - 1)];
                RanDriveTo = Mod_Systems::LessRandomInt("RandomMod_Maths20a", 0, (int)MultiSpot.size() - 1);
                FillVeh = true;
                Mod_Data::Deputize = true;
                PlayerDrives = false;
                Action = 1;
            }       //><!-- Sherif
            else if (SubSet == 7)
            {
                MySpot = Service_Fib[Mod_Systems::LessRandomInt("RandomMod_Maths21g", 0, (int)Service_Fib.size() - 1)];
                FillVeh = true;
                Mod_Data::Deputize = true;
                Action = 1;
            }       //><!-- fib
            else if (SubSet == 8)
            {
                MySpot = Service_Swat[Mod_Systems::LessRandomInt("RandomMod_Maths21h", 0, (int)Service_Swat.size() - 1)];
                FillVeh = true;
                Mod_Data::Deputize = true;
                Action = 1;
            }       //><!-- swat
            else if (SubSet == 9)
            {
                MySpot = Service_Military[Mod_Systems::LessRandomInt("RandomMod_Maths21i", 0, (int)Service_Military.size() - 1)];
                FillVeh = true;
                Mod_Data::Deputize = true;
                Action = 1;
                AccessAllAreas(true);
            }       //military
            else if (SubSet == 10)
            {
                if (NSPM_Include)
                {
                    NSPMLaunch = "" + Mod_Systems::GetDir() + "/scripts/NSPM/RequestMedic.txt";
                    MySpot = AmbulanceStarts[Mod_Systems::LessRandomInt("RandomMod_Maths21j2", 0, (int)AmbulanceStarts.size() - 1)];

                }
                else
                    MySpot = Service_Medic[Mod_Systems::LessRandomInt("RandomMod_Maths21j", 0, (int)Service_Medic.size() - 1)];

                Action = 1;
            }      //medic
            else
            {
                if (NSPM_Include)
                {
                    NSPMLaunch = "" + Mod_Systems::GetDir() + "/scripts/NSPM/RequestFire.txt";
                    MySpot = FireStarts[Mod_Systems::LessRandomInt("RandomMod_Maths21k1", 0, (int)FireStarts.size() - 1)];
                }
                else
                {
                    MySpot = Service_Fireman[Mod_Systems::LessRandomInt("RandomMod_Maths21k", 0, (int)Service_Fireman.size() - 1)];
                    FillVeh = true;
                }
                Action = 1;

                Mod_Data::Deputize = true;
            }      //fireman
        }           //Services 
        else if (selectSen == 22)
        {
            Mod_Systems::RandomWeatherTime();

            SubSet = Mod_Systems::LessRandomInt("RandomMod_Maths22", 1, 4);

            if (SubSet == 1)
            {
                MultiSpot.push_back(Flight_Civi[Mod_Systems::LessRandomInt("RandomMod_Maths22a", 0, (int)Flight_Civi.size() - 1)]);
                MultiSpot.push_back(Mod_Class::Vector4(-2352.11f, 2274.94f, 1500.0f, 0.0f));
                Plane = true;
                FillVeh = true;
                Action = 1;
            }       //civilian
            else if (SubSet == 2)
            {
                MultiSpot.push_back(Flight_Milatary[Mod_Systems::LessRandomInt("RandomMod_Maths22b", 0, (int)Flight_Milatary.size() - 1)]);
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
                RanDriveTo = Mod_Systems::LessRandomInt("RandomMod_Maths22c", 0, (int)MultiSpot.size() - 1);
            }       //helitours
            else
            {
                MultiSpot = Flight_HeliPaleto;
                Heli = true;
                FillVeh = true;
                Action = 1;
                RanDriveTo = Mod_Systems::LessRandomInt("RandomMod_Maths22d", 0, (int)MultiSpot.size() - 1);
            }      //PaletoHeli
        }           //Pilot
        else if (selectSen == 23)
        {
            Mod_Systems::RandomWeatherTime();

            if (!Mod_Data::Mod_Settings.Random_Ped || Mod_Data::Mod_Settings.Saved_Ped)
                SubSet = Mod_Systems::LessRandomInt("RandomMod_Maths23a", 1, 11);
            else
                SubSet = Mod_Systems::LessRandomInt("RandomMod_Maths23b", 1, 14);

            if (SubSet == 1)
                MySpot = Animals_Boar[Mod_Systems::LessRandomInt("RandomMod_Maths23c", 0, (int)Animals_Boar.size() - 1)];//a_c_boar
            else if (SubSet == 2)
                MySpot = Animals_CatsDogs[Mod_Systems::LessRandomInt("RandomMod_Maths23d", 0, (int)Animals_CatsDogs.size() - 1)];//cats/dogs
            else if (SubSet == 3)
                MySpot = Animals_Pigeon[Mod_Systems::LessRandomInt("RandomMod_Maths23e", 0, (int)Animals_Pigeon.size() - 1)];//a_c_pigeon
            else if (SubSet == 4)
                MySpot = Animals_Rat[Mod_Systems::LessRandomInt("RandomMod_Maths23f", 0, (int)Animals_Rat.size() - 1)];//a_c_rat
            else if (SubSet == 5)
                MySpot = Animals_Cow[Mod_Systems::LessRandomInt("RandomMod_Maths23g", 0, (int)Animals_Cow.size() - 1)];//a_c_cow
            else if (SubSet == 6)
                MySpot = Animals_Coyote[Mod_Systems::LessRandomInt("RandomMod_Maths23h", 0, (int)Animals_Coyote.size() - 1)];//a_c_coyote
            else if (SubSet == 7)
                MySpot = Animals_Crow[Mod_Systems::LessRandomInt("RandomMod_Maths23i", 0, (int)Animals_Crow.size() - 1)];//a_c_crow
            else if (SubSet == 8)
                MySpot = Animals_DeerRabit[Mod_Systems::LessRandomInt("RandomMod_Maths23j", 0, (int)Animals_DeerRabit.size() - 1)];//a_c_deer/a_c_rabbit_01
            else if (SubSet == 9)
                MySpot = Animals_Hen[Mod_Systems::LessRandomInt("RandomMod_Maths23k", 0, (int)Animals_Hen.size() - 1)];//a_c_hen                
            else if (SubSet == 10)
                MySpot = Animals_Lion[Mod_Systems::LessRandomInt("RandomMod_Maths23l", 0, (int)Animals_Lion.size() - 1)];//a_c_mtlion-mountain lion
            else if (SubSet == 11)
                MySpot = Animals_Pig[Mod_Systems::LessRandomInt("RandomMod_Maths23m", 0, (int)Animals_Pig.size() - 1)];//a_c_pig
            else if (SubSet == 12)
                MySpot = Animals_Fish[Mod_Systems::LessRandomInt("RandomMod_Maths23n", 0, (int)Animals_Fish.size() - 1)];//Fish/sharks
            else if (SubSet == 13)
                MySpot = Animals_Hawk[Mod_Systems::LessRandomInt("RandomMod_Maths23o", 0, (int)Animals_Hawk.size() - 1)];//a_c_chickenhawk
            else
                MySpot = Animals_Corm[Mod_Systems::LessRandomInt("RandomMod_Maths23p", 0, (int)Animals_Corm.size() - 1)];//a_c_cormorant

            Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }           //Animals
        else if (selectSen == 24)
        {
            Mod_Systems::WeatherReport(Mod_Systems::RandomInt(10, 13));

            if (Mod_Systems::LessRandomInt("RandomMod_Maths24", 1, 4) < 2)
                MySpot = Mod_Data::Yankton[Mod_Systems::LessRandomInt("RandomMod_Maths24a", 0, (int)Mod_Data::Yankton.size() - 1)];
            else
            {
                MySpot = YanktonVeh[Mod_Systems::LessRandomInt("RandomMod_Maths24b", 0, (int)YanktonVeh.size() - 1)];
                Action = 1;
            }
            WeaponSet = 5;

            if (!Mod_Data::Yankton_Loaded)
                IplFail = Mod_Maths::YanktonIPL();
            if (!IplFail)
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
        }           //North Yankton
        else if (selectSen == 25)
        {
            TIME::SET_CLOCK_TIME(12, 0, 0);
            Mod_Systems::WeatherReport(1);

            SubSet = Mod_Systems::LessRandomInt("RandomMod_Maths25", 1, 6);
            if (SubSet == 1)
            {
                MySpot = Mod_Class::Vector4(4979.349f, -5764.603f, 20.87796f, 45.00f);//A_C_Panther
            }
            else if (SubSet == 2)
            {
                MySpot = Cayo_Beach[Mod_Systems::LessRandomInt("RandomMod_Maths25a", 0, (int)Cayo_Beach.size() - 1)];
                Action = 11;
            }       //A_F_Y_Beach_02
            else if (SubSet == 3)
            {
                if (Mod_Systems::LessRandomInt("RandomMod_Maths31", 1, 4) < 2)
                    MySpot = Cayo_Guard[Mod_Systems::LessRandomInt("RandomMod_Maths25b", 0, (int)Cayo_Guard.size() - 1)];
                else
                {
                    MySpot = Cayo_GuardVeh[Mod_Systems::LessRandomInt("RandomMod_Maths25c", 0, (int)Cayo_GuardVeh.size() - 1)];
                    Action = 1;
                }
                WeaponSet = 5;
            }       //Guard
            else if (SubSet == 4)
                MySpot = Mod_Class::Vector4(4904.958f, -4941.593f, 3.378354f, 37.49379f); //Bar
            else if (SubSet == 5)
                MySpot = Cayo_Workers[Mod_Systems::LessRandomInt("RandomMod_Maths25d", 0, (int)Cayo_Workers.size() - 1)];//worker
            else if (SubSet == 6)
            {
                MySpot = Mod_Class::Vector4(4499.6f, -4523.962f, 4.412367f, 276.4212f);
                Action = 12;
            }       //pilot
            else
                MySpot = Mod_Class::Vector4(4877.928f, -4488.06f, 26.93383f, 7.88381f);//randomOther??


            if (!Mod_Data::Cayo_Loaded)
                IplFail = Mod_Maths::CayoPericoIPL();

            if (!IplFail)
            {
                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
                Mod_Entitys::CayoPartay();
            }
        }                              //Cayo Perico

        Mod_Systems::LoggerLight("RandomLocation SubSet == " + std::to_string(SubSet));
    }

    CAM::DO_SCREEN_FADE_IN(3000);

    if (IplFail)
        RandomLocation(1);
    else
    {
        int MySaved = -1;

        if (Mod_Data::Mod_Settings.Random_Ped)
        {
            if (selectSen > 0)
                Mod_Entitys::ChangePlayer(selectSen, SubSet, WeaponSet);
            else
                Mod_Entitys::ChangePlayer(Mod_Systems::LessRandomInt("NoAutoPlayRp", 1, 18), -1, WeaponSet);
        }
        else if (Mod_Data::Mod_Settings.Saved_Ped && (int)Mod_Data::SavedPeds.size() > 1)
        {
            MySaved = Mod_Systems::LessRandomInt("SavedPedFind", 1, (int)Mod_Data::SavedPeds.size() - 1);
            Mod_Entitys::SavedPlayer(&Mod_Data::SavedPeds[MySaved], WeaponSet);
        }

        if (MySaved != -1)
        {
            if (Mod_Data::SavedPeds[MySaved].Animal_Farm)
            {
                Action = 0;
                Mod_Data::Deputize = false;
                if (!Mod_Data::Yankton_Loaded && !Mod_Data::Cayo_Loaded)
                    Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), Animals_Boar[Mod_Systems::LessRandomInt("RandomMod_Maths23c", 0, (int)Animals_Boar.size() - 1)]);
            }
        }

        if (Mod_Data::Deputize)
            Mod_Entitys::PoliceAcadamy(Mod_Data::Deputize);

        if (Action == 1)
        {
            Vehicle Vbob = NULL;
            std::string Car = Mod_Entitys::RandVeh(selectSen, SubSet);
            Mod_Class::Veh_Set MyVehSet = Mod_Class::Veh_Set(Car, Plane, Heli, PlayerInVeh, PlayerDrives, FillVeh, selectSen, SubSet, MySpot, { });
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

                Vbob = Mod_Entitys::VehicleSpawn(MyVehSet);
            }
            else
                Vbob = Mod_Entitys::VehicleSpawn(MyVehSet);

            if (PlayerDrives && Vbob != NULL)
                VEHICLE::_0xCFD778E7904C255E((Any)Vbob);

            if (NSPMLaunch != "")
                Mod_Systems::Write_ini(NSPMLaunch, std::vector<std::string>{ std::to_string((int)Vbob)});

            GotClutter = true;
        }//DriveVeh
        else if (Action == 2)
        {
            if ((int)MultiSpot.size() > 1)
            {
                bool btrue = true;
                for (int i = 1; i < (int)MultiSpot.size(); i++)
                {
                    btrue = !btrue;
                    Ped Peddy = Mod_Entitys::PlayerPedGen(MultiSpot[i], selectSen, SubSet, true, true);
                    Mod_Entitys::SunningIt(Peddy, MultiSpot[i]);
                }
            }

            Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MultiSpot[0]);

            int iPose = Mod_Systems::LessRandomInt("RandsAction2", 0, 20);
            if (iPose < 10)
            {
                if (PED::IS_PED_MALE(PLAYER::PLAYER_PED_ID()))
                    Mod_Entitys::RunAnimSeq(Mod_Data::SunbathebackM, MultiSpot[0]);
                else
                    Mod_Entitys::RunAnimSeq(Mod_Data::SunbathebackF, MultiSpot[0]);
            }
            else
            {
                if (PED::IS_PED_MALE(PLAYER::PLAYER_PED_ID()))
                    Mod_Entitys::RunAnimSeq(Mod_Data::SunbathefrontM, MultiSpot[0]);
                else
                    Mod_Entitys::RunAnimSeq(Mod_Data::SunbathefrontF, MultiSpot[0]);
            }

            GotClutter = true;
        }//SunBath
        else if (Action == 3)
        {
            Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            GAMEPLAY::POPULATE_NOW();
            Prop Sign = Mod_Entitys::BuildProps(TrampSigns[Mod_Systems::LessRandomInt("TrampSign", 0, (int)TrampSigns.size() - 1)], MySpot, false, false);
            ENTITY::ATTACH_ENTITY_TO_ENTITY(Sign, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), 28422), 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, false, false, true, false, 2, true);
            Mod_Entitys::RunAnimSeq(Mod_Class::AnimList(Mod_Class::AnimatedActions("amb@lo_res_idles@", "world_human_bum_freeway_lo_res_base"), Mod_Class::AnimatedActions("amb@prop_human_bum_bin@exit", "exit"), {}), MySpot);
            ENTITY::DETACH_ENTITY(Sign, 0, 0);
            Mod_Entitys::ClearAllEntitys(false);
            //dettachsign
        }//TrampSign
        else if (Action == 4)
        {
            Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            GAMEPLAY::POPULATE_NOW();
            Mod_Entitys::RunAnimSeq(Mod_Class::AnimList(Mod_Class::AnimatedActions("switch@trevor@scares_tramp", "trev_scares_tramp_idle_tramp"), Mod_Class::AnimatedActions("switch@trevor@scares_tramp", "trev_scares_tramp_exit_tramp"), {}), MySpot);
        }//TrampSleap
        else if (Action == 5)
        {
            Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            PED::SET_PED_SWEAT(PLAYER::PLAYER_PED_ID(), 99.0f);
            GAMEPLAY::POPULATE_NOW();
            if (SubSet == 0)
                Mod_Entitys::ForceSenario("PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", MySpot, true);
            else if (SubSet < 3)
                Mod_Entitys::ForceSenario("PROP_HUMAN_MUSCLE_CHIN_UPS", MySpot, false);
            else
            {
                int iPose = Mod_Systems::LessRandomInt("RandsAction5", 0, 30);
                if (iPose < 10)
                    Mod_Entitys::RunAnimSeq(Mod_Data::SitUps, MySpot);
                else if (iPose < 20)
                    Mod_Entitys::ForceSenario("WORLD_HUMAN_MUSCLE_FREE_WEIGHTS", MySpot, false);
                else
                    Mod_Entitys::RunAnimSeq(Mod_Data::PushUps, MySpot);
            }
        }
        else if (Action == 6)
        {
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
                    Mod_Entitys::PlayerPedGen(GStars[i], selectSen, SubSet, true, true);

                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("VIRGO2", false, false, true, true, true, selectSen, SubSet, Mod_Class::Vector4(-286.2027f, 311.9702f, 92.69145f, 358.9505f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("CHINO2", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(-282.5865f, 324.6772f, 92.68803f, 183.9263f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("FACTION3", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(-274.7456f, 324.9384f, 92.69529f, 179.5375f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("BUCCANEER2", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(-275.7558f, 312.8728f, 92.68794f, 19.96654f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("MINIVAN2", false, false, false, false, true, selectSen, 8, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                Mod_Entitys::VehicleSpawn(Att);
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
                    Mod_Entitys::PlayerPedGen(GStars[i], selectSen, SubSet, true, true);

                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("SULTAN", false, false, true, true, true, selectSen, SubSet, Mod_Class::Vector4(-458.0122f, -1719.43f, 18.08753f, 336.3535f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("FORKLIFT", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(-424.3365f, -1688.027f, 18.49347f, 162.8363f), {}));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("FBI2", false, false, false, false, true, 21, 9, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                Mod_Entitys::VehicleSpawn(Att);
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
                    Mod_Entitys::PlayerPedGen(GStars[i], selectSen, SubSet, true, true);

                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("EMPEROR", false, false, true, true, true, selectSen, SubSet, Mod_Class::Vector4(100.9958f, -1929.075f, 19.88203f, 160.4151f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("PEYOTE", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(113.7581f, -1939.326f, 19.91485f, 116.716f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("MANANA", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(106.8031f, -1949.032f, 19.91415f, 15.96025f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("VOODOO", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(97.78821f, -1944.386f, 19.94981f, 312.7894f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("BALLER", false, false, false, false, true, selectSen, 5, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                Mod_Entitys::VehicleSpawn(Att);

                Hash ThisGp = Mod_Systems::MyHashKey("AMBIENT_GANG_BALLAS");
                Mod_Entitys::SetRelBetween_Gp(ThisGp, Mod_Data::GP_Player, 0);
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
                    Mod_Entitys::PlayerPedGen(GStars[i], selectSen, SubSet, true, true);

                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), Mod_Class::Vector4(458.5448f, -735.9688f, 27.35763f, 204.9358f));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("BURRITO", false, false, false, false, true, selectSen, 6, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                Mod_Entitys::VehicleSpawn(Att);
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
                    Mod_Entitys::PlayerPedGen(GStars[i], selectSen, SubSet, true, true);

                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("BALLER", false, false, true, true, true, selectSen, SubSet, Mod_Class::Vector4(-224.047f, -1487.307f, 30.99617f, 140.3711f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("TORNADO2", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(-218.7061f, -1491.246f, 30.95563f, 139.3282f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("BALLER", false, false, false, false, true, selectSen, 3, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                Mod_Entitys::VehicleSpawn(Att);

                Hash ThisGp = Mod_Systems::MyHashKey("AMBIENT_GANG_FAMILY");
                Mod_Entitys::SetRelBetween_Gp(ThisGp, Mod_Data::GP_Player, 0);
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
                    Mod_Entitys::PlayerPedGen(GStars[i], selectSen, SubSet, true, true);

                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("KURUMA", false, false, true, true, true, selectSen, SubSet, Mod_Class::Vector4(-755.6411f, -1035.036f, 12.59574f, 118.859f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("ELEGY", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(-737.267f, -1032.804f, 12.42186f, 299.1285f), { }));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("FUTO", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(-751.9888f, -1041.709f, 12.31588f, 116.6273f), { }));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("FUTO", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(-741.7025f, -1045.407f, 12.05153f, 23.04387f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("BALLER", false, false, false, false, true, selectSen, 4, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                Mod_Entitys::VehicleSpawn(Att);
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
                    Mod_Entitys::PlayerPedGen(GStars[i], selectSen, SubSet, true, true);

                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("ELEGY", false, false, true, true, true, selectSen, SubSet, Mod_Class::Vector4(323.1364f, -2023.899f, 20.57834f, 143.4038f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("FUTO", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(320.1991f, -2034.714f, 20.33097f, 323.2342f), { }));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("KURUMA", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(329.5031f, -2030.321f, 20.78702f, 141.8689f), { }));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("Z190", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(336.029f, -2037.448f, 20.90948f, 90.30424f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("RUMPO3", false, false, false, false, true, selectSen, 9, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                Mod_Entitys::VehicleSpawn(Att);

                Hash ThisGp = Mod_Systems::MyHashKey("AMBIENT_GANG_MEXICAN");
                Mod_Entitys::SetRelBetween_Gp(ThisGp, Mod_Data::GP_Player, 0);
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
                    Mod_Entitys::PlayerPedGen(GStars[i], selectSen, SubSet, true, true);

                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("PANTO", false, false, true, true, true, selectSen, SubSet, Mod_Class::Vector4(-753.3419f, 5531.84f, 33.00214f, 31.34572f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("RHAPSODY", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(-747.302f, 5535.622f, 33.00214f, 28.5319f), { }));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("BRIOSO", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(-759.3707f, 5547.82f, 33.00235f, 177.4559f), { }));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("BLISTA3", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(-752.3031f, 5547.335f, 33.00233f, 177.423f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("SLAMVAN2", false, false, false, false, true, selectSen, 10, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                Mod_Entitys::VehicleSpawn(Att);
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
                    Mod_Entitys::PlayerPedGen(GStars[i], selectSen, SubSet, true, true);

                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("MANANA", false, false, true, true, true, selectSen, SubSet, Mod_Class::Vector4(1166.919f, -1643.647f, 36.44419f, 177.7492f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("REBEL", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(1154.781f, -1657.428f, 36.08745f, 116.5546f), { }));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("PEYOTE", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(1157.266f, -1661.953f, 36.12128f, 117.0901f), { }));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("TORNADO2", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(1153.491f, -1650.302f, 36.03091f, 28.40678f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("RUMPO3", false, false, false, false, true, selectSen, 7, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                Mod_Entitys::VehicleSpawn(Att);

                Hash ThisGp = Mod_Systems::MyHashKey("AMBIENT_GANG_SALVA");
                Mod_Entitys::SetRelBetween_Gp(ThisGp, Mod_Data::GP_Player, 0);
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
                    Mod_Entitys::PlayerPedGen(GStars[i], selectSen, SubSet, true, true);

                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("DAEMON2", false, false, true, true, true, selectSen, SubSet, Mod_Class::Vector4(981.2489f, -128.9782f, 73.09866f, 63.50796f), {}));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("GARGOYLE", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(965.4485f, -119.1682f, 73.82195f, 216.7741f), { }));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("CLIFFHANGER", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(971.0372f, -115.0153f, 73.82298f, 218.4778f), { }));
                Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set("DAEMON", false, false, false, false, true, selectSen, SubSet, Mod_Class::Vector4(979.4431f, -133.8394f, 72.97166f, 62.28038f), { }));
                Mod_Class::Veh_Set Att = Mod_Class::Veh_Set("MOONBEAM2", false, false, false, false, true, selectSen, 1, GangstarDriveFrom, { GangstarDriveFrom, GangstarDriveTo });
                Att.bFriend = false;
                Mod_Entitys::VehicleSpawn(Att);

                Hash ThisGp = Mod_Systems::MyHashKey("AMBIENT_GANG_LOST");
                Mod_Entitys::SetRelBetween_Gp(ThisGp, Mod_Data::GP_Player, 0);
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
                int iLocate = Mod_Systems::LessRandomInt("RandomMod_Maths08Sub11", 0, (int)GStars.size() - 1);

                Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), GStars[iLocate]);
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
                    int iGran = Mod_Systems::LessRandomInt("GranSub11", 0, (int)OldD.size() - 1);
                    Mod_Class::ClothBank Cbank = Mod_Class::ClothBank("", OldD[iGran], -1, false, Mod_Entitys::AddFace(false), false, false, Mod_Class::HairSets(0, 0, "H_FMM_0_0", "Close Shave", -1, -1), 0, 0, 0, 0, {}, {}, {}, {}, {}, 0, 0, 0, 200, 1.0f, 1.0f);
                    Ped Deary = Mod_Entitys::PlayerPedGen(Mod_Maths::NearByStreet(GStars[iLocate]), &Cbank, true, false);
                    Mod_Entitys::FightPlayer(Deary, false, 0);
                    WEAPON::REMOVE_ALL_PED_WEAPONS(Deary, false);
                    Mod_Entitys::GunningIt(Deary, 1);
                }
            }           //Street Punk-- Vs Old Ladys

            GotClutter = true;
        }       //GangStar--Fixup..
        else if (Action == 7)
        {
            PED::SET_PED_SWEAT(PLAYER::PLAYER_PED_ID(), 99.0f);
            Mod_Entitys::JogOn(MultiSpot, Mod_Systems::RandomInt(0, (int)MultiSpot.size() - 1));
        }       //JogOn
        else if (Action == 8)
        {
            std::string Car = Mod_Entitys::RandVeh(selectSen, SubSet);
            Vehicle Vic = Mod_Entitys::VehicleSpawn(Mod_Class::Veh_Set(Car, false, false, false, false, false, selectSen, SubSet, MySpotFu.Car, { }));
            int iPose = Mod_Systems::LessRandomInt("RandsAction8", 0, 20);
            if (iPose < 10)
            {
                int iStart = 0;
                int iSeating = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(Vic);

                for (int i = iStart; i < iSeating; i++)
                {
                    Mod_Systems::LoggerLight("Fill Vehicle with peds");
                    Ped CarPed = Mod_Entitys::PlayerPedGen(MySpotFu.Car, selectSen, SubSet, false, true);
                    // Wtf Is this doing here????---Mod_Entitys::SavedPlayer(&Mod_Data::SavedPeds[MySaved], WeaponSet);
                    PED::SET_PED_CAN_BE_DRAGGED_OUT(CarPed, false);
                    Mod_Entitys::WarptoAnyVeh(Vic, CarPed, i);
                }
            }
            Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpotFu.Ped);
            WAIT(1000);
            Mod_Entitys::GetInVehicle(PLAYER::PLAYER_PED_ID(), Vic, Seat, true);
            WAIT(1000);
            GotClutter = true;
        }       //EnterVehicle
        else if (Action == 9)
        {
            Mod_Systems::RandomWeatherTime();
            Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            Mod_Data::Meth_Act = true;
            Mod_Entitys::MethEdd(Mod_Data::Meth_Act);
        }      //MethActing
        else if (Action == 10)
        {
            Mod_Entitys::MoveEntity(PLAYER::PLAYER_PED_ID(), MySpot);
            Mod_Entitys::ForceSenario("WORLD_HUMAN_GARDENER_PLANT", MySpot, false);
        }
        else if (Action == 11)
        {

        }      //Dancing
        else if (Action == 12)
        {
            WAIT(1000);
            std::vector<std::string> Hashes = {
                "prop_patio_lounger1",
                "prop_patio_lounger_2",
                "prop_patio_lounger_3"
            };
            Entity SunL = NULL;
            int i = 0;
            for (; i < (int)Hashes.size(); i++)
            {
                SunL = Mod_Entitys::FindingProps(MySpot, 20.0f, Hashes[i]);
                if (SunL != NULL)
                    break;
            }

            if (SunL != NULL)
            {
                ENTITY::FREEZE_ENTITY_POSITION(SunL, true);
                Mod_Class::Vector4 SunPos = Mod_Maths::GetPosV4(SunL);
                Ped outPed = Mod_Entitys::NearByPed(SunPos, 0.0f, 2.0f);

                if (outPed != NULL)
                    ENTITY::DELETE_ENTITY(&outPed);

                if (i == 0)
                {
                    Vector3 VPos = Mod_Maths::FowardOf(SunL, 0.255f, false);
                    SunPos.X = VPos.x;
                    SunPos.Y = VPos.y;
                }
                else if (i == 1)
                {
                    Vector3 VPos = Mod_Maths::FowardOf(SunL, 0.255f, true);
                    SunPos.X = VPos.x;
                    SunPos.Y = VPos.y;
                    SunPos.Z += 0.16f;
                }
                SunPos.R -= 180.0f;
                SunPos.Z += 0.32f;
                Mod_Entitys::ForceSenario("PROP_HUMAN_SEAT_SUNLOUNGER", SunPos, true);
            }
        }     //Sitting-SunLounger
        else if (Action == 13)
        {
            Vehicle Vbob = NULL;
            std::string Car = Mod_Entitys::RandVeh(selectSen, SubSet);
            Mod_Class::Veh_Set MyVehSet = Mod_Class::Veh_Set(Car, Plane, Heli, PlayerInVeh, PlayerDrives, FillVeh, selectSen, SubSet, MySpot, { });
            Vbob = Mod_Entitys::VehicleSpawn(MyVehSet);

            int iSeating = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(Vbob);

            for (int i = -1; i < iSeating - 1; i++)
            {
                Mod_Systems::LoggerLight("Fill Vehicle with peds");
                Ped CarPed = Mod_Entitys::PlayerPedGen(MySpot, selectSen, SubSet, false, true);
                PED::SET_PED_CAN_BE_DRAGGED_OUT(CarPed, false);
                Mod_Entitys::WarptoAnyVeh(Vbob, CarPed, i);
            }
            Mod_Entitys::WarptoAnyVeh(Vbob, PLAYER::PLAYER_PED_ID(), iSeating - 1);
            AI::TASK_VEHICLE_DRIVE_WANDER(VEHICLE::GET_PED_IN_VEHICLE_SEAT(Vbob, -1), Vbob, 12.0f, 1);

            GotClutter = true;
        }
    }
}
void RandomStart()
{
    Mod_Systems::LoggerLight("RandomStart");
    WAIT(4000);
    CAM::DO_SCREEN_FADE_OUT(4000);
    RandomLocation(-1);

    if (Mod_Systems::File_exists(Mod_Systems::GetDir() + "/scripts/HeadCam.dll"))
        CAM::SET_FOLLOW_PED_CAM_VIEW_MODE(2);
}

Mod_Class::ClothBank MyNewBank = Mod_Class::ClothBank();
Mod_Class::ClothBank ProTag = Mod_Class::ClothBank();
void KeyCapture()
{
    Rs_MenuList.clear();
    Mod_Data::Mod_Settings.MenuKey = Mod_Systems::FindKeyBinds(false);
    if (Mod_Data::Mod_Settings.MenuKey == -1)
        Mod_Data::Mod_Settings.MenuKey = 55;

    WAIT(2000);
}
void ControlerCapture()
{
    Rs_MenuList.clear();
    Mod_Data::Mod_Settings.ControlA = Mod_Systems::FindKeyBinds(true);
    Mod_Data::Mod_Settings.ControlB = Mod_Systems::FindKeyBinds(true);

    if (Mod_Data::Mod_Settings.ControlA != -1 && Mod_Data::Mod_Settings.ControlB != -1)
        Mod_Data::Mod_Settings.ControlSupport = true;

    WAIT(2000);
}
void WeaponCapture()
{
    Rs_MenuList.clear();
    if (Mod_Systems::File_exists(Mod_Systems::GetDir() + "/RandomStart/MyWeaps.ini"))
        Mod_Data::Player_Weaps = Mod_Systems::LoadSavedWeapons();
    else
    {
        Mod_Data::Player_Weaps.clear();
        Mod_Data::Player_Weaps = Mod_Systems::BuildWeaponList();
        Mod_Systems::SaveMyWeaps();
    }
}
void MenuSideSwap()
{
    if (Mod_Data::Mod_Settings.Menu_Left_Side)
        GVM::DefaultRatio.MenuLeftSide();
    else
        GVM::DefaultRatio.MenuRightSide();

}
int iPedMale = 0;
void NewRandomFreePed(int male)
{
    if (Rs_MenuList.size() > 0)
        Rs_MenuList.pop_back();

    MyNewBank = Mod_Entitys::NewFreeModePed(male);
    Mod_Entitys::SavedPlayer(&MyNewBank, -1);

    Rs_Pedditor(&MyNewBank);
}
void OutfitChange(void* obj)
{
    Mod_Systems::LoggerLight("OutfitChange");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
        Mod_Entitys::ApplyTats(PLAYER::PLAYER_PED_ID(), thisPed);

        Mod_Entitys::OnlineDress(PLAYER::PLAYER_PED_ID(), &thisPed->Cothing[thisPed->Cloth_Pick]);

        if (thisPed->FreeMode)
            Mod_Entitys::SetingtheHair(PLAYER::PLAYER_PED_ID(), &thisPed->MyHair);
    }
}
void QuickChange(void* obj)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
        Mod_Entitys::SavedPlayer(thisPed, -1);
}
void CanRandondomizeStart()
{
    std::string sLocate = "" + Mod_Systems::GetDir() + "/Scripts/NSPM/Settings/Settings.Xml";
    bool Yolo = false;
    std::vector<std::string> MyColect = Mod_Systems::Read_ini(sLocate);

    if (MyColect.size() == 0)
    {
        sLocate = "" + Mod_Systems::GetDir() + "/Scripts/NSPM/Settings/Settings.ini";
        MyColect.clear();

        MyColect = Mod_Systems::Read_ini(sLocate);
    }

    for (int i = 0; i < MyColect.size(); i++)
    {
        std::string line = MyColect[i];
        if (Mod_Systems::Contains_string("StartOnYAcht", line))
            Yolo = Mod_Systems::Convert_to_bool(line);
    }

    if (Yolo)
        Mod_Data::Mod_Settings.Auto_Run = false;
}
void SetWeatherDate()
{
    Mod_Data::CanSnow = false;
    std::string Today = Mod_Systems::TimeDate();
    if (Mod_Systems::Contains_string("Jan", Today) && Mod_Data::Mod_Settings.Jan)
        Mod_Data::CanSnow = true;
    else if (Mod_Systems::Contains_string("Feb", Today) && Mod_Data::Mod_Settings.Feb)
        Mod_Data::CanSnow = true;
    else if (Mod_Systems::Contains_string("Mar", Today) && Mod_Data::Mod_Settings.Mar)
        Mod_Data::CanSnow = true;
    else if (Mod_Systems::Contains_string("Apr", Today) && Mod_Data::Mod_Settings.Apr)
        Mod_Data::CanSnow = true;
    else if (Mod_Systems::Contains_string("May", Today) && Mod_Data::Mod_Settings.May)
        Mod_Data::CanSnow = true;
    else if (Mod_Systems::Contains_string("Jun", Today) && Mod_Data::Mod_Settings.Jun)
        Mod_Data::CanSnow = true;
    else if (Mod_Systems::Contains_string("Jul", Today) && Mod_Data::Mod_Settings.Jul)
        Mod_Data::CanSnow = true;
    else if (Mod_Systems::Contains_string("Aug", Today) && Mod_Data::Mod_Settings.Aug)
        Mod_Data::CanSnow = true;
    else if (Mod_Systems::Contains_string("Sep", Today) && Mod_Data::Mod_Settings.Sep)
        Mod_Data::CanSnow = true;
    else if (Mod_Systems::Contains_string("Oct", Today) && Mod_Data::Mod_Settings.Oct)
        Mod_Data::CanSnow = true;
    else if (Mod_Systems::Contains_string("Nov", Today) && Mod_Data::Mod_Settings.Nov)
        Mod_Data::CanSnow = true;
    else if (Mod_Systems::Contains_string("Dec", Today) && Mod_Data::Mod_Settings.Dec)
        Mod_Data::CanSnow = true;

    Mod_Systems::WeatherReport(-1);
}
void LoadinData()
{
    Mod_Systems::LoggerLight("LoadinData");
    Mod_Systems::FindSettings(&Mod_Data::Mod_Settings);
    MainProtags = { Mod_Systems::MyHashKey(MainChar[0]), Mod_Systems::MyHashKey(MainChar[1]), Mod_Systems::MyHashKey(MainChar[2]), Mod_Systems::MyHashKey(MainChar[3]), Mod_Systems::MyHashKey(MainChar[4])};
    Mod_Data::GP_Player = Mod_Entitys::GetRelationship();
    Mod_Data::FollowMe = PED::GET_PED_GROUP_INDEX(PLAYER::PLAYER_PED_ID());// PED::CREATE_GROUP(0);
    Mod_Data::Gp_Friend = Mod_Entitys::AddRelationship("FrendlyNPCs");
    Mod_Data::GP_Attack = Mod_Entitys::AddRelationship("AttackNPCs");
    Mod_Data::Gp_Follow = Mod_Entitys::AddRelationship("FollowerNPCs");
    Mod_Data::GP_Mental = Mod_Entitys::AddRelationship("MentalNPCs");
    Mod_Entitys::SetRelationType(true);

    CustomMenuBannerPos = GVM::AddMeunBanner(BannerFile);

    MenuSideSwap();

    Mod_Systems::FindAddCars();
    Mod_Systems::FindAddPeds();

    int iAm = YourCharIs();
    if (iAm == 1)
    {
        MainChar[0] = "player_zero";
        MainChar[1] = "player_two";
        MainChar[2] = "player_one";
        ProTag = Mod_Class::ClothBank("-Michael-", "player_zero", Mod_Systems::MyHashKey("player_zero"), false, Mod_Entitys::FreeFaces(PLAYER::PLAYER_PED_ID(), false), true, false, Mod_Entitys::PickAStyle(true), 0, 0, 0, 0, {}, Mod_Entitys::AddOverLay(true, false), {}, { Mod_Entitys::GetYourTogs(PLAYER::PLAYER_PED_ID()) }, {}, 0, 0, 0, 200, 1.0f, 1.0f);

    }//Michal   
    else if (iAm == 3)
    {
        MainChar[0] = "player_two";
        MainChar[1] = "player_one";
        MainChar[2] = "player_zero";
        ProTag = Mod_Class::ClothBank("-Trevor-", "player_two", Mod_Systems::MyHashKey("player_two"), false, Mod_Entitys::FreeFaces(PLAYER::PLAYER_PED_ID(), false), true, false, Mod_Entitys::PickAStyle(true), 0, 0, 0, 0, {}, Mod_Entitys::AddOverLay(true, false), {}, { Mod_Entitys::GetYourTogs(PLAYER::PLAYER_PED_ID()) }, {}, 0, 0, 0, 200, 1.0f, 1.0f);
    }//Trevor
    else
    {
        MainChar[0] = "player_one";
        MainChar[1] = "player_two";
        MainChar[2] = "player_zero";
        ProTag = Mod_Class::ClothBank("-Franklin-", "player_one", Mod_Systems::MyHashKey("player_one"), false, Mod_Entitys::FreeFaces(PLAYER::PLAYER_PED_ID(), false), true, false, Mod_Entitys::PickAStyle(true), 0, 0, 0, 0, {}, Mod_Entitys::AddOverLay(true, false), {}, { Mod_Entitys::GetYourTogs(PLAYER::PLAYER_PED_ID()) }, {}, 0, 0, 0, 200, 1.0f, 1.0f);
    }//Michael

    Mod_Systems::LoadSavedPeds(ProTag);

    CanRandondomizeStart();
    NSPM_Include = Mod_Systems::File_exists(Mod_Systems::GetDir() + "/Scripts/NSPM/Settings/NSPMach.NSPM");
    Mod_Data::Ahhhh = Mod_Systems::GetDir() + "/RandomStart/heavenly_choir.wav";

    GVM::BottomLeft("" + MultC[Mod_Systems::LessRandomInt("LoadinData01", 0, 5)] + "Random Start " + MultC[Mod_Systems::LessRandomInt("LoadinData01", 0, 5)] + Mod_Vesion + MultC[Mod_Systems::LessRandomInt("LoadinData01", 0, 5)] + " by" + MultC[Mod_Systems::LessRandomInt("LoadinData01", 0, 5)] + " Adopcalipt " + MultC[Mod_Systems::LessRandomInt("LoadinData01", 0, 5)] + "Loaded" + MultC[Mod_Systems::LessRandomInt("LoadinData01", 0, 5)] + ".");

    if (Mod_Systems::File_exists(Mod_Systems::GetDir() + "/PlayerZero++.asi"))
        Mod_Data::GotPlayZero = true;

    Mod_Systems::LoadLang();
    WeaponCapture();
    SetWeatherDate();

    RandomStart();

    Mod_Load = false;
}

std::vector<GVM::GVMSystem> MyMenus = {};
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

int PedBanking(Mod_Class::ClothBank* thisPed)
{
    int YourPed = -1;
    if (thisPed == nullptr)
        MyNewBank = Mod_Entitys::PlayerClothBank();
    else
        MyNewBank = *thisPed;

    for (int i = 0; i < (int)Mod_Data::SavedPeds.size(); i++)
    {
        if (MyNewBank.ModelHash == Mod_Data::SavedPeds[i].ModelHash)
        {
            if (MyNewBank.FreeMode && Mod_Data::SavedPeds[i].FreeMode)
            {
                if (MyNewBank.MyFaces.ShapeFirstID == Mod_Data::SavedPeds[i].MyFaces.ShapeFirstID && MyNewBank.MyFaces.ShapeSecondID == Mod_Data::SavedPeds[i].MyFaces.ShapeSecondID && MyNewBank.MyFaces.ShapeThirdID == Mod_Data::SavedPeds[i].MyFaces.ShapeThirdID)
                {
                    if (MyNewBank.Cothing[0].ClothA[6] == Mod_Data::SavedPeds[i].Cothing[Mod_Data::SavedPeds[i].Cloth_Pick].ClothA[6] && MyNewBank.Cothing[0].ClothA[3] == Mod_Data::SavedPeds[i].Cothing[Mod_Data::SavedPeds[i].Cloth_Pick].ClothA[3])
                    {
                        if (MyNewBank.Cothing[0].ClothA[2] == Mod_Data::SavedPeds[i].Cothing[Mod_Data::SavedPeds[i].Cloth_Pick].ClothA[2] || MyNewBank.Cothing[0].ClothA[2] == Mod_Data::SavedPeds[i].MyHair.Comp)
                        {
                            YourPed = i;
                            break;
                        }
                    }
                }
            }
            else if (!MyNewBank.FreeMode && !Mod_Data::SavedPeds[i].FreeMode)
            {
                if (MyNewBank.Cothing[0].ClothA[0] == Mod_Data::SavedPeds[i].Cothing[Mod_Data::SavedPeds[i].Cloth_Pick].ClothA[0])
                {
                    YourPed = i;
                    break;
                }
            }
        }
    }

    return YourPed;
}

void ShowPlayerLabel(Vector3 location, float baseSize, const std::vector<std::string>& textLines)
{
    Vector3 cameraPos = CAM::GET_GAMEPLAY_CAM_COORD();
    float distance = Mod_Maths::DistanceTo(cameraPos, location);
    float totalMult = baseSize / (distance * (CAM::GET_GAMEPLAY_CAM_FOV() / 60.0f));

    float height = 0.0125f * totalMult;
    GVM::RGBA fontColor = GVM::RGBA(255, 255, 255, 255);
    GRAPHICS::SET_DRAW_ORIGIN(location.x, location.y, location.z, 0);
    int i = 0;

    for (auto line : textLines) {

        GVM::ShowText(0.0f, 0.0f + height * i, 0.2f * totalMult, line, 0, fontColor, true);
        i++;
    }

    GRAPHICS::CLEAR_DRAW_ORIGIN();
}

void PedSaving(void* obj)
{
    Mod_Systems::LoggerLight("PedSaving");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        if (thisPed->CharName == "" || thisPed->CharName == "Current" || thisPed->CharName == " ")
            thisPed->CharName = GVM::CaptureScreenText(Mod_Data::RSLangMenu[238]);

        if (thisPed->CharName != "" || thisPed->CharName != " ")
        {
            Mod_Systems::SaveClothBank(*thisPed);
            Mod_Systems::LoadSavedPeds(ProTag);
        }
    }
}
void SavingTheSavedPed(void* obj)
{
    Mod_Systems::LoggerLight("SavingTheSavedPed");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        Rs_MenuList.clear();
        PedSaving(thisPed);
    }
}
void PedAutoSaver(void* obj)
{
    Mod_Systems::LoggerLight("PedAutoSaver");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
    {
        if (Mod_Data::Mod_Settings.Auto_Save && thisPed->CharName != "-Michael-" && thisPed->CharName != "-Trevor-" && thisPed->CharName != "-Franklin-")
            PedSaving(thisPed);
        else if (thisPed->CharName == "")
        {
            std::vector<GVM::GVMFields> PedCompOut = {
                GVM::GVMFields(Mod_Data::RSLangMenu[12], "", &PedSaving, thisPed)
            };
        }
    }
}

void OutfitAndPropFix(int item, void* obj)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
    {
        if (item == 0 && Rs_MenuList[(int)Rs_MenuList.size() - 1].Menu_Form[1].IntNum != nullptr)
            *Rs_MenuList[(int)Rs_MenuList.size() - 1].Menu_Form[1].IntNum = 0;

        OutfitChange(thisPed);
    }
}
void Rs_Prop_Edit(int item, void* obj)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        Mod_Class::ClothX* Outfit = &thisPed->Cothing[thisPed->Cloth_Pick];

        int DrawVar = PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), item);
        int TextVar = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), item, Outfit->ClothA[item]);

        std::vector<GVM::GVMFields> PedCompOut = {
            GVM::GVMFields(Mod_Data::RSLangMenu[117], "", &Outfit->ExtraA[item], -1, DrawVar, false, &OutfitAndPropFix, thisPed, true, true),
            GVM::GVMFields(Mod_Data::RSLangMenu[118], "", &Outfit->ExtraB[item], 0, TextVar, false, &OutfitAndPropFix, thisPed, true, true)
        };
        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, PedCompOut);
        Rs_MenuList.push_back(NewMenu);
    }

}
void Rs_PropEdit(void* obj)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
    {

        std::vector<std::string> PedPropsList = { RSLangMenu[139], RSLangMenu[140], RSLangMenu[141], RSLangMenu[142] };
        std::vector<GVM::GVMFields> PedCompOut = {};

        for (int i = 0; i < PedPropsList.size(); i++)
            PedCompOut.push_back(GVM::GVMFields(PedPropsList[i], Mod_Data::RSLangMenu[119], &Rs_Prop_Edit, thisPed));

        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, PedCompOut);
        Rs_MenuList.push_back(NewMenu);
    }

}
void Rs_ClothX_Edit(int item, void* obj)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        int iCharType = YourCharIs();
        if (item == 1 && iCharType < 3)
        {
            std::vector<GVM::GVMFields> PedCompOut = {
                GVM::GVMFields("No Variations Avalable", "")
            };
            GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, PedCompOut);
            Rs_MenuList.push_back(NewMenu);
        }
        else
        {
            Mod_Class::ClothX* Outfit = &thisPed->Cothing[thisPed->Cloth_Pick];
            int iTake = 0;
            if (item == 6)
                iTake = 2;

            int DrawVar = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), item) - iTake;
            int TextVar = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), item, Outfit->ClothA[item]);

            std::vector<GVM::GVMFields> PedCompOut = {
                GVM::GVMFields(Mod_Data::RSLangMenu[117], "", &Outfit->ClothA[item], -1, DrawVar, false, &OutfitAndPropFix, thisPed, true, true),
                GVM::GVMFields(Mod_Data::RSLangMenu[118], "", &Outfit->ClothB[item], 0, TextVar, false, &OutfitAndPropFix, thisPed, true, true)
            };
            GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, PedCompOut);
            Rs_MenuList.push_back(NewMenu);
        }
    }
}
void Rs_OutfitEdit(void* obj)
{    
    Mod_Systems::LoggerLight("Rs_OutfitEdit");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
    {
        std::vector<std::string> PedComposList = { RSLangMenu[127], RSLangMenu[128], RSLangMenu[129], RSLangMenu[130], RSLangMenu[131], RSLangMenu[132], RSLangMenu[133], RSLangMenu[134], RSLangMenu[135], RSLangMenu[136], RSLangMenu[137], RSLangMenu[138] };
        std::vector<GVM::GVMFields> PedCompOut = {};

        for (int i = 0; i < PedComposList.size(); i++)
            PedCompOut.push_back(GVM::GVMFields(PedComposList[i], Mod_Data::RSLangMenu[119], &Rs_ClothX_Edit, thisPed));

        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, PedCompOut);
        Rs_MenuList.push_back(NewMenu);
    }

}
void DeleteSavedPed(void* obj)
{
    Mod_Systems::LoggerLight("DeleteSavedPed");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        Rs_MenuList.clear();
        Mod_Systems::Delete_ini(DirSavedPed + "/" + thisPed->CharName + ".ini");
        Mod_Systems::LoadSavedPeds(ProTag);
    }
}

void DeleteOutfit(void* obj)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        if (thisPed->Cloth_Pick < (int)thisPed->Cothing.size() && (int)thisPed->Cothing.size() > 1)
            thisPed->Cothing.erase(thisPed->Cothing.begin() + thisPed->Cloth_Pick);
        thisPed->Cloth_Pick = 0;
        OutfitChange(thisPed);
    }
    if ((int)Rs_MenuList.size() > 0)
        Rs_MenuList.pop_back();

    Rs_SavedPedEdit(thisPed);
}
void MakeNewOutfit(void* obj)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        std::string newNames = GVM::CaptureScreenText(Mod_Data::RSLangMenu[239]);
        int ListSize = (int)thisPed->Cothing.size();
        if (newNames == "")
            newNames = "NewOutfit_" + std::to_string(ListSize);
        Mod_Class::ClothX NewOutfit_ = Mod_Entitys::GetYourTogs(PLAYER::PLAYER_PED_ID());
        NewOutfit_.Title = newNames;
        thisPed->Cothing.push_back(NewOutfit_); 
        if (ListSize < (int)thisPed->Cothing.size())
            thisPed->Cloth_Pick = ListSize;
    }
    if ((int)Rs_MenuList.size() > 0)
        Rs_MenuList.pop_back();

    Rs_SavedPedEdit(thisPed);
}
int iOutfit = 0;
std::vector<std::string> SavedOutfits = {};
void OutFitList(int item, void* obj)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        Mod_Class::ClothX MyCloths = Mod_Entitys::LoadCloths(SavedOutfits[item]);
        thisPed->Cothing[thisPed->Cloth_Pick] = MyCloths;

        PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
        Mod_Entitys::ApplyTats(PLAYER::PLAYER_PED_ID(), thisPed);
        Mod_Entitys::OnlineDress(PLAYER::PLAYER_PED_ID(), &MyCloths);

        if (thisPed->FreeMode)
        {
            Mod_Class::HairSets Hairs = thisPed->MyHair;
            Mod_Entitys::SetingtheHair(PLAYER::PLAYER_PED_ID(), &Hairs);
        }
        Rs_MenuList[(int)Rs_MenuList.size() - 1].Menu_Form[0].Description = thisPed->Cothing[thisPed->Cloth_Pick].Title;
    }
}
void AddRemoveLabel(int list, void* obj)
{
    Mod_Systems::LoggerLight("AddRemoveLabel");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
        if (list == 0)
        {
            thisPed->Cothing[thisPed->Cloth_Pick].Badge.BaseName = "";
            thisPed->Cothing[thisPed->Cloth_Pick].Badge.Name = "";
            thisPed->Cothing[thisPed->Cloth_Pick].Badge.TatName = "";
        }
        else if (thisPed->Male)
        {
            if (list < (int)MaleTshirt.size())
            {
                if (list > 0)
                {
                    PED::_APPLY_PED_OVERLAY(PLAYER::PLAYER_PED_ID(), Mod_Systems::MyHashKey(MaleTshirt[list].BaseName), Mod_Systems::MyHashKey(MaleTshirt[list].TatName));
                    thisPed->Cothing[thisPed->Cloth_Pick].Badge = MaleTshirt[list];
                }
            }
        }
        else
        {
            if (list < (int)FemaleTshirt.size())
            {
                if (list > 0)
                {
                    PED::_APPLY_PED_OVERLAY(PLAYER::PLAYER_PED_ID(), Mod_Systems::MyHashKey(FemaleTshirt[list].BaseName), Mod_Systems::MyHashKey(FemaleTshirt[list].TatName));
                    thisPed->Cothing[thisPed->Cloth_Pick].Badge = FemaleTshirt[list];
                }
            }
        }

        Mod_Entitys::ApplyTats(PLAYER::PLAYER_PED_ID(), thisPed);
        Rs_MenuList[(int)Rs_MenuList.size() - 1].Menu_Form[list].Description = thisPed->Cothing[thisPed->Cloth_Pick].Badge.TatName;
    }
}
void OutFitPicker(int list, void* obj)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        OutfitChange(obj);
        Rs_MenuList[(int)Rs_MenuList.size() - 1].Menu_Form[list].Description = thisPed->Cothing[thisPed->Cloth_Pick].Title;
    }
}
void ReMakeDecorations(void* obj)
{
    Mod_Systems::LoggerLight("ReMakeDecorations");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
        Mod_Entitys::ApplyTats(PLAYER::PLAYER_PED_ID(), thisPed);
        OutfitChange(obj);
    }
}
void Rs_AddBadges(void* obj)
{
    Mod_Systems::LoggerLight("Rs_SavedPedEdit");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        int Indexed = 0;
        std::vector<GVM::GVMFields> MainFields = {};
        if (thisPed->Male)
        {
            for (int i = 0; i < MaleTshirt.size(); i++)
            {
                MainFields.push_back(GVM::GVMFields(MaleTshirt[i].TatName, "", &AddRemoveLabel, obj));
                if (MaleTshirt[i].TatName == thisPed->Cothing[thisPed->Cloth_Pick].Badge.TatName)
                    Indexed = i;
            }
        }
        else
        {
            for (int i = 0; i < FemaleTshirt.size(); i++)
            {
                MainFields.push_back(GVM::GVMFields(FemaleTshirt[i].TatName, "", &AddRemoveLabel, obj));
                if (FemaleTshirt[i].TatName == thisPed->Cothing[thisPed->Cloth_Pick].Badge.TatName)
                    Indexed = i;
            }
        }        
        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields);
        if (Indexed > 7)
        {
            NewMenu.Low = Indexed - 7;
            NewMenu.High = Indexed;
        }
        NewMenu.Index = Indexed;
        Rs_MenuList.push_back(NewMenu);
    }
}
void Rs_SavedPedEdit(void* obj)
{
    Mod_Systems::LoggerLight("Rs_SavedPedEdit");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        SavedOutfits = Mod_Entitys::FindCloths(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()));

        int iSize = 4;
        int iCharType = YourCharIs();

        std::vector<std::string> YourOufits = {};

        for (int i = 0; i < (int)thisPed->Cothing.size(); i++)
            YourOufits.push_back(thisPed->Cothing[i].Title);

        std::vector<std::string> tShirty = {};


        std::vector<GVM::GVMFields> MainFields = {
            GVM::GVMFields(Mod_Data::RSLangMenu[109], thisPed->Cothing[thisPed->Cloth_Pick].Title, YourOufits, &thisPed->Cloth_Pick, &OutFitPicker, thisPed, true, true),
            GVM::GVMFields(Mod_Data::RSLangMenu[110], Mod_Data::RSLangMenu[111], &MakeNewOutfit, thisPed),
            GVM::GVMFields(Mod_Data::RSLangMenu[262], Mod_Data::RSLangMenu[263], &DeleteOutfit, thisPed),
            GVM::GVMFields(Mod_Data::RSLangMenu[112], Mod_Data::RSLangMenu[113], &Rs_OutfitEdit, thisPed),
            GVM::GVMFields(Mod_Data::RSLangMenu[114], Mod_Data::RSLangMenu[115], &Rs_PropEdit, thisPed),
            GVM::GVMFields(RSLangMenu[261], thisPed->Cothing[thisPed->Cloth_Pick].Badge.Name, &Rs_AddBadges, thisPed)
        };

        if ((int)SavedOutfits.size() > 0)
            MainFields.push_back(GVM::GVMFields(Mod_Data::RSLangMenu[116], "", SavedOutfits, &iOutfit, &OutFitList, thisPed, true, false));

        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields, &ReMakeDecorations, obj, true);
        Rs_MenuList.push_back(NewMenu);
    }
}

std::vector<int> Rs_WeapintList = {};
std::vector<int> Rs_AddintList = {};
std::vector<Mod_Class::Weap_Read> Rs_WeapsList = {};
std::vector<Mod_Class::Weap_Addons> Rs_AddonList = {};

void UpdateSavedWeapons(void* obj)
{
    Mod_Systems::LoggerLight("UpdateSavedWeapons");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        if (Rs_WeapintList.size() == Rs_WeapsList.size())
        {
            std::vector<int> MarkForDelete = {};
            std::vector<std::string> GotWeaps = {};
            for (int i = 0; i < (int)thisPed->MyWeapons.size(); i++)
                GotWeaps.push_back(thisPed->MyWeapons[i].MyWeapon);

            for (int i = 0; i < (int)Rs_WeapsList.size(); i++)
            {
                int GotThis = Mod_Systems::Find_String_Pos(GotWeaps, Rs_WeapsList[i].MyWeapon);
                if (Rs_WeapintList[i] == 0)
                {
                    if (GotThis != -1)
                        MarkForDelete.push_back(GotThis);
                }
                else
                {
                    if (GotThis == -1)
                        thisPed->MyWeapons.push_back(Mod_Class::WeaponSaver(Rs_WeapsList[i].MyWeapon, {}, 9999, Rs_WeapsList[i].Tint, 0));
                }
            }
            std::sort(MarkForDelete.begin(), MarkForDelete.end(), std::greater<int>());

            for (int i = 0; i < (int)MarkForDelete.size(); i++)
                thisPed->MyWeapons.erase(thisPed->MyWeapons.begin() + MarkForDelete[i]);
        }
    }
}
void UpdateSavedAddons(void* obj, void* obj2)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    std::string* thisWeap = static_cast<std::string*>(obj2);
    if (thisPed != nullptr && thisWeap != nullptr)
    {
        Mod_Systems::LoggerLight("UpdateSavedAddons == " + *thisWeap);
        if (Rs_AddintList.size() == Rs_AddonList.size())
        {
            std::vector<int> MarkForDelete = {};
            std::vector<std::string> GotWeaps = {};
            for (int i = 0; i < (int)thisPed->MyWeapons.size(); i++)
                GotWeaps.push_back(thisPed->MyWeapons[i].MyWeapon);

            std::vector<std::string> GotAddons = {};
            int GotThis = Mod_Systems::Find_String_Pos(GotWeaps, *thisWeap);
            if (GotThis != -1)
            {
                for (int i = 0; i < (int)thisPed->MyWeapons[GotThis].MyAddons.size(); i++)
                    GotAddons.push_back(thisPed->MyWeapons[GotThis].MyAddons[i]);

                for (int i = 0; i < (int)Rs_AddonList.size(); i++)
                {
                    int GotAdd = Mod_Systems::Find_String_Pos(GotAddons, Rs_AddonList[i].MyComponent);
                    if (Rs_AddintList[i] == 0)
                    {
                        if (GotAdd != -1)
                            MarkForDelete.push_back(GotAdd);
                    }
                    else
                    {
                        if (GotAdd == -1)
                            thisPed->MyWeapons[GotThis].MyAddons.push_back(Rs_AddonList[i].MyComponent);
                    }
                }
            }
            std::sort(MarkForDelete.begin(), MarkForDelete.end(), std::greater<int>());

            for (int i = 0; i < (int)MarkForDelete.size(); i++)
                thisPed->MyWeapons[GotThis].MyAddons.erase(thisPed->MyWeapons[GotThis].MyAddons.begin() + MarkForDelete[i]);
        }
    }
}

void Rs_WeaponLiverys(void* obj, void* obj2)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    Mod_Class::Weap_Read* thisWeap = static_cast<Mod_Class::Weap_Read*>(obj2);
    if (thisPed != nullptr && thisWeap != nullptr)
    {
        Mod_Systems::LoggerLight("Rs_WeaponAddons == " + thisWeap->MyWeapon);
        if (Rs_MenuList.size() > 0)
            Rs_MenuList.pop_back();

        Rs_AddintList.clear();
        Rs_AddonList.clear();

        std::vector<GVM::GVMFields> WeapsMenu = {};

        std::vector<std::string> GotWeaps = {};
        for (int i = 0; i < (int)thisPed->MyWeapons.size(); i++)
            GotWeaps.push_back(thisPed->MyWeapons[i].MyWeapon);

        int GotThis = Mod_Systems::Find_String_Pos(GotWeaps, thisWeap->MyWeapon);
        if (GotThis != -1)
            Mod_Systems::FindWeaponComponents(&Rs_AddonList, WeapLiverys, thisWeap->MyWeapon);

        for (int i = 0; i < (int)Rs_AddonList.size(); i++)
            Rs_AddintList.push_back(0);
        for (int i = 0; i < (int)Rs_AddonList.size(); i++)
        {
            if (Mod_Systems::Find_String_Pos(thisPed->MyWeapons[GotThis].MyAddons, Rs_AddonList[i].MyComponent) != -1)
                Rs_AddintList[i] = 1;
            WeapsMenu.push_back(GVM::GVMFields(Rs_AddonList[i].MyDecription, "", &Rs_AddintList[i], 0, 1, true));
        }

        if ((int)WeapsMenu.size() == 0)
            WeapsMenu.push_back(GVM::GVMFields(RSLangMenu[260], ""));

        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, WeapsMenu, UpdateSavedAddons, obj, &thisWeap->MyWeapon, false);
        Rs_MenuList.push_back(NewMenu);
    }
}
void Rs_WeaponAddons(void* obj, void* obj2)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    Mod_Class::Weap_Read* thisWeap = static_cast<Mod_Class::Weap_Read*>(obj2);
    if (thisPed != nullptr && thisWeap != nullptr)
    {
        Mod_Systems::LoggerLight("Rs_WeaponAddons == " + thisWeap->MyWeapon);
        if (Rs_MenuList.size() > 0)
            Rs_MenuList.pop_back();

        Rs_AddintList.clear();
        Rs_AddonList.clear();

        std::vector<GVM::GVMFields> WeapsMenu = {};

        std::vector<std::string> GotWeaps = {};
        for (int i = 0; i < (int)thisPed->MyWeapons.size(); i++)
            GotWeaps.push_back(thisPed->MyWeapons[i].MyWeapon);

        int GotThis = Mod_Systems::Find_String_Pos(GotWeaps, thisWeap->MyWeapon);
        if (GotThis != -1)
            Mod_Systems::FindWeaponComponents(&Rs_AddonList, WeapCompon, thisWeap->MyWeapon);

        for (int i = 0; i < (int)Rs_AddonList.size(); i++)
            Rs_AddintList.push_back(0);
        for (int i = 0; i < (int)Rs_AddonList.size(); i++)
        {
            if (Mod_Systems::Find_String_Pos(thisPed->MyWeapons[GotThis].MyAddons, Rs_AddonList[i].MyComponent) != -1)
                Rs_AddintList[i] = 1;
            WeapsMenu.push_back(GVM::GVMFields(Rs_AddonList[i].MyDecription, "", &Rs_AddintList[i], 0, 1, true));
        }

        if ((int)WeapsMenu.size() == 0)
            WeapsMenu.push_back(GVM::GVMFields(RSLangMenu[259], ""));

        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, WeapsMenu, &UpdateSavedAddons, obj, &thisWeap->MyWeapon, false);
        Rs_MenuList.push_back(NewMenu);
    }
}
void Rs_WeaponEditer(int item, void* obj)
{
    Mod_Systems::LoggerLight("Rs_WeaponEditer == " + std::to_string(item));
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr && item < (int)Rs_WeapsList.size())
    {
        if (Rs_MenuList.size() > 0)
            Rs_MenuList.pop_back();

        std::vector<std::string> GotWeaps = {};
        for (int i = 0; i < (int)thisPed->MyWeapons.size(); i++)
            GotWeaps.push_back(thisPed->MyWeapons[i].MyWeapon);

        int GotThis = Mod_Systems::Find_String_Pos(GotWeaps, Rs_WeapsList[item].MyWeapon);
        if (GotThis == -1)
        {
            thisPed->MyWeapons.push_back(Mod_Class::WeaponSaver(Rs_WeapsList[item].MyWeapon, {}, 9999, Rs_WeapsList[item].Tint, 0));
            GotThis = (int)thisPed->MyWeapons.size() - 1;
        }
        std::vector<std::string> TintList;

        Mod_Systems::FindWeaponTints(&TintList, Rs_WeapsList[item].Tint);

        if (TintList.size() == 0)
            TintList.push_back(RSLangMenu[255]);

        std::vector<GVM::GVMFields> WeapsMenu = {
            GVM::GVMFields(RSLangMenu[256], "", &Rs_WeaponAddons, obj, &Rs_WeapsList[item]),
            GVM::GVMFields(RSLangMenu[257], "", &Rs_WeaponLiverys, obj, &Rs_WeapsList[item]),
            GVM::GVMFields(RSLangMenu[258], "", TintList, &thisPed->MyWeapons[GotThis].WeapTint, false)
        };

        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, WeapsMenu);
        Rs_MenuList.push_back(NewMenu);
    }
}
void Rs_WeaponSelect(int item, void* obj)
{
    Mod_Systems::LoggerLight("Rs_WeaponSelect");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
    {
        Rs_WeapintList.clear();
        Rs_WeapsList.clear();

        std::vector<std::string> GotWeaps = {};
        for (int i = 0; i < (int)thisPed->MyWeapons.size(); i++)
            GotWeaps.push_back(thisPed->MyWeapons[i].MyWeapon);

        std::string WeapFile = WeaponsDir[item];
        std::vector<GVM::GVMFields> WeapsMenu = {};

        Mod_Systems::FindWeapons(&Rs_WeapsList, WeapFile);

        for (int i = 0; i < Rs_WeapsList.size(); i++)
            Rs_WeapintList.push_back(0);

        for (int i = 0; i < Rs_WeapsList.size(); i++)
        {
            if (Mod_Systems::Find_String_Pos(GotWeaps, Rs_WeapsList[i].MyWeapon) != -1)
                Rs_WeapintList[i] = 1;
            WeapsMenu.push_back(GVM::GVMFields(Rs_WeapsList[i].MyDecription, "", &Rs_WeapintList[i], 0, 1, true, &Rs_WeaponEditer, obj, false, true));
        }

        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, WeapsMenu, &UpdateSavedWeapons, obj, false);
        Rs_MenuList.push_back(NewMenu);
    }
}
void Rs_ClearAllWeaps(void* obj)
{
    Mod_Systems::LoggerLight("Rs_ClearAllWeaps");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
        thisPed->MyWeapons.clear();
}
void GiveTakeWeapons(void* obj)
{
    Mod_Systems::LoggerLight("Rs_ClearAllWeaps");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
        Mod_Entitys::GunningIt(PLAYER::PLAYER_PED_ID(), thisPed->MyWeapons);
}
void Rs_SavedWeapons(void* obj)
{
    Mod_Systems::LoggerLight("Rs_SavedWeapons");
    if (obj != nullptr)
    {
        std::vector<GVM::GVMFields> MainFields = {
            GVM::GVMFields(RSLangMenu[245], "", &Rs_WeaponSelect, obj),
            GVM::GVMFields(RSLangMenu[246], "", &Rs_WeaponSelect, obj),
            GVM::GVMFields(RSLangMenu[247], "", &Rs_WeaponSelect, obj),
            GVM::GVMFields(RSLangMenu[248], "", &Rs_WeaponSelect, obj),
            GVM::GVMFields(RSLangMenu[249], "", &Rs_WeaponSelect, obj),
            GVM::GVMFields(RSLangMenu[250], "",  &Rs_WeaponSelect, obj),
            GVM::GVMFields(RSLangMenu[251], "", &Rs_WeaponSelect, obj),
            GVM::GVMFields(RSLangMenu[252], "",  &Rs_WeaponSelect, obj),
            GVM::GVMFields(RSLangMenu[253], "",  &Rs_WeaponSelect, obj),
            GVM::GVMFields(RSLangMenu[254], "", &Rs_ClearAllWeaps, obj)
        };
        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields, &GiveTakeWeapons, obj, true);
        Rs_MenuList.push_back(NewMenu);
    }
}

std::vector<Mod_Class::Tattoo> TattoosList(int pedType, int zone)
{
    Mod_Systems::LoggerLight("TattoosList, pedType == " + std::to_string(pedType) + ", iZone == " + std::to_string(zone));

    bool bEmpty = false;
    std::vector<Mod_Class::Tattoo> TatOutput = {};

    if (pedType == 1)
    {
        if (zone == 0)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_018", "Impotent Rage"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_014", "Chinese Dragon"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_008", "Trinity Knot"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_004", "Lucky"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_020", "Way of the Gun"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_017", "Whiskey Life"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_015", "Flaming Shamrock"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_006", "Eagle and Serpent"));
        }//TORSO
        else if (zone == 1)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_003", "The Rose of My Heart"));
        }//HEAD
        else if (zone == 2)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_019", "Dragon"));//     
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_012", "Faith"));//   
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_010", "Lady M"));//   
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_009", "Lucky Celtic Dogs"));//  
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_007", "Mermaid"));//       
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_000", "Mandy"));//    
        }//LEFT ARM 
        else if (zone == 3)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_016", "Michael and Amanda"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_013", "Flower Mural"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_005", "Virgin Mary"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_001", "Family is Forever"));
        }//RIGHT ARM
        else if (zone == 4)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_002", "Smoking Dagger"));
        }//LEFT LEG
        else
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "MK_011", "Tiki Pinup "));
        }//RIGHT LEG
    }// Michael
    else if (pedType == 2)
    {
        if (zone == 0)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_038", "Angel of Los Santos"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_010", "Grace and Power"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_004", "Dragon"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_039", "Impotent Rage"));//   
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_037", "Los Santos Bills"));// 
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_036", "These Streets"));//    
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_035", "Families"));//      
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_032", "LS Flames"));//  
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_031", "Fam 4 Life"));//   
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_030", "Families Symbol"));//      
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_029", "FAM Power"));//    
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_028", "Flaming Cross"));//  
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_021", "Chamberlain Families LS"));//  
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_020", "LS Heart "));//   
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_018", "Families Kings"));//  
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_011", "Forum4Life"));//      
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_000", "Chamberlain"));//     
            //Not in List
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_025", "Skull on the Cross"));//    
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_024", "Skull and Dragon"));
        }//TORSO
        else if (zone == 1)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_022", "Chamberlain Families"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_005", "Faith"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_034", "LS Bold"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_033", "LS Script"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_014", "F King"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_013", "F Crown "));
        }//HEAD
        else if (zone == 2)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_019", "FAMILIES"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_017", "Lion"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_016", "Dragon Mural"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_007", "Serpent Skull"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_001", "Brotherhood"));
        }//LEFT ARM
        else if (zone == 3)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_023", "Fiery Dragon"));//    
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_012", "Oriental Mural"));//    
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_009", "Chop"));//    
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_008", "Mother"));//    
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_006", "Serpents"));//    
        }//RIGHT ARM
        else if (zone == 4)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_027", "Hottie"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_015", "The Warrior"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_002", "Dragons"));
        }//LEFT LEG
        else
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_026", "Trust No One"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "fr_003", "Melting Skull"));
        }//RIGHT LEG
    }// Franklin
    else if (pedType == 3)
    {
        if (zone == 0)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_032", "Lucky"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_031", "Unzipped"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_026", "Skulls and Rose"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_022", "Chinese Dragon"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_033", "Impotent Rage"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_030", "Fuck Cops"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_029", "Smiley"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_028", "Ace"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_027", "Piggy"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_023", "Monster Pups"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_021", "Stone Cross"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_015", "Tweaker"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_013", "Betraying Scroll"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_012", "Eye Catcher"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_006", "Blackjack"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_004", "Evil Clown"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_000", "Imperial Douche"));
        }//TORSO
        else if (zone == 1)
        {
            bEmpty = true;
        }//HEAD
        else if (zone == 2)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_024", "Grim Reaper Smoking Gun"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_018", "Dope Skull"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_017", "The Wages of Sin"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_016", "Dragon and Dagger"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_003", "Zodiac Skull"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_001", "R.I.P Michael"));
        }//LEFT ARM
        else if (zone == 3)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_020", "Indian Ram"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_014", "Muertos"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_010", "Flaming Skull"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_009", "Broken Skull"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_008", "Dagger"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_007", "Tribal"));
        }//RIGHT ARM
        else if (zone == 4)
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_011", "Serpant Skull"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_002", "Grim Reaper"));
        }//LEFT LEG
        else
        {
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_025", "Freedom"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_019", "Flaming Scorpion"));
            TatOutput.push_back(Mod_Class::Tattoo("singleplayer_overlays", "TP_005", "Love to Hate"));
        }//RIGHT LEG
    }// Trevor
    else if (pedType == 4)
    {
        if (zone == 0)
        {
            TatOutput = Mod_Data::maleTats01;
        }//BACK
        else if (zone == 1)
        {
            TatOutput = Mod_Data::maleTats02;
        }//CHEST
        else if (zone == 2)
        {
            TatOutput = Mod_Data::maleTats03;
        }//STOMACH
        else if (zone == 3)
        {
            TatOutput = Mod_Data::maleTats04;
            //Not On the TatOutput     ...                            
        }//HEAD
        else if (zone == 4)
        {
            TatOutput = Mod_Data::maleTats05;
        }//LEFT ARM
        else if (zone == 5)
        {
            TatOutput = Mod_Data::maleTats06;
        }//RIGHT ARM
        else if (zone == 6)
        {
            TatOutput = Mod_Data::maleTats07;
        }//LEFT LEG
        else
        {
            TatOutput = Mod_Data::maleTats08;
        }//RIGHT LEG
    }// FreeMale
    else if (pedType == 5)
    {
        if (zone == 0)
        {
            TatOutput = Mod_Data::femaleTats01;
        }//BACK
        else if (zone == 1)
        {
            TatOutput = Mod_Data::femaleTats02;
        }//CHEST
        else if (zone == 2)
        {
            TatOutput = Mod_Data::femaleTats03;
        }//STOMACH
        else if (zone == 3)
        {
            TatOutput = Mod_Data::femaleTats04;
        }//HEAD
        else if (zone == 4)
        {
            TatOutput = Mod_Data::femaleTats05;
        }//LEFT ARM
        else if (zone == 5)
        {
            TatOutput = Mod_Data::femaleTats06;
        }//RIGHT ARM
        else if (zone == 6)
        {
            TatOutput = Mod_Data::femaleTats07;
        }//LEFT LEG
        else
        {
            TatOutput = Mod_Data::femaleTats08;
        }//RIGHT LEG
    }// FreeFemale

    if (bEmpty || TatOutput.size() == 0)
        TatOutput.push_back(Mod_Class::Tattoo("", "", "No Tattoos Available"));

    return TatOutput;
}
std::vector<int> GotTats = {};
std::vector<Mod_Class::Tattoo> TatList = {};
void AddRemoveThemTats(void* obj)
{
    Mod_Systems::LoggerLight("AddRemoveThemTats");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        if (GotTats.size() == TatList.size())
        {
            std::vector<int> MarkForDelete = {};
            std::vector<std::string> YourTats = {};
            for (int i = 0; i < (int)thisPed->MyTattoo.size(); i++)
                YourTats.push_back(thisPed->MyTattoo[i].TatName);

            for (int i = 0; i < (int)TatList.size(); i++)
            {
                int GotThis = Mod_Systems::Find_String_Pos(YourTats, TatList[i].TatName);
                if (GotTats[i] == 0)
                {
                    if (GotThis != -1)
                        MarkForDelete.push_back(GotThis);
                }
                else
                {
                    if (GotThis == -1)
                        thisPed->MyTattoo.push_back(TatList[i]);
                }
            }
            std::sort(MarkForDelete.begin(), MarkForDelete.end(), std::greater<int>());

            for (int i = 0; i < (int)MarkForDelete.size(); i++)
                thisPed->MyTattoo.erase(thisPed->MyTattoo.begin() + MarkForDelete[i]);
        }
        ReMakeDecorations(obj);
    }
}
void TatChanges(void* obj, void* obj2)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    Mod_Class::Tattoo* thisTat = static_cast<Mod_Class::Tattoo*>(obj2);
    if (thisPed != nullptr && thisTat != nullptr)
    {
        PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
        PED::_APPLY_PED_OVERLAY(PLAYER::PLAYER_PED_ID(), Mod_Systems::MyHashKey(thisTat->BaseName), Mod_Systems::MyHashKey(thisTat->TatName));
    }
}
void Rs_TatListings(int list, void* obj)
{
    Mod_Systems::LoggerLight("Rs_TatListFree");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (obj != nullptr)
    {
        GotTats.clear();
        TatList.clear();
        int Main_Char = YourCharIs();
        TatList = TattoosList(Main_Char, list);

        std::vector<GVM::GVMFields> MainFields = {};

        std::vector<std::string> YourTats = {};
        for (int i = 0; i < (int)thisPed->MyTattoo.size(); i++)
            YourTats.push_back(thisPed->MyTattoo[i].TatName);

        for (int i = 0; i < (int)TatList.size(); i++)
            GotTats.push_back(0);

        for (int i = 0; i < (int)TatList.size(); i++)
        {
            if (Mod_Systems::Find_String_Pos(YourTats, TatList[i].TatName) != -1)
                GotTats[i] = 1;
            MainFields.push_back(GVM::GVMFields(TatList[i].Name, "", &GotTats[i], 0, 1, true, &TatChanges, obj, &TatList[i], true, false));
        }
        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields, &AddRemoveThemTats, obj, false);
        Rs_MenuList.push_back(NewMenu);
    }
}
void RemoveAllTats(void* obj)
{
    Mod_Systems::LoggerLight("RemoveAllTats");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (obj != nullptr)
    {
        PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
        thisPed->MyTattoo.clear();
        OutfitChange(obj);
    }
}
void Rs_TattooEdit(void* obj)
{
    Mod_Systems::LoggerLight("Rs_TattooEdit");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (obj != nullptr)
    {
        if (thisPed->FreeMode)
        {
            std::vector<GVM::GVMFields> MainFields = {
                GVM::GVMFields(RSLangMenu[149], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[150], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[151], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[144], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[145], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[146], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[147], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[148], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[244], "", &RemoveAllTats, obj)
            };
            GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields);
            Rs_MenuList.push_back(NewMenu);
        }
        else
        {
            std::vector<GVM::GVMFields> MainFields = {
                GVM::GVMFields(RSLangMenu[143], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[144], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[145], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[146], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[147], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[148], "", &Rs_TatListings, obj),
                GVM::GVMFields(RSLangMenu[244], "", &RemoveAllTats, obj)
            };
            GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields);
            Rs_MenuList.push_back(NewMenu);
        }
    }
}

int iHairIndex = 0;
void HairStylist(int list, void* obj)
{
    Mod_Systems::LoggerLight("HairStylist");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
    {
        if (thisPed->Male)
            thisPed->MyHair = MHairsets[iHairIndex];
        else
            thisPed->MyHair = FHairsets[iHairIndex];

        Mod_Entitys::SetingtheHair(PLAYER::PLAYER_PED_ID(), &thisPed->MyHair);
        Rs_MenuList[(int)Rs_MenuList.size() - 1].Menu_Form[list].Description = thisPed->MyHair.Name;
    }
}
void HairHighlights(void* obj)
{
    Mod_Systems::LoggerLight("HairStylist");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
        PED::_SET_PED_HAIR_COLOR(PLAYER::PLAYER_PED_ID(), thisPed->HairColour, thisPed->HairStreaks);
}
void EyesSavedPed(void* obj)
{
    Mod_Systems::LoggerLight("HairStylist");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
        PED::_SET_PED_EYE_COLOR(PLAYER::PLAYER_PED_ID(), thisPed->EyeColour);
}
void Rs_PedHair(void* obj)
{
    Mod_Systems::LoggerLight("Rs_PedHair");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
    {
        std::vector<std::string> Hairy = {};

        if (thisPed->Male)
        {
            for (int i = 0; i < (int)MHairsets.size(); i++)
            {
                Hairy.push_back(MHairsets[i].Name);
                if (thisPed->MyHair.Name == MHairsets[i].Name)
                    iHairIndex = i;
            }

        }
        else
        {
            for (int i = 0; i < (int)FHairsets.size(); i++)
            {
                Hairy.push_back(FHairsets[i].Name);
                if (thisPed->MyHair.Name == MHairsets[i].Name)
                    iHairIndex = i;
            }
        }

        std::vector<GVM::GVMFields> MainFields = {
            GVM::GVMFields(Mod_Data::RSLangMenu[93], thisPed->MyHair.Name, Hairy, &iHairIndex, &HairStylist, obj, true, true),//MHairsets
            GVM::GVMFields(Mod_Data::RSLangMenu[96], thisPed->MyHair.Name, &thisPed->HairColour, 0, 61, false, &HairHighlights, thisPed, true, false),
            GVM::GVMFields(Mod_Data::RSLangMenu[97], thisPed->MyHair.Name, &thisPed->HairStreaks, 0, 61, false, &HairHighlights, thisPed, true, false),
            GVM::GVMFields(Mod_Data::RSLangMenu[94], Mod_Data::RSLangMenu[95], &thisPed->EyeColour, 0, 22, false, &EyesSavedPed, thisPed, true, false),
        };
        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields);
        Rs_MenuList.push_back(NewMenu);
    }
}

int iFaceValue = 0;
void FaceFitting(void* obj, void* obj2)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    int* faceIt = static_cast<int*>(obj2);
    if (thisPed != nullptr)
    {
        if (*faceIt < (int)thisPed->MyOverlay.size())
        {
            PED::SET_PED_HEAD_OVERLAY(PLAYER::PLAYER_PED_ID(), *faceIt, thisPed->MyOverlay[*faceIt].Overlay, thisPed->MyOverlay[*faceIt].OverOpc);
            if (thisPed->MyOverlay[*faceIt].Colour > 0)
                PED::_SET_PED_HEAD_OVERLAY_COLOR(PLAYER::PLAYER_PED_ID(), *faceIt, thisPed->MyOverlay[*faceIt].Colour, thisPed->MyOverlay[*faceIt].OverCol, 0);
        }
    }
}
void Rs_FaceFeaturesAdd(int index, void* obj)
{
    Mod_Systems::LoggerLight("Rs_FaceFeaturesAdd");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
    {
        std::vector<std::string> PedOversList = { RSLangMenu[172],RSLangMenu[173],RSLangMenu[174],RSLangMenu[175],RSLangMenu[176],RSLangMenu[177],RSLangMenu[178],RSLangMenu[179],RSLangMenu[180],RSLangMenu[181],RSLangMenu[182],RSLangMenu[183],RSLangMenu[184] };
        iFaceValue = index;
        int iOPC = (int)(thisPed->MyOverlay[index].OverOpc * 100);

        std::vector<GVM::GVMFields> MainFields = {
            GVM::GVMFields(Mod_Data::RSLangMenu[117], PedOversList[index], &thisPed->MyOverlay[index].Overlay, 0, Mod_Entitys::GetPedOverlayValues(index), false, &FaceFitting, obj, &iFaceValue, true, false),
            GVM::GVMFields(Mod_Data::RSLangMenu[120], PedOversList[index], &thisPed->MyOverlay[index].OverOpc, 0, 1, 0.01f, &FaceFitting, obj, &iFaceValue, true)
        };
        if (thisPed->MyOverlay[index].OverCol != -1)
            MainFields.push_back(GVM::GVMFields(Mod_Data::RSLangMenu[121], PedOversList[index], &thisPed->MyOverlay[index].OverCol, 0, 62, false, &FaceFitting, obj, &iFaceValue, true, false));

        GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields);
        Rs_MenuList.push_back(NewMenu);
    }
}
void Rs_FaceFeatures(void* obj)
{
    Mod_Systems::LoggerLight("Rs_FaceFeatures");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (obj != nullptr)
    {
        if (thisPed->FreeMode)
        {
            std::vector<GVM::GVMFields> MainFields = {
                GVM::GVMFields(RSLangMenu[171], "", &Rs_FaceFeaturesAdd, obj),
                GVM::GVMFields(RSLangMenu[172], "", &Rs_FaceFeaturesAdd, obj),
                GVM::GVMFields(RSLangMenu[173], "", &Rs_FaceFeaturesAdd, obj),
                GVM::GVMFields(RSLangMenu[174], "", &Rs_FaceFeaturesAdd, obj),
                GVM::GVMFields(RSLangMenu[175], "", &Rs_FaceFeaturesAdd, obj),
                GVM::GVMFields(RSLangMenu[176], "", &Rs_FaceFeaturesAdd, obj),
                GVM::GVMFields(RSLangMenu[177], "", &Rs_FaceFeaturesAdd, obj),
                GVM::GVMFields(RSLangMenu[178], "", &Rs_FaceFeaturesAdd, obj),
                GVM::GVMFields(RSLangMenu[179], "", &Rs_FaceFeaturesAdd, obj),
                GVM::GVMFields(RSLangMenu[180], "", &Rs_FaceFeaturesAdd, obj),
                GVM::GVMFields(RSLangMenu[181], "", &Rs_FaceFeaturesAdd, obj),
                GVM::GVMFields(RSLangMenu[182], "", &Rs_FaceFeaturesAdd, obj),
                GVM::GVMFields(RSLangMenu[183], "", &Rs_FaceFeaturesAdd, obj)
            };
            GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields);
            Rs_MenuList.push_back(NewMenu);
        }
    }
}
void FaceShapeShift(int index, void* obj)
{
    Mod_Systems::LoggerLight("FaceShapeShift");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
        PED::_SET_PED_FACE_FEATURE(PLAYER::PLAYER_PED_ID(), index, thisPed->FaceScale[index]);
}
void Rs_FaceShape(void* obj)
{
    Mod_Systems::LoggerLight("Rs_FaceShape");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (obj != nullptr)
    {
        if (thisPed->FreeMode)
        {
            if (thisPed->FaceScale.size() != 20)
            {
                for (int i = 0; i < 20; i++)
                    thisPed->FaceScale.push_back(0.0f);
            }
            std::vector<GVM::GVMFields> MainFields = {
                GVM::GVMFields(RSLangMenu[152], "", &thisPed->FaceScale[0], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[153], "", &thisPed->FaceScale[1], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[154], "", &thisPed->FaceScale[2], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[155], "", &thisPed->FaceScale[3], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[156], "", &thisPed->FaceScale[4], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[157], "", &thisPed->FaceScale[5], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[158], "", &thisPed->FaceScale[6], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[159], "", &thisPed->FaceScale[7], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[160], "", &thisPed->FaceScale[8], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[161], "", &thisPed->FaceScale[9], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[162], "", &thisPed->FaceScale[10], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[163], "", &thisPed->FaceScale[11], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[164], "", &thisPed->FaceScale[12], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[165], "", &thisPed->FaceScale[13], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[166], "", &thisPed->FaceScale[14], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[167], "", &thisPed->FaceScale[15], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[168], "", &thisPed->FaceScale[16], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[169], "", &thisPed->FaceScale[17], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[170], "", &thisPed->FaceScale[18], -1, 1, 0.01f, &FaceShapeShift, obj, true),
                GVM::GVMFields(RSLangMenu[171], "", &thisPed->FaceScale[19], -1, 1, 0.01f, &FaceShapeShift, obj, true),
            };
            GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields);
            Rs_MenuList.push_back(NewMenu);
        }
    }
}
void PickFreeParent(void* obj)
{
    Mod_Systems::LoggerLight("FaceShapeShift");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
        PED::SET_PED_HEAD_BLEND_DATA(PLAYER::PLAYER_PED_ID(), thisPed->MyFaces.ShapeFirstID, thisPed->MyFaces.ShapeSecondID, thisPed->MyFaces.ShapeThirdID, thisPed->MyFaces.SkinFirstID, thisPed->MyFaces.SkinSecondID, thisPed->MyFaces.SkinThirdID, thisPed->MyFaces.ShapeMix, thisPed->MyFaces.SkinMix, thisPed->MyFaces.ThirdMix, 0);

}
void Rs_FaceParenting(void* obj)
{
    Mod_Systems::LoggerLight("Rs_FaceParenting");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (obj != nullptr)
    {
        if (thisPed->FreeMode)
        {
            std::vector<GVM::GVMFields> MainFields = {
                GVM::GVMFields(Mod_Data::RSLangMenu[122], "", &thisPed->MyFaces.ShapeFirstID, 0, 45, false, &PickFreeParent, obj, true, false),
                GVM::GVMFields(Mod_Data::RSLangMenu[123], "", &thisPed->MyFaces.ShapeSecondID, 0, 45, false, &PickFreeParent, obj, true, false),
                GVM::GVMFields(Mod_Data::RSLangMenu[124], "", &thisPed->MyFaces.ShapeMix, 0, 1, 0.01f, &PickFreeParent, obj, true),
                GVM::GVMFields(Mod_Data::RSLangMenu[125], "", &thisPed->MyFaces.SkinMix, 0, 1, 0.01f, &PickFreeParent, obj, true),
                GVM::GVMFields(Mod_Data::RSLangMenu[126], "", &thisPed->MyFaces.ThirdMix, 0, 1, 0.01f, &PickFreeParent, obj, true)
            };
            GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields);
            Rs_MenuList.push_back(NewMenu);
        }
    }
}
void WalkingSavedPed(int list, void* obj)
{
    Mod_Systems::LoggerLight("WalkingSavedPed");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        if (thisPed->Walkies == 0)
            PED::RESET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), 0.0f);
        else if (thisPed->Male)
        {
            if (thisPed->Walkies < M_Walks.size())
                Mod_Entitys::WalkingStyle(PLAYER::PLAYER_PED_ID(), M_Walks[thisPed->Walkies]);
            Rs_MenuList[(int)Rs_MenuList.size() - 1].Menu_Form[list].Description = M_Walks[thisPed->Walkies];
        }
        else
        {
            if (thisPed->Walkies < F_Walks.size())
                Mod_Entitys::WalkingStyle(PLAYER::PLAYER_PED_ID(), F_Walks[thisPed->Walkies]);
            Rs_MenuList[(int)Rs_MenuList.size() - 1].Menu_Form[list].Description = F_Walks[thisPed->Walkies];
        }
    }
}
void FacingSavedPed(int list, void* obj)
{
    Mod_Systems::LoggerLight("FacingSavedPed");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        if (thisPed->Moods == 0)
            PED::CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(PLAYER::PLAYER_PED_ID());
        else
            Mod_Entitys::PullingFaces(FaceAn[thisPed->Moods]);

        Rs_MenuList[(int)Rs_MenuList.size() - 1].Menu_Form[list].Description = FaceAn[thisPed->Moods];
    }
}
void VoiceOverSavedPed(int list, void* obj)
{
    Mod_Systems::LoggerLight("VoiceOverSavedPed");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    { 
        if (thisPed->Voice == 0)
        {
            invoke <Void>(0x40CF0D12D142A9E8, PLAYER::PLAYER_PED_ID());
            invoke <Void>(0x4ADA3F19BE4A6047, PLAYER::PLAYER_PED_ID());
        }
        else if(thisPed->Male)
        {
            if (thisPed->Voice < VoicesMale.size())
                Mod_Entitys::ThemVoices(VoicesMale[thisPed->Voice]);

            Rs_MenuList[(int)Rs_MenuList.size() - 1].Menu_Form[list].Description = VoicesMale[thisPed->Voice];
        }
        else
        {
            if (thisPed->Voice < VoicesFemale.size())
                Mod_Entitys::ThemVoices(VoicesFemale[thisPed->Voice]);


            Rs_MenuList[(int)Rs_MenuList.size() - 1].Menu_Form[list].Description = VoicesFemale[thisPed->Voice];
        }
    }
}
void RenameSavedPed(void* obj)
{
    Mod_Systems::LoggerLight("RenameSavedPed");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        int PedIn = PedBanking(thisPed);
        std::string newNames = GVM::CaptureScreenText(Mod_Data::RSLangMenu[238]);
        if (PedIn != -1)
        {
            Mod_Systems::Delete_ini(DirSavedPed + "/" + thisPed->CharName + ".ini");
            thisPed->CharName = newNames;
            Mod_Systems::SaveClothBank(*thisPed);
        }
        else
            thisPed->CharName = newNames;
    }
}
void HealthConcern(void* obj)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        PED::SET_PED_MAX_HEALTH(PLAYER::PLAYER_PED_ID(), thisPed->PlHealth);
        ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), thisPed->PlHealth);
    }
}
void RunForest(void* obj)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        if (thisPed->PlRunSp > 1.49f)
            thisPed->PlRunSp = 1.49f;
        PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), thisPed->PlRunSp);
    }
}
void TomDaily(void* obj)
{
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        if (thisPed->PlSwimSp > 1.49f)
            thisPed->PlSwimSp = 1.49f;
        PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), thisPed->PlSwimSp);
    }
}
void Rs_Pedditor(void* obj)
{
    Rs_MenuList.clear();
    Mod_Systems::LoggerLight("Rs_Pedditor");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);
    if (thisPed != nullptr)
    {
        if ((int)thisPed->MyWeapons.size() == 0)
            thisPed->MyWeapons = Mod_Systems::BuildWeaponList();

        int Main_Char = YourCharIs();
        if (Main_Char == 1 || Main_Char == 2 || Main_Char == 3)
        {
            std::vector<GVM::GVMFields> MainFields = {
                GVM::GVMFields(Mod_Data::RSLangMenu[89], Mod_Data::RSLangMenu[90], &Rs_SavedPedEdit, thisPed),
                GVM::GVMFields(Mod_Data::RSLangMenu[91], Mod_Data::RSLangMenu[92], &Rs_TattooEdit, thisPed),
                GVM::GVMFields(Mod_Data::RSLangMenu[104], VoicesMale[thisPed->Voice], VoicesMale, &thisPed->Voice, &VoiceOverSavedPed, thisPed, true, true),
                GVM::GVMFields(Mod_Data::RSLangMenu[240], FaceAn[thisPed->Moods], FaceAn, &thisPed->Moods, &FacingSavedPed, thisPed, true, true),
                GVM::GVMFields(Mod_Data::RSLangMenu[241], M_Walks[thisPed->Walkies], M_Walks, &thisPed->Walkies, &WalkingSavedPed, thisPed, true, true),
                GVM::GVMFields(Mod_Data::RSLangMenu[265], Mod_Data::RSLangMenu[266], &thisPed->PlHealth, 110, 1000, false, &HealthConcern, thisPed, true, false),
                GVM::GVMFields(Mod_Data::RSLangMenu[267], Mod_Data::RSLangMenu[268], &thisPed->PlRunSp, 0, 2, 0.01f, &RunForest, thisPed, true),
                GVM::GVMFields(Mod_Data::RSLangMenu[269], Mod_Data::RSLangMenu[270], &thisPed->PlSwimSp, 0, 2, 0.01f, &TomDaily, thisPed, true),
                GVM::GVMFields(Mod_Data::RSLangMenu[242], Mod_Data::RSLangMenu[243], &Rs_SavedWeapons, thisPed),
                GVM::GVMFields(Mod_Data::RSLangMenu[87], Mod_Data::RSLangMenu[88], &RenameSavedPed, thisPed),
                GVM::GVMFields(Mod_Data::RSLangMenu[105], Mod_Data::RSLangMenu[106], &SavingTheSavedPed,thisPed),
                GVM::GVMFields(Mod_Data::RSLangMenu[107], Mod_Data::RSLangMenu[108], &DeleteSavedPed, thisPed)
            };
            GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields, &PedAutoSaver, thisPed, true);
            Rs_MenuList.push_back(NewMenu);
        }
        else if (Main_Char == 4 || Main_Char == 5)
        {
            if (thisPed->Male)
            {
                std::vector<GVM::GVMFields> MainFields = {
                    GVM::GVMFields(Mod_Data::RSLangMenu[89], Mod_Data::RSLangMenu[90], &Rs_SavedPedEdit, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[91], Mod_Data::RSLangMenu[92], &Rs_TattooEdit, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[93], thisPed->MyHair.Name, &Rs_PedHair,thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[98], Mod_Data::RSLangMenu[99], &Rs_FaceFeatures, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[100], Mod_Data::RSLangMenu[101], &Rs_FaceShape, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[102], Mod_Data::RSLangMenu[103], &Rs_FaceParenting, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[104], VoicesMale[thisPed->Voice], VoicesMale, &thisPed->Voice, &VoiceOverSavedPed, thisPed, true, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[240], FaceAn[thisPed->Moods], FaceAn, &thisPed->Moods, &FacingSavedPed, thisPed, true, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[241], M_Walks[thisPed->Walkies], M_Walks, &thisPed->Walkies, &WalkingSavedPed, thisPed, true, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[265], Mod_Data::RSLangMenu[266], &thisPed->PlHealth, 110, 1000, false, &HealthConcern, thisPed, true, false),
                    GVM::GVMFields(Mod_Data::RSLangMenu[267], Mod_Data::RSLangMenu[268], &thisPed->PlRunSp, 0, 2, 0.01f, &RunForest, thisPed, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[269], Mod_Data::RSLangMenu[270], &thisPed->PlSwimSp, 0, 2, 0.01f, &TomDaily, thisPed, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[242], Mod_Data::RSLangMenu[243], &Rs_SavedWeapons, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[87], Mod_Data::RSLangMenu[88], &RenameSavedPed, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[105], Mod_Data::RSLangMenu[106], &SavingTheSavedPed,thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[107], Mod_Data::RSLangMenu[108], &DeleteSavedPed, thisPed)
                };
                GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields, &PedAutoSaver, thisPed, true);
                Rs_MenuList.push_back(NewMenu);
            }
            else
            {
                std::vector<GVM::GVMFields> MainFields = {
                    GVM::GVMFields(Mod_Data::RSLangMenu[89], Mod_Data::RSLangMenu[90], &Rs_SavedPedEdit, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[91], Mod_Data::RSLangMenu[92], &Rs_TattooEdit, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[93], thisPed->MyHair.Name, &Rs_PedHair,thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[98], Mod_Data::RSLangMenu[99], &Rs_FaceFeatures, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[100], Mod_Data::RSLangMenu[101], &Rs_FaceShape, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[102], Mod_Data::RSLangMenu[103], &Rs_FaceParenting, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[104], VoicesFemale[thisPed->Voice], VoicesFemale, &thisPed->Voice, &VoiceOverSavedPed, thisPed, true, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[240], FaceAn[thisPed->Moods], FaceAn, &thisPed->Moods, &FacingSavedPed, thisPed, true, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[241], F_Walks[thisPed->Walkies], F_Walks, &thisPed->Walkies, &WalkingSavedPed, thisPed, true, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[265], Mod_Data::RSLangMenu[266], &thisPed->PlHealth, 110, 1000, false, &HealthConcern, thisPed, true, false),
                    GVM::GVMFields(Mod_Data::RSLangMenu[267], Mod_Data::RSLangMenu[268], &thisPed->PlRunSp, 0, 2, 0.01f, &RunForest, thisPed, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[269], Mod_Data::RSLangMenu[270], &thisPed->PlSwimSp, 0, 2, 0.01f, &TomDaily, thisPed, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[242], Mod_Data::RSLangMenu[243], &Rs_SavedWeapons, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[87], Mod_Data::RSLangMenu[88], &RenameSavedPed, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[105], Mod_Data::RSLangMenu[106], &SavingTheSavedPed,thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[107], Mod_Data::RSLangMenu[108], &DeleteSavedPed, thisPed)
                };
                GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields, &PedAutoSaver, thisPed, true);
                Rs_MenuList.push_back(NewMenu);
            }
        }
        else
        {
            if (thisPed->Male)
            {
                std::vector<GVM::GVMFields> MainFields = {
                    GVM::GVMFields(Mod_Data::RSLangMenu[89], Mod_Data::RSLangMenu[90], &Rs_SavedPedEdit, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[91], Mod_Data::RSLangMenu[92], &Rs_TattooEdit, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[104], VoicesMale[thisPed->Voice], VoicesMale, &thisPed->Voice, &VoiceOverSavedPed, thisPed, true, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[240], FaceAn[thisPed->Moods], FaceAn, &thisPed->Moods, &FacingSavedPed, thisPed, true, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[241], M_Walks[thisPed->Walkies], M_Walks, &thisPed->Walkies, &WalkingSavedPed, thisPed, true, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[265], Mod_Data::RSLangMenu[266], &thisPed->PlHealth, 110, 1000, false, &HealthConcern, thisPed, true, false),
                    GVM::GVMFields(Mod_Data::RSLangMenu[267], Mod_Data::RSLangMenu[268], &thisPed->PlRunSp, 0, 2, 0.01f, &RunForest, thisPed, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[269], Mod_Data::RSLangMenu[270], &thisPed->PlSwimSp, 0, 2, 0.01f, &TomDaily, thisPed, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[242], Mod_Data::RSLangMenu[243], &Rs_SavedWeapons, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[87], Mod_Data::RSLangMenu[88], &RenameSavedPed, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[105], Mod_Data::RSLangMenu[106], &SavingTheSavedPed,thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[107], Mod_Data::RSLangMenu[108], &DeleteSavedPed, thisPed)
                };
                GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields, &PedAutoSaver, thisPed, true);
                Rs_MenuList.push_back(NewMenu);
            }
            else
            {
                std::vector<GVM::GVMFields> MainFields = {
                    GVM::GVMFields(Mod_Data::RSLangMenu[89], Mod_Data::RSLangMenu[90], &Rs_SavedPedEdit, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[91], Mod_Data::RSLangMenu[92], &Rs_TattooEdit, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[104], VoicesFemale[thisPed->Voice], VoicesFemale, &thisPed->Voice, &VoiceOverSavedPed, thisPed, true, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[240], FaceAn[thisPed->Moods], FaceAn, &thisPed->Moods, &FacingSavedPed, thisPed, true, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[241], F_Walks[thisPed->Walkies], F_Walks, &thisPed->Walkies, &WalkingSavedPed, thisPed, true, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[265], Mod_Data::RSLangMenu[266], &thisPed->PlHealth, 110, 1000, false, &HealthConcern, thisPed, true, false),
                    GVM::GVMFields(Mod_Data::RSLangMenu[267], Mod_Data::RSLangMenu[268], &thisPed->PlRunSp, 0, 2, 0.01f, &RunForest, thisPed, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[269], Mod_Data::RSLangMenu[270], &thisPed->PlSwimSp, 0, 2, 0.01f, &TomDaily, thisPed, true),
                    GVM::GVMFields(Mod_Data::RSLangMenu[242], Mod_Data::RSLangMenu[243], &Rs_SavedWeapons, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[87], Mod_Data::RSLangMenu[88], &RenameSavedPed, thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[105], Mod_Data::RSLangMenu[106], &SavingTheSavedPed,thisPed),
                    GVM::GVMFields(Mod_Data::RSLangMenu[107], Mod_Data::RSLangMenu[108], &DeleteSavedPed, thisPed)
                };
                GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields, &PedAutoSaver, thisPed, true);
                Rs_MenuList.push_back(NewMenu);
            }
        }
    }
}
void Rs_LoadPedditor(void* obj)
{
    Mod_Systems::LoggerLight("Rs_LoadPedditor");
    Mod_Class::ClothBank* thisPed = static_cast<Mod_Class::ClothBank*>(obj);

    if (thisPed != nullptr)
    {
        Mod_Entitys::SavedPlayer(thisPed, -1);
        Rs_Pedditor(thisPed);
    }
}
void Rs_SavePed()
{
    std::vector<GVM::GVMFields> MainFields = {};
    for (int i = 0; i < (int)Mod_Data::SavedPeds.size(); i++)
        MainFields.push_back(GVM::GVMFields(SavedPeds[i].CharName, Mod_Data::RSLangMenu[86], &Rs_LoadPedditor, &SavedPeds[i]));

    GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields);
    Rs_MenuList.push_back(NewMenu);
}
void Rs_PedMenu()
{
    Mod_Systems::LoggerLight("Rs_PedMenu");

    int MyPedIs = PedBanking(nullptr);

    Mod_Class::ClothBank* Clothpoint;
    if (MyPedIs != -1)
        Clothpoint = &Mod_Data::SavedPeds[MyPedIs];
    else
        Clothpoint = &MyNewBank;

    std::vector<GVM::GVMFields> MainFields = {
        GVM::GVMFields(Mod_Data::RSLangMenu[227] + " " + Clothpoint->CharName, Mod_Data::RSLangMenu[81], &Rs_Pedditor, Clothpoint),   //Ext
        GVM::GVMFields(Mod_Data::RSLangMenu[78], Mod_Data::RSLangMenu[79],  &Rs_SavePed),   //Ext
        GVM::GVMFields(Mod_Data::RSLangMenu[82], Mod_Data::RSLangMenu[83], { RSLangMenu[228], RSLangMenu[229] }, &iPedMale, &NewRandomFreePed, false, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[84], Mod_Data::RSLangMenu[85], &Reposesion)
    };
    GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields);
    Rs_MenuList.push_back(NewMenu);
}
void Rs_Scenario()
{
    std::vector<GVM::GVMFields> MainFields = {
        GVM::GVMFields(Mod_Data::RSLangMenu[8], Mod_Data::RSLangMenu[4], &RandomLocation),
        GVM::GVMFields(Mod_Data::RSLangMenu[28], Mod_Data::RSLangMenu[29],  &Mod_Data::Mod_Settings.BeachPed, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[30], Mod_Data::RSLangMenu[31],  &Mod_Data::Mod_Settings.Tramps, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[32], Mod_Data::RSLangMenu[33],  &Mod_Data::Mod_Settings.Highclass, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[34], Mod_Data::RSLangMenu[35],  &Mod_Data::Mod_Settings.Midclass, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[36], Mod_Data::RSLangMenu[37],  &Mod_Data::Mod_Settings.Lowclass, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[38], Mod_Data::RSLangMenu[39],  &Mod_Data::Mod_Settings.Business, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[40], Mod_Data::RSLangMenu[41],  &Mod_Data::Mod_Settings.Bodybuilder, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[42], Mod_Data::RSLangMenu[43],  &Mod_Data::Mod_Settings.GangStars, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[44], Mod_Data::RSLangMenu[45],  &Mod_Data::Mod_Settings.Epsilon, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[46], Mod_Data::RSLangMenu[47],  &Mod_Data::Mod_Settings.Jogger, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[48], Mod_Data::RSLangMenu[49],  &Mod_Data::Mod_Settings.Golfer, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[50], Mod_Data::RSLangMenu[51],  &Mod_Data::Mod_Settings.Hiker, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[52], Mod_Data::RSLangMenu[53],  &Mod_Data::Mod_Settings.Methaddict, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[54], Mod_Data::RSLangMenu[55],  &Mod_Data::Mod_Settings.Rural, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[56], Mod_Data::RSLangMenu[57],  &Mod_Data::Mod_Settings.Cyclist, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[58], Mod_Data::RSLangMenu[59],  &Mod_Data::Mod_Settings.LGBTWXYZ, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[60], Mod_Data::RSLangMenu[61],  &Mod_Data::Mod_Settings.PoolPeds, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[62], Mod_Data::RSLangMenu[63],  &Mod_Data::Mod_Settings.Workers, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[64], Mod_Data::RSLangMenu[65],  &Mod_Data::Mod_Settings.Jetski, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[66], Mod_Data::RSLangMenu[67],  &Mod_Data::Mod_Settings.BikeATV, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[68], Mod_Data::RSLangMenu[69],  &Mod_Data::Mod_Settings.Services, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[70], Mod_Data::RSLangMenu[71],  &Mod_Data::Mod_Settings.Pilot, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[72], Mod_Data::RSLangMenu[73],  &Mod_Data::Mod_Settings.Animals, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[74], Mod_Data::RSLangMenu[75],  &Mod_Data::Mod_Settings.Yankton, &RandomLocation, false),
        GVM::GVMFields(Mod_Data::RSLangMenu[76], Mod_Data::RSLangMenu[77],  &Mod_Data::Mod_Settings.Cayo, &RandomLocation, false)
    };
    GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields, &Mod_Systems::ReBuildIni, &Mod_Data::Mod_Settings, false);
    Rs_MenuList.push_back(NewMenu);
}

void Rs_LangChange()
{
    Rs_MenuList.clear();
    Mod_Systems::LoadLang();
    Rs_MenuStart();
}

bool bSnowToggle = false;
void SnowToggle()
{
    Mod_Data::Mod_Settings.Jan = bSnowToggle;
    Mod_Data::Mod_Settings.Feb = bSnowToggle;
    Mod_Data::Mod_Settings.Mar = bSnowToggle;
    Mod_Data::Mod_Settings.Apr = bSnowToggle;
    Mod_Data::Mod_Settings.May = bSnowToggle;
    Mod_Data::Mod_Settings.Jun = bSnowToggle;
    Mod_Data::Mod_Settings.Jul = bSnowToggle;
    Mod_Data::Mod_Settings.Aug = bSnowToggle;
    Mod_Data::Mod_Settings.Sep = bSnowToggle;
    Mod_Data::Mod_Settings.Oct = bSnowToggle;
    Mod_Data::Mod_Settings.Nov = bSnowToggle;
    Mod_Data::Mod_Settings.Dec = bSnowToggle;
    bSnowToggle = !bSnowToggle;
}
void Rs_SnowJoke()
{
    Mod_Systems::LoggerLight("Rs_Winter");

    std::vector<GVM::GVMFields> WinterFields = {
        GVM::GVMFields(Mod_Data::RSLangMenu[214], "", &Mod_Data::Mod_Settings.Jan),
        GVM::GVMFields(Mod_Data::RSLangMenu[215], "", &Mod_Data::Mod_Settings.Feb),
        GVM::GVMFields(Mod_Data::RSLangMenu[216], "", &Mod_Data::Mod_Settings.Mar),
        GVM::GVMFields(Mod_Data::RSLangMenu[217], "", &Mod_Data::Mod_Settings.Apr),
        GVM::GVMFields(Mod_Data::RSLangMenu[218], "", &Mod_Data::Mod_Settings.May),
        GVM::GVMFields(Mod_Data::RSLangMenu[219], "", &Mod_Data::Mod_Settings.Jun),
        GVM::GVMFields(Mod_Data::RSLangMenu[220], "", &Mod_Data::Mod_Settings.Jul),
        GVM::GVMFields(Mod_Data::RSLangMenu[221], "", &Mod_Data::Mod_Settings.Aug),
        GVM::GVMFields(Mod_Data::RSLangMenu[222], "", &Mod_Data::Mod_Settings.Sep),
        GVM::GVMFields(Mod_Data::RSLangMenu[223], "", &Mod_Data::Mod_Settings.Oct),
        GVM::GVMFields(Mod_Data::RSLangMenu[224], "", &Mod_Data::Mod_Settings.Nov),
        GVM::GVMFields(Mod_Data::RSLangMenu[225], "", &Mod_Data::Mod_Settings.Dec),
        GVM::GVMFields(Mod_Data::RSLangMenu[237], "", &SnowToggle)
    };
    GVM::GVMSystem WinterMenu = GVM::GVMSystem(CustomMenuBannerPos, WinterFields, &SetWeatherDate, true);
    Rs_MenuList.push_back(WinterMenu);
}
void Rs_KeyCapture()
{
    std::vector<GVM::GVMFields> MainFields = {
        GVM::GVMFields(Mod_Data::RSLangMenu[184], Mod_Data::RSLangMenu[185], &KeyCapture),   //Ext
        GVM::GVMFields(Mod_Data::RSLangMenu[186], Mod_Data::RSLangMenu[187], &ControlerCapture)    //Ext
    };
    GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields);
    Rs_MenuList.push_back(NewMenu);
}

void ClashingOptions(int item)
{
    if (item == 1)
    {
        if (Mod_Data::Mod_Settings.Random_Ped)
            Mod_Data::Mod_Settings.Saved_Ped = false;
    }
    else if (item == 2)
    {
        if (Mod_Data::Mod_Settings.Saved_Ped)
            Mod_Data::Mod_Settings.Random_Ped = false;
    }
    else if (item == 3)
    {
        if (Mod_Data::Mod_Settings.Reincarnate)
            Mod_Data::Mod_Settings.Funeral = false;
    }
    else if (item == 5)
    {
        if (Mod_Data::Mod_Settings.Funeral)
            Mod_Data::Mod_Settings.Reincarnate = false;
    }
}
void Rs_OptionsMenu()
{
    Mod_Systems::LoggerLight("Rs_OptionsMenu");

    std::vector<GVM::GVMFields> MainFields = {
        GVM::GVMFields(Mod_Data::RSLangMenu[8], Mod_Data::RSLangMenu[9], &Mod_Data::Mod_Settings.Auto_Run),
        GVM::GVMFields(Mod_Data::RSLangMenu[10], Mod_Data::RSLangMenu[11], &Mod_Data::Mod_Settings.Random_Ped, ClashingOptions, true),
        GVM::GVMFields(Mod_Data::RSLangMenu[12], Mod_Data::RSLangMenu[13], &Mod_Data::Mod_Settings.Saved_Ped, ClashingOptions, true),
        GVM::GVMFields(Mod_Data::RSLangMenu[14], Mod_Data::RSLangMenu[15], &Mod_Data::Mod_Settings.Reincarnate, ClashingOptions, true),
        GVM::GVMFields(Mod_Data::RSLangMenu[16], Mod_Data::RSLangMenu[17], &Mod_Data::Mod_Settings.ReCurr),
        GVM::GVMFields(Mod_Data::RSLangMenu[271], Mod_Data::RSLangMenu[272], &Mod_Data::Mod_Settings.WatchDead),
        GVM::GVMFields(Mod_Data::RSLangMenu[18], Mod_Data::RSLangMenu[19], &Mod_Data::Mod_Settings.Funeral, ClashingOptions, true),
        GVM::GVMFields(Mod_Data::RSLangMenu[20], Mod_Data::RSLangMenu[21], &Mod_Data::Mod_Settings.Prison),
        GVM::GVMFields(Mod_Data::RSLangMenu[22], Mod_Data::RSLangMenu[23], &Mod_Data::Mod_Settings.Random_Weapons),
        GVM::GVMFields(Mod_Data::RSLangMenu[232], Mod_Data::RSLangMenu[233], &Mod_Data::Mod_Settings.Auto_Save),
        GVM::GVMFields(Mod_Data::RSLangMenu[24], Mod_Data::RSLangMenu[25], &WeaponCapture),
        GVM::GVMFields(Mod_Data::RSLangMenu[26], Mod_Data::RSLangMenu[27], &Rs_KeyCapture),
        GVM::GVMFields(Mod_Data::RSLangMenu[234], Mod_Data::RSLangMenu[235], &Mod_Data::Mod_Settings.Menu_Left_Side, &MenuSideSwap, true),         //Ext
        GVM::GVMFields(TranlatesTo[Mod_Data::Mod_Settings.Lang_Set], Mod_Data::RSLangMenu[236], TranlatesTo, &Mod_Data::Mod_Settings.Lang_Set, &Rs_LangChange, false, false)
    };
    GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields, &Mod_Systems::ReBuildIni, &Mod_Data::Mod_Settings, false);
    Rs_MenuList.push_back(NewMenu);
}

bool MenuOpen = false;
void Rs_MenuStart()
{
    Mod_Systems::LoggerLight("Rs_MenuStart");

    std::vector<GVM::GVMFields> MainFields = {
        GVM::GVMFields(Mod_Data::RSLangMenu[4], Mod_Data::RSLangMenu[5], &Rs_Scenario),
        GVM::GVMFields(Mod_Data::RSLangMenu[6], Mod_Data::RSLangMenu[7], &Rs_PedMenu),
        GVM::GVMFields(Mod_Data::RSLangMenu[213], Mod_Data::RSLangMenu[226], &Rs_SnowJoke),
        GVM::GVMFields(Mod_Data::RSLangMenu[230], Mod_Data::RSLangMenu[231], &Rs_OptionsMenu)
    };
    GVM::GVMSystem NewMenu = GVM::GVMSystem(CustomMenuBannerPos, MainFields);
    Rs_MenuList.push_back(NewMenu);
}

int iWait = 0;
int ClosePhone = 0;
void RemoveWhenFar()
{
    if ((int)Mod_Data::Vehicle_List.size() > 0)
    {
        if (Mod_Maths::DistanceTo(Mod_Maths::PlayerPosi(), Mod_Maths::EntPosition(Mod_Data::Vehicle_List[0])) > 150.00f)
            Mod_Entitys::ClearAllEntitys(true);
        GotClutter = false;
    }
    else if ((int)Mod_Data::Ped_List.size() > 0)
    {
        if (Mod_Maths::DistanceTo(Mod_Maths::PlayerPosi(), Mod_Maths::EntPosition(Mod_Data::Ped_List[0])) > 150.00f)
            Mod_Entitys::ClearAllPeds();
        GotClutter = false;
    }
    else
        GotClutter = false;
}

const Mod_Class::Vector4 CayoDance01 = Mod_Class::Vector4(4894.263f, -4913.141f, 3.36446f, 0.0f);
const Mod_Class::Vector4 CayoDance02 = Mod_Class::Vector4(4890.318f, -4923.923f, 3.368097f, 0.0f);

bool PrivateDancer = false;
int Strictly = 0;

void StrictlyCome()
{
    if (Strictly < (int)Mod_Data::CayDancers.size())
    {
        if ((bool)ENTITY::IS_ENTITY_DEAD(Mod_Data::CayDancers[Strictly]))
            Mod_Entitys::ClearAllPeds();
        else if (!AI::GET_IS_TASK_ACTIVE(Mod_Data::CayDancers[Strictly], 134))
            Mod_Entitys::DanceDanceDance(Mod_Data::CayDancers[Strictly]);
        Strictly++;
    }
    else
        Strictly = 0;
}
void YouMakeMeFeal()
{
    if (PrivateDancer)
    {
        GVM::TopLeft(Mod_Data::RSLangMenu[209]);
        if (GVM::WhileButtonDown(75))
        {
            AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
            AI::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
            AI::STOP_ANIM_PLAYBACK(PLAYER::PLAYER_PED_ID(), 0, 0);
            PrivateDancer = false;
        }
        else if (GVM::WhileButtonDown(46))
            Mod_Entitys::DanceDanceDance(PLAYER::PLAYER_PED_ID());
    }
    else
    {
        GVM::TopLeft(Mod_Data::RSLangMenu[210]);
        if (GVM::WhileButtonDown(46))
        {
            Mod_Entitys::DanceDanceDance(PLAYER::PLAYER_PED_ID());
            PrivateDancer = true;
        }
    }
}
void Rs_main()
{
    Mod_Systems::DirectoryTest();

    while (true)
    {
        if (Mod_Load)
        {
            WAIT(100);
            if (!(bool)DLC2::GET_IS_LOADING_SCREEN_ACTIVE())
                LoadinData();
        }
        else
        {
            if (!MenuOpen)//
            {
                bool Key0 = false;
                Mod_Systems::Menu_Button_state(&Key0, Mod_Data::KeyFind[Mod_Data::Mod_Settings.MenuKey]);
                if (Mod_Data::Mod_Settings.ControlSupport)
                {
                    if (GVM::ButtonDown(Mod_Data::Mod_Settings.ControlA) && GVM::ButtonDown(Mod_Data::Mod_Settings.ControlB))
                        Key0 = true;
                }

                if (Key0)
                {
                    CAM::DO_SCREEN_FADE_IN(1);
                    ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, true);
                    Mod_Data::Close_Menu = false;
                    MenuOpen = true;
                    Rs_MenuStart();
                }
            }
            else
            {
                if (Rs_MenuList.size() > 0)
                {
                    if (Rs_MenuList[(int)Rs_MenuList.size() - 1]._Back)
                        Rs_MenuList.pop_back();
                    else
                        GVM::MenuDisplay(&Rs_MenuList[(int)Rs_MenuList.size() - 1], GVM::DefaultRatio);
                }
                else
                    MenuOpen = false;
            }

            if (DeadOrArestCheck)
            {
                if ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
                {
                    Mod_Data::Close_Menu = true;
                    DeadOrArestCheck = false;
                    if (Mod_Data::BackStagePass)
                        AccessAllAreas(false);
                    Mod_Entitys::ClearAllEntitys(false);
                    DeathAndArrest((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()));
                }
            }

            if (Mod_Data::MissingFilesNag)
            {
                GVM::BottomLeft(Mod_Data::RSLangMenu[264]);
                Mod_Data::MissingFilesNag = false;
            }
            else if (Mod_Data::BackStagePass)
                InRestrictedArea();
            else if (Mod_Data::Cayo_Loaded)
            {
                if (Mod_Maths::DistanceTo(PLAYER::PLAYER_PED_ID(), CayoDance01) < 90.0f)
                {
                    if ((int)Mod_Data::CayDancers.size() > 0)
                        StrictlyCome();

                    if (Mod_Maths::DistanceTo(PLAYER::PLAYER_PED_ID(), CayoDance01) < 7.0f || Mod_Maths::DistanceTo(PLAYER::PLAYER_PED_ID(), CayoDance02) < 11.0f)
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
        WAIT(0);
    }
}

void ScriptMain()
{
    srand(GetTickCount());
    Rs_main();
}