#pragma once

#include "..\inc\main.h"
#include "..\inc\types.h"
#include "..\inc\natives.h"
#include "filesystem.hpp"
#include <Windows.h>

#include <fstream>		//ofstream read/write text documents
#include <string>
#include <vector>
#include <array>

namespace Mod_Class
{
    class Settings_Ini
    {
    public:
        int MenuKey;
        bool Auto_Run;
        bool Random_Ped;
        bool Saved_Ped;
        bool Funeral;
        bool Prison;
        bool BeachPart;
        bool Reincarnate;
        bool WatchDead;
        bool ReCurr;
        bool Random_Weapons;
        bool Disable_Record_Key;
        bool Auto_Save;
        bool Menu_Left_Side;

        bool ControlSupport;
        int ControlA;
        int ControlB;

        int Lang_Set;

        bool BeachPed;
        bool Tramps;
        bool Highclass;
        bool Midclass;
        bool Lowclass;
        bool Business;
        bool Bodybuilder;
        bool GangStars;
        bool Epsilon;
        bool Jogger;
        bool Golfer;
        bool Hiker;
        bool Methaddict;
        bool Rural;
        bool Cyclist;
        bool LGBTWXYZ;
        bool PoolPeds;
        bool Workers;
        bool Jetski;
        bool BikeATV;
        bool Services;
        bool Pilot;;
        bool Animals;
        bool Yankton;
        bool Cayo;

        bool Loging;

        bool Jan;
        bool Feb;
        bool Mar;
        bool Apr;
        bool May;
        bool Jun;
        bool Jul;
        bool Aug;
        bool Sep;
        bool Oct;
        bool Nov;
        bool Dec;

    public:
        Settings_Ini()
            : MenuKey(76), Auto_Run(true), Random_Ped(true), Saved_Ped(false), Disable_Record_Key(true), Random_Weapons(true), WatchDead(false), Funeral(true), Prison(true), BeachPart(false), Reincarnate(false), ReCurr(false), ControlSupport(false), Auto_Save(true), Menu_Left_Side(true), ControlA(0), ControlB(0), Lang_Set(-1), BeachPed(true), Tramps(true), Highclass(true), Midclass(true), Lowclass(true), Business(true), Bodybuilder(true), GangStars(true), Epsilon(true), Jogger(true), Golfer(true), Hiker(true), Methaddict(true), Rural(true), Cyclist(true), LGBTWXYZ(true), PoolPeds(true), Workers(true), Jetski(true), BikeATV(true), Services(true), Pilot(true), Animals(true), Yankton(true), Cayo(true), Loging(true), Jan(true), Feb(true), Mar(false), Apr(false), May(false), Jun(false), Jul(false), Aug(false), Sep(false), Oct(false), Nov(false), Dec(true) {}
    };

    struct Vector4
    {
    public:
        float X;
        float Y;
        float Z;
        float R;
    public:
        Vector4(float x, float y, float z, float r)
            : X(x), Y(y), Z(z), R(r) {}
        Vector4(Vector3 pos)
            : X(pos.x), Y(pos.y), Z(pos.z), R(0.0f) {}
    };
    struct Point
    {
    public:
        int X;
        int Y;
    public:
        Point(int x, int y)
            : X(x), Y(y) {}
    };
    struct Size
    {
    public:
        int Width;
        int Height;
    public:
        Size(int width, int height)
            : Width(width), Height(height) {}
    };
    struct RGBA
    {
    public:
        int R;
        int G;
        int B;
        int A;
    public:
        RGBA(int r, int g, int b, int a)
            : R(r), G(g), B(b), A(a) {}
    };

    class FubarVectors
    {
    public:
        int Area;
        Vector4 Car;
        Vector4 Ped;
        std::string Name;
        int Number;

    public:
        FubarVectors(int area, Vector4 car, Vector4 ped, std::string name, int number)
            : Area(area), Car(car), Ped(ped), Name(name), Number(number) {}
    };

    class AnimatedActions
    {
    public:
        std::string Libary;
        std::string Action;

    public:
        AnimatedActions(std::string libary, std::string action)
            : Libary(libary), Action(action) {}
    };
    class AnimList
    {
    public:
        AnimatedActions Start;
        AnimatedActions End;
        std::vector<AnimatedActions> Middle;

    public:
        AnimList(AnimatedActions start, AnimatedActions end, std::vector<AnimatedActions> middle)
            : Start(start), Middle(middle), End(end) {}

    };

    class Weap_Read 
    {
    public:
        std::string MyWeapon;
        std::string MyDecription;
        int Tint;
        bool Addons;
        bool Liverys;
    public:
        Weap_Read(std::string myWeapon, std::string myDecription, int tint, bool addons, bool liverys)
            : MyWeapon(myWeapon), MyDecription(myDecription), Tint(tint), Addons(addons), Liverys(liverys) {}
    };
    class Weap_Addons 
    {
    public:
        std::string MyComponent;
        std::string MyDecription;
    public:
            Weap_Addons(std::string myComponent, std::string myDecription)
            : MyComponent(myComponent), MyDecription(myDecription) {}
    };
    class WeaponSaver
    {
    public:
        std::string MyWeapon;
        std::vector<std::string> MyAddons;
        int Ammo;
        int TintSet;
        int WeapTint;
    public:
        WeaponSaver(std::string myWeapon, std::vector<std::string> myAddons, int ammo, int tintSet, int weapTint)
            : MyWeapon(myWeapon), MyAddons(myAddons), Ammo(ammo), TintSet(tintSet), WeapTint(weapTint) {}
    };
    class HairSets
    {
    public:
        int Comp;
        int Text;
        std::string HandName;
        std::string Name;
        int OverLib;
        int Over;

    public:
        HairSets(int comp, int text, std::string handName, std::string name, int overLib, int over)
            : Comp(comp), Text(text), HandName(handName), Name(name), OverLib(overLib), Over(over) {}
        HairSets()
            : Comp(0), Text(0), HandName(""), Name(""), OverLib(0), Over(0) {}
    };
    class Tattoo
    {
    public:
        std::string BaseName;
        std::string TatName;
        std::string Name;

    public:
        Tattoo(std::string baseName, std::string tatName, std::string name)
            : BaseName(baseName), TatName(tatName), Name(name) {}
    };
    class FreeOverLay
    {
    public:
        int Colour;
        int Overlay;
        int OverCol;
        float OverOpc;

    public:
        FreeOverLay(int colour, int overlay, int overCol, float overOpc)
            : Colour(colour), Overlay(overlay), OverCol(overCol), OverOpc(overOpc) {}
    };
    class FaceBank
    {
    public:
        int ShapeFirstID;
        int ShapeSecondID;
        int ShapeThirdID;
        int SkinFirstID;
        int SkinSecondID;
        int SkinThirdID;
        float ShapeMix;
        float SkinMix;
        float ThirdMix;
        int IsParent;
    public:
        FaceBank(int shapeFirstID, int shapeSecondID, float shapeMix, float skinMix, float thirdMix)
            : ShapeFirstID(shapeFirstID), ShapeSecondID(shapeSecondID), ShapeThirdID(shapeFirstID), SkinFirstID(shapeFirstID), SkinSecondID(shapeSecondID), SkinThirdID(shapeFirstID), ShapeMix(shapeMix), SkinMix(skinMix), ThirdMix(thirdMix), IsParent(0) {}
        FaceBank()
            : ShapeFirstID(0), ShapeSecondID(0), ShapeThirdID(0), SkinFirstID(0), SkinSecondID(0), SkinThirdID(0), ShapeMix(0.0f), SkinMix(0.0f), ThirdMix(0.0f), IsParent(0) {}
    };
    class ClothX
    {
    public:
        std::string Title;

        Tattoo Badge;

        std::vector<int> ClothA;
        std::vector<int> ClothB;

        std::vector<int> ExtraA;
        std::vector<int> ExtraB;

    public:
        ClothX(std::string title, std::vector<int> clothA, std::vector<int> clothB, std::vector<int> extraA, std::vector<int> extraB)
            : Title(title), Badge(Tattoo("", "", "")), ClothA(clothA), ClothB(clothB), ExtraA(extraA), ExtraB(extraB) {}
    };
    class ClothBank
    {
    public:
        std::string CharName;
        std::string Model;
        Hash ModelHash;
        bool FreeMode;
        int Cloth_Pick;
        std::vector<ClothX> Cothing;
        FaceBank MyFaces;
        bool Male;
        bool Animal_Farm;
        HairSets MyHair;
        int HairColour;
        int HairStreaks;
        int EyeColour;
        std::vector<WeaponSaver> MyWeapons;
        std::vector<FreeOverLay> MyOverlay;
        std::vector<Tattoo> MyTattoo;
        std::vector<float> FaceScale;
        int Voice;
        int Walkies;
        int Moods;
        int PlHealth;
        float PlRunSp;
        float PlSwimSp;

    public:
        ClothBank(std::string name, std::string model, Hash mdelHash, bool freeMode, FaceBank myFaces, bool male, bool animal_Farm, HairSets myHair, int hairColour, int hairStreaks, int eyeColour, int cloth_Pick, std::vector< WeaponSaver> myWeapons, std::vector<FreeOverLay> myOverlay, std::vector<Tattoo> myTattoo, std::vector<ClothX> cothing, std::vector<float> faceScale, int voice, int walkies, int moods, int plHealth, float PlRunSp, float PlSwimSp)
            : CharName(name), Model(model), ModelHash(mdelHash), FreeMode(freeMode), MyFaces(myFaces), Animal_Farm(animal_Farm), Male(male), MyHair(myHair), HairColour(hairColour), HairStreaks(hairStreaks), EyeColour(eyeColour), MyWeapons(myWeapons), MyOverlay(myOverlay), MyTattoo(myTattoo), Cothing(cothing), Cloth_Pick(cloth_Pick), FaceScale(faceScale), Voice(voice), Walkies(walkies), Moods(moods), PlHealth(plHealth), PlRunSp(PlRunSp), PlSwimSp(PlSwimSp) {}
        ClothBank()
            : CharName(""), Model(""), ModelHash(0), FreeMode(false), MyFaces(FaceBank()), Animal_Farm(false), Male(false), MyHair(HairSets()), HairColour(0), HairStreaks(0), EyeColour(0), MyWeapons({}), MyOverlay({}), MyTattoo({}), Cothing({}), Cloth_Pick(0), FaceScale({}), Voice(0), Walkies(0), Moods(0), PlHealth(200), PlRunSp(1.0f), PlSwimSp(1.0f) {}
    };

    class Veh_Set
    {
    public:
        std::string Model;
        Hash ModelHash;
        bool IsPlane;
        bool IsHeli;
        bool PlayerInVeh;
        bool PlayerDriver;
        bool FillVeh;
        bool bFriend;
        int Select;
        int SubSet;
        int RanDriveTo;
        Vector4 SpawnPoint;
        std::vector<Vector4> DriveTo;

    public:
        Veh_Set(std::string model, bool isPlane, bool isHeli, bool playerInVeh, bool playerDriver, bool fillVeh, int select, int subSet, Vector4 spawnPoint, std::vector<Vector4> driveTo)
            : Model(model), ModelHash(0), IsPlane(isPlane), IsHeli(isHeli), PlayerInVeh(playerInVeh), PlayerDriver(playerDriver), FillVeh(fillVeh), bFriend(true), Select(select), SubSet(subSet), RanDriveTo(1), SpawnPoint(spawnPoint), DriveTo(driveTo) {}
    };

    class VehBlips
    {
    public:
        std::string VehicleKey;
        int BlipNo;

    public:
        VehBlips(std::string vehicle, int blipNo)
            : VehicleKey(vehicle), BlipNo(blipNo) {}
    };

    class Ped_Label
    {
    public:
        Ped ThisPed;
        std::string Name;
    public:
        Ped_Label(Ped thisPed, std::string name)
            : ThisPed(thisPed), Name(name) {}
    };

    class MenuRatioSettings
    {
    public:
        float boxWidth;
        float lineHeight;
        float boxTop;
        float lineSpace;
        float boxPosition;
        float textPosition;

        float tickSizeX;
        float tickSizeY;
        float tickX;
        float tickY;
        float tickMulti;

        float sizeX;
        float sizeY;
        float centerX;
        float centerY;
        float posX;
        float posY;
        float rotation;
        float red;
        float green;
        float blue;
        float alfa;

        float arrowLeft;
        float arrowRight;
        float arrowHeight;
        float arrowNumberStart;

        float arrowTickSizeX;
        float arrowTickSizeY;
        float arrowNumberGap;
    public:
        MenuRatioSettings()
            : boxWidth(288.5f), lineHeight(5.5f), boxTop(104.5f), lineSpace(28.0f), boxPosition(19.5f), textPosition(6.0f), tickSizeX(64.0f), tickSizeY(64.0f), tickX(383.5f), tickY(3.6f), tickMulti(41.4f), sizeX(0.227f), sizeY(0.062f), centerX(0.5f), centerY(0.5f), posX(0.128f), posY(0.092f), rotation(0.0f), red(1.0f), green(1.0f), blue(1.0f), alfa(1.0f), arrowLeft(-25.0f), arrowRight(13.0f), arrowHeight(3.85f), arrowNumberStart(260.0f), arrowTickSizeX(32.0f), arrowTickSizeY(32.0f), arrowNumberGap(9.0f) {}
    };
    class MeunFields
    {
    public:
        std::string Title;
        std::string Description;
        bool TickBox;
        bool Numbers;
        int Min;
        int Max;
        int Current;

    public:
        MeunFields(std::string title, std::string description, bool tickBox, bool numbers, int min, int max, int current)
            : Title(title), Description(description), TickBox(tickBox), Numbers(numbers), Min(min), Max(max), Current(current) {}
    };
    class MeunSystem
    {
    public:
        bool _Activate;
        bool _Exit;
        bool _Left;
        bool _Right;
        int waitTime;
        int Low;
        int High;
        int Index;
        bool Scroling;
        Mod_Class::MenuRatioSettings Meun_Screen;
        std::vector<MeunFields> Menu_Form;

    public:
        MeunSystem(int low, int high, bool scroling, std::vector<MeunFields> menu_Form)
            : _Activate(false), _Exit(false), _Left(false), _Right(false), waitTime(150), Low(low), High(high), Index(0), Scroling(scroling), Meun_Screen(Mod_Class::MenuRatioSettings()), Menu_Form(menu_Form) {}
    };
}

namespace Mod_Systems
{
    Hash MyHashKey(const std::string& name);

    std::string GetExeFileName();
    std::string GetDir();
    std::string TimeDate();
    void DirectoryTest();
    bool File_exists(const std::string& filename);
    void Write_ini(const std::string& file, const std::vector<std::string>& text);
    void Delete_ini(const std::string& filename);
    std::vector<std::string> Read_ini(const std::string& fileName);

    void LoggerLight(const std::string& text);

    void Play_wav(const std::string& soundFile);

    std::vector<std::string> Convert_to_strings(const std::vector<int>& text);
    int Find_String_Pos(const std::vector<std::string>& stringList, const std::string& item);

    bool Contains_int(const std::vector<int>& intList, int item);
    bool Contains_string(const std::string& line, const std::string& wholeString);
    bool Contains_string(char line, const std::string& wholeString);
    int Find_char_position(char chars, const std::string& wholeString);
    int Find_char_position(const std::string& chars, const std::string& wholeString);
    
    int Convert_to_int(const std::string& line);
    float Convert_to_float(const std::string& line);
    bool Convert_to_bool(const std::string& line);
    std::string Remove_char61(const std::string& line);
    float Two_decimal(const std::string& num);

    int DayOfWeek();

    float RandomFloat(float min, float max);
    int RandomInt(int min, int max);
    void NewNums(std::vector<int>* intList,int min, int max);
    int LessRandomInt(const std::string& file, int min, int max);
    int LessRandomInt(const std::string& file, const std::vector<int>& ranNum);

    bool PressAnyKey();

    void StartScript(const std::string& scriptName, int buffer);

    void ReBuildIni(void* obj);
    void FindSettings(Mod_Class::Settings_Ini* modSets);

    void FindWeapons(std::vector<Mod_Class::Weap_Read>* myWeaps, const std::string& file);
    void FindWeaponComponents(std::vector<Mod_Class::Weap_Addons>* myWeaps, const std::string& file, const std::string& weapon);
    void FindWeaponTints(std::vector<std::string>* myWeaps, int list);

    void SaveMyWeaps();
    std::vector<Mod_Class::WeaponSaver> LoadSavedWeapons();
    std::vector<Mod_Class::WeaponSaver> BuildWeaponList();

    void LoadLang();

    void menu_beep();

    void get_button_state(bool* a, bool* b, bool* up, bool* down, bool* l, bool* r, bool* shutDown);
    void Menu_Button_state(bool* returnBool, DWORD myButton);
    int FindKeyBinds(bool controler);

    int InGameTime();
    bool IsIsSafe(int key);

    void LoadSavedPeds(Mod_Class::ClothBank& clothBank);
    void SaveClothBank(const Mod_Class::ClothBank& clothBank);

    void AddMonies(int amount);

    void FindAddCars();
    void FindAddPeds();
    void WeatherReport(int wet);
    void RandomWeatherTime();
}

namespace Mod_Maths
{
    Vector3 NewVector3(float x, float y, float z);
    Vector3 NewVector3(Mod_Class::Vector4 pos);
    float GetAngle(Vector3 postion1, Vector3 postion2);
    float DistanceTo(Vector3 postion1, Vector3 postion2);
    float DistanceTo(Entity entity1, Entity entity2);
    float DistanceTo(Entity entity1, Mod_Class::Vector4 entity2);
    float DistanceTo(Entity entity1, Vector3 postion2);
    float DistanceTo(Mod_Class::Vector4 postion1, Vector3 postion2);
    float DistanceTo(Mod_Class::Vector4 postion1, Mod_Class::Vector4 postion2);

    Vector3 MyWayPoint();
    Vector3 EntPosition(Entity ent);
    Vector3 PlayerPosi();
    Vector3 RightOfEntity(Entity ent);
    Vector3 FowardOf(Entity ent, float multi, bool inFront);
    Vector3 RightOf(Entity ent, float multi, bool inFront);

    Mod_Class::Vector4 GetPosV4(Entity ent);
    Mod_Class::Vector4 PlayerV4();
    Mod_Class::Vector4 InAreaOf(Mod_Class::Vector4  area, float minDist, float maxDist);
    Mod_Class::Vector4 InAreaOf(Vector3 area, float minDist, float maxDist);
    Mod_Class::Vector4 NearByStreet(Mod_Class::Vector4 area);

    Mod_Class::Vector4 FindPedSpPoint(Vector3 Pos);

    bool NotTheSame(Mod_Class::Vector4 postion1, Mod_Class::Vector4 postion2);
    float GroundHight(Vector3 postion);

    std::vector<Vector3> BuildFlightPath(Vector3 start);

    bool YanktonIPL();
    bool CayoPericoIPL();

    void AnyPreActives(int select, bool mainLand);
}

namespace Mod_Entitys
{
    int AddRelationship(const std::string& name);
    Hash GetRelationship();
    void SetRelBetween_Gp(Hash group1, Hash group2, int relation);
    void SetRelationType(bool friendly);

    void MoveEntity(Entity ent, Vector3 position);
    void MoveEntity(Entity ent, Mod_Class::Vector4 position);
    void StayOnGround(Vehicle vic);

    int GetPedOverlayValues(int overlay);
    int GetPedOverlay(Ped peddy, int overlay);

    std::vector<int> RandVehModsist();
    Prop BuildProps(const std::string& propName, Vector3 vPos, Vector3 vRot, bool bPush, bool Frozen);
    Prop BuildProps(const std::string& propName, Mod_Class::Vector4 vPos, bool bPush, bool Frozen);

    void EraseBlip(Blip blippy);
    void ClearAllPeds();
    void ClearAllEntitys(bool andPeds);

    int OhMyBlip(Vehicle vic);

    Prop FindingProps(Vector3 area, float radius, const std::string& modelHash);
    Prop FindingProps(Mod_Class::Vector4 area, float radius, const std::string& modelHash);

    int FindUSeat(Vehicle vic);
    void WarptoAnyVeh(Vehicle vic, Ped peddy, int seat);
    void GetOutVehicle(Ped peddy);
    void EmptyVeh(Vehicle vic);
    bool InSameVeh(Ped peddy);

    void BlipFiler(Blip blippy, int blipType, const std::string& name, int colour);
    Blip PedBlimp(Blip blippy, Ped peddy, int blipType, const std::string& name, int colour, bool heading);
    Blip LocalBlip(Blip blippy, Mod_Class::Vector4 local, int blipType, const std::string& name, int colour);

    void GetInVehicle(Ped peddy, Vehicle vic, int seat, bool clearSeat);
    void PlayerEnterVeh(Vehicle vic);

    void WalkingStyle(Ped peddy, const std::string& anim);
    void ForceAnim(Ped peddy, const std::string& animDict, const std::string& animName, Vector3 pos, Vector3 rot);
    void ForceAnim(Ped peddy, const std::string& animDict, const std::string& animName, Mod_Class::Vector4 pos);
    void ForceSenario(const std::string& senareo, Mod_Class::Vector4 pos, bool sitting);
    void RunAnimSeq(Mod_Class::AnimList animList, Mod_Class::Vector4 pos);
    void DanceDanceDance(Ped peddy);
    void SunningIt(Ped peddy, Mod_Class::Vector4 pos);

    void PlayHorn(Vehicle vic, int duration);
    int LandingGear(Vehicle vic);
    void LandNearHeli(Ped Peddy, Vehicle vic, Vector3 target);
    void LandNearPlane(Ped Peddy, Vehicle vic, Vector3 start, Vector3 finish);

    void WalkHere(Ped peddy, Mod_Class::Vector4 dest);
    void RunHere(Ped peddy, Vector3 dest);
    void DriveAround(Ped peddy);
    void DriveToooPed(Ped peddy, Ped target, bool runOver);
    void DriveBye(Ped peddy, Ped target, int vehType);
    void FlyHeli(Ped peddy, Vehicle vic, Vector3 dest, float speed, float landing);
    void FlyPlane(Ped peddy, Vehicle vic, Vector3 dest);
    void DriveToooDest(Ped peddy, Vector3 dest, float speed);
    void DriveDirect(Ped peddy, Vector3 dest, float speed);

    void FightPlayer(Ped peddy, bool inVeh, int vehType);
    void GreefWar(Ped peddy, Ped target);
    void JogOn(const std::vector<Mod_Class::Vector4>& destList, int start);
    void MethEdd(bool act);

    void GunningIt(Ped peddy, std::vector<Mod_Class::WeaponSaver>& gunList);
    void GunningIt(Ped peddy, int gun);

    void MaxOutAllModsNoWheels(Vehicle vic, int vehType);
    void MakeModsNotWar(Vehicle vic, std::vector<int>* modsList);

    void PoliceAcadamy(bool togg);

    std::vector<std::string> FindCloths(Hash UserName);
    Mod_Class::ClothX LoadCloths(const std::string& file);

    int SizeUpHairList(bool male);
    Mod_Class::HairSets PickAStyle(int style, bool male);
    Mod_Class::HairSets PickAStyle(bool male);
    Mod_Class::FaceBank AddFace(bool male);
    std::vector<Mod_Class::FreeOverLay> AddOverLay(bool male, bool freeMode);
    Mod_Class::ClothBank NewFreeModePed(int male);

    void ThemVoices(const std::string& voice);
    void PullingFaces(const std::string& aniName);

    Mod_Class::ClothX GetYourTogs(Ped peddy);
    Mod_Class::FaceBank FreeFaces(Ped peddy, bool free);
    std::string RandomPed(int pedtype, int subType);
    Mod_Class::ClothBank NewClothBank(const std::string& pedTitle);
    Mod_Class::ClothBank NewClothBank(int pedtype, int subType);
    Mod_Class::ClothBank PlayerClothBank();

    void ApplyTats(Ped peddy, Mod_Class::ClothBank* getTats);
    void OnlineDress(Ped peddy, Mod_Class::ClothX* cloths);
    void SetingtheHair(Ped peddy, Mod_Class::HairSets* hair);
    void OnlineFaces(Ped peddy, Mod_Class::ClothBank* feats);

    Ped PlayerPedGen(Mod_Class::Vector4 pos, Mod_Class::ClothBank* clothBank, bool onFoot, bool isfriend);
    Ped PlayerPedGen(Mod_Class::Vector4 pos, int set, int Subset, bool onFoot, bool isfriend);
    Ped PlayerPedGen(Mod_Class::Vector4 pos, const std::string& pedModel, bool onFoot, bool isfriend);

    void RepoPedPlayer(Ped target);
    void ChangePlayer(Hash modelHash);
    void ChangePlayer(int select, int subset, int weap);
    void SavedPlayer(Mod_Class::ClothBank* clothBank, int weap);

    std::string RandVeh(int vehList, int subSet);
    bool IsItARealVehicle(const std::string& vehName);
    bool HasASeat(Vehicle vic);

    Vehicle VehicleSpawn(Mod_Class::Veh_Set vehSet);

    void CollectPeds(std::vector<Ped>* pedList);
    Ped NearByPed(Mod_Class::Vector4 area, float areaMin, float areaMax);
    
    void WatchDeath();
    void Reicarnations();

    void CayoAudio();
    void CayoPartay();
}

namespace Mod_Data
{
    inline int FollowMe = 0;
    inline Hash GP_Player = 0;
    inline Hash Gp_Friend = 0;
    inline Hash GP_Attack = 0;
    inline Hash Gp_Follow = 0;
    inline Hash GP_Mental = 0;

    inline std::vector<std::string> MainChar = { "player_zero", "player_one", "player_two", "mp_m_freemode_01", "mp_f_freemode_01" };
    inline std::vector<Hash> MainProtags;

    inline bool Meth_Act = false;
    inline bool First_Load = false;
    inline bool Yankton_Loaded = false;
    inline bool Cayo_Loaded = false;
    inline bool CallTheCops = false;
    inline bool Deputize = false;
    inline bool BackStagePass = false;
    inline bool GotPlayZero = false;
    inline bool CanSnow = false;
    inline bool MissingFilesNag = false;
    inline bool Close_Menu = false;

    inline std::string Ahhhh = "";

    inline bool PlayerIsDead = false;
    inline bool ShowMobile = false;

    inline int Side_Add_Time = 0;
    inline int AnyKeyTimer = 0;

    inline const std::string DirRandStart = Mod_Systems::GetDir() + "/RandomStart";
    inline const std::string DirRandNumb = DirRandStart + "/Randoms";
    inline const std::string DirSavedPed = DirRandStart + "/SavedPeds";
    inline const std::string DirWeapons = DirRandStart + "/Weapons";
    inline const std::string DirVehicles = DirRandStart + "/Vehicles";
    inline const std::string DirTranslate = DirRandStart + "/Translate";
    inline const std::string DirCustPeds = DirRandStart + "/Peds";

    inline const std::string DirectOutfitFolder = Mod_Systems::GetDir() + "/Outfits";
    inline const std::string DirectOutfitMale = DirectOutfitFolder + "/Male";
    inline const std::string DirectOutfitFemale = DirectOutfitFolder + "/Female";
    inline const std::string DirectOutfitMichael = DirectOutfitFolder + "/Michael";
    inline const std::string DirectOutfitFranklin = DirectOutfitFolder + "/Franklin";
    inline const std::string DirectOutfitTrevor = DirectOutfitFolder + "/Trevor";

    inline const std::string BannerFile = DirRandStart + "/RandomStartBanner@256x64.png";
    inline const std::string LoggingFile = DirRandStart + "/LoggerLight.txt";
    inline const std::string SettingsFile = DirRandStart + "/Settings.ini";
    inline const std::string SaveWeapsFile = DirRandStart + "/MyWeaps.ini";

    inline const std::string ZeroYank = Mod_Systems::GetDir() + "/PlayerZero/Yankton.txt";
    inline const std::string ZeroCayo = Mod_Systems::GetDir() + "/PlayerZero/Cayo.txt";

    inline const std::string WeapCompon = DirWeapons + "/GROUP_COMPONENTS.ini";
    inline const std::string WeapLiverys = DirWeapons + "/GROUP_LIVARY.ini";
    inline const std::string WeapTints = DirWeapons + "/GROUP_TINTS.ini";

    inline const std::vector<std::string> LangosPick = {
        "English=",
        "French=",
        "German=",
        "Italian=",
        "Spanish=",
        "Portuguese=",
        "Polish=",
        "Russian=",
        "Korean=",
        "TraditionalChinese=",
        "Japanese=",
        "Mexican=",
        "SimplifiedChinese="
    };
    inline const std::vector<std::string> WeaponsDir = {
        Mod_Systems::GetDir() + "/RandomStart/Weapons/GROUP_MELEE.ini",
        Mod_Systems::GetDir() + "/RandomStart/Weapons/GROUP_THROWN.ini",
        Mod_Systems::GetDir() + "/RandomStart/Weapons/GROUP_PISTOL.ini",
        Mod_Systems::GetDir() + "/RandomStart/Weapons/GROUP_SMG.ini",
        Mod_Systems::GetDir() + "/RandomStart/Weapons/GROUP_SHOTGUN.ini",
        Mod_Systems::GetDir() + "/RandomStart/Weapons/GROUP_RIFLE.ini",
        Mod_Systems::GetDir() + "/RandomStart/Weapons/GROUP_SNIPER.ini",
        Mod_Systems::GetDir() + "/RandomStart/Weapons/GROUP_MG.ini",
        Mod_Systems::GetDir() + "/RandomStart/Weapons/GROUP_HEAVY.ini"
    };

    inline const std::vector<std::string> TranlsteDir = {
        Mod_Systems::GetDir() + "/RandomStart/Translate/English.txt",
        Mod_Systems::GetDir() + "/RandomStart/Translate/French.txt",
        Mod_Systems::GetDir() + "/RandomStart/Translate/German.txt",
        Mod_Systems::GetDir() + "/RandomStart/Translate/Italian.txt",
        Mod_Systems::GetDir() + "/RandomStart/Translate/Spanish.txt",
        Mod_Systems::GetDir() + "/RandomStart/Translate/Portuguese.txt",
        Mod_Systems::GetDir() + "/RandomStart/Translate/Polish.txt",
        Mod_Systems::GetDir() + "/RandomStart/Translate/Russian.txt",
        Mod_Systems::GetDir() + "/RandomStart/Translate/Korean.txt",
        Mod_Systems::GetDir() + "/RandomStart/Translate/Chinese.txt",
        Mod_Systems::GetDir() + "/RandomStart/Translate/Japanese.txt",
        Mod_Systems::GetDir() + "/RandomStart/Translate/Spanish.txt",
        Mod_Systems::GetDir() + "/RandomStart/Translate/ChineseSimplify.txt"
    };
    inline std::vector<std::string> RSLangMenu = {
            "Enter",                                                                                    //0
            "Back",                                                                                     //1
            "Left",                                                                                     //2
            "Right",                                                                                    //3
            "Random Scenarios",                                                                         //4
            "Select available or launch a random scenario.",                                            //5
            "Save Ped Menu",                                                                            //6
            "Change customize and save characters.",                                                    //7
            "Random Start",                                                                             //8
            "Select a random scenario when game loads.",                                                //9
            "Random Ped",                                                                               //10
            "Load as or re-spawn as a random ped (includes animals).",                                  //11
            "Saved Ped",                                                                                //12
            "Load as or re-spawn as a saved ped.",                                                      //13
            "Reincarnation",                                                                            //14
            "Life after death?",                                                                        //15
            "Re-spawn",                                                                                 //16
            "Return as your current character in the area you died in.",                                //17
            "Funeral",                                                                                  //18
            "If you are using a random or non main character have a funeral service on death.",         //19
            "Prison",                                                                                   //20
            "Go straight to Bolingbroke do not pass go do not collect 200.",                            //21
            "Random Weapons",                                                                           //22
            "Get a random weapon selection or keep your current weapons.",                              //23
            "Capture Weapon Load-out",                                                                  //24
            "Save you current weapon selection.",                                                       //25
            "Change Key-bindings",                                                                      //26
            "Select menu load key.",                                                                    //27
            "Beach Ped",                                                                                //28
            "Sun bathing and motor boating.",                                                           //29
            "Tramps",                                                                                   //30
            "Down and out in Los Santos.",                                                              //31
            "High class",                                                                               //32
            "Nice house, nice car, nice weather.",                                                      //33
            "Mid class",                                                                                //34
            "Reasonable house, reasonable car, reasonable weather.",                                    //35
            "Low class",                                                                                //36
            "Rubbish house, trash car, crap weather.",                                                  //37
            "Business",                                                                                 //38
            "The high flying Los Santos elite.",                                                        //39
            "Body builder",                                                                             //40
            "Use the facilities at muscle beach.",                                                      //41
            "Gangsters",                                                                                //42
            "Defend your turf in the Los Santos war zones.",                                            //43
            "Epsilon ",                                                                                 //44
            "Join a cult and look down on the non-believers.",                                          //45
            "Jogger",                                                                                   //46
            "Take a run in some random location.",                                                      //47
            "Golfer",                                                                                   //48
            "Play a round or just burn up the turf in your caddy.",                                     //49
            "Hiker",                                                                                    //50
            "Explore the wilderness of Los Santos.",                                                    //51
            "Meth addict",                                                                              //52
            "Strawberry fields for ever.",                                                              //53
            "Rural",                                                                                    //54
            "Down on the farm.",                                                                        //55
            "Cyclist",                                                                                  //56
            "Put on the lycra and start peddling.",                                                     //57
            "LGBTWXYZ",                                                                                 //58
            "I am the very model of a modern Major-General I've information vegetable, animal, and mineral.",//59
            "Pool Peds",                                                                                //60
            "Take a swim or just chill by the pool.",                                                   //61
            "Workers",                                                                                  //62
            "The many trades and occupations in Los Santos.",                                           //63
            "Jet ski",                                                                                  //64
            "Race your jet-ski or just ride around for fun.",                                           //65
            "Bike/ATV",                                                                                 //66
            "Do some off-roading around Los Santos.",                                                   //67
            "Services",                                                                                 //68
            "Do your civic duty with fire, police, ambulance or military.",                             //69
            "Pilot",                                                                                    //70
            "Earn your wings gallivanting above Los Santos.",                                           //71
            "Animals",                                                                                  //72
            "Soar like a bird, strut like a deer, swim like a fish.",                                   //73
            "Yankton",                                                                                  //74
            "Visit snowy Yankton.",                                                                     //75
            "Cayo Piero",                                                                               //76
            "Visit sunny Cayo Piero.",                                                                  //77
            "Saved Peds",                                                                               //78
            "Select and edit your ped collection.",                                                     //79
            "Save current ped",                                                                         //80
            "save your current character.",                                                             //81
            "Freemode Ped",                                                                             //82
            "Generate a random freemode ped.",                                                          //83
            "Reposes Ped",                                                                              //84
            "Become a nearby ped.",                                                                     //85
            "Select a Ped",                                                                             //86
            "Rename Ped",                                                                               //87
            "Change the name of your ped.",                                                             //88
            "Change Outfit",                                                                            //89
            "Change your outfit.",                                                                      //90
            "Tattoo Pallor",                                                                            //91
            "Add Tattoos to your character.",                                                           //92
            "Set Hair Style",                                                                           //93
            "Eye Colour",                                                                               //94
            "Pick the colour of your eyes .",                                                           //95
            "Pick Hair Colour",                                                                         //96
            "Pick Hair Streaks",                                                                        //97
            "Set Overlays",                                                                             //98
            "Ped decals like age blush facial hair and make-up.",                                       //99
            "Alter Face Shape",                                                                         //100
            "Change position of chin, mouth, nose.",                                                    //101
            "Change Parents",                                                                           //102
            "Alter the base parents of your freemode character.",                                       //103
            "Set Voice",                                                                                //104
            "Save Changes",                                                                             //105
            "Create or update saved peds ini.",                                                         //106
            "Delete Ped",                                                                               //107
            "Remove this ped from saved peds directory.",                                               //108
            "Select outfit",                                                                            //109  
            "Create New Outfit",                                                                        //110
            "Save a new outfit on your character.",                                                     //111
            "Edit Outfits",                                                                             //112
            "edit the components on current outfit.",                                                   //113
            "Edit Props",                                                                               //114
            "Pick hats and glasses.",                                                                   //115
            "Pre-made outfits",                                                                         //116
            "Base Component",                                                                           //117
            "Texture",                                                                                  //118
            "Select ",                                                                                  //119
            "Opacity",                                                                                  //120
            "Colour",                                                                                   //121
            "First Parent",                                                                             //122
            "Second Parent",                                                                            //123
            "Shape Mix",                                                                                //124
            "Skin Mix",                                                                                 //125
            "Third Mix",                                                                                //126
            "Face",                                                                                     //127
            "Head",                                                                                     //128
            "Hair",                                                                                     //129
            "Torso",                                                                                    //130
            "Legs",                                                                                     //131
            "Back Packs",                                                                               //132
            "Feet",                                                                                     //133
            "Accessories",                                                                              //134
            "Top Add-ons",                                                                              //135
            "Armour",                                                                                   //136
            "Textures",                                                                                 //137
            "Coats",                                                                                    //138
            "Hats",                                                                                     //139
            "Glasses",                                                                                  //140
            "Ears",                                                                                     //141
            "Watches",                                                                                  //142
            "Torso",                                                                                    //143
            "Head",                                                                                     //144
            "Left Arm",                                                                                 //145
            "Right Arm",                                                                                //146
            "Left Leg",                                                                                 //147
            "Right Leg",                                                                                //148
            "Back",                                                                                     //149
            "Chest",                                                                                    //150
            "Stomach",                                                                                  //151
            "Nose Width",                                                                               //152
            "Nose Peak Hight",                                                                          //153
            "Nose Peak Length",                                                                         //154
            "Nose Bone_High",                                                                           //155
            "Nose Peak Lowering",                                                                       //156
            "Nose Bone Twist",                                                                          //157
            "Eye Brow High",                                                                            //158
            "Eye Brow Forward",                                                                         //159
            "Cheeks Bone High",                                                                         //160
            "Cheeks Bone Width",                                                                        //161
            "Cheeks Width",                                                                             //162
            "Eyes Opening",                                                                             //163
            "Lips Thickness",                                                                           //164
            "Jaw Bone Width 'Bone size to sides",                                                       //165
            "Jaw Bone Back Length 'Bone size to back",                                                  //166
            "Chimp_Bone_Lowering 'Go Down",                                                             //167
            "Chimp Bone Length 'Go forward",                                                            //168
            "Chimp Bone Width", "Chimp Hole",                                                           //169
            "Neck Thickness",                                                                           //170
            "Blemishes",                                                                                //171
            "Facial Hair",                                                                              //172
            "Eyebrows",                                                                                 //173
            "Ageing",                                                                                   //174
            "Make-up",                                                                                  //175
            "Blush",                                                                                    //176
            "Complexion",                                                                               //177
            "Sun Damage",                                                                               //178
            "Lipstick",                                                                                 //179
            "Moles & Freckles",                                                                         //180
            "Chest Hair",                                                                               //181
            "Body Blemishes",                                                                           //182
            "Add Body Blemishes",                                                                       //183
            "Select a Keyboard Key",                                                                    //184
            "Sets the menu open key.",                                                                  //185
            "Select a Controller Combo",                                                                //186
            "Choose two controller keys to open menu.",                                                 //187
            "Hold ~INPUT_VEH_EXIT~ to take control",                                                    //188
            "Hold the key you would like to use.",                                                      //189
            "Key Changed",                                                                              //190
            "Hold ~INPUT_VEH_EXIT~ to hide under van",                                                  //191
            "Hold ~INPUT_VEH_EXIT~ to hide in waste bin",                                               //192
            "Top Decal",                                                                                //193
            "Explore the World: GTA games often feature vast open worlds with a lot of hidden content, collectibles, and easter eggs. Take your time to explore and enjoy the scenery.",
            "Follow the Story: While you can engage in random chaos, the main story missions provide structure and context for the game. Completing these missions often unlocks new content and areas.",
            "Use Cover: In gunfights, always use cover to protect yourself. Pop out to shoot, then take cover again. This reduces the chances of getting shot.",
            "Manage Your Health: Keep an eye on your health and armor levels. You can usually find health packs and armor scattered throughout the game world. Stock up before difficult missions.",
            "Plan Your Getaways: After committing a crime, have an escape plan. Know where you're going and what you'll do to evade the police.",
            "Invest in Properties: In some GTA games, you can buy properties. These can provide a passive income and sometimes even offer other benefits.",
            "Experiment with Vehicles: GTA games have a wide variety of vehicles, from cars to planes to bicycles. Experiment with different vehicles to see which ones suit your style and mission needs.",
            "Customize Your Character: Many GTA games allow you to customize your character's appearance. Experiment with clothing and accessories to create your own unique style.",
            "Use the Internet: In later GTA games, characters have smartphones and access to the internet. You can use it to buy vehicles, properties, and more.",
            "Save Your Game: Don't forget to save your progress regularly, especially after completing important missions. This will prevent you from losing a lot of progress in case you fail a mission or get busted.",
            "Don't Ignore Side Missions: Side missions can offer fun and unique experiences, as well as rewards like weapons, money, and even character upgrades.",
            "Respect Traffic Rules (or Not): Sometimes following traffic rules can help you blend in and avoid the attention of the police. On the other hand, reckless driving can be a lot of fun. It's up to you!",
            "Be Mindful of Police: Committing crimes will get the attention of the police. Pay attention to wanted levels and use Pay 'n' Spray or other hiding spots to lose the cops.",
            "Play with Friends: If the game supports it, playing GTA with friends can be a blast. You can complete missions together or engage in chaotic, open-world mayhem.",
            "Have Fun: Ultimately, GTA games are meant to be enjoyed. Whether you prefer causing chaos, following the story, or just exploring, remember that it's a game, and the goal is to have fun.",
            "Press ~INPUT_TALK~ to change dance, hold ~INPUT_VEH_EXIT~ to  stop Dancing",               //209
            "Press ~INPUT_TALK~ to start dancing",                                                      //210
            "press ~INPUT_DUCK~ to select a ped, press ~INPUT_SPRINT~ to  become this ped, Press ~INPUT_RELOAD~ to Close.",//211
            "Press ~INPUT_TALK~ to change action, hold ~INPUT_VEH_EXIT~ to exit.",                      //212
            "Winter is Coming",                                                                         //213
            "January",                                                                                  //214
            "February",                                                                                 //215
            "March",                                                                                    //216
            "April",                                                                                    //217
            "May",                                                                                      //218
            "June",                                                                                     //219
            "July",                                                                                     //220
            "August",                                                                                   //221
            "September",                                                                                //222
            "October",                                                                                  //223
            "November",                                                                                 //224
            "December",                                                                                 //225
            "Set your winter months",                                                                   //226
            "Edit",                                                                                     //227
            "Male",                                                                                     //228
            "Female",                                                                                   //229
            "Options",                                                                                  //230
            "Random Start Settings",                                                                    //231
            "Auto Save-Peds",                                                                           //232
            "Saved-ped changes are automaticly saved",                                                  //233
            "Menu Orientation",                                                                         //234
            "Change menu location",                                                                     //235
            "Change mod language",                                                                      //236
            "Toggle All",                                                                               //237
            "Enter a name for your Saved-Ped",                                                          //238
            "Enter a name for your outfit",                                                             //239
            "Face Moods",                                                                               //240
            "Walking Style",                                                                            //241
            "Weapon Load-out",                                                                          //242
            "Create a custom weapon load-out for your Save-Ped",                                        //243
            "Remove all tattoos",                                                                       //244
            "Melee",                                                                                    //245
            "Thrown",                                                                                   //246
            "Pistol",                                                                                   //247
            "SMG",                                                                                      //248
            "Shotgun",                                                                                  //249
            "Rifle",                                                                                    //250
            "Sniper",                                                                                   //251
            "MG",                                                                                       //252
            "Heavy",                                                                                    //253
            "Clear Load-out",                                                                           //254
            "No Tints Available",                                                                       //255
            "Add-ons",                                                                                  //256
            "Livery's",                                                                                 //257
            "Tint",                                                                                     //258
            "No Add-ons Available",                                                                     //259
            "No Livery's Available",                                                                    //260
            "Shirt Label",                                                                              //261
            "Delete Outfit",                                                                            //262
            "Delete your current outfit.",                                                              //263
            "You are missing V_Functions.asi. please download this from here : https://www.gta5-mods.com/scripts/new-street-phone-missions",  //264
            "Max Health",                                                                               //265
            "Set your max health (110 - 1000)",                                                         //266
            "Run Speed",                                                                                //267
            "Set your run speed multiplier (0 - 1.49)",                                                 //268
            "Swim Speed",                                                                               //269
            "Set your swim speed multiplier (0 - 1.49)",                                                //270
            "Watch your death",                                                                         //271                                            
            "Don't restart untill the anykeys are pressed",                                             //272
            "Blank",                                                                                    //273
            "Blank",                                                                                    //274
            "Blank",                                                                                    //275
            "Blank",                                                                                    //276
            "Blank",                                                                                    //277
            "Blank",                                                                                    //278
            "Blank",                                                                                    //279
            "Blank"                                                                                     //280

    };

    inline Mod_Class::Settings_Ini Mod_Settings = Mod_Class::Settings_Ini();
    inline std::vector<Prop> Prop_List = {};
    inline std::vector<Vehicle> Vehicle_List = {};
    inline std::vector<Ped> Ped_List = {};
    inline std::vector<Mod_Class::Ped_Label> PedLabels = {};
    inline std::vector<Mod_Class::ClothBank> SavedPeds = {};
    inline std::vector<Mod_Class::WeaponSaver> Player_Weaps = {};
    inline std::vector<std::string> Disp_Pick = {};
    inline std::vector<Ped> CayDancers = {};
    inline const std::vector<std::string> TrampSigns = {
    "prop_beggers_sign_01", "prop_beggers_sign_02", "prop_beggers_sign_03", "prop_beggers_sign_04"
    };

    inline const std::vector<Mod_Class::Vector4> BeachLounger = {
        Mod_Class::Vector4(-1901.387f, 601.9302f, 122.747f, 101.2703f),
        Mod_Class::Vector4(-1955.096f, 152.9954f, 84.65206f, 108.163f),
        Mod_Class::Vector4(-3207.767f, 1229.766f, 14.17144f, 333.922f),
        Mod_Class::Vector4(-3007.52f, 36.86938f, 10.11817f, 152.7064f),
        Mod_Class::Vector4(-3012.478f, 25.29012f, 10.11811f, 324.7065f),
        Mod_Class::Vector4(-3023.49f, 24.92224f, 10.11801f, 109.4003f),
        Mod_Class::Vector4(-3036.376f, 31.18606f, 10.11793f, 18.74356f),
        Mod_Class::Vector4(-3048.185f, 42.57432f, 10.16289f, 325.6173f),
        Mod_Class::Vector4(-3055.468f, 54.49728f, 10.11826f, 36.65013f),
        Mod_Class::Vector4(-3044.712f, 64.52509f, 10.11813f, 281.2551f),
        Mod_Class::Vector4(-3028.956f, 49.0123f, 10.1182f, 234.9155f),
        Mod_Class::Vector4(-2958.513f, 15.47114f, 7.963671f, 326.1963f),
        Mod_Class::Vector4(-2931.722f, 2.505281f, 7.595721f, 303.8367f),
        Mod_Class::Vector4(894.2353f, -473.1367f, 59.01067f, 262.7164f),
        Mod_Class::Vector4(822.4598f, -537.9042f, 56.41828f, 293.0066f),
        Mod_Class::Vector4(501.4693f, 222.5012f, 104.739f, 69.37634f),
        Mod_Class::Vector4(496.7185f, 210.1964f, 104.744f, 231.0057f),
        Mod_Class::Vector4(509.9245f, 205.8668f, 104.7699f, 232.22f),
        Mod_Class::Vector4(514.1538f, 217.5587f, 104.8245f, 338.704f),
        Mod_Class::Vector4(293.853f, 484.2852f, 151.1835f, 292.2342f),
        Mod_Class::Vector4(282.8335f, 514.3438f, 150.4887f, 325.3587f),
        Mod_Class::Vector4(245.8542f, 646.533f, 185.8173f, 16.84508f),
        Mod_Class::Vector4(251.5109f, 753.3502f, 199.6893f, 22.97883f),
        Mod_Class::Vector4(257.6632f, 774.6618f, 199.69f, 117.3021f),
        Mod_Class::Vector4(-87.49277f, 949.1955f, 232.8036f, 209.1391f),
        Mod_Class::Vector4(-72.9754f, 950.9635f, 232.801f, 168.9043f),
        Mod_Class::Vector4(-74.11761f, 818.8749f, 235.7165f, 359.0551f),
        Mod_Class::Vector4(-84.36983f, 817.2608f, 235.7032f, 4.507927f),
        Mod_Class::Vector4(-45.13728f, 802.7262f, 227.2023f, 281.186f),
        Mod_Class::Vector4(-43.60674f, 797.9984f, 227.2237f, 288.4688f),
        Mod_Class::Vector4(-45.82627f, 781.0888f, 227.1765f, 287.0849f),
        Mod_Class::Vector4(-147.36f, 871.0223f, 232.6567f, 291.0363f),
        Mod_Class::Vector4(-174.2184f, 875.8726f, 232.6836f, 349.8759f),
        Mod_Class::Vector4(-211.1984f, 995.325f, 231.7272f, 84.40921f),
        Mod_Class::Vector4(-219.6337f, 1000.102f, 232.1182f, 332.9131f),
        Mod_Class::Vector4(-194.386f, 976.9227f, 231.7039f, 287.662f),
        Mod_Class::Vector4(-198.7629f, 662.1785f, 200.6572f, 263.4688f),
        Mod_Class::Vector4(-201.966f, 666.7929f, 200.6002f, 232.783f),
        Mod_Class::Vector4(-329.3861f, 605.4657f, 172.3438f, 10.37949f),
        Mod_Class::Vector4(-325.2376f, 603.5941f, 172.3968f, 325.7649f),
        Mod_Class::Vector4(-290.3098f, 565.5517f, 173.7786f, 31.94912f),
        Mod_Class::Vector4(-226.2798f, 567.7051f, 185.6142f, 269.6378f),
        Mod_Class::Vector4(-188.5987f, 565.8499f, 189.7396f, 344.3721f),
        Mod_Class::Vector4(-102.1416f, 568.8666f, 195.9693f, 9.293203f),
        Mod_Class::Vector4(59.4543f, 537.5726f, 175.8493f, 313.7076f),
        Mod_Class::Vector4(55.05299f, 529.1929f, 175.2981f, 336.7262f),
        Mod_Class::Vector4(42.64702f, 528.0017f, 175.4126f, 37.85212f),
        Mod_Class::Vector4(73.92604f, 543.9423f, 181.494f, 343.4132f),
        Mod_Class::Vector4(79.07658f, 534.4333f, 173.4785f, 294.7078f),
        Mod_Class::Vector4(176.7386f, 549.1556f, 179.9342f, 16.13215f),
        Mod_Class::Vector4(181.1799f, 557.4152f, 180.0801f, 0.2226735f),
        Mod_Class::Vector4(222.3097f, 488.2309f, 140.6522f, 46.94685f),
        Mod_Class::Vector4(222.8971f, 474.3389f, 140.6988f, 133.138f),
        Mod_Class::Vector4(157.1525f, 451.3972f, 140.7081f, 304.3905f),
        Mod_Class::Vector4(90.71783f, 441.566f, 142.2086f, 37.87337f),
        Mod_Class::Vector4(35.74286f, 427.6038f, 143.2353f, 339.422f),
        Mod_Class::Vector4(-14.7762f, 423.3163f, 123.1823f, 88.37698f),
        Mod_Class::Vector4(-7.468292f, 342.6011f, 113.1079f, 279.7206f),
        Mod_Class::Vector4(-12.7883f, 330.1599f, 113.1232f, 231.2084f),
        Mod_Class::Vector4(-190.3212f, 378.0515f, 109.2621f, 11.10603f),
        Mod_Class::Vector4(-253.4126f, 358.4453f, 110.5965f, 14.80021f),
        Mod_Class::Vector4(-325.5653f, 344.3188f, 110.0115f, 26.63357f),
        Mod_Class::Vector4(-374.4421f, 326.4197f, 109.3259f, 32.3867f),
        Mod_Class::Vector4(-356.5861f, 398.2888f, 110.1473f, 26.75199f),
        Mod_Class::Vector4(-433.8472f, 383.3545f, 108.418f, 28.97797f),
        Mod_Class::Vector4(-433.8591f, 429.546f, 113.0959f, 312.1473f),
        Mod_Class::Vector4(-380.8614f, 454.5622f, 112.8019f, 11.90785f),
        Mod_Class::Vector4(-406.7488f, 476.3299f, 120.2951f, 57.12598f),
        Mod_Class::Vector4(-324.6384f, 527.9346f, 120.4905f, 32.08671f),
        Mod_Class::Vector4(-358.9505f, 557.9938f, 126.9182f, 104.3504f),
        Mod_Class::Vector4(-446.1362f, 513.045f, 119.8907f, 46.32145f),
        Mod_Class::Vector4(-476.7184f, 509.8212f, 121.4604f, 53.09084f),
        Mod_Class::Vector4(-504.1373f, 506.2393f, 112.3733f, 58.73829f),
        Mod_Class::Vector4(-498.9734f, 496.5609f, 108.0648f, 284.3159f),
        Mod_Class::Vector4(-516.9915f, 469.8321f, 103.1432f, 129.1857f),
        Mod_Class::Vector4(-483.1294f, 447.3335f, 96.75388f, 275.4441f),
        Mod_Class::Vector4(-477.9137f, 429.6738f, 103.0685f, 246.5339f),
        Mod_Class::Vector4(-499.0058f, 388.1232f, 101.7039f, 30.05921f),
        Mod_Class::Vector4(-586.079f, 458.6164f, 109.0009f, 20.32831f),
        Mod_Class::Vector4(-631.5347f, 464.9187f, 108.8165f, 46.00986f),
        Mod_Class::Vector4(-606.8313f, 449.4947f, 109.5428f, 296.0625f),
        Mod_Class::Vector4(-656.7912f, 459.0228f, 110.3846f, 56.72178f),
        Mod_Class::Vector4(-701.0938f, 420.76f, 106.8859f, 51.83106f),
        Mod_Class::Vector4(-708.643f, 424.4017f, 106.9397f, 77.00647f),
        Mod_Class::Vector4(-879.8017f, 344.328f, 85.07574f, 103.3894f),
        Mod_Class::Vector4(-883.9801f, 326.173f, 83.87492f, 303.1125f),
        Mod_Class::Vector4(-827.2352f, 253.2751f, 79.10831f, 10.6565f),
        Mod_Class::Vector4(-810.2282f, 244.4349f, 86.19154f, 332.8618f),
        Mod_Class::Vector4(-1033.233f, 298.0311f, 66.57035f, 32.3629f),
        Mod_Class::Vector4(-1051.08f, 369.5484f, 69.89721f, 36.30455f),
        Mod_Class::Vector4(-1152.273f, 363.3773f, 71.27719f, 301.1121f),
        Mod_Class::Vector4(-882.2004f, 583.0345f, 100.9214f, 353.243f),
        Mod_Class::Vector4(-850.6298f, 548.9523f, 95.16833f, 252.313f),
        Mod_Class::Vector4(-954.8043f, 597.6062f, 109.2928f, 1.939213f),
        Mod_Class::Vector4(-1018.762f, 564.5819f, 100.4906f, 37.1813f),
        Mod_Class::Vector4(-1069.427f, 576.8413f, 102.8898f, 51.0636f),
        Mod_Class::Vector4(-1197.239f, 492.0663f, 98.79515f, 71.41296f),
        Mod_Class::Vector4(-1452.795f, 483.2077f, 116.1968f, 4.028077f),
        Mod_Class::Vector4(-1517.552f, 398.9835f, 107.4564f, 357.2027f),
        Mod_Class::Vector4(-1396.447f, 506.0385f, 121.0097f, 57.28375f),
        Mod_Class::Vector4(-1324.685f, 544.9714f, 124.2968f, 64.37734f),
        Mod_Class::Vector4(-1080.518f, 716.3364f, 164.4123f, 307.667f),
        Mod_Class::Vector4(-1025.242f, 760.1791f, 171.1999f, 22.85331f),
        Mod_Class::Vector4(-970.848f, 719.126f, 173.54f, 296.7943f),
        Mod_Class::Vector4(-969.4875f, 659.8306f, 158.1113f, 25.15557f),
        Mod_Class::Vector4(-920.6921f, 838.6293f, 185.0639f, 16.80444f),
        Mod_Class::Vector4(-901.6813f, 740.9628f, 182.1482f, 291.5386f),
        Mod_Class::Vector4(-677.4209f, 876.7596f, 225.612f, 8.211149f),
        Mod_Class::Vector4(-1183.655f, -238.6993f, 37.94341f, 306.2998f),
        Mod_Class::Vector4(-1193.935f, -231.5986f, 37.93821f, 43.41149f),
        Mod_Class::Vector4(-1201.769f, -241.0676f, 37.94997f, 88.99844f),
        Mod_Class::Vector4(-3061.349f, 501.9692f, 12.65688f, 121.433f),
        Mod_Class::Vector4(-3074.045f, 449.7134f, 9.635981f, 0.4974319f),
        Mod_Class::Vector4(-3109.201f, 380.7574f, 11.9808f, 42.73471f),
        Mod_Class::Vector4(-3114.576f, 345.7181f, 14.4122f, 8.718539f),
        Mod_Class::Vector4(-3120.02f, 333.911f, 7.535872f, 25.08315f),
        Mod_Class::Vector4(-3121.526f, 312.6818f, 8.376632f, 17.81916f),
        Mod_Class::Vector4(-3135.126f, 230.2289f, 16.14367f, 81.67059f),
        Mod_Class::Vector4(-3049.126f, 555.3533f, 13.50345f, 45.71813f),
        Mod_Class::Vector4(-3052.876f, 566.6545f, 11.17762f, 47.88347f),
        Mod_Class::Vector4(-2991.29f, 767.4554f, 26.68259f, 43.82799f),
        Mod_Class::Vector4(-2960.576f, 731.6472f, 29.43841f, 80.7441f),
        Mod_Class::Vector4(-2950.546f, 650.2014f, 24.15294f, 272.862f),
        Mod_Class::Vector4(-3269.05f, 1031.35f, 16.5972f, 282.7632f),
        Mod_Class::Vector4(-3264.453f, 1061.552f, 11.20902f, 271.4971f),
        Mod_Class::Vector4(-3254.789f, 1074.879f, 14.37858f, 252.587f),
        Mod_Class::Vector4(-3225.153f, 1147.962f, 9.850228f, 236.912f),
        Mod_Class::Vector4(-3212.877f, 1166.313f, 15.75135f, 146.21f),
        Mod_Class::Vector4(-3207.785f, 1229.536f, 14.17278f, 272.4669f),
        Mod_Class::Vector4(-3214.311f, 1283.73f, 12.81738f, 258.4384f),
        Mod_Class::Vector4(-2802.429f, 1452.875f, 100.8793f, 145.6181f),
        Mod_Class::Vector4(-2643.982f, 1871.975f, 160.0868f, 191.9371f),
        Mod_Class::Vector4(-1875.376f, 657.1772f, 129.9833f, 166.5154f),
        Mod_Class::Vector4(-1901.421f, 601.9164f, 122.7439f, 304.3366f),
        Mod_Class::Vector4(-2021.045f, 594.5302f, 117.6942f, 109.7995f),
        Mod_Class::Vector4(-1909.342f, 400.0037f, 96.2742f, 292.831f),
        Mod_Class::Vector4(-1903.799f, 368.8193f, 93.17726f, 265.9415f),
        Mod_Class::Vector4(-1852.098f, 292.5544f, 89.11565f, 36.36103f),
        Mod_Class::Vector4(-1839.925f, 286.1024f, 89.12218f, 293.8094f),
        Mod_Class::Vector4(-1915.589f, 120.2055f, 82.02905f, 211.0226f),
        Mod_Class::Vector4(-1955.406f, 153.1845f, 84.63536f, 297.0201f),
        Mod_Class::Vector4(-2003.177f, 325.5555f, 91.34314f, 332.7921f),
        Mod_Class::Vector4(-2036.243f, 355.9741f, 94.47336f, 118.88f),
        Mod_Class::Vector4(-985.358f, -1488.401f, 5.58675f, 18.46118f),
        Mod_Class::Vector4(-996.9863f, -1493.063f, 5.590873f, 97.63935f),
        Mod_Class::Vector4(-998.8095f, -1504.997f, 5.586561f, 221.2491f),
        Mod_Class::Vector4(-2903.003f, -9.539117f, 7.124954f, 203.3871f)
    };
    inline const std::vector<Mod_Class::Vector4> BeachLay = {
        Mod_Class::Vector4(-1241.018f, -1782.915f, 2.512238f, 311.3507f),
        Mod_Class::Vector4(-1240.467f, -1785.391f, 2.516439f, 244.1266f),
        Mod_Class::Vector4(-1252.934f, -1772.418f, 2.693475f, 299.0875f),
        Mod_Class::Vector4(-1253.307f, -1774.146f, 2.595573f, 278.5364f),
        Mod_Class::Vector4(-1252.684f, -1775.427f, 2.610553f, 302.4079f),
        Mod_Class::Vector4(-1250.159f, -1772.440f, 2.652082f, 96.72529f),
        Mod_Class::Vector4(-1281.400f, -1762.807f, 2.166895f, 304.6913f),
        Mod_Class::Vector4(-1282.367f, -1761.431f, 2.160393f, 309.1139f),
        Mod_Class::Vector4(-1283.043f, -1760.414f, 2.165863f, 311.0824f),
        Mod_Class::Vector4(-1288.296f, -1717.74f, 2.575229f, 227.5724f),
        Mod_Class::Vector4(-1289.102f, -1718.394f, 2.576662f, 227.5724f),
        Mod_Class::Vector4(-1308.550f, -1728.681f, 2.130515f, 315.7358f),
        Mod_Class::Vector4(-1300.599f, -1693.816f, 2.6387f, 303.5509f),
        Mod_Class::Vector4(-1299.935f, -1695.019f, 2.637542f, 298.0522f),
        Mod_Class::Vector4(-1299.456f, -1696.399f, 2.641833f, 292.2518f),
        Mod_Class::Vector4(-1322.402f, -1663.354f, 2.627295f, 322.0356f),
        Mod_Class::Vector4(-1321.943f, -1665.101f, 2.610151f, 308.9845f),
        Mod_Class::Vector4(-1320.887f, -1666.081f, 2.62632f, 328.2236f),
        Mod_Class::Vector4(-1319.893f, -1662.236f, 2.631291f, 129.2401f),
        Mod_Class::Vector4(-1343.349f, -1623.587f, 2.709837f, 315.8477f),
        Mod_Class::Vector4(-1344.256f, -1622.703f, 2.713317f, 315.8477f),
        Mod_Class::Vector4(-1345.369f, -1622.052f, 2.703463f, 322.7376f),
        Mod_Class::Vector4(-1356.881f, -1593.336f, 2.861417f, 307.0485f),
        Mod_Class::Vector4(-1359.217f, -1593.168f, 2.864242f, 24.71251f),
        Mod_Class::Vector4(-1393.763f, -1585.805f, 2.15202f, 354.0496f),
        Mod_Class::Vector4(-1395.056f, -1585.333f, 2.141257f, 326.438f),
        Mod_Class::Vector4(-1394.059f, -1582.47f, 2.161732f, 185.6453f),
        Mod_Class::Vector4(-1392.443f, -1584.105f, 2.159806f, 18.49261f),
        Mod_Class::Vector4(-1385.895f, -1570.711f, 2.551907f, 290.671f),
        Mod_Class::Vector4(-1385.142f, -1571.766f, 2.53961f, 294.7195f),
        Mod_Class::Vector4(-1403.700f, -1533.807f, 2.550539f, 307.7706f),
        Mod_Class::Vector4(-1402.847f, -1534.817f, 2.561245f, 305.7824f),
        Mod_Class::Vector4(-1402.139f, -1536.028f, 2.579014f, 300.5658f),
        Mod_Class::Vector4(-1395.003f, -1527.983f, 2.714166f, 319.706f),
        Mod_Class::Vector4(-1393.826f, -1528.786f, 2.756421f, 309.4763f),
        Mod_Class::Vector4(-1399.792f, -1513.238f, 2.725808f, 18.74144f),
        Mod_Class::Vector4(-1398.480f, -1512.726f, 2.698768f, 18.74144f),
        Mod_Class::Vector4(-1399.082f, -1509.991f, 2.734775f, 163.6954f),
        Mod_Class::Vector4(-1400.608f, -1509.622f, 2.725877f, 163.6954f),
        Mod_Class::Vector4(-1429.167f, -1472.740f, 2.603141f, 337.0543f),
        Mod_Class::Vector4(-1463.157f, -1459.042f, 2.144997f, 23.97153f),
        Mod_Class::Vector4(-1461.406f, -1459.309f, 2.153293f, 0.08028773f),
        Mod_Class::Vector4(-1462.109f, -1460.952f, 2.149052f, 268.1315f),
        Mod_Class::Vector4(-1450.923f, -1418.267f, 2.517263f, 296.7604f),
        Mod_Class::Vector4(-1449.986f, -1419.647f, 2.536479f, 291.8983f),
        Mod_Class::Vector4(-1465.307f, -1425.848f, 2.171783f, 293.8079f),
        Mod_Class::Vector4(-1464.592f, -1427.238f, 2.185665f, 286.7738f),
        Mod_Class::Vector4(-1464.339f, -1428.718f, 2.156226f, 286.0127f),
        Mod_Class::Vector4(-1482.187f, -1413.022f, 2.121229f, 319.3725f),
        Mod_Class::Vector4(-1480.993f, -1413.941f, 2.109021f, 310.6389f),
        Mod_Class::Vector4(-1477.501f, -1361.669f, 2.493434f, 357.916f),
        Mod_Class::Vector4(-1479.386f, -1363.261f, 2.548198f, 247.8508f),
        Mod_Class::Vector4(-1474.581f, -1366.031f, 2.562512f, 322.5491f),
        Mod_Class::Vector4(-1495.909f, -1315.23f, 2.486061f, 354.9244f),
        Mod_Class::Vector4(-1494.629f, -1315.319f, 2.490464f, 345.9218f),
        Mod_Class::Vector4(-1493.276f, -1315.878f, 2.508637f, 345.9218f),
        Mod_Class::Vector4(-1498.894f, -1298.615f, 2.402473f, 329.2617f),
        Mod_Class::Vector4(-1497.321f, -1299.146f, 2.412022f, 356.1056f),
        Mod_Class::Vector4(-1496.121f, -1297.28f, 2.403391f, 17.22088f),
        Mod_Class::Vector4(-1497.758f, -1295.624f, 2.393175f, 174.8387f),
        Mod_Class::Vector4(-1521.425f, -1240.291f, 2.339097f, 304.8259f),
        Mod_Class::Vector4(-1522.476f, -1239.307f, 2.340996f, 322.5687f),
        Mod_Class::Vector4(-1531.263f, -1245.153f, 2.189537f, 315.0559f),
        Mod_Class::Vector4(-1530.397f, -1246.012f, 2.175066f, 305.0559f),
        Mod_Class::Vector4(-1529.607f, -1247.526f, 2.189808f, 306.3683f),
        Mod_Class::Vector4(-1585.738f, -1166.065f, 2.130819f, 20.97485f),
        Mod_Class::Vector4(-1584.714f, -1165.620f, 2.11654f, 22.7268f),
        Mod_Class::Vector4(-1586.384f, -1162.648f, 2.142184f, 166.2041f),
        Mod_Class::Vector4(-1801.780f, -883.6934f, 4.546616f, 347.798f),
        Mod_Class::Vector4(-1800.687f, -883.5885f, 4.689929f, 350.4489f),
        Mod_Class::Vector4(-1799.297f, -884.0929f, 4.850968f, 335.9542f),
        Mod_Class::Vector4(-1830.397f, -830.5594f, 5.102286f, 306.1971f),
        Mod_Class::Vector4(-1831.218f, -829.3455f, 5.116156f, 303.9464f),
        Mod_Class::Vector4(-1832.317f, -828.1578f, 5.107981f, 318.9465f),
        Mod_Class::Vector4(-1839.319f, -810.482f, 5.924665f, 176.3867f),
        Mod_Class::Vector4(-1840.607f, -809.4081f, 5.930286f, 142.9351f),
        Mod_Class::Vector4(-1895.508f, -732.0837f, 6.178241f, 355.7171f),
        Mod_Class::Vector4(-1894.336f, -732.1937f, 6.324547f, 354.9297f),
        Mod_Class::Vector4(-1892.988f, -732.6408f, 6.373506f, 335.6056f),
        Mod_Class::Vector4(-1956.059f, -659.5606f, 6.356329f, 4.634604f),
        Mod_Class::Vector4(-1953.876f, -660.5043f, 6.553986f, 318.4146f),
        Mod_Class::Vector4(-1953.095f, -658.1672f, 6.79789f, 200.2727f),
        Mod_Class::Vector4(-2008.436f, -622.4333f, 4.256786f, 357.7266f),
        Mod_Class::Vector4(-2905.811f, -24.56715f, 5.582788f, 191.8491f),
        Mod_Class::Vector4(-2907.202f, -25.06522f, 5.411035f, 195.5894f),
        Mod_Class::Vector4(-2904.915f, -27.620f, 5.113777f, 48.74567f),
        Mod_Class::Vector4(-2904.060f, -26.71244f, 5.302473f, 46.44249f),
        Mod_Class::Vector4(-2910.658f, -12.64766f, 6.770673f, 319.5335f),
        Mod_Class::Vector4(-2931.755f, -8.413383f, 6.753997f, 43.16842f),
        Mod_Class::Vector4(-2931.073f, -7.410044f, 6.913908f, 45.83247f),
        Mod_Class::Vector4(-2934.11f, -5.827422f, 7.014185f, 192.1256f),
        Mod_Class::Vector4(-2953.064f, 2.98832f, 7.349693f, 48.05029f),
        Mod_Class::Vector4(-2950.973f, 4.334025f, 7.488911f, 333.3324f),
        Mod_Class::Vector4(-3282.942f, 1004.377f, 3.601203f, 335.732f),
        Mod_Class::Vector4(-3284.103f, 1004.818f, 3.436242f, 333.8094f),
        Mod_Class::Vector4(-3285.315f, 1006.349f, 3.293736f, 287.6809f),
        Mod_Class::Vector4(-3283.62f, 1049.714f, 3.379558f, 241.8611f),
        Mod_Class::Vector4(-3283.843f, 1048.37f, 3.403792f, 286.7301f),
        Mod_Class::Vector4(-3267.981f, 1126.026f, 2.442192f, 267.5443f),
        Mod_Class::Vector4(-3267.524f, 1124.552f, 2.407591f, 263.4565f),
        Mod_Class::Vector4(-3267.774f, 1123.098f, 2.407187f, 257.3347f),
        Mod_Class::Vector4(-3252.64f, 1175.364f, 3.040092f, 149.7304f),
        Mod_Class::Vector4(-3255.025f, 1173.752f, 2.978993f, 290.6163f),
        Mod_Class::Vector4(-3254.056f, 1172.539f, 2.932649f, 318.7726f),
        Mod_Class::Vector4(-3246.073f, 1216.653f, 2.534976f, 265.7483f),
        Mod_Class::Vector4(-3246.417f, 1215.365f, 2.546444f, 262.0739f),
        Mod_Class::Vector4(-357.0365f, 6486.374f, 2.984426f, 219.246f),
        Mod_Class::Vector4(-355.1489f, 6488.625f, 3.065699f, 225.4996f),
        Mod_Class::Vector4(-353.5633f, 6486.101f, 3.027579f, 208.3938f),
        Mod_Class::Vector4(-352.0255f, 6487.431f, 3.067748f, 211.8525f),
        Mod_Class::Vector4(-351.1665f, 6488.659f, 3.093848f, 234.7069f),
        Mod_Class::Vector4(1531.488f, 6618.15f, 2.33354f, 208.5601f),
        Mod_Class::Vector4(1527.994f, 6616.621f, 2.327634f, 180.7982f),
        Mod_Class::Vector4(1293.017f, 6605.183f, 2.035692f, 242.5957f),
        Mod_Class::Vector4(1292.921f, 6606.33f, 2.001515f, 255.0041f)
    };
    inline const std::vector<Mod_Class::Vector4> BeachBoat = {
        Mod_Class::Vector4(84.15928f, 870.0395f, 196.9632f, 198.6257f),
        Mod_Class::Vector4(1085.424f, -623.1199f, 55.74931f, 231.864f),
        Mod_Class::Vector4(1935.267f, 138.6639f, 161.0021f, 252.3587f),
        Mod_Class::Vector4(-1545.141f, 5333.643f, 0.374609f, 252.4405f),
        Mod_Class::Vector4(191.4103f, 4008.992f, 30.16784f, 247.7711f),
        Mod_Class::Vector4(735.3177f, 3875.103f, 30.30095f, 250.4637f),
        Mod_Class::Vector4(1301.419f, 4081.359f, 30.85315f, 250.8063f),
        Mod_Class::Vector4(1890.581f, 4207.984f, 29.69297f, 254.4965f),
        Mod_Class::Vector4(3942.418f, 4520.72f, 0.04050386f, 254.2912f),
        Mod_Class::Vector4(1275.859f, 6781.243f, 1.875325f, 255.149f),
        Mod_Class::Vector4(817.8608f, 6868.745f, 0.6500905f, 254.5598f),
        Mod_Class::Vector4(555.2587f, 6948.927f, 2.070866f, 235.7191f),
        Mod_Class::Vector4(380.6453f, 7111.351f, 1.341785f, 103.1293f),
        Mod_Class::Vector4(-75.04967f, 7162.032f, 0.7809207f, 106.3162f),
        Mod_Class::Vector4(-136.6161f, 6985.519f, 2.248812f, 109.5711f),
        Mod_Class::Vector4(-217.6722f, 6772.711f, 0.7187195f, 112.3855f),
        Mod_Class::Vector4(-432.1755f, 6602.485f, -0.9444882f, 113.2111f),
        Mod_Class::Vector4(-711.3498f, 6438.557f, 1.175478f, 114.2294f),
        Mod_Class::Vector4(-783.0923f, 6179.819f, 1.159182f, 113.195f),
        Mod_Class::Vector4(-855.4564f, 6329.2f, 1.649986f, 112.0618f),
        Mod_Class::Vector4(-1105.409f, 6230.149f, 1.402328f, 106.5892f),
        Mod_Class::Vector4(-1041.873f, 5980.121f, 1.402047f, 102.712f),
        Mod_Class::Vector4(-1089.262f, 5718.566f, 2.109917f, 99.14839f),
        Mod_Class::Vector4(-1259.799f, 5542.388f, 1.329061f, 101.9638f),
        Mod_Class::Vector4(-2010.965f, 4706.432f, 0.2131054f, 98.64931f),
        Mod_Class::Vector4(-2289.724f, 4718.518f, 1.205942f, 100.3706f),
        Mod_Class::Vector4(-2620.681f, 4375.571f, 2.598233f, 102.3983f),
        Mod_Class::Vector4(-2752.379f, 3823.479f, 2.192016f, 108.3891f),
        Mod_Class::Vector4(-3094.804f, 3660.478f, 0.3773279f, 108.2939f),
        Mod_Class::Vector4(-3285.914f, 3382.975f, -0.6846119f, 111.7754f),
        Mod_Class::Vector4(-3106.192f, 3070.644f, 0.5554894f, 102.6006f),
        Mod_Class::Vector4(-2875.93f, 2896.969f, 1.137105f, 103.0204f),
        Mod_Class::Vector4(-3370.646f, 1288.255f, 1.050613f, 104.7735f),
        Mod_Class::Vector4(-3457.67f, 1109.7f, -0.8914479f, 86.42601f),
        Mod_Class::Vector4(-3358.214f, 755.0081f, 0.5048277f, 89.27978f),
        Mod_Class::Vector4(-3270.875f, 507.7149f, 1.220188f, 97.51931f),
        Mod_Class::Vector4(-3299.841f, 145.6124f, 1.549924f, 98.60503f),
        Mod_Class::Vector4(-3109.922f, -176.991f, 0.5766438f, 98.75866f),
        Mod_Class::Vector4(-2576.633f, -557.041f, 0.371466f, 96.98157f),
        Mod_Class::Vector4(-2186.475f, -772.5471f, 2.227773f, 98.03549f),
        Mod_Class::Vector4(-1997.154f, -1051.069f, 0.6151424f, 99.92389f),
        Mod_Class::Vector4(-1693.719f, -1348.646f, -0.7338865f, 314.2184f),
        Mod_Class::Vector4(-1604.932f, -1523.64f, -0.2957365f, 317.7053f),
        Mod_Class::Vector4(-1508.621f, -1717.438f, 2.088923f, 314.3288f),
        Mod_Class::Vector4(-1412.39f, -1908.503f, 1.763029f, 340.169f),
        Mod_Class::Vector4(-1564.309f, -2060.263f, 0.694436f, 337.7032f)
    };

    inline const std::vector<Mod_Class::Vector4> TrampSign = {
        Mod_Class::Vector4(203.1747f, -1323.28f, 29.49488f, 193.3338f),
        Mod_Class::Vector4(208.8623f, -1112.774f, 29.48404f, 24.76219f),
        Mod_Class::Vector4(-275.8094f, -1454.74f, 31.61106f, 253.4336f),
        Mod_Class::Vector4(-693.1378f, -1577.24f, 18.84266f, 353.1736f),
        Mod_Class::Vector4(-800.6707f, -2524.994f, 14.12026f, 169.2693f),
        Mod_Class::Vector4(-394.2787f, -1808.287f, 21.73676f, 62.14956f),
        Mod_Class::Vector4(-442.7756f, -1421.596f, 29.47493f, 296.8138f),
        Mod_Class::Vector4(-749.0342f, -1104.87f, 10.93612f, 343.8803f),
        Mod_Class::Vector4(-970.386f, -417.4318f, 38.12127f, 58.37359f),
        Mod_Class::Vector4(-268.4693f, -369.2575f, 30.27961f, 35.20417f),
        Mod_Class::Vector4(-229.4433f, -57.87684f, 49.78816f, 327.3621f),
        Mod_Class::Vector4(-201.4504f, 259.4538f, 92.27294f, 317.8449f)
    };
    inline const std::vector<Mod_Class::Vector4> TrampSleap = {
        Mod_Class::Vector4(351.7925f, -1188.58f, 29.48054f, 1.868855f),
        Mod_Class::Vector4(138.2023f, -1218.859f, 29.74356f, 149.2099f),
        Mod_Class::Vector4(18.54766f, -1213.865f, 29.78357f, 277.7195f),
        Mod_Class::Vector4(345.3155f, -1093.126f, 29.72063f, 329.6081f),
        Mod_Class::Vector4(466.7483f, -864.7038f, 27.09684f, 98.30646f),
        Mod_Class::Vector4(262.903f, -1114.465f, 29.64995f, 29.92652f),
        Mod_Class::Vector4(843.3406f, -852.6771f, 26.6483f, 335.358f)
    };

    inline const std::vector<Mod_Class::FubarVectors> HighClass = {
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(318.8127f, 496.3661f, 152.5035f,281.6071f), Mod_Class::Vector4(325.3149f, 513.2526f, 153.1802f,176.9303f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(215.3257f, 758.5961f, 204.4705f,54.70864f), Mod_Class::Vector4(228.7233f, 765.6225f, 204.9766f,60.57176f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(227.3211f, 680.8201f, 189.3211f,108.4066f), Mod_Class::Vector4(232.2005f, 672.3677f, 189.9457f,17.49693f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(64.58726f, 456.2051f, 146.6121f,38.19732f), Mod_Class::Vector4(57.70588f, 449.8846f, 147.0315f,330.7135f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(90.09676f, 486.9627f, 147.5335f,204.4576f), Mod_Class::Vector4(79.89433f, 486.2136f, 148.2015f,211.3625f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(113.6128f, 496.2102f, 146.943f,191.1292f), Mod_Class::Vector4(119.7328f, 494.3987f, 147.343f,96.75148f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(173.5254f, 482.3466f, 142.0656f,349.3443f), Mod_Class::Vector4(174.2039f, 466.5258f, 141.9075f,340.2406f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-184.2236f, 420.0336f, 110.4789f,16.08652f), Mod_Class::Vector4(-176.1895f, 423.6454f, 111.2499f,112.1185f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-202.1047f, 409.8227f, 110.3036f,16.04276f), Mod_Class::Vector4(-213.9507f, 399.727f, 111.3039f,16.8197f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-353.7564f, 474.8524f, 112.5154f,285.6599f), Mod_Class::Vector4(-355.6916f, 458.2476f, 116.6474f,317.5224f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-362.2122f, 514.9112f, 119.3604f,135.6201f), Mod_Class::Vector4(-348.6426f, 514.8634f, 120.6501f,132.31f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-399.775f, 518.1522f, 120.145f,353.0008f), Mod_Class::Vector4(-386.6427f, 504.4515f, 120.4127f,336.3673f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-408.2724f, 559.9554f, 124.1673f,154.2473f), Mod_Class::Vector4(-406.4761f, 567.3199f, 124.6036f,159.2473f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-469.7041f, 541.201f, 120.8802f,356.8915f), Mod_Class::Vector4(-459.1455f, 537.1053f, 121.4599f,3.323273f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-478.6201f, 597.3229f, 127.341f,92.0453f), Mod_Class::Vector4(-474.2755f, 586.0066f, 128.6839f,84.01727f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-512.4046f, 577.1302f, 120.2451f,280.7281f), Mod_Class::Vector4(-520.4376f, 594.2043f, 120.8367f,271.7799f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-543.3492f, 543.871f, 110.1703f,247.399f), Mod_Class::Vector4(-554.4238f, 541.1027f, 110.7071f,166.609f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-525.6572f, 527.3201f, 111.9418f,45.30171f), Mod_Class::Vector4(-526.5902f, 517.1929f, 112.9406f,41.81937f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-537.5423f, 485.6831f, 102.781f,53.94619f), Mod_Class::Vector4(-536.6965f, 477.2957f, 103.1936f,53.67907f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-576.5366f, 400.8622f, 100.4606f,21.4386f), Mod_Class::Vector4(-561.1863f, 402.92f, 101.8053f,23.25938f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-604.6118f, 397.7712f, 101.5185f,5.700022f), Mod_Class::Vector4(-595.7487f, 393.0933f, 101.8825f,5.97052f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-520.4191f, 393.612f, 93.43296f,21.67514f), Mod_Class::Vector4(-500.6455f, 398.63f, 98.08712f,52.72701f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-457.5839f, 393.2669f, 103.4656f,2.933417f), Mod_Class::Vector4(-451.1712f, 395.4468f, 104.7742f,85.61269f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-392.0697f, 432.4407f, 111.9837f,246.8938f), Mod_Class::Vector4(-400.8264f, 427.5692f, 112.3414f,250.3701f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-322.4262f, 431.2195f, 109.5666f,10.18072f), Mod_Class::Vector4(-305.0169f, 431.3801f, 110.4723f,12.44402f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-305.3652f, 379.4485f, 110.1347f,16.26957f), Mod_Class::Vector4(-297.6968f, 380.0132f, 112.0954f,27.14002f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-381.332f, 346.6836f, 108.9861f,7.034455f), Mod_Class::Vector4(-371.863f, 343.6674f, 109.9426f,5.457379f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-404.2261f, 338.9417f, 108.5134f,0.3291996f), Mod_Class::Vector4(-409.3182f, 341.4418f, 108.9075f,269.5646f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-473.7736f, 354.4996f, 103.6425f,334.2458f), Mod_Class::Vector4(-478.8647f, 352.0819f, 104.1457f,347.9644f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-524.8502f, 645.942f, 137.9588f,326.1953f), Mod_Class::Vector4(-523.0588f, 628.2188f, 137.9739f,293.1599f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-465.0109f, 643.8513f, 143.9835f,46.34229f), Mod_Class::Vector4(-476.7407f, 647.8394f, 144.3867f,15.64181f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-395.1528f, 671.1686f, 162.8374f,359.6853f), Mod_Class::Vector4(-400.0963f, 664.945f, 163.8302f,359.3605f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-344.9743f, 663.3989f, 169.2626f,171.1561f), Mod_Class::Vector4(-339.8586f, 669.1342f, 172.7843f,262.9623f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-343.6224f, 634.3452f, 172.0965f,52.99996f), Mod_Class::Vector4(-339.922f, 625.514f, 171.3569f,56.90737f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-302.5193f, 631.861f, 175.4442f,117.7551f), Mod_Class::Vector4(-299.0081f, 635.5462f, 175.6917f,111.2493f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-274.5317f, 600.1389f, 181.5089f,356.5742f), Mod_Class::Vector4(-293.5075f, 600.8858f, 181.5756f,350.6989f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-224.0718f, 592.1751f, 190.0356f,354.7806f), Mod_Class::Vector4(-232.5696f, 588.3168f, 190.5363f,350.4607f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-197.6937f, 614.6669f, 196.7917f,182.0588f), Mod_Class::Vector4(-198.9457f, 636.6884f, 199.6429f,358.0923f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-179.0646f, 592.517f, 197.4248f,356.2981f), Mod_Class::Vector4(-188.9543f, 591.7107f, 197.8231f,270.9746f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-144.5513f, 595.9666f, 203.5569f,18.34551f), Mod_Class::Vector4(-126.5195f, 588.4652f, 204.7106f,355.9948f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-494.8479f, 744.3373f, 162.7411f,248.4828f), Mod_Class::Vector4(-495.6496f, 738.6761f, 163.0311f,333.3955f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-660.9177f, 807.1927f, 198.9049f,358.1064f), Mod_Class::Vector4(-655.1315f, 803.2078f, 198.9912f,358.0805f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-595.5434f, 806.5671f, 190.1349f,150.7332f), Mod_Class::Vector4(-587.2784f, 806.5978f, 191.2476f,143.8838f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-579.5834f, 740.6581f, 183.4856f,137.3068f), Mod_Class::Vector4(-579.5991f, 732.8576f, 184.2119f,12.34716f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-670.3287f, 752.3672f, 173.657f,358.9892f), Mod_Class::Vector4(-646.1149f, 740.5093f, 174.2768f,29.26677f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-614.6937f, 678.5223f, 149.3577f,350.7242f), Mod_Class::Vector4(-606.1802f, 672.3806f, 151.5968f,348.5289f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-559.8077f, 685.6489f, 145.0379f,163.5413f), Mod_Class::Vector4(-551.9026f, 686.8129f, 146.0746f,160.0818f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-711.7605f, 656.2303f, 154.8006f,347.2955f), Mod_Class::Vector4(-700.8209f, 647.2943f, 155.1797f,343.4536f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-667.9805f, 670.0135f, 150.0492f,78.2793f), Mod_Class::Vector4(-661.8883f, 678.765f, 153.9105f,91.90803f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-766.6292f, 665.9629f, 144.3472f,295.9562f), Mod_Class::Vector4(-765.5724f, 650.708f, 145.7009f,310.9063f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-806.8042f, 705.327f, 146.6031f,19.24083f), Mod_Class::Vector4(-819.4746f, 696.8098f, 148.1098f,20.49006f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-950.4979f, 688.0117f, 153.2586f,1.711245f), Mod_Class::Vector4(-931.5179f, 691.3855f, 153.4668f,0.1517567f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1022.999f, 694.4565f, 161.0156f,356.0608f), Mod_Class::Vector4(-1033.217f, 685.9224f, 161.3029f,82.47516f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1057.742f, 736.4571f, 165.0407f,295.9679f), Mod_Class::Vector4(-1065.144f, 726.8954f, 165.4747f,21.02359f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1052.495f, 768.1278f, 166.8871f,274.8205f), Mod_Class::Vector4(-1056.151f, 761.4487f, 167.3164f,267.1714f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-812.8171f, 807.8094f, 201.3971f,18.17716f), Mod_Class::Vector4(-824.1274f, 806.2383f, 202.7845f,16.62208f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-851.7211f, 792.0988f, 191.1466f,6.379981f), Mod_Class::Vector4(-867.3304f, 784.9983f, 191.9343f,2.053166f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-905.2603f, 783.0583f, 185.3374f,10.43882f), Mod_Class::Vector4(-912.2769f, 777.4453f, 187.0112f,7.442374f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-918.7078f, 806.9541f, 183.6067f,185.8774f), Mod_Class::Vector4(-921.1113f, 813.6768f, 184.3361f,194.3121f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-955.9373f, 800.6656f, 177.1945f,184.6668f), Mod_Class::Vector4(-962.6827f, 813.8876f, 177.5658f,184.572f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-970.3416f, 766.3366f, 174.4704f,46.66233f), Mod_Class::Vector4(-972.2784f, 752.2701f, 176.3808f,38.5029f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1000.281f, 785.6187f, 170.9521f,289.1853f), Mod_Class::Vector4(-998.4088f, 768.6085f, 171.5826f,295.0405f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1024.018f, 812.2822f, 171.3941f,185.676f), Mod_Class::Vector4(-1013.067f, 818.3909f, 172.3797f,135.8375f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1121.198f, 788.3663f, 162.3206f,232.7807f), Mod_Class::Vector4(-1130.642f, 784.4011f, 163.8875f,232.461f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1116.805f, 769.6484f, 162.7472f,27.5284f), Mod_Class::Vector4(-1117.804f, 761.6957f, 164.2888f,25.97767f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1160.398f, 741.2746f, 154.8455f,46.88651f), Mod_Class::Vector4(-1165.583f, 727.0689f, 155.6068f,332.7302f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1249.97f, 664.7272f, 142.2922f,216.816f), Mod_Class::Vector4(-1241.33f, 674.0937f, 142.8134f,174.5139f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1283.548f, 649.0323f, 139.2707f,195.7354f), Mod_Class::Vector4(-1291.867f, 650.233f, 141.5015f,195.6528f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1289.159f, 626.0635f, 138.1995f,42.20447f), Mod_Class::Vector4(-1277.768f, 629.8492f, 143.1888f,128.5902f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1346.258f, 610.5354f, 133.3745f,98.08596f), Mod_Class::Vector4(-1337.636f, 606.1381f, 134.3799f,85.66702f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1357.674f, 578.7719f, 130.9355f,248.7664f), Mod_Class::Vector4(-1364.308f, 570.2775f, 134.9729f,240.3346f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1452.525f, 534.3056f, 118.7793f,257.9918f), Mod_Class::Vector4(-1452.805f, 545.5567f, 120.7994f,259.8272f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1482.342f, 530.4329f, 117.7977f,213.1592f), Mod_Class::Vector4(-1500.594f, 522.8561f, 118.2721f,207.9011f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1471.884f, 514.642f, 117.5872f,15.8216f), Mod_Class::Vector4(-1453.886f, 512.446f, 117.7964f,70.62026f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1504.848f, 425.8355f, 110.832f,41.97743f), Mod_Class::Vector4(-1496.01f, 437.0359f, 112.4979f,53.20035f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1541.578f, 429.3669f, 109.0081f,271.6294f), Mod_Class::Vector4(-1540.04f, 420.9024f, 110.014f,1.374532f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1418.02f, 468.6653f, 108.8807f,345.707f), Mod_Class::Vector4(-1413.387f, 462.6624f, 109.2085f,334.4767f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1376.452f, 452.9557f, 104.6378f,82.44392f), Mod_Class::Vector4(-1371.408f, 444.057f, 105.8572f,82.7045f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1272.138f, 452.7144f, 94.775f,32.07218f), Mod_Class::Vector4(-1263.355f, 455.0761f, 94.77367f,41.70851f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1179.269f, 456.428f, 86.40733f,82.7791f), Mod_Class::Vector4(-1174.776f, 440.2753f, 86.84985f,83.48888f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1111.094f, 477.6239f, 81.88736f,170.295f), Mod_Class::Vector4(-1122.536f, 486.1293f, 82.35567f,171.3635f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1078.805f, 462.1515f, 77.29704f,147.5997f), Mod_Class::Vector4(-1087.607f, 479.4379f, 81.32063f,58.70352f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1092.437f, 438.9475f, 75.01263f,261.8433f), Mod_Class::Vector4(-1094.531f, 427.3982f, 75.88006f,263.4119f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1040.038f, 495.8495f, 82.34982f,233.2739f), Mod_Class::Vector4(-1059.639f, 515.5388f, 84.38102f,53.55426f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1012.415f, 489.8326f, 79.03043f,4.231028f), Mod_Class::Vector4(-1009.264f, 479.5622f, 79.4146f,327.7209f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-993.8633f, 495.3938f, 81.06633f,354.9972f), Mod_Class::Vector4(-987.258f, 487.3222f, 82.46126f,13.29768f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-976.9498f, 517.1743f, 81.19785f,143.4696f), Mod_Class::Vector4(-967.3892f, 510.278f, 82.06638f,153.4967f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1097.503f, 361.4458f, 68.29243f,356.7833f), Mod_Class::Vector4(-1130.32f, 361.0236f, 71.71848f,56.60651f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1051.329f, 316.0146f, 66.14833f,296.2429f), Mod_Class::Vector4(-1038.475f, 312.1982f, 67.27436f,19.25218f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1015.469f, 357.717f, 70.04961f,157.7254f), Mod_Class::Vector4(-1025.812f, 360.4001f, 71.36146f,252.449f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-845.9332f, 460.2166f, 87.08342f,99.5103f), Mod_Class::Vector4(-842.9318f, 466.8084f, 87.59698f,102.3203f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-871.2172f, 499.3638f, 89.37999f,283.7275f), Mod_Class::Vector4(-883.9303f, 518.0816f, 92.44287f,285.0275f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-846.2355f, 514.9747f, 90.41426f,108.4869f), Mod_Class::Vector4(-848.6625f, 508.8511f, 90.81708f,10.45732f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-909.2509f, 554.6064f, 96.15231f,315.8858f), Mod_Class::Vector4(-907.5173f, 545.0802f, 100.205f,313.1519f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-916.2592f, 585.7996f, 100.4603f,152.0125f), Mod_Class::Vector4(-904.6435f, 587.8419f, 101.1908f,150.728f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-951.5414f, 575.9009f, 100.8275f,341.1044f), Mod_Class::Vector4(-947.8389f, 567.7078f, 101.5077f,355.4088f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1095.902f, 598.5202f, 102.8574f,211.4888f), Mod_Class::Vector4(-1107.479f, 594.1757f, 104.4547f,213.5989f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1106.987f, 552.2368f, 102.3779f,29.54501f), Mod_Class::Vector4(-1090.422f, 548.3315f, 103.6333f,120.3299f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1209.008f, 557.5132f, 99.15355f,183.7141f), Mod_Class::Vector4(-1193.096f, 563.8548f, 100.3394f,182.2157f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1270.597f, 503.7831f, 97.02524f,179.3631f), Mod_Class::Vector4(-1277.653f, 497.0977f, 97.89041f,264.6013f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1236.806f, 486.4729f, 92.98049f,131.1081f), Mod_Class::Vector4(-1217.873f, 506.0433f, 95.66708f,180.517f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-754.9761f, 441.7753f, 99.65048f,21.17248f), Mod_Class::Vector4(-762.2422f, 431.1789f, 100.1969f,19.54113f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-766.1439f, 465.4737f, 99.84455f,214.9303f), Mod_Class::Vector4(-784.4272f, 459.1835f, 100.1791f,208.3917f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-733.9666f, 446.2859f, 106.2041f,26.20407f), Mod_Class::Vector4(-717.9078f, 448.933f, 106.9092f,28.30388f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-716.2523f, 494.0204f, 108.8374f,207.0717f), Mod_Class::Vector4(-721.3455f, 490.2122f, 109.3857f,210.3048f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-687.3202f, 502.5805f, 109.6894f,199.9449f), Mod_Class::Vector4(-679.076f, 511.9479f, 113.526f,191.8366f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-587.2115f, 529.0335f, 107.4421f,210.9947f), Mod_Class::Vector4(-586.7624f, 541.3615f, 110.3284f,276.6161f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-575.4766f, 498.0202f, 105.8446f,11.15088f), Mod_Class::Vector4(-580.5882f, 492.2771f, 108.903f,8.991305f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-826.2047f, 272.0132f, 85.87145f,351.0056f), Mod_Class::Vector4(-819.5183f, 267.857f, 86.39596f,71.20386f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-869.1068f, 319.3342f, 83.29476f,186.0734f), Mod_Class::Vector4(-876.8299f, 306.3361f, 84.1543f,238.1838f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-888.3319f, 364.8171f, 84.34824f,4.419883f), Mod_Class::Vector4(-881.5927f, 363.7405f, 85.3627f,57.2331f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-978.6483f, -1200.687f, 4.028273f,300.2132f), Mod_Class::Vector4(-986.5679f, -1199.396f, 6.047775f,296.0049f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1036.361f, -1237.672f, 5.286499f,209.2803f), Mod_Class::Vector4(-1035.77f, -1228.016f, 6.346429f,113.4062f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1036.636f, -1599.48f, 4.240905f,37.49187f), Mod_Class::Vector4(-1037.267f, -1605.186f, 4.973884f,28.55429f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1044.919f, -1605.405f, 4.214279f,37.13557f), Mod_Class::Vector4(-1038.781f, -1610.055f, 4.996139f,309.5647f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1054.096f, -1594.601f, 3.974956f,215.3273f), Mod_Class::Vector4(-1056.945f, -1587.358f, 4.611769f,211.1144f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1064.465f, -1566.796f, 3.925897f,215.2828f), Mod_Class::Vector4(-1072.934f, -1561.893f, 4.692028f,116.2765f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1044.395f, -1571.362f, 4.338543f,34.36719f), Mod_Class::Vector4(-1043.264f, -1580.302f, 5.041376f,34.41164f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1037.087f, -1568.339f, 4.446574f,35.08035f), Mod_Class::Vector4(-1032.227f, -1582.888f, 5.13635f,128.5182f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1101.508f, -1497.694f, 4.160627f,216.5465f), Mod_Class::Vector4(-1102.456f, -1491.978f, 4.88708f,214.353f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1109.988f, -1504.075f, 3.984198f,211.9197f), Mod_Class::Vector4(-1111.039f, -1498.035f, 4.672972f,218.438f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1090.554f, -1631.604f, 4.080342f,126.4985f), Mod_Class::Vector4(-1082.602f, -1631.274f, 4.739912f,118.3442f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1081.945f, -1670.237f, 4.053997f,305.3939f), Mod_Class::Vector4(-1088.434f, -1672.304f, 4.699928f,297.9261f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1108.007f, -1228.391f, 1.936681f,119.0822f), Mod_Class::Vector4(-1103.736f, -1222.148f, 2.567274f,21.86139f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1133.214f, -1173.517f, 1.706819f,115.3653f), Mod_Class::Vector4(-1125.815f, -1171.82f, 2.355613f,108.8428f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1144.045f, -1153.354f, 2.160536f,121.8484f), Mod_Class::Vector4(-1135.558f, -1153.264f, 2.744727f,118.6349f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1149.098f, -1145.813f, 2.183599f,122.6256f), Mod_Class::Vector4(-1142.575f, -1144.144f, 2.848527f,115.1439f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1158.401f, -1126.026f, 1.755121f,122.3532f), Mod_Class::Vector4(-1143.73f, -1122.083f, 2.5961f,218.3322f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1189.225f, -1065.824f, 1.499536f,119.5338f), Mod_Class::Vector4(-1182.946f, -1064.361f, 2.150416f,117.8702f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1185.759f, -928.7217f, 2.090576f,209.7034f), Mod_Class::Vector4(-1179.527f, -929.2076f, 6.992926f,119.2376f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1185.571f, -948.7433f, 3.358301f,212.7497f), Mod_Class::Vector4(-1203.022f, -944.9437f, 8.114871f,134.0965f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1035.348f, -899.8041f, 3.612249f,29.06924f), Mod_Class::Vector4(-1031.14f, -902.8995f, 3.695777f,34.97942f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1022.112f, -890.0821f, 5.06163f,33.67837f), Mod_Class::Vector4(-1022.584f, -896.729f, 5.415418f,42.78962f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-949.3619f, -899.3148f, 1.512146f,297.1637f), Mod_Class::Vector4(-950.8911f, -905.6533f, 2.759314f,294.0639f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-938.354f, -927.7917f, 1.49428f,301.4236f), Mod_Class::Vector4(-947.825f, -928.0125f, 2.145313f,293.5189f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-921.298f, -951.6708f, 1.51206f,299.7054f), Mod_Class::Vector4(-927.3926f, -949.5184f, 2.745368f,294.5931f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-891.5771f, -1006.704f, 1.49878f,300.0399f), Mod_Class::Vector4(-892.8921f, -996.0531f, 2.24341f,303.004f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-873.7162f, -1073.753f, 1.506729f,301.2325f), Mod_Class::Vector4(-884.2474f, -1072.572f, 2.525175f,34.02031f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-864.4176f, -1090.45f, 1.511336f,299.6432f), Mod_Class::Vector4(-869.2363f, -1103.792f, 6.445571f,232.039f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-948.1478f, -1095.93f, 1.499038f,30.76507f), Mod_Class::Vector4(-948.6233f, -1107.861f, 2.171846f,115.5819f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-959.6019f, -1100.887f, 1.499249f,29.21922f), Mod_Class::Vector4(-959.7524f, -1109.692f, 2.150312f,20.53431f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1046.119f, -1151.479f, 1.507566f,32.19191f), Mod_Class::Vector4(-1045.882f, -1159.871f, 2.158599f,23.60791f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1064.915f, -1144.697f, 1.507192f,211.8922f), Mod_Class::Vector4(-1054.156f, -1143.676f, 2.158597f,216.1087f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1109.217f, -1049.216f, 1.498985f,209.683f), Mod_Class::Vector4(-1108.842f, -1040.977f, 2.150357f,202.6895f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1121.071f, -1053.575f, 1.499126f,211.4961f), Mod_Class::Vector4(-1122.203f, -1046.216f, 2.150357f,204.523f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1021.386f, -1015.118f, 1.498902f,31.22802f), Mod_Class::Vector4(-1022.295f, -1022.968f, 2.15036f,27.09616f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1009.645f, -1007.466f, 1.499278f,30.70059f), Mod_Class::Vector4(-1008.455f, -1015.352f, 2.150309f,18.27499f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(230.2194f, -160.4216f, 58.10718f,247.3503f), Mod_Class::Vector4(224.9709f, -160.9504f, 59.06062f,248.4403f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(238.0489f, -140.7968f, 63.11253f,247.6174f), Mod_Class::Vector4(231.0122f, -131.2872f, 63.76349f,345.2468f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(215.0969f, -85.35986f, 68.5939f,340.3171f), Mod_Class::Vector4(206.5384f, -85.87484f, 69.38208f,342.0331f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(196.1434f, -123.9325f, 62.84327f,69.58694f), Mod_Class::Vector4(202.1811f, -133.0024f, 63.49434f,158.0101f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(162.8428f, -111.4885f, 61.64407f,250.4696f), Mod_Class::Vector4(156.2838f, -117.0666f, 62.59745f,254.2728f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(132.2793f, -63.67412f, 67.02013f,73.82039f), Mod_Class::Vector4(137.0904f, -72.14262f, 68.06479f,148.126f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(118.5604f, -101.6884f, 60.06484f,72.65191f), Mod_Class::Vector4(127.1309f, -107.7606f, 60.7161f,155.2583f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(72.84455f, -101.6542f, 57.5042f,252.4982f), Mod_Class::Vector4(67.63523f, -103.6553f, 58.44378f,258.0023f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(83.47623f, -80.62891f, 61.6936f,256.6328f), Mod_Class::Vector4(76.42636f, -86.64355f, 62.81653f,255.5934f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(37.82995f, -62.58858f, 62.83085f,74.46173f), Mod_Class::Vector4(38.40622f, -71.52248f, 63.73074f,71.26472f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(1.24029f, -68.6165f, 60.61922f,254.8609f), Mod_Class::Vector4(-6.399803f, -74.44074f, 61.67424f,250.2828f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(15.70354f, -8.1376f, 69.46462f,340.8037f), Mod_Class::Vector4(17.69664f, -13.67813f, 70.11626f,352.4458f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(10.67354f, -6.838574f, 69.46469f,341.3873f), Mod_Class::Vector4(5.95322f, -9.303666f, 70.11619f,337.8993f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1045.552f, 221.6632f, 63.45662f,178.3034f), Mod_Class::Vector4(-1038.421f, 222.0945f, 64.37576f,101.7399f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-929.1015f, 211.0671f, 67.04869f,160.508f), Mod_Class::Vector4(-940.0865f, 202.5357f, 67.85973f,265.7908f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-912.4919f, 191.0148f, 69.02045f,175.5768f), Mod_Class::Vector4(-902.3611f, 191.5495f, 69.44602f,103.8158f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-993.4126f, 143.9969f, 60.24857f,291.2359f), Mod_Class::Vector4(-998.2958f, 157.7819f, 62.31877f,203.2687f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-961.9285f, 110.4381f, 55.89871f,302.7112f), Mod_Class::Vector4(-971.5331f, 122.0743f, 57.04857f,302.1059f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-917.6478f, 111.73f, 54.89901f,173.1191f), Mod_Class::Vector4(-913.7607f, 108.373f, 55.51467f,77.4723f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-839.1078f, 116.3889f, 54.98486f,184.1754f), Mod_Class::Vector4(-830.5832f, 115.2545f, 56.01638f,92.8595f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-874.3297f, -51.5565f, 37.8f,295.6655f), Mod_Class::Vector4(-862.5923f, -33.26305f, 40.55947f,90.03361f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-887.561f, -14.49451f, 42.69457f,300.4996f), Mod_Class::Vector4(-896.0683f, -4.812224f, 43.79892f,300.6788f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-928.6014f, 15.05872f, 47.3377f,302.9328f), Mod_Class::Vector4(-929.8884f, 19.34689f, 48.32583f,214.9419f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1531.366f, 83.56633f, 56.30471f,316.3572f), Mod_Class::Vector4(-1535.95f, 97.68037f, 56.77564f,225.0239f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1491.08f, 21.53012f, 54.30249f,7.461652f), Mod_Class::Vector4(-1482.41f, 33.45013f, 54.73831f,67.48167f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1505.229f, 26.07533f, 55.68369f,0.5788527f), Mod_Class::Vector4(-1515.509f, 23.86928f, 56.82068f,345.3811f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1568.126f, 33.21057f, 58.68525f,75.32178f), Mod_Class::Vector4(-1570.556f, 22.58729f, 59.55393f,349.9645f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1612.722f, 25.84081f, 61.66789f,334.1264f), Mod_Class::Vector4(-1621.656f, 15.58023f, 62.54132f,338.0487f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1460.498f, -24.12371f, 54.22675f,47.59397f), Mod_Class::Vector4(-1464.954f, -34.40237f, 55.05045f,314.3598f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1573.916f, -59.76668f, 56.07469f,268.2455f), Mod_Class::Vector4(-1580.114f, -34.0481f, 57.5652f,266.531f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1562.867f, -86.90454f, 53.71671f,270.8474f), Mod_Class::Vector4(-1549.388f, -90.47054f, 54.92917f,5.372835f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1613.838f, -375.9868f, 42.95982f,225.3058f), Mod_Class::Vector4(-1622.614f, -379.8445f, 43.71574f,238.272f), "", 51),
        Mod_Class::FubarVectors(2, Mod_Class::Vector4(-1671.823f, -451.071f, 38.95443f,231.6969f), Mod_Class::Vector4(-1667.287f, -441.3857f, 40.3559f,223.16f), "", 51)
    };
    inline const std::vector<Mod_Class::FubarVectors> MidClass = {
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3180.658f, 1290.957f, 14.0592f,247.7512f), Mod_Class::Vector4(-3190.676f, 1297.731f, 19.0674f,245.0513f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3183.311f, 1270.346f, 12.17393f,254.9015f), Mod_Class::Vector4(-3187.064f, 1273.6f, 12.66133f,254.1247f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3236.842f, 1038.351f, 11.37313f,262.0938f), Mod_Class::Vector4(-3248.461f, 1042.195f, 11.7577f,342.4902f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3071.85f, 657.6034f, 10.67065f,310.6417f), Mod_Class::Vector4(-3077.758f, 659.0297f, 11.66709f,305.8495f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3031.909f, 554.9281f, 7.221505f,273.7011f), Mod_Class::Vector4(-3037.06f, 559.1101f, 7.507685f,262.9286f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3032.044f, 548.8285f, 7.222395f,273.0267f), Mod_Class::Vector4(-3036.783f, 544.8415f, 7.507689f,279.4198f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3028.466f, 529.1766f, 7.110633f,266.5662f), Mod_Class::Vector4(-3031.609f, 525.1259f, 7.418378f,293.1272f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3054.984f, 446.1913f, 6.078387f,241.2682f), Mod_Class::Vector4(-3059.439f, 453.4136f, 6.355f,308.1406f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3056.779f, 440.1962f, 6.078247f,244.6572f), Mod_Class::Vector4(-3071.112f, 442.2274f, 6.432204f,200.837f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3074.463f, 395.0111f, 6.68469f,250.7313f), Mod_Class::Vector4(-3088.022f, 392.052f, 11.44828f,245.008f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3081.795f, 367.2194f, 6.841104f,253.4775f), Mod_Class::Vector4(-3094.386f, 364.0299f, 7.11908f,212.237f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3078.729f, 371.1037f, 6.756917f,256.4778f), Mod_Class::Vector4(-3091.218f, 379.27f, 7.112116f,249.9387f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3088.71f, 339.0896f, 7.057094f,256.34f), Mod_Class::Vector4(-3093.62f, 349.5225f, 7.542557f,258.2035f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3090.359f, 323.5883f, 6.994868f,252.5663f), Mod_Class::Vector4(-3110.266f, 335.707f, 7.493345f,239.4375f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3100.997f, 286.9933f, 8.70353f,256.6824f), Mod_Class::Vector4(-3115.969f, 294.5186f, 8.972109f,343.9737f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3101.86f, 250.9796f, 11.79934f,283.5082f), Mod_Class::Vector4(-3115.135f, 253.3001f, 12.49199f,280.4746f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3083.172f, 221.4865f, 13.66574f,321.9735f), Mod_Class::Vector4(-3089.267f, 221.317f, 14.11646f,324.8273f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-2981.23f, 612.3184f, 19.82067f,103.2088f), Mod_Class::Vector4(-2977.365f, 609.4474f, 20.24566f,117.3492f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-2982.986f, 654.5662f, 24.62313f,102.9709f), Mod_Class::Vector4(-2972.843f, 642.5392f, 25.80846f,96.64449f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3002.513f, 687.8111f, 23.83623f,104.8339f), Mod_Class::Vector4(-2994.945f, 682.1981f, 25.04325f,105.6758f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3003.329f, 718.7411f, 27.93678f,109.5287f), Mod_Class::Vector4(-2986.688f, 720.377f, 28.49688f,280.5353f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-3018.92f, 740.0507f, 27.20635f,108.2156f), Mod_Class::Vector4(-3017.154f, 746.4309f, 27.77834f,109.3754f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1890.317f, 625.6895f, 129.8048f,134.5031f), Mod_Class::Vector4(-1896.41f, 642.3912f, 130.2091f,135.6104f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1972.61f, 622.8682f, 122.0211f,249.3061f), Mod_Class::Vector4(-1974.167f, 630.8234f, 122.5363f,239.3418f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1940.914f, 582.2904f, 118.7524f,73.77197f), Mod_Class::Vector4(-1929.144f, 595.3513f, 122.2849f,73.76144f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1987.146f, 602.5629f, 117.7295f,255.3423f), Mod_Class::Vector4(-1995.914f, 591.3108f, 118.1018f,269.3795f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1942.445f, 553.5145f, 114.5114f,160.2522f), Mod_Class::Vector4(-1938.31f, 551.1836f, 114.8284f,70.85834f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-2011.322f, 484.195f, 106.6195f,256.0873f), Mod_Class::Vector4(-2014.473f, 499.3258f, 107.1717f,244.5216f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1956.843f, 447.2014f, 100.5681f,192.2569f), Mod_Class::Vector4(-1942.926f, 449.446f, 102.9281f,95.02689f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-2008.929f, 454.8618f, 102.3518f,288.5639f), Mod_Class::Vector4(-2011.005f, 445.3031f, 103.0159f,278.0325f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-2002.379f, 378.7492f, 93.87296f,178.9765f), Mod_Class::Vector4(-2008.202f, 367.7929f, 94.81432f,280.081f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1939.113f, 361.9132f, 92.99133f,188.1561f), Mod_Class::Vector4(-1931.501f, 362.5919f, 93.78577f,100.4027f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1857.348f, 327.1342f, 88.17714f,11.79387f), Mod_Class::Vector4(-1839.171f, 314.4151f, 90.91705f,107.2775f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1795.378f, 347.3343f, 88.05728f,67.10529f), Mod_Class::Vector4(-1807.901f, 333.482f, 89.56721f,26.32763f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1751.036f, 365.346f, 89.19474f,119.8925f), Mod_Class::Vector4(-1741.989f, 365.0535f, 88.72823f,132.9538f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1669.214f, 396.9711f, 88.50093f,67.6088f), Mod_Class::Vector4(-1673.167f, 385.8703f, 89.34826f,334.4228f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1995.319f, 293.8503f, 91.49142f,285.6034f), Mod_Class::Vector4(-1995.287f, 300.1558f, 91.96467f,179.6584f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1926.644f, 292.5228f, 88.79985f,11.73591f), Mod_Class::Vector4(-1922.596f, 298.3171f, 89.2872f,92.09549f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1977.376f, 259.8421f, 86.94446f,288.032f), Mod_Class::Vector4(-1970.291f, 246.368f, 87.81214f,295.7983f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1906.842f, 243.9758f, 85.63078f,25.30107f), Mod_Class::Vector4(-1905.841f, 252.8489f, 86.45291f,125.6398f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1952.425f, 211.8754f, 85.2787f,205.6115f), Mod_Class::Vector4(-1960.469f, 212.1031f, 86.80087f,283.9886f), "", 51),
        Mod_Class::FubarVectors(3, Mod_Class::Vector4(-1895.115f, 138.9963f, 80.78864f,34.80264f), Mod_Class::Vector4(-1898.98f, 132.871f, 81.98471f,299.9321f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1295.376f, -567.9024f, 70.75495f,344.1851f), Mod_Class::Vector4(1301.253f, -573.5514f, 71.73225f,341.7915f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1319.005f, -575.0912f, 72.48561f,338.2868f), Mod_Class::Vector4(1323.626f, -582.8721f, 73.24647f,338.9369f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1348.813f, -603.4597f, 73.88947f,326.5587f), Mod_Class::Vector4(1341.663f, -597.4514f, 74.70089f,247.6048f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1359.929f, -602.2659f, 73.86779f,357.5853f), Mod_Class::Vector4(1367.098f, -606.2906f, 74.71091f,2.989266f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1379.085f, -596.9114f, 73.86754f,53.01553f), Mod_Class::Vector4(1386.105f, -593.3985f, 74.48546f,58.50755f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1388.36f, -577.789f, 73.86846f,111.8918f), Mod_Class::Vector4(1388.947f, -569.5814f, 74.49652f,123.4853f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1362.931f, -554.0172f, 73.86754f,156.5999f), Mod_Class::Vector4(1373.296f, -555.8261f, 74.68562f,68.44845f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1354.012f, -552.6052f, 73.49485f,158.3126f), Mod_Class::Vector4(1348.199f, -547.2642f, 73.89163f,152.8504f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1316.796f, -537.9033f, 71.47861f,161.5897f), Mod_Class::Vector4(1328.452f, -536.0343f, 72.44083f,71.44156f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1308.672f, -534.2927f, 70.8349f,161.667f), Mod_Class::Vector4(1303.016f, -527.8336f, 71.46064f,161.5036f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1262.95f, -715.1516f, 64.03774f,240.8946f), Mod_Class::Vector4(1264.701f, -702.7781f, 64.90907f,240.0456f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1278.863f, -672.2916f, 65.61749f,275.1073f), Mod_Class::Vector4(1270.782f, -683.3943f, 66.03163f,348.3714f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1277.071f, -656.444f, 67.14643f,290.0173f), Mod_Class::Vector4(1265.569f, -648.3455f, 67.92182f,43.03191f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1259.367f, -622.5423f, 68.815f,295.2193f), Mod_Class::Vector4(1251.347f, -621.3013f, 69.41325f,216.018f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1243.992f, -585.7985f, 68.79922f,272.6827f), Mod_Class::Vector4(1236.836f, -589.4675f, 69.78013f,6.338792f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1244.244f, -578.3922f, 68.85719f,269.6844f), Mod_Class::Vector4(1241.927f, -566.3712f, 69.65741f,288.1931f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1249.26f, -522.2668f, 68.50861f,256.182f), Mod_Class::Vector4(1250.788f, -515.5221f, 69.34905f,242.1898f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1260.297f, -492.5744f, 68.91977f,256.9387f), Mod_Class::Vector4(1251.542f, -494.0509f, 69.90688f,250.3926f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1259.068f, -419.8898f, 68.95522f,299.4943f), Mod_Class::Vector4(1262.366f, -429.9049f, 70.01472f,300.8087f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1200.074f, -613.0391f, 64.55002f,94.95676f), Mod_Class::Vector4(1207.419f, -620.009f, 66.43862f,97.66859f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1215.724f, -665.5594f, 62.25998f,105.1844f), Mod_Class::Vector4(1221.608f, -669.1736f, 63.49343f,13.46015f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1222.419f, -704.3478f, 60.2279f,96.78835f), Mod_Class::Vector4(1222.887f, -696.9181f, 60.80474f,105.7308f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1223.63f, -731.601f, 59.47527f,149.0665f), Mod_Class::Vector4(1229.317f, -725.6071f, 60.79803f,91.76685f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(981.3393f, -709.6439f, 57.15787f,310.0305f), Mod_Class::Vector4(979.1669f, -716.2917f, 58.22069f,310.7902f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(972.4129f, -685.7778f, 57.25153f,309.2305f), Mod_Class::Vector4(970.8255f, -701.52f, 58.48197f,354.5152f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(958.8745f, -661.8682f, 57.51588f,304.1452f), Mod_Class::Vector4(960.0464f, -669.7861f, 58.44978f,306.5766f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(949.5441f, -654.5562f, 57.52147f,309.1548f), Mod_Class::Vector4(943.4562f, -653.584f, 58.4287f,216.3886f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(926.4679f, -629.5486f, 57.3954f,319.9789f), Mod_Class::Vector4(928.9008f, -639.7322f, 58.24244f,312.6214f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(915.1364f, -628.0727f, 57.57964f,319.2966f), Mod_Class::Vector4(902.8493f, -615.579f, 58.4533f,246.7886f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(876.7163f, -595.7554f, 57.60468f,315.5723f), Mod_Class::Vector4(875.6384f, -602.271f, 58.44205f,48.01766f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(874.3272f, -587.4362f, 57.19896f,315.6563f), Mod_Class::Vector4(861.6575f, -583.5533f, 58.15649f,337.0353f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(848.7827f, -566.3721f, 57.23867f,279.6228f), Mod_Class::Vector4(844.2364f, -562.9039f, 57.83413f,190.2357f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(850.058f, -541.8986f, 56.85556f,264.3753f), Mod_Class::Vector4(850.2711f, -532.7251f, 57.92553f,268.921f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(859.718f, -522.5883f, 56.8409f,226.5662f), Mod_Class::Vector4(861.8169f, -509.5154f, 57.32895f,227.2639f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(875.5849f, -507.2527f, 56.9897f,228.1333f), Mod_Class::Vector4(878.6003f, -498.2205f, 58.10064f,228.1311f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(914.4882f, -490.0322f, 58.54957f,205.0751f), Mod_Class::Vector4(906.2788f, -489.4254f, 59.43626f,199.8672f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(932.5269f, -478.7095f, 60.27127f,204.433f), Mod_Class::Vector4(921.7753f, -478.077f, 61.08363f,201.9862f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(943.8246f, -470.6311f, 60.78315f,213.0169f), Mod_Class::Vector4(944.274f, -463.3413f, 61.51734f,140.1394f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(973.9123f, -451.6287f, 61.93366f,215.0411f), Mod_Class::Vector4(967.0895f, -451.6115f, 62.78954f,220.4082f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(997.0678f, -435.5168f, 63.55046f,264.8619f), Mod_Class::Vector4(987.5968f, -433.2158f, 63.89077f,205.1448f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1023.098f, -419.4548f, 65.34373f,218.5261f), Mod_Class::Vector4(1029.05f, -408.7803f, 65.94938f,222.3555f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1056.69f, -387.189f, 67.38435f,222.1012f), Mod_Class::Vector4(1060.556f, -378.2659f, 68.23121f,223.6127f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1106.454f, -399.7615f, 67.50427f,72.72183f), Mod_Class::Vector4(1114.356f, -391.3941f, 68.94821f,67.15671f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1100.32f, -418.7397f, 66.68211f,86.01027f), Mod_Class::Vector4(1101.103f, -411.3693f, 67.55517f,88.9761f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1099.369f, -429.3362f, 66.89532f,83.01512f), Mod_Class::Vector4(1099.459f, -438.4716f, 67.7906f,353.4471f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1091.125f, -471.4535f, 65.61601f,76.97134f), Mod_Class::Vector4(1098.569f, -464.5248f, 67.31943f,149.9425f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1052.162f, -487.9549f, 63.41039f,258.7199f), Mod_Class::Vector4(1046.217f, -497.9194f, 64.07937f,346.5026f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1055.993f, -483.0686f, 63.39307f,256.5244f), Mod_Class::Vector4(1051.741f, -470.7442f, 63.89892f,262.8094f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1062.449f, -445.5917f, 65.4231f,257.3079f), Mod_Class::Vector4(1056.267f, -449.0076f, 66.25752f,346.4865f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1019.49f, -460.5889f, 63.49864f,36.95961f), Mod_Class::Vector4(1014.657f, -469.23f, 64.50294f,36.86657f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(961.8917f, -502.6351f, 61.0839f,30.91768f), Mod_Class::Vector4(970.2992f, -502.3734f, 62.1409f,63.95373f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(947.2533f, -511.7283f, 59.7457f,29.79747f), Mod_Class::Vector4(945.79f, -518.9921f, 60.7491f,322.1016f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(888.6f, -552.6331f, 57.47837f,115.7793f), Mod_Class::Vector4(892.9021f, -540.6024f, 58.50665f,111.6948f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(927.5731f, -568.8168f, 57.31059f,206.4541f), Mod_Class::Vector4(919.8404f, -569.6871f, 58.36638f,197.9201f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(958.3226f, -552.3696f, 58.64332f,209.7552f), Mod_Class::Vector4(965.3028f, -542.1897f, 59.53446f,205.8423f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(982.9958f, -535.0028f, 59.38626f,211.3965f), Mod_Class::Vector4(987.8207f, -526.0056f, 60.69076f,211.1506f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1004.337f, -517.0163f, 60.12453f,204.8713f), Mod_Class::Vector4(1006.223f, -511.052f, 60.83396f,120.5434f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(983.1898f, -573.9033f, 58.70306f,31.48137f), Mod_Class::Vector4(976.7343f, -580.5659f, 59.85005f,28.81238f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(954.9034f, -599.2274f, 58.80585f,28.27949f), Mod_Class::Vector4(964.1855f, -596.0289f, 59.90272f,83.6746f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(974.8517f, -619.3837f, 58.275f,125.435f), Mod_Class::Vector4(980.1414f, -627.6998f, 59.23585f,36.90541f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1007.61f, -589.0872f, 58.51507f,258.1907f), Mod_Class::Vector4(999.6492f, -593.9169f, 59.63858f,262.3635f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1009.365f, -562.7611f, 59.63181f,263.5792f), Mod_Class::Vector4(1009.797f, -572.4837f, 60.59442f,260.7605f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(946.2366f, -254.3581f, 67.11252f,144.8288f), Mod_Class::Vector4(952.6766f, -252.3817f, 67.96442f,74.69676f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(871.5029f, -204.2031f, 70.354f,150.321f), Mod_Class::Vector4(880.307f, -205.2603f, 71.97645f,155.9502f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1373.176f, -1521.595f, 56.65441f,197.1799f), Mod_Class::Vector4(1379.385f, -1515.369f, 58.21299f,211.9685f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1251.666f, -1617.034f, 52.81802f,32.56459f), Mod_Class::Vector4(1261.547f, -1616.846f, 54.74287f,45.56825f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1302.72f, -1741.39f, 53.30978f,21.59027f), Mod_Class::Vector4(1295.516f, -1739.581f, 54.27173f,297.1445f), "", 51),
        Mod_Class::FubarVectors(4, Mod_Class::Vector4(1303.4f, -1708.492f, 54.53121f,200.613f), Mod_Class::Vector4(1289.201f, -1710.854f, 55.47483f,205.4635f), "", 51),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-378.2895f, 6183.842f, 30.91386f,224.1558f), Mod_Class::Vector4(-374.3609f, 6191.076f, 31.72955f,213.7215f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-365.457f, 6197.103f, 30.91161f,224.8345f), Mod_Class::Vector4(-356.9607f, 6207.465f, 31.84228f,217.4898f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-348.5826f, 6216.824f, 30.9116f,223.0872f), Mod_Class::Vector4(-347.2804f, 6225.171f, 31.88411f,228.8832f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-354.3269f, 6263.537f, 30.90641f,14.65497f), Mod_Class::Vector4(-359.9115f, 6260.599f, 31.91941f,323.9963f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-382.342f, 6268.489f, 30.21799f,42.81025f), Mod_Class::Vector4(-379.9861f, 6252.66f, 31.85119f,329.2118f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-439.0626f, 6204.78f, 28.98327f,273.5947f), Mod_Class::Vector4(-468.124f, 6206.047f, 29.55284f,19.22442f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-432.1454f, 6265.637f, 29.70366f,250.108f), Mod_Class::Vector4(-437.9515f, 6272.258f, 30.06829f,350.2123f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-434.3738f, 6260.266f, 29.63981f,252.5641f), Mod_Class::Vector4(-447.9078f, 6260.229f, 30.04783f,148.9435f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-395.0632f, 6310.881f, 28.47791f,223.1733f), Mod_Class::Vector4(-407.3616f, 6314.171f, 28.94115f,215.9467f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-355.2157f, 6335.14f, 29.25954f,223.3189f), Mod_Class::Vector4(-367.9648f, 6341.555f, 29.84363f,222.3839f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-315.4155f, 6312.906f, 31.74133f,44.73646f), Mod_Class::Vector4(-332.5182f, 6302.069f, 33.09311f,32.35503f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-269.8477f, 6357.037f, 31.82169f,42.61639f), Mod_Class::Vector4(-280.4556f, 6350.621f, 32.60081f,42.18668f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-255.3885f, 6360.959f, 30.9038f,44.32188f), Mod_Class::Vector4(-247.6346f, 6370.081f, 31.84554f,56.12477f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-265.0267f, 6405.287f, 30.37198f,206.1364f), Mod_Class::Vector4(-272.6486f, 6400.961f, 31.50496f,212.3271f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-220.1924f, 6383.631f, 31.02857f,43.73579f), Mod_Class::Vector4(-227.2453f, 6377.636f, 31.75924f,42.31236f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-233.0658f, 6420.51f, 30.6535f,220.3545f), Mod_Class::Vector4(-246.0963f, 6414.247f, 31.46059f,142.2568f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-206.001f, 6406.523f, 31.24026f,42.05452f), Mod_Class::Vector4(-213.5712f, 6396.188f, 33.08514f,50.19847f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-225.3319f, 6435.872f, 30.62032f,226.2794f), Mod_Class::Vector4(-229.7038f, 6445.498f, 31.19744f,141.6786f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-192.2425f, 6415.839f, 31.28901f,312.2372f), Mod_Class::Vector4(-188.8396f, 6409.688f, 32.29678f,43.08266f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-50.10324f, 6626.888f, 29.45157f,215.9371f), Mod_Class::Vector4(-41.61409f, 6637.372f, 31.08751f,221.6378f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-37.89799f, 6589.47f, 30.19251f,38.65286f), Mod_Class::Vector4(-37.54647f, 6578.901f, 32.40085f,311.2406f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-13.37525f, 6603.816f, 30.85353f,38.64811f), Mod_Class::Vector4(-26.40973f, 6597.367f, 31.86078f,43.14886f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-4.842309f, 6616.701f, 30.89397f,31.55751f), Mod_Class::Vector4(1.710805f, 6612.73f, 32.07975f,26.80808f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-16.48819f, 6646.774f, 30.54872f,206.0879f), Mod_Class::Vector4(-9.496887f, 6654.269f, 31.70242f,206.7057f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(21.86651f, 6660.181f, 30.94708f,184.5206f), Mod_Class::Vector4(35.40755f, 6663.105f, 32.19041f,157.8432f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(35.83234f, 6607.108f, 31.89514f,250.3097f), Mod_Class::Vector4(31.2813f, 6596.776f, 32.82225f,225.4272f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(13.81533f, 6585.716f, 31.89092f,223.9284f), Mod_Class::Vector4(11.62843f, 6578.257f, 33.0708f,230.5704f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(1504.038f, 6331.375f, 23.40549f,331.9838f), Mod_Class::Vector4(1510.509f, 6325.985f, 24.60712f,55.61734f), "", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-2205.945f, 4248.757f, 46.86387f,35.91669f), Mod_Class::Vector4(-2205.664f, 4242.877f, 48.2797f,48.22973f), "2000 Great Ocean Highway", 52),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-244.0425f, 6237.475f, 30.80112f,226.1291f), Mod_Class::Vector4(-252.1004f, 6235.035f, 31.48921f,227.8413f), "1 Strawberry Ave", 52),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-294.7468f, 6338.973f, 31.55339f,43.93359f), Mod_Class::Vector4(-302.3819f, 6327.095f, 32.8872f,38.04961f), "4401 Procopio Drv", 51),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-104.2227f, 6533.657f, 29.12038f,47.80323f), Mod_Class::Vector4(-105.6748f, 6528.679f, 30.16694f,335.9423f), "4584 Procopio Drv", 51),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-12.21089f, 6564.014f, 31.26414f,224.5186f), Mod_Class::Vector4(-15.11612f, 6557.34f, 33.24039f,314.2951f), "0232 Paleto Blvd", 50),
        Mod_Class::FubarVectors(6, Mod_Class::Vector4(-70.84333f, 6428.631f, 30.75062f,44.96909f), Mod_Class::Vector4(-72.89036f, 6422.281f, 31.49044f,32.35375f), "142 Paleto Blvd", 52)
    };
    inline const std::vector<Mod_Class::FubarVectors> LowClass = {
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(-38.58185f, -1447.042f, 31.11786f,180.4345f), Mod_Class::Vector4(-32.69102f, -1446.299f, 31.89141f,92.93349f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(-55.59203f, -1785.176f, 27.46565f,135.7456f), Mod_Class::Vector4(-50.4203f, -1783.343f, 28.30082f,133.4054f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(-27.58285f, -1851.537f, 25.32663f,318.8048f), Mod_Class::Vector4(-34.17255f, -1847.338f, 26.19355f,221.1098f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(2.966005f, -1874.796f, 23.32661f,317.7646f), Mod_Class::Vector4(-5.009315f, -1872.022f, 24.15102f,43.48953f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(41.04702f, -1855.154f, 22.45056f,136.1201f), Mod_Class::Vector4(45.90803f, -1864.434f, 23.27828f,136.9859f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(53.37162f, -1877.428f, 21.92259f,134.9134f), Mod_Class::Vector4(54.29624f, -1873.232f, 22.80583f,129.4138f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(46.33907f, -1914.932f, 21.27094f,319.6206f), Mod_Class::Vector4(39.02694f, -1911.614f, 21.9535f,222.7011f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(92.06572f, -1964.331f, 20.36646f,320.8834f), Mod_Class::Vector4(85.83772f, -1959.654f, 21.12168f,49.18516f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(105.1436f, -1880.649f, 23.57489f,322.7626f), Mod_Class::Vector4(103.9861f, -1885.299f, 24.31878f,320.235f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(164.2681f, -1864.343f, 23.70184f,155.667f), Mod_Class::Vector4(171.5513f, -1871.345f, 24.40023f,68.41203f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(168.937f, -1930.692f, 20.62996f,229.5449f), Mod_Class::Vector4(179.0472f, -1924.073f, 21.37102f,138.9209f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(335.2253f, -1835.831f, 26.95012f,44.30309f), Mod_Class::Vector4(329.4572f, -1845.896f, 27.74809f,47.83199f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(424.3431f, -1729.366f, 28.86539f,50.20735f), Mod_Class::Vector4(418.6838f, -1735.682f, 29.6077f,148.2224f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(488.5052f, -1721.471f, 28.99154f,249.7533f), Mod_Class::Vector4(489.4659f, -1714.361f, 29.70688f,250.8587f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(475.7072f, -1744.061f, 28.5261f,251.4569f), Mod_Class::Vector4(479.6391f, -1735.673f, 29.15104f,157.5574f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(477.7349f, -1777.262f, 28.26374f,270.731f), Mod_Class::Vector4(472.0552f, -1775.294f, 29.07087f,259.6294f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(405.9705f, -1860.696f, 26.42558f,223.1872f), Mod_Class::Vector4(412.4088f, -1856.41f, 27.32313f,320.492f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(362.7894f, -1902.583f, 24.39289f,229.7933f), Mod_Class::Vector4(368.7201f, -1895.808f, 25.17853f,138.0717f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(317.0536f, -1943.915f, 24.26343f,231.5196f), Mod_Class::Vector4(324.2066f, -1937.158f, 25.01898f,153.2901f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(286.7917f, -1986.442f, 20.76287f,227.0554f), Mod_Class::Vector4(291.2271f, -1980.155f, 21.60053f,146.5357f), "", 50),
        Mod_Class::FubarVectors(1, Mod_Class::Vector4(284.5191f, -1990.111f, 20.08838f,227.9783f), Mod_Class::Vector4(279.8212f, -1993.77f, 20.80378f,312.2727f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(-60.07063f, 1959.315f, 189.5029f,118.714f), Mod_Class::Vector4(-43.83769f, 1960.149f, 190.3533f,21.36499f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(463.1003f, 2606.616f, 42.59025f,7.486252f), Mod_Class::Vector4(470.995f, 2607.702f, 44.4772f,8.536172f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(497.8976f, 2614.769f, 42.27741f,8.831396f), Mod_Class::Vector4(506.5158f, 2610.732f, 43.68818f,13.93271f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(968.9386f, 2715.708f, 38.80089f,175.5282f), Mod_Class::Vector4(984.1534f, 2718.711f, 39.50344f,172.3708f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(993.6621f, 2673.85f, 39.33046f,0.3766021f), Mod_Class::Vector4(980.5497f, 2666.548f, 40.04411f,356.6924f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(813.7386f, 2179.959f, 51.60617f,343.2384f), Mod_Class::Vector4(803.4117f, 2175.007f, 53.0708f,322.7184f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(720.6358f, 2339.233f, 49.66687f,90.30038f), Mod_Class::Vector4(722.5844f, 2331.195f, 51.75034f,352.5101f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1523.582f, 2233.614f, 74.76787f,171.2222f), Mod_Class::Vector4(1535.616f, 2231.895f, 77.69904f,83.97175f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(236.3872f, 3105.419f, 41.73588f,184.8902f), Mod_Class::Vector4(241.0598f, 3107.748f, 42.48718f,92.22945f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(196.6732f, 3038.988f, 43.02736f,274.8384f), Mod_Class::Vector4(195.306f, 3030.964f, 43.88668f,277.7713f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(237.0881f, 3164.726f, 41.94236f,98.2386f), Mod_Class::Vector4(247.2576f, 3169.09f, 42.79127f,102.7627f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(-37.65726f, 2864.669f, 58.5313f,66.48999f), Mod_Class::Vector4(-35.49042f, 2871.262f, 59.59824f,156.7449f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(-263.7923f, 2188.784f, 129.155f,216.862f), Mod_Class::Vector4(-263.9079f, 2195.968f, 130.3988f,238.6304f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(-283.5657f, 2544.437f, 73.70554f,357.8858f), Mod_Class::Vector4(-287.4019f, 2535.703f, 75.47443f,278.7175f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(2635.17f, 3263.966f, 54.55294f,231.1293f), Mod_Class::Vector4(2632.344f, 3258.061f, 55.46336f,332.7899f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(2615.157f, 3267.511f, 54.54915f,250.2655f), Mod_Class::Vector4(2618.491f, 3274.824f, 55.7382f,231.0173f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(2626.032f, 3288.488f, 54.64927f,223.3137f), Mod_Class::Vector4(2634.398f, 3291.614f, 55.72837f,147.1315f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(2426.147f, 4010.396f, 36.02813f,243.4933f), Mod_Class::Vector4(2418.775f, 4020.591f, 36.83404f,246.7558f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1832.03f, 3748.053f, 32.53752f,300.2946f), Mod_Class::Vector4(1830.884f, 3738.097f, 33.96191f,290.2749f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1851.66f, 3768.838f, 32.32976f,122.7865f), Mod_Class::Vector4(1843.261f, 3778.095f, 33.58501f,61.49633f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1893.687f, 3812.721f, 31.63893f,213.6467f), Mod_Class::Vector4(1881.175f, 3810.584f, 32.77881f,295.0231f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1921.434f, 3815.156f, 31.36322f,122.5019f), Mod_Class::Vector4(1925.061f, 3824.4f, 32.43999f,213.7845f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1449.517f, 3652.83f, 33.71304f,20.3736f), Mod_Class::Vector4(1435.8f, 3657.095f, 34.34364f,293.7834f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(3713.465f, 4522.436f, 20.95025f,149.0632f), Mod_Class::Vector4(3725.4f, 4525.177f, 22.4705f,178.5197f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(3696.032f, 4558.43f, 24.75818f,176.8189f), Mod_Class::Vector4(3688.897f, 4562.733f, 25.18305f,267.1775f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(3792.868f, 4469.359f, 5.038733f,71.94101f), Mod_Class::Vector4(3807.896f, 4478.277f, 6.365377f,210.3574f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(3333.444f, 5159.47f, 17.62036f,152.5844f), Mod_Class::Vector4(3310.9f, 5176.172f, 19.61458f,236.721f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(2213.701f, 5607.016f, 53.39285f,13.87942f), Mod_Class::Vector4(2221.507f, 5614.481f, 54.90165f,96.0819f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1670.854f, 4751.54f, 41.19155f,290.69f), Mod_Class::Vector4(1664.081f, 4739.884f, 42.00737f,284.8084f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1715.069f, 4668.863f, 42.41995f,84.59276f), Mod_Class::Vector4(1718.772f, 4677.138f, 43.6558f,90.96929f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1685.134f, 4681.097f, 42.3722f,268.2254f), Mod_Class::Vector4(1683.134f, 4689.38f, 43.06541f,271.9297f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1682.39f, 4651.135f, 42.68787f,267.54f), Mod_Class::Vector4(1674.162f, 4658.021f, 43.37114f,268.1052f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1725.233f, 4630.789f, 42.60341f,117.9296f), Mod_Class::Vector4(1725.087f, 4642.037f, 43.87548f,116.2964f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1971.284f, 4641.456f, 40.25161f,39.49141f), Mod_Class::Vector4(1966.769f, 4634.283f, 41.10112f,19.76906f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1422.55f, 4379.623f, 43.32235f,335.7315f), Mod_Class::Vector4(1429.65f, 4377.926f, 44.59929f,41.46988f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1368.005f, 4365.023f, 43.64425f,80.47865f), Mod_Class::Vector4(1365.839f, 4358.577f, 44.50069f,328.2971f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(1342.655f, 4366.59f, 43.6447f,268.793f), Mod_Class::Vector4(1338.447f, 4359.707f, 44.36736f,310.4155f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(766.3184f, 4182.986f, 39.97334f,10.9133f), Mod_Class::Vector4(775.9548f, 4183.997f, 41.78099f,91.86606f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(749.3324f, 4194.625f, 40.12261f,297.5035f), Mod_Class::Vector4(749.6724f, 4184.149f, 41.08787f,79.96129f), "", 50),
        Mod_Class::FubarVectors(5, Mod_Class::Vector4(711.0807f, 4178.596f, 40.02594f,272.4257f), Mod_Class::Vector4(710.9149f, 4185.534f, 41.08266f,82.2551f), "", 50)
    };

    inline const std::vector<Mod_Class::Vector4> Buisness = {
        Mod_Class::Vector4(-122.6672f, -863.2216f, 33.33057f, 104.0432f),
        Mod_Class::Vector4(-209.1611f, -785.0453f, 30.45403f, 250.6104f),
        Mod_Class::Vector4(-296.5672f, -829.0057f, 32.41154f, 214.424f),
        Mod_Class::Vector4(-262.2707f, -902.109f, 32.30236f, 25.94688f),
        Mod_Class::Vector4(-270.4421f, -706.5453f, 38.26569f, 289.103f),
        Mod_Class::Vector4(-317.5008f, -609.5009f, 33.55332f, 247.4754f),
        Mod_Class::Vector4(-129.8538f, -597.3844f, 48.23175f, 222.6407f),
        Mod_Class::Vector4(-12.27154f, -676.7337f, 49.47276f, 30.79782f),
        Mod_Class::Vector4(205.6318f, -678.3058f, 43.13748f, 48.80375f),
        Mod_Class::Vector4(-175.5412f, -759.5623f, 44.22504f, 235.1201f),
        Mod_Class::Vector4(6.524668f, -933.7928f, 29.90014f, 130.7768f)
    };
    inline const std::vector<Mod_Class::Vector4> BuisnessHeli = {
        Mod_Class::Vector4(-1161.642f, -2191.744f, 12.8148f,57.32962f), //"LSIA Vehicle Warehouse", 5),
        Mod_Class::Vector4(-501.4268f, -2183.638f, 6.946587f,321.1457f), //"Big House Vehicle Warehouse", 5),
        Mod_Class::Vector4(-636.5945f, -1790.944f, 23.62133f,66.77604f), //"La Puerta Vehicle Warehouse", 5),
        Mod_Class::Vector4(-55.26973f, -1838.358f, 26.16808f,318.1885f), //"Davis Vehicle Warehouse", 5),
        Mod_Class::Vector4(131.8759f, -2987.817f, 6.638521f,269.7666f), //"Elysian Island Vehicle Warehouse", 5),
        Mod_Class::Vector4(823.5082f, -2126.997f, 28.91375f,84.27451f), //"Cypress Flats Vehicle Warehouse", 5),
        Mod_Class::Vector4(1006.479f, -1865.767f, 30.50913f,85.25732f), //"La Messa Vehicle Warehouse", 5),
        Mod_Class::Vector4(-1062.604f, -2021.664f, 12.78076f,132.728f), //"Xero Gas Factory", 3),
        Mod_Class::Vector4(-891.0944f, -2734.081f, 13.44745f,150.3703f), //"Bilgeco Warehouse", 3),
        Mod_Class::Vector4(98.10351f, -2193.174f, 5.653489f,89.89806f), //"Walker & Sons Warehouse", 3),
        Mod_Class::Vector4(1004.175f, -2519.513f, 27.92308f,83.26608f), //"Cypress Warehouses Warehouse", 3),
        Mod_Class::Vector4(1071.635f, -2171.634f, 31.53667f,353.9962f), //"Wholesale Furniture Warehouse", 3),
        Mod_Class::Vector4(906.0683f, -1561.211f, 30.34963f,91.20412f), //"Logistics Depot Warehouse", 3),
        Mod_Class::Vector4(766.0025f, -880.819f, 24.59484f,359.1105f), //"Darnel Bros Warehouse", 3),
        Mod_Class::Vector4(-541.9368f, -1767.85f, 21.15111f,330.4702f), //"Fridgit Annexe", 2),
        Mod_Class::Vector4(-344.285f, -1348.406f, 30.88845f,179.0238f), //"Disused Factory Outlet", 2),
        Mod_Class::Vector4(-303.7468f, -2719.221f, 5.619645f,133.8696f), //"LS Marine Building 3", 2),
        Mod_Class::Vector4(550.4014f, -1924.716f, 24.42177f,305.7132f), //"Old Power Station", 2),
        Mod_Class::Vector4(512.8342f, -637.7836f, 24.37022f,178.8968f), //"Railyard Warehouse", 2),
        Mod_Class::Vector4(898.0537f, -1020.824f, 34.58628f,57.24908f),// "Celltowa Unit", 1),
        Mod_Class::Vector4(265.688f, -3004.435f, 5.353796f,358.4464f), // "Pier 400 Utility Building", 1)
        Mod_Class::Vector4(-258.6324f, 194.7045f, 84.54053f,268.0275f), // "West Vinewood Backlot", 3),
        Mod_Class::Vector4(350.2894f, 320.1672f, 103.7689f,75.94923f), // "Discount Retail Unit", 2),
        Mod_Class::Vector4(-1283.439f, -812.7316f, 16.85418f,36.85705f), // "Derriere Lingerie Backlot", 2),
        Mod_Class::Vector4(-1074.916f, -1253.214f, 5.177716f,212.0248f), // "White Widow Garage", 1),
        Mod_Class::Vector4(144.6222f, 159.8517f, 104.2794f,335.4177f), // "Foreclosed Garage", 1)
        Mod_Class::Vector4(-3112.512f, 1325.861f, 19.42356f,88.64252f), // "Chumash Bunker", 4),
        Mod_Class::Vector4(-3016.994f, 3338.623f, 9.622828f,192.2166f), //"Zancuda Bunker", 4)
        Mod_Class::Vector4(1209.959f, -1262.494f, 34.53808f,91.42775f), // "Murrieta Heights", 5),
        Mod_Class::Vector4(1760.141f, -1650.94f, 111.9821f,185.9895f), // "El Burro Heights", 5),
        Mod_Class::Vector4(1573.778f, 2205.523f, 78.27287f,91.86152f), // "Farmhouse Bunker", 4),
        Mod_Class::Vector4(1555.701f, -2142.788f, 76.8575f,14.434f), // "GEE Warehouse", 4)
        Mod_Class::Vector4(64.04389f, 2854.463f, 53.03243f,289.4287f), // "Route 68 Bunker", 4),
        Mod_Class::Vector4(513.9001f, 3048.316f, 39.19131f,212.7776f), // "Oilfields Bunker", 4),
        Mod_Class::Vector4(864.6389f, 3082.295f, 39.34605f,264.9445f), // "Desert Bunker", 4),
        Mod_Class::Vector4(2054.58f, 3340.217f, 44.42887f,336.9905f), // "Smoke Bunker", 4),
        Mod_Class::Vector4(2451.124f, 3111.103f, 47.08403f,277.6165f), // "Thomson Bunker", 4),
        Mod_Class::Vector4(1762.311f, 4731.798f, 40.49058f,317.059f), //
        Mod_Class::Vector4(-398.1481f, 4291.621f, 53.20945f,264.4828f),// "Canyon Bunker", 4),
        Mod_Class::Vector4(-682.0676f, 5948.211f, 14.77343f,359.0253f), // "Paleto Bunker", 4)	
        Mod_Class::Vector4(-75.94235f, -818.4665f, 326.8517f, 235.0135f),//offices
        Mod_Class::Vector4(-145.5026f, -593.9283f, 211.6755f, 208.2894f),
        Mod_Class::Vector4(-912.637f, -378.214f, 137.8069f, 170.1538f),
        Mod_Class::Vector4(-1581.926f, -568.9014f, 116.2295f, 258.0362f),
        Mod_Class::Vector4(-1391.658f, -478.108f, 91.15266f, 92.62007f)
    };

    inline const std::vector<Mod_Class::Vector4> BodyBeach = {
    Mod_Class::Vector4(-1197.88f, -1568.177f, 4.049531f, 305.7955f),//BenchPress
    Mod_Class::Vector4(-1253.458f, -1601.687f, 4.145141f, 217.3408f),
    Mod_Class::Vector4(-1464.325f, -1063.733f, 3.817513f, 272.4313f),//pull ups
    Mod_Class::Vector4(-1208.286f, -1559.48f, 4.609246f, 300.789f),
    Mod_Class::Vector4(-1202.085f, -1572.774f, 4.607903f, 353.9804f),
    Mod_Class::Vector4(-1259.167f, -1615.391f, 4.126909f, 303.0038f),
    Mod_Class::Vector4(-1236.495f, -1574.453f, 4.145737f, 221.2573f),
    Mod_Class::Vector4(-1413.208f, -1067.924f, 3.928926f, 18.29077f),
    Mod_Class::Vector4(-1432.567f, -1048.669f, 4.555942f, 231.4996f),
    Mod_Class::Vector4(-1208.97f, -1574.327f, 4.607889f, 121.9219f)//all else
    };

    inline const std::vector<Mod_Class::Vector4> Epslon = {
    Mod_Class::Vector4(-673.7844f, 76.16772f, 69.68565f, 267.2886f),
    Mod_Class::Vector4(-719.2163f, 43.45778f, 65.19431f, 177.8458f),
    Mod_Class::Vector4(-708.9506f, 70.23295f, 69.68565f, 154.9646f),
    Mod_Class::Vector4(-698.1004f, 46.26298f, 44.03382f, 217.7002f),
    Mod_Class::Vector4(-672.0215f, 88.88709f, 55.85543f, 210.2695f)
    };

    inline const std::vector<Mod_Class::Vector4> GolfCaddy = {
        Mod_Class::Vector4(-1345.164f, 126.815f, 55.63783f, 184.3627f),
        Mod_Class::Vector4(-1343.425f, 109.4654f, 55.62779f, 184.3636f),
        Mod_Class::Vector4(-1330.055f, 109.6066f, 55.90018f, 274.4469f),
        Mod_Class::Vector4(-1321.593f, 22.33979f, 52.89485f, 191.8394f),
        Mod_Class::Vector4(-1294.728f, -24.02095f, 48.1541f, 217.7598f),
        Mod_Class::Vector4(-1283.951f, -34.19522f, 47.44555f, 237.9138f),
        Mod_Class::Vector4(-1236.039f, -55.95164f, 44.34953f, 245.1714f),
        Mod_Class::Vector4(-1195.751f, -78.32055f, 44.12944f, 243.1435f),
        Mod_Class::Vector4(-1170.27f, -87.5376f, 43.99423f, 249.1485f),
        Mod_Class::Vector4(-1128.781f, -112.0847f, 41.42752f, 231.7394f),
        Mod_Class::Vector4(-1114.487f, -126.1622f, 40.83469f, 223.334f),
        Mod_Class::Vector4(-1080.56f, -141.7797f, 40.09267f, 248.8671f),
        Mod_Class::Vector4(-1058.481f, -142.9249f, 40.26999f, 283.3883f),
        Mod_Class::Vector4(-1036.726f, -132.4286f, 39.84369f, 303.1458f),
        Mod_Class::Vector4(-1028.812f, -128.0656f, 39.90619f, 284.1356f),
        Mod_Class::Vector4(-1000.174f, -124.0582f, 39.9119f, 292.5765f),
        Mod_Class::Vector4(-995.474f, -116.6375f, 40.02259f, 355.4651f),
        Mod_Class::Vector4(-996.8564f, -109.8355f, 40.20571f, 30.58298f),
        Mod_Class::Vector4(-1020.028f, -72.35f, 43.10561f, 37.2562f),
        Mod_Class::Vector4(-1056.505f, -40.22454f, 48.29516f, 56.44382f),
        Mod_Class::Vector4(-1092.041f, -26.27667f, 49.66682f, 77.0358f),
        Mod_Class::Vector4(-1178.893f, 41.62355f, 51.81155f, 60.49968f),
        Mod_Class::Vector4(-1253.992f, 88.22222f, 54.19407f, 41.34328f),
        Mod_Class::Vector4(-1275.322f, 104.3254f, 55.6952f, 65.08829f),
        Mod_Class::Vector4(-1322.751f, 109.93f, 55.98849f, 92.79484f)
    };
    inline const std::vector<Mod_Class::Vector4> GolfTee = {
        Mod_Class::Vector4(-1313.334f, 126.7042f, 57.45684f, 251.6158f),
        Mod_Class::Vector4(-1221.41f, 109.3301f, 58.02803f, 236.8991f),
        Mod_Class::Vector4(-1104.894f, 157.2917f, 63.03527f, 94.39286f),
        Mod_Class::Vector4(-1098.374f, 70.06686f, 54.1208f, 177.6088f),
        Mod_Class::Vector4(-983.2672f, -103.5009f, 40.56807f, 114.5253f),
        Mod_Class::Vector4(-1137.586f, -1.602138f, 48.97748f, 34.49409f),
        Mod_Class::Vector4(-1114.5f, -105.7892f, 41.83275f, 50.6364f),
        Mod_Class::Vector4(-1274.89f, 38.05314f, 49.90777f, 246.9902f),
        Mod_Class::Vector4(-1371.6f, 172.2634f, 58.00825f, 291.0517f)
    };

    inline const std::vector<Mod_Class::Vector4> Hiker = {
        Mod_Class::Vector4(2720.672f, 5199.552f, 46.27291f, 122.5306f),
        Mod_Class::Vector4(2963.182f, 5326.022f, 100.778f, 122.5306f),
        Mod_Class::Vector4(2949.531f, 5438.373f, 162.5469f, 122.5306f),
        Mod_Class::Vector4(2992.025f, 5621.749f, 232.6244f, 122.5306f),
        Mod_Class::Vector4(2879.819f, 5899.114f, 365.6005f, 122.5306f),
        Mod_Class::Vector4(2593.217f, 6181.326f, 166.5712f, 122.5306f),
        Mod_Class::Vector4(2878.431f, 6306.65f, 61.58187f, 122.5306f),
        Mod_Class::Vector4(3088.869f, 5976.871f, 142.4146f, 122.5306f),
        Mod_Class::Vector4(3343.402f, 5605.421f, 20.52476f, 122.5306f),
        Mod_Class::Vector4(2396.466f, 3537.57f, 73.30798f, 122.5306f),
        Mod_Class::Vector4(2312.362f, 3462.918f, 63.92526f, 122.5306f),
        Mod_Class::Vector4(2283.617f, 3717.97f, 37.76125f, 122.5306f),
        Mod_Class::Vector4(2616.046f, 3664.323f, 102.1026f, 122.5306f),
        Mod_Class::Vector4(283.5832f, 947.1102f, 210.7036f, 122.5306f),
        Mod_Class::Vector4(348.7232f, 931.5547f, 203.4314f, 122.5306f),
        Mod_Class::Vector4(373.0858f, 779.3486f, 185.2447f, 122.5306f),
        Mod_Class::Vector4(948.7731f, 1037.539f, 261.536f, 122.5306f),
        Mod_Class::Vector4(700.1483f, 1207.633f, 325.3834f, 122.5306f),
        Mod_Class::Vector4(387.6657f, 1040.978f, 237.5461f, 122.5306f),
        Mod_Class::Vector4(-14.01058f, 1159.781f, 245.6257f, 122.5306f),
        Mod_Class::Vector4(-20.51055f, 1325.732f, 272.8569f, 122.5306f),
        Mod_Class::Vector4(-185.2845f, 1296.065f, 303.9481f, 122.5306f),
        Mod_Class::Vector4(-288.8628f, 1453.615f, 337.2819f, 122.5306f),
        Mod_Class::Vector4(-378.9312f, 1239.677f, 326.7248f, 122.5306f),
        Mod_Class::Vector4(-252.5762f, 1563.565f, 336.6067f, 122.5306f),
        Mod_Class::Vector4(-426.8705f, 1592.102f, 356.4857f, 122.5306f),
        Mod_Class::Vector4(-2272.792f, -23.2073f, 112.7793f, 122.5306f),
        Mod_Class::Vector4(-2200.135f, 109.4031f, 164.6617f, 122.5306f),
        Mod_Class::Vector4(-840.225f, 4182.86f, 215.2899f, 122.5306f),
        Mod_Class::Vector4(-690.8635f, 4176.191f, 154.5896f, 122.5306f),
        Mod_Class::Vector4(-524.2221f, 4194.03f, 193.7312f, 122.5306f),
        Mod_Class::Vector4(-206.6364f, 4332.957f, 31.91346f, 122.5306f),
        Mod_Class::Vector4(-526.2425f, 4505.556f, 79.13145f, 122.5306f),
        Mod_Class::Vector4(-893.4651f, 4529.192f, 115.0835f, 122.5306f),
        Mod_Class::Vector4(-1129.78f, 4593.836f, 141.6974f, 122.5306f),
        Mod_Class::Vector4(-1282.924f, 4608.878f, 122.7074f, 122.5306f),
        Mod_Class::Vector4(-1640.868f, 4556.064f, 43.19655f, 122.5306f),
        Mod_Class::Vector4(-1850.567f, 4794.448f, 4.776535f, 122.5306f),
        Mod_Class::Vector4(-1496.777f, 4969.285f, 63.59271f, 122.5306f),
        Mod_Class::Vector4(-1640.963f, 4732.36f, 53.54873f, 122.5306f),
        Mod_Class::Vector4(-1311.3f, 4852.929f, 143.8367f, 122.5306f),
        Mod_Class::Vector4(-964.3344f, 4723.415f, 270.2252f, 122.5306f),
        Mod_Class::Vector4(-943.7798f, 4610.354f, 238.8457f, 122.5306f),
        Mod_Class::Vector4(-291.9144f, 4670.902f, 243.5815f, 122.5306f),
        Mod_Class::Vector4(-587.2416f, 4754.331f, 212.2155f, 122.5306f),
        Mod_Class::Vector4(-565.4411f, 4879.412f, 168.1732f, 122.5306f),
        Mod_Class::Vector4(112.5606f, 5108.352f, 511.6148f, 122.5306f),
        Mod_Class::Vector4(230.4509f, 5247.983f, 601.9519f, 122.5306f),
        Mod_Class::Vector4(971.1742f, 5642.117f, 634.5059f, 122.5306f),
        Mod_Class::Vector4(501.2652f, 5605.104f, 797.9101f, 122.5306f),
        Mod_Class::Vector4(2280.013f, 5789.094f, 155.2191f, 122.5306f),
        Mod_Class::Vector4(2326.279f, 5665.603f, 99.50616f, 122.5306f),
        Mod_Class::Vector4(1793.711f, 5425.402f, 257.2485f, 122.5306f),
        Mod_Class::Vector4(2397.77f, 5316.37f, 96.5042f, 122.5306f)
    };

    inline const std::vector<Mod_Class::Vector4> MethodActing = {
        Mod_Class::Vector4(1444.053f, 3749.468f, 31.92976f, 327.8784f),
        Mod_Class::Vector4(1548.64f, 3513.32f, 35.98967f, 272.104f),
        Mod_Class::Vector4(1533.76f, 3587.345f, 38.87133f, 114.6104f),
        Mod_Class::Vector4(1628.359f, 3656.295f, 35.1298f, 336.5864f),
        Mod_Class::Vector4(1636.128f, 3672.148f, 34.49414f, 115.8842f),
        Mod_Class::Vector4(1542.536f, 3801.337f, 38.26442f, 174.2905f),
        Mod_Class::Vector4(-177.5078f, 6151.445f, 42.63219f, 146.5759f),
        Mod_Class::Vector4(66.09401f, 6663.828f, 31.7822f, 106.9903f),
        Mod_Class::Vector4(-1096.575f, 318.6839f, 66.57769f, 76.68429f),
        Mod_Class::Vector4(1416.632f, 6359.68f, 23.9975f, 211.194f)
    };

    inline const std::vector<Mod_Class::Vector4> FarmingVeh = {
        Mod_Class::Vector4(606.2311f, 6460.72f, 30.36371f, 5.789507f),
        Mod_Class::Vector4(320.5405f, 6446.443f, 31.04944f, 270.2463f),
        Mod_Class::Vector4(290.7818f, 6630.841f, 29.3664f, 90.56525f),
        Mod_Class::Vector4(2888.594f, 4678.878f, 48.91417f, 194.4243f),
        Mod_Class::Vector4(2570.12f, 4376.354f, 40.19937f, 221.7568f),
        Mod_Class::Vector4(2558.896f, 4476.233f, 38.08518f, 315.5452f),
        Mod_Class::Vector4(2594.646f, 4650.071f, 33.75171f, 136.7592f),
        Mod_Class::Vector4(2494.011f, 4804.704f, 35.34127f, 175.9323f),
        Mod_Class::Vector4(2325.911f, 4943.582f, 41.73738f, 222.2322f),
        Mod_Class::Vector4(2255.547f, 5126.423f, 52.96769f, 227.4431f),
        Mod_Class::Vector4(2162.245f, 5100.812f, 46.41386f, 308.368f),
        Mod_Class::Vector4(2048.374f, 4850.952f, 41.61911f, 315.2769f),
        Mod_Class::Vector4(1862.38f, 4848.723f, 44.41615f, 308.6472f),
        Mod_Class::Vector4(1908.713f, 4948.124f, 50.11693f, 246.5423f),
        Mod_Class::Vector4(2008.261f, 4949.729f, 41.91264f, 133.3243f),
        Mod_Class::Vector4(430.6846f, 6468.167f, 28.74771f, 50.51311f),
        Mod_Class::Vector4(173.5756f, 2281.659f, 92.56126f, 263.4358f),
        Mod_Class::Vector4(-128.4896f, 1935.452f, 195.7328f, 0.565784f),
        Mod_Class::Vector4(851.4491f, 2197.121f, 51.95424f, 0.72941f),
        Mod_Class::Vector4(1510.296f, 2203.938f, 79.86816f, 89.00253f),
        Mod_Class::Vector4(2915.768f, 4706.488f, 49.70249f, 289.0847f),
        Mod_Class::Vector4(2544.22f, 4665.709f, 34.05292f, 9.306635f),
        Mod_Class::Vector4(1959.184f, 4648.749f, 40.72918f, 251.9252f),
        Mod_Class::Vector4(1800.967f, 4583.435f, 36.61988f, 3.34992f),
        Mod_Class::Vector4(1722.527f, 4706.51f, 42.44329f, 283.467f),
        Mod_Class::Vector4(1690.262f, 4787.966f, 41.89737f, 88.87373f),
        Mod_Class::Vector4(1661.02f, 4856.334f, 41.85426f, 185.8731f)
    };
    inline const std::vector<Mod_Class::Vector4> Farming = {
        Mod_Class::Vector4(-106.8555f, 1909.862f, 197.0744f, 268.5506f),
        Mod_Class::Vector4(2222.35f, 5577.166f, 53.84396f, 276.1251f),
        Mod_Class::Vector4(1912.766f, 4822.175f, 45.52872f, 228.9311f),
        Mod_Class::Vector4(2247.639f, 4774.398f, 39.89716f, 344.2038f),
        Mod_Class::Vector4(1872.865f, 5055.132f, 51.92373f, 309.9024f),
        Mod_Class::Vector4(1784.382f, 5000.532f, 52.79548f, 128.8428f),
        Mod_Class::Vector4(340.2533f, 6625.122f, 28.87183f, 23.61716f),
        Mod_Class::Vector4(518.1836f, 6496.691f, 30.03387f, 191.6541f)
    };

    inline const std::vector<Mod_Class::Vector4> CycleRacer = {
        Mod_Class::Vector4(-1831.184f, 812.9753f, 138.7346f, 311.9534f),
        Mod_Class::Vector4(-1764.571f, 820.3898f, 140.6735f, 224.452f),
        Mod_Class::Vector4(-1703.508f, 863.8099f, 146.1381f, 329.4052f),
        Mod_Class::Vector4(-1616.284f, 1302.846f, 135.705f, 347.8204f),
        Mod_Class::Vector4(-1486.132f, 1480.176f, 116.4422f, 348.227f),
        Mod_Class::Vector4(-1441.415f, 1967.07f, 70.34432f, 27.66854f),
        Mod_Class::Vector4(-1533.887f, 2206.239f, 55.41714f, 355.8203f),
        Mod_Class::Vector4(-1660.077f, 2391.279f, 34.17039f, 44.57704f),
        Mod_Class::Vector4(-1751.416f, 2434.735f, 31.05655f, 109.2942f),
        Mod_Class::Vector4(-2023.357f, 2341.409f, 33.70339f, 108.7265f),
        Mod_Class::Vector4(-2061.96f, 2275.943f, 41.02344f, 267.6714f),
        Mod_Class::Vector4(-1675.041f, 2222.344f, 85.92983f, 242.9998f),
        Mod_Class::Vector4(-1866.669f, 2028.195f, 138.2143f, 135.3699f),
        Mod_Class::Vector4(-1920.531f, 1768.664f, 172.25f, 107.3471f),
        Mod_Class::Vector4(-2207.551f, 1929.131f, 187.8876f, 114.3961f),
        Mod_Class::Vector4(-2545.024f, 1883.435f, 166.6029f, 204.0507f),
        Mod_Class::Vector4(-2638.612f, 1611.174f, 126.6342f, 155.5314f),
        Mod_Class::Vector4(-2633.305f, 1457.598f, 127.2729f, 184.6736f),
        Mod_Class::Vector4(-2194.78f, 1038.959f, 192.1174f, 220.2004f),
        Mod_Class::Vector4(-1931.807f, 725.5128f, 140.8996f, 309.9311f),
        Mod_Class::Vector4(-1098.633f, -1707.841f, 3.88987f, 90.94658f),
        Mod_Class::Vector4(-1159.836f, -1675.204f, 3.896749f, 113.9283f),
        Mod_Class::Vector4(-1290.18f, -1653.48f, 3.943152f, 35.13303f),
        Mod_Class::Vector4(-1364.189f, -1481.239f, 3.893025f, 14.74119f),
        Mod_Class::Vector4(-1376.141f, -1363.218f, 3.025539f, 303.6996f),
        Mod_Class::Vector4(-1414.212f, -1251.127f, 3.946122f, 35.59299f),
        Mod_Class::Vector4(-1509.133f, -1073.262f, 3.942042f, 69.98211f),
        Mod_Class::Vector4(-1682.818f, -955.2328f, 7.185737f, 74.90568f),
        Mod_Class::Vector4(-1721.408f, -886.7053f, 7.388651f, 317.7188f),
        Mod_Class::Vector4(-1703.534f, -778.4359f, 9.642578f, 48.75169f),
        Mod_Class::Vector4(-1835.261f, -665.6154f, 9.865945f, 50.18934f),
        Mod_Class::Vector4(-2067.342f, -468.4766f, 11.15151f, 50.04951f),
        Mod_Class::Vector4(-2056.839f, -428.9153f, 11.02667f, 320.5753f),
        Mod_Class::Vector4(-2075.677f, -461.2531f, 11.15421f, 235.472f),
        Mod_Class::Vector4(-1886.761f, -619.9555f, 11.02383f, 230.0587f),
        Mod_Class::Vector4(-1672.096f, -805.3911f, 9.649653f, 229.8522f),
        Mod_Class::Vector4(-1718.168f, -922.6528f, 7.201679f, 212.6043f),
        Mod_Class::Vector4(-1594.58f, -1008.036f, 6.960374f, 230.1252f),
        Mod_Class::Vector4(-1421.424f, -1200.432f, 2.879864f, 174.2845f),
        Mod_Class::Vector4(-1363.745f, -1354.689f, 3.734038f, 116.6605f),
        Mod_Class::Vector4(-1373.53f, -1462.265f, 3.899288f, 207.7464f),
        Mod_Class::Vector4(-1188.865f, -1696.42f, 3.944314f, 302.5409f),
        Mod_Class::Vector4(-1119.958f, -1689.427f, 3.891113f, 208.4599f)
    };
    inline const std::vector<Mod_Class::Vector4> CycleMountain = {
        Mod_Class::Vector4(-1017.562f, 5106.583f, 143.565f, 143.8827f),
        Mod_Class::Vector4(-1071.64f, 5061.932f, 166.1416f, 174.5619f),
        Mod_Class::Vector4(-1035.021f, 4968.975f, 200.3412f, 211.0696f),
        Mod_Class::Vector4(-1010.414f, 4957.312f, 195.5821f, 313.6152f),
        Mod_Class::Vector4(-969.2093f, 5008.816f, 180.9947f, 31.7368f),
        Mod_Class::Vector4(-912.714f, 5157.586f, 154.868f, 258.4962f),
        Mod_Class::Vector4(-731.6442f, 5088.924f, 137.6509f, 242.9037f),
        Mod_Class::Vector4(-655.4277f, 5090.802f, 132.4683f, 250.5016f),
        Mod_Class::Vector4(-649.8322f, 5126.122f, 125.6041f, 46.66806f),
        Mod_Class::Vector4(-754.5825f, 5187.835f, 110.7141f, 62.56298f),
        Mod_Class::Vector4(-824.0505f, 5177.887f, 111.9148f, 101.8079f),
        Mod_Class::Vector4(-893.9097f, 5209.729f, 112.5179f, 80.07652f),
        Mod_Class::Vector4(-988.9006f, 5185.046f, 121.5435f, 132.7849f),
        Mod_Class::Vector4(-90.27805f, 1530.019f, 285.9787f, 69.38036f),
        Mod_Class::Vector4(-181.8039f, 1542.743f, 312.8849f, 103.2741f),
        Mod_Class::Vector4(-224.489f, 1560.842f, 325.914f, 63.67017f),
        Mod_Class::Vector4(-267.6929f, 1545.163f, 335.6747f, 132.9373f),
        Mod_Class::Vector4(-289.0792f, 1456.778f, 336.3503f, 170.9723f),
        Mod_Class::Vector4(-327.6443f, 1350.852f, 344.5363f, 167.0383f),
        Mod_Class::Vector4(-375.376f, 1247.601f, 326.4334f, 139.2814f),
        Mod_Class::Vector4(-387.3534f, 1230.396f, 325.1447f, 147.9483f),
        Mod_Class::Vector4(-388.1032f, 1176.121f, 325.1177f, 249.1379f),
        Mod_Class::Vector4(-229.2232f, 1291.04f, 306.4082f, 300.9233f),
        Mod_Class::Vector4(-186.1638f, 1292.394f, 303.1103f, 235.3964f),
        Mod_Class::Vector4(-122.8801f, 1312.186f, 297.1616f, 290.4021f),
        Mod_Class::Vector4(-16.56782f, 1320.053f, 271.3388f, 250.8344f),
        Mod_Class::Vector4(35.19429f, 1292.053f, 262.6383f, 250.6078f),
        Mod_Class::Vector4(111.7312f, 1261.334f, 253.0591f, 249.888f),
        Mod_Class::Vector4(192.726f, 1286.057f, 244.9456f, 286.535f),
        Mod_Class::Vector4(218.4447f, 1324.374f, 239.0383f, 349.563f),
        Mod_Class::Vector4(189.5349f, 1361.092f, 244.0261f, 50.20052f),
        Mod_Class::Vector4(-35.94518f, 1482.559f, 276.2757f, 47.98716f)
    };
    inline const std::vector<Mod_Class::Vector4> CycleBMX = {
        Mod_Class::Vector4(1131.343f, 2220.968f, 48.44126f, 243.5716f),
        Mod_Class::Vector4(1159.706f, 2217.349f, 50.82573f, 258.8792f),
        Mod_Class::Vector4(1166.896f, 2162.989f, 53.84629f, 169.9953f),
        Mod_Class::Vector4(1098.576f, 2155.015f, 52.69805f, 73.61179f),
        Mod_Class::Vector4(1090.835f, 2211.467f, 48.93021f, 9.747736f),
        Mod_Class::Vector4(1044.372f, 2192.271f, 44.4439f, 118.0097f),
        Mod_Class::Vector4(993.3459f, 2211.962f, 46.28838f, 41.27867f),
        Mod_Class::Vector4(928.5845f, 2252.565f, 44.727f, 65.21915f),
        Mod_Class::Vector4(898.9063f, 2299.954f, 45.55281f, 1.079976f),
        Mod_Class::Vector4(893.9247f, 2367.798f, 51.03556f, 9.637207f),
        Mod_Class::Vector4(890.4763f, 2458.718f, 50.12368f, 344.7286f),
        Mod_Class::Vector4(946.5344f, 2481.687f, 49.33643f, 244.823f),
        Mod_Class::Vector4(987.7492f, 2452.002f, 48.93232f, 244.9161f),
        Mod_Class::Vector4(1041.457f, 2437.304f, 44.44455f, 260.0757f),
        Mod_Class::Vector4(1079.171f, 2446.667f, 48.99023f, 308.1842f),
        Mod_Class::Vector4(1119.289f, 2479.278f, 50.80782f, 276.7901f),
        Mod_Class::Vector4(1158.328f, 2469.449f, 53.44667f, 220.5749f),
        Mod_Class::Vector4(1165.507f, 2273.166f, 50.33825f, 175.9661f),
        Mod_Class::Vector4(1125.515f, 2274.496f, 48.946f, 24.32979f),
        Mod_Class::Vector4(1114.623f, 2402.528f, 49.40758f, 7.477652f),
        Mod_Class::Vector4(1057.731f, 2410.765f, 49.92449f, 93.07478f),
        Mod_Class::Vector4(1008.178f, 2407.365f, 51.17159f, 96.8075f),
        Mod_Class::Vector4(927.653f, 2374.892f, 46.21589f, 143.9296f),
        Mod_Class::Vector4(974.15f, 2347.133f, 48.14143f, 229.5057f),
        Mod_Class::Vector4(976.75f, 2319.152f, 47.77378f, 136.5242f),
        Mod_Class::Vector4(937.3336f, 2297.426f, 45.63793f, 157.523f),
        Mod_Class::Vector4(966.1271f, 2274.494f, 46.90409f, 249.9637f),
        Mod_Class::Vector4(1012.06f, 2256.639f, 44.98619f, 273.5895f),
        Mod_Class::Vector4(1074.876f, 2257.516f, 43.97958f, 269.696f),
        Mod_Class::Vector4(1119.866f, 2237.699f, 48.11778f, 205.3962f),
        Mod_Class::Vector4(709.8904f, -1209.633f, 24.15573f, 271.7742f),
        Mod_Class::Vector4(725.6425f, -1209.393f, 24.15294f, 264.8582f),
        Mod_Class::Vector4(727.7066f, -1226.787f, 24.16752f, 176.0324f),
        Mod_Class::Vector4(711.7754f, -1230.785f, 26.01836f, 89.38039f),
        Mod_Class::Vector4(695.2515f, -1233.058f, 24.22271f, 99.51613f),
        Mod_Class::Vector4(691.3087f, -1221.595f, 24.2079f, 1.18434f),
        Mod_Class::Vector4(710.1845f, -1218.317f, 24.13501f, 271.655f)
    };
    inline const std::vector<Mod_Class::Vector4> CycleCruser = {
        Mod_Class::Vector4(-851.1493f, -856.7646f, 18.77589f, 358.0621f),
        Mod_Class::Vector4(-906.5968f, -968.0899f, 1.743039f, 210.8783f),
        Mod_Class::Vector4(-1348.573f, -1115.726f, 3.962325f, 299.9897f),
        Mod_Class::Vector4(-659.8745f, -959.2974f, 20.91997f, 263.4982f),
        Mod_Class::Vector4(-241.4375f, -1584.557f, 33.22305f, 187.4465f),
        Mod_Class::Vector4(270.0584f, -1683.841f, 28.84942f, 297.7897f),
        Mod_Class::Vector4(473.6976f, -1815.705f, 27.51255f, 129.6885f),
        Mod_Class::Vector4(986.9617f, -676.3321f, 56.99862f, 24.37898f),
        Mod_Class::Vector4(1061.91f, -410.1332f, 66.65007f, 306.7592f),
        Mod_Class::Vector4(-3227.214f, 985.9169f, 12.22838f, 3.493601f),
        Mod_Class::Vector4(-181.3568f, 6463.39f, 30.20193f, 323.6627f),
        Mod_Class::Vector4(1665.24f, 4906.476f, 41.67233f, 354.5847f)
    };

    inline const std::vector<Mod_Class::Vector4> LGBQWXYZ = {
        Mod_Class::Vector4(-555.8153f, 204.4809f, 82.72643f, 252.7766f),
        Mod_Class::Vector4(-237.4932f, 207.43f, 84.30554f, 303.6445f),
        Mod_Class::Vector4(224.884f, 302.908f, 105.5358f, 247.2323f)
    };

    inline const std::vector<Mod_Class::Vector4> PoolPlace = {
        Mod_Class::Vector4(-3045.812f, 55.64172f, 8.627448f, 191.5956f),
        Mod_Class::Vector4(-2943.079f, 655.5176f, 22.39165f, 32.5262f),
        Mod_Class::Vector4(-2962.768f, 703.4619f, 26.46712f, 164.4944f),
        Mod_Class::Vector4(-2964.547f, 731.1447f, 27.88261f, 84.45402f),
        Mod_Class::Vector4(-2983.335f, 751.6773f, 25.11157f, 111.447f),
        Mod_Class::Vector4(-2795.803f, 1452.367f, 99.25223f, 66.35561f),
        Mod_Class::Vector4(-2634.445f, 1880.577f, 158.3878f, 153.5368f),
        Mod_Class::Vector4(3096.864f, 6025.98f, 121.8479f, 336.2496f),
        Mod_Class::Vector4(2563.98f, 6153.684f, 161.2354f, 346.2019f),
        Mod_Class::Vector4(-1859.59f, 228.4411f, 82.96251f, 127.7508f),
        Mod_Class::Vector4(-1877.686f, 259.271f, 84.43298f, 51.80576f),
        Mod_Class::Vector4(-1881.919f, 295.7777f, 87.72468f, 250.4356f),
        Mod_Class::Vector4(-1847.838f, 282.9479f, 87.24543f, 240.6522f),
        Mod_Class::Vector4(-1775.012f, 322.7032f, 87.18047f, 197.6634f),
        Mod_Class::Vector4(-1710.577f, 367.765f, 88.29889f, 106.1305f),
        Mod_Class::Vector4(-1678.33f, 364.0826f, 83.0807f, 119.0709f),
        Mod_Class::Vector4(-1893.09f, 357.7369f, 91.81727f, 89.98589f),
        Mod_Class::Vector4(-1906.691f, 389.7257f, 95.27182f, 70.20741f),
        Mod_Class::Vector4(-1917.88f, 442.0487f, 101.2374f, 23.85498f),
        Mod_Class::Vector4(-1775.343f, 437.326f, 125.9239f, 279.1228f),
        Mod_Class::Vector4(-1919.291f, 127.1571f, 80.51678f, 248.5568f),
        Mod_Class::Vector4(-1955.446f, 141.1171f, 83.02171f, 15.4176f),
        Mod_Class::Vector4(-1988.662f, 239.2818f, 85.75612f, 317.5026f),
        Mod_Class::Vector4(-1997.83f, 324.9079f, 89.55524f, 300.8342f),
        Mod_Class::Vector4(-2033.305f, 356.9896f, 92.78632f, 259.0774f),
        Mod_Class::Vector4(-2017.061f, 419.425f, 100.7554f, 104.0086f),
        Mod_Class::Vector4(-2042.502f, 510.5439f, 105.0207f, 201.5715f),
        Mod_Class::Vector4(-2019.332f, 607.6757f, 116.0399f, 176.9692f),
        Mod_Class::Vector4(-1906.127f, 597.2462f, 121.0427f, 133.3996f),
        Mod_Class::Vector4(-2004.849f, 647.3167f, 120.8392f, 179.2453f),
        Mod_Class::Vector4(-1864.729f, 667.7847f, 128.7296f, 120.8827f),
        Mod_Class::Vector4(-994.6255f, -1503.056f, 3.619596f, 286.6233f),
        Mod_Class::Vector4(-1303.983f, -1042.059f, 11.07695f, 95.69601f),
        Mod_Class::Vector4(-1418.43f, -993.3387f, 18.16207f, 113.1817f),
        Mod_Class::Vector4(-1347.12f, -928.1561f, 10.38993f, 280.809f),
        Mod_Class::Vector4(-1127.6f, -368.2942f, 47.66271f, 2.678566f),
        Mod_Class::Vector4(-1194.313f, -238.2115f, 36.40221f, 302.0073f),
        Mod_Class::Vector4(-1655.04f, -423.9619f, 39.99371f, 215.616f),
        Mod_Class::Vector4(-1701.476f, -466.6209f, 39.99554f, 79.94219f),
        Mod_Class::Vector4(-1996.455f, -271.146f, 30.81234f, 161.3845f),
        Mod_Class::Vector4(-1197.041f, 313.4686f, 67.751f, 239.0723f),
        Mod_Class::Vector4(-1337.581f, 350.9042f, 62.31931f, 289.1602f),
        Mod_Class::Vector4(-1492.492f, -56.38963f, 53.43258f, 256.6854f),
        Mod_Class::Vector4(-1540.042f, -109.9774f, 52.42807f, 335.4102f),
        Mod_Class::Vector4(-1611.778f, -16.5292f, 56.53456f, 226.6901f),
        Mod_Class::Vector4(-1639.233f, -9.076792f, 59.92145f, 4.578232f),
        Mod_Class::Vector4(-1586.684f, 4.038853f, 59.26731f, 98.43343f),
        Mod_Class::Vector4(-1529.05f, -5.181115f, 54.84669f, 332.3435f),
        Mod_Class::Vector4(-1479.162f, 14.24485f, 52.43146f, 311.0717f),
        Mod_Class::Vector4(-1461.813f, 179.0799f, 54.75267f, 268.7966f),
        Mod_Class::Vector4(-788.2491f, -788.2381f, 26.32391f, 347.4677f),
        Mod_Class::Vector4(-552.5022f, -783.8768f, 29.30106f, 186.7736f),
        Mod_Class::Vector4(-724.062f, -1001.766f, 16.71691f, 75.74413f),
        Mod_Class::Vector4(-1029.607f, 290.339f, 65.11586f, 78.66148f),
        Mod_Class::Vector4(-1053.091f, 365.7118f, 68.35947f, 165.9629f),
        Mod_Class::Vector4(-878.9501f, 340.3165f, 83.47378f, 320.597f),
        Mod_Class::Vector4(-887.8083f, 327.1554f, 82.18018f, 180.3041f),
        Mod_Class::Vector4(-831.8134f, 248.9689f, 77.22815f, 273.1329f),
        Mod_Class::Vector4(-893.313f, 169.0273f, 67.68666f, 93.2482f),
        Mod_Class::Vector4(-954.7523f, 220.4424f, 65.75686f, 136.6233f),
        Mod_Class::Vector4(-1010.184f, 226.0269f, 63.68847f, 38.22365f),
        Mod_Class::Vector4(-1017.759f, 148.1357f, 56.12671f, 293.8944f),
        Mod_Class::Vector4(-1000.254f, 121.9075f, 53.94715f, 270.1829f),
        Mod_Class::Vector4(-888.7141f, 101.3723f, 53.14249f, 87.43171f),
        Mod_Class::Vector4(-787.3904f, 123.0227f, 54.69615f, 80.05839f),
        Mod_Class::Vector4(-952.6634f, 53.73639f, 48.71432f, 208.2334f),
        Mod_Class::Vector4(-895.5533f, -37.63317f, 36.60196f, 233.8345f),
        Mod_Class::Vector4(-1024.37f, 432.2284f, 71.08146f, 154.1581f),
        Mod_Class::Vector4(-995.2686f, 438.8302f, 78.33302f, 334.0864f),
        Mod_Class::Vector4(-1000.844f, 463.134f, 77.19495f, 104.392f),
        Mod_Class::Vector4(-980.0664f, 463.8022f, 79.73483f, 46.73758f),
        Mod_Class::Vector4(-927.5062f, 487.5936f, 82.77666f, 170.0165f),
        Mod_Class::Vector4(-936.8797f, 501.3094f, 79.72826f, 53.92431f),
        Mod_Class::Vector4(-1013.338f, 539.5078f, 77.79255f, 282.0752f),
        Mod_Class::Vector4(-1066.973f, 497.7644f, 83.94453f, 220.1158f),
        Mod_Class::Vector4(-1117.826f, 512.5352f, 80.53722f, 231.0205f),
        Mod_Class::Vector4(-1160.468f, 509.6538f, 84.52025f, 279.801f),
        Mod_Class::Vector4(-1193.058f, 491.3557f, 96.80259f, 331.3968f),
        Mod_Class::Vector4(-1303.943f, 492.6552f, 96.08507f, 225.8883f),
        Mod_Class::Vector4(-1392.492f, 601.5625f, 129.8707f, 353.5048f),
        Mod_Class::Vector4(-1413.317f, 588.257f, 125.1205f, 217.9151f),
        Mod_Class::Vector4(-1386.419f, 505.1083f, 119.582f, 105.1062f),
        Mod_Class::Vector4(-1326.583f, 540.5914f, 122.6075f, 269.3641f),
        Mod_Class::Vector4(-1298.875f, 577.9588f, 128.2203f, 178.3084f),
        Mod_Class::Vector4(-1271.058f, 596.7078f, 137.4534f, 247.1871f),
        Mod_Class::Vector4(-1233.919f, 615.423f, 137.1098f, 289.2881f),
        Mod_Class::Vector4(-1136.452f, 713.3501f, 153.7498f, 201.2598f),
        Mod_Class::Vector4(-1107.412f, 732.3629f, 157.4969f, 143.5177f),
        Mod_Class::Vector4(-1087.713f, 750.5551f, 167.9281f, 164.4328f),
        Mod_Class::Vector4(-1025.926f, 770.5267f, 169.6798f, 211.2749f),
        Mod_Class::Vector4(-977.2301f, 735.5602f, 172.0218f, 265.5352f),
        Mod_Class::Vector4(-909.6926f, 740.3763f, 180.0956f, 81.82249f),
        Mod_Class::Vector4(-868.6624f, 752.2235f, 189.9032f, 7.877455f),
        Mod_Class::Vector4(-814.408f, 783.7341f, 200.6464f, 29.9381f),
        Mod_Class::Vector4(-752.7916f, 777.5481f, 211.9392f, 194.7471f),
        Mod_Class::Vector4(-909.4453f, 843.1014f, 184.2988f, 140.1425f),
        Mod_Class::Vector4(-971.9465f, 842.3605f, 175.6778f, 54.60799f),
        Mod_Class::Vector4(-1022.66f, 842.3872f, 170.6267f, 244.5529f),
        Mod_Class::Vector4(-1066.097f, 839.69f, 164.9688f, 217.0195f),
        Mod_Class::Vector4(-1094.515f, 836.8392f, 166.7997f, 226.6554f),
        Mod_Class::Vector4(-1159.052f, 807.4681f, 165.6994f, 247.5676f),
        Mod_Class::Vector4(-1336.202f, 429.5737f, 98.90172f, 10.91781f),
        Mod_Class::Vector4(-1209.78f, 434.0115f, 83.63775f, 79.56482f),
        Mod_Class::Vector4(-1146.08f, 437.287f, 84.84669f, 213.0582f),
        Mod_Class::Vector4(-1461.746f, 478.9407f, 114.6442f, 294.9983f),
        Mod_Class::Vector4(-1474.807f, 432.7327f, 110.9154f, 211.9605f),
        Mod_Class::Vector4(-1518.777f, 391.6364f, 106.1265f, 187.5404f),
        Mod_Class::Vector4(-1062.276f, 567.8226f, 100.8951f, 14.25475f),
        Mod_Class::Vector4(-907.7054f, 504.5181f, 91.1715f, 343.916f),
        Mod_Class::Vector4(-900.4271f, 478.245f, 87.10304f, 240.5481f),
        Mod_Class::Vector4(-814.1697f, 454.6563f, 88.76468f, 97.29221f),
        Mod_Class::Vector4(-834.1874f, 492.4228f, 88.93082f, 302.3769f),
        Mod_Class::Vector4(-845.0479f, 545.5221f, 93.45917f, 20.59651f),
        Mod_Class::Vector4(-887.1305f, 575.8942f, 99.39474f, 305.7055f),
        Mod_Class::Vector4(-937.6163f, 612.3262f, 108.1101f, 114.1795f),
        Mod_Class::Vector4(-1125.642f, 604.6667f, 102.6665f, 23.63789f),
        Mod_Class::Vector4(-1175.469f, 604.4519f, 101.4761f, 220.994f),
        Mod_Class::Vector4(-685.0389f, 794.5554f, 197.2649f, 238.0637f),
        Mod_Class::Vector4(-614.069f, 759.4872f, 187.0014f, 221.4456f),
        Mod_Class::Vector4(-649.715f, 743.8446f, 172.4775f, 87.59254f),
        Mod_Class::Vector4(-613.1782f, 621.3754f, 149.7904f, 164.7444f),
        Mod_Class::Vector4(-634.371f, 659.1119f, 148.6696f, 22.42731f),
        Mod_Class::Vector4(-661.1744f, 616.6246f, 146.1949f, 199.2662f),
        Mod_Class::Vector4(-729.4888f, 685.0509f, 155.9513f, 180.7433f),
        Mod_Class::Vector4(-734.0542f, 652.4131f, 154.2377f, 167.3811f),
        Mod_Class::Vector4(-839.3329f, 693.5334f, 145.2106f, 154.7381f),
        Mod_Class::Vector4(-1064.972f, 701.9827f, 163.6349f, 353.3205f),
        Mod_Class::Vector4(-1601.946f, 770.3289f, 187.6154f, 101.8007f),
        Mod_Class::Vector4(-674.3577f, 866.253f, 223.6916f, 351.8296f),
        Mod_Class::Vector4(-621.1686f, 832.4181f, 204.3554f, 326.4169f),
        Mod_Class::Vector4(-544.7578f, 793.3355f, 195.8609f, 177.7308f),
        Mod_Class::Vector4(-554.5526f, 612.8793f, 136.0247f, 192.0421f),
        Mod_Class::Vector4(-570.2823f, 544.6909f, 108.9361f, 196.9023f),
        Mod_Class::Vector4(-571.0569f, 580.2227f, 113.3992f, 304.4825f),
        Mod_Class::Vector4(-623.428f, 555.0164f, 110.5005f, 256.445f),
        Mod_Class::Vector4(-661.4534f, 551.3612f, 109.9831f, 274.937f),
        Mod_Class::Vector4(-662.6475f, 520.2614f, 108.8628f, 35.55315f),
        Mod_Class::Vector4(-760.3415f, 495.6663f, 105.6227f, 197.768f),
        Mod_Class::Vector4(-792.6409f, 488.0746f, 98.77155f, 239.2353f),
        Mod_Class::Vector4(-557.361f, 410.2712f, 98.9854f, 103.8872f),
        Mod_Class::Vector4(-622.6409f, 452.2882f, 107.0253f, 21.81733f),
        Mod_Class::Vector4(-654.8201f, 443.7271f, 108.8958f, 98.25793f),
        Mod_Class::Vector4(-707.8818f, 434.7238f, 105.3034f, 206.2419f),
        Mod_Class::Vector4(-793.0532f, 408.5196f, 90.11823f, 317.7177f),
        Mod_Class::Vector4(-429.6884f, 433.9929f, 111.3882f, 142.4591f),
        Mod_Class::Vector4(-470.8019f, 431.3893f, 101.4715f, 65.82205f),
        Mod_Class::Vector4(-485.7001f, 446.8537f, 95.78496f, 143.3383f),
        Mod_Class::Vector4(-526.5187f, 455.3444f, 101.9223f, 82.61566f),
        Mod_Class::Vector4(-502.1317f, 483.4032f, 105.871f, 353.9517f),
        Mod_Class::Vector4(-467.4027f, 505.9088f, 120.1588f, 152.0833f),
        Mod_Class::Vector4(-446.5811f, 507.9971f, 118.1903f, 237.8992f),
        Mod_Class::Vector4(-400.2415f, 479.6264f, 118.3372f, 194.5138f),
        Mod_Class::Vector4(-377.3803f, 442.6701f, 112.4488f, 352.5979f),
        Mod_Class::Vector4(-315.0863f, 523.4f, 120.1131f, 172.5486f),
        Mod_Class::Vector4(-343.7807f, 556.3951f, 125.0126f, 58.56496f),
        Mod_Class::Vector4(-462.3269f, 570.8691f, 125.009f, 198.8191f),
        Mod_Class::Vector4(-433.771f, 698.8554f, 151.4797f, 104.4336f),
        Mod_Class::Vector4(-246.2313f, 658.5173f, 186.7893f, 78.76883f),
        Mod_Class::Vector4(-202.4824f, 662.7463f, 199.0307f, 206.3775f),
        Mod_Class::Vector4(-442.3546f, 621.9311f, 141.2312f, 94.32441f),
        Mod_Class::Vector4(-409.7963f, 626.1968f, 156.7769f, 294.2011f),
        Mod_Class::Vector4(-328.9471f, 602.281f, 170.6802f, 186.9233f),
        Mod_Class::Vector4(-280.7156f, 567.8633f, 172.5188f, 153.9769f),
        Mod_Class::Vector4(-244.0822f, 565.3209f, 183.8785f, 164.9493f),
        Mod_Class::Vector4(-174.8147f, 565.8653f, 188.8128f, 166.2484f),
        Mod_Class::Vector4(-122.5135f, 571.5621f, 194.6613f, 180.1518f),
        Mod_Class::Vector4(298.9084f, 463.998f, 141.1974f, 177.8186f),
        Mod_Class::Vector4(283.5058f, 501.5374f, 146.2818f, 272.0558f),
        Mod_Class::Vector4(294.0867f, 530.4378f, 150.9946f, 147.5757f),
        Mod_Class::Vector4(242.9051f, 639.3737f, 184.2167f, 174.0911f),
        Mod_Class::Vector4(184.7669f, 551.7874f, 178.1748f, 161.2797f),
        Mod_Class::Vector4(91.22596f, 535.8976f, 171.8904f, 191.2823f),
        Mod_Class::Vector4(52.97155f, 533.974f, 173.7988f, 98.56342f),
        Mod_Class::Vector4(223.5663f, 481.628f, 138.9433f, 186.0741f),
        Mod_Class::Vector4(154.6444f, 479.0873f, 140.5918f, 229.5701f),
        Mod_Class::Vector4(150.1482f, 456.2213f, 139.5088f, 192.9131f),
        Mod_Class::Vector4(100.1431f, 439.8868f, 140.4936f, 240.5627f),
        Mod_Class::Vector4(24.01077f, 431.562f, 141.2572f, 191.9438f),
        Mod_Class::Vector4(-72.6179f, 465.5805f, 135.9239f, 76.12296f),
        Mod_Class::Vector4(-123.3051f, 484.7867f, 135.2343f, 277.5651f),
        Mod_Class::Vector4(-181.1604f, 481.0771f, 132.1258f, 173.1447f),
        Mod_Class::Vector4(-240.873f, 462.7502f, 124.9531f, 265.0873f),
        Mod_Class::Vector4(-280.4801f, 455.5736f, 108.9758f, 11.24059f),
        Mod_Class::Vector4(-151.0757f, 397.4683f, 109.3303f, 102.5608f),
        Mod_Class::Vector4(-195.848f, 375.325f, 107.4195f, 118.4353f),
        Mod_Class::Vector4(-250.1479f, 349.482f, 108.4312f, 257.0241f),
        Mod_Class::Vector4(-312.6213f, 338.596f, 108.3876f, 270.0114f),
        Mod_Class::Vector4(-305.1698f, 404.4672f, 107.9418f, 19.61601f),
        Mod_Class::Vector4(-361.4859f, 388.3761f, 110.2353f, 296.8794f),
        Mod_Class::Vector4(-427.2299f, 374.5766f, 106.6869f, 346.4425f),
        Mod_Class::Vector4(-495.9285f, 379.7473f, 100.1044f, 110.8691f),
        Mod_Class::Vector4(259.914f, 768.7663f, 198.1667f, 171.6786f),
        Mod_Class::Vector4(-82.69418f, 951.5432f, 231.5304f, 4.040697f),
        Mod_Class::Vector4(-53.98798f, 801.733f, 225.2128f, 198.7475f),
        Mod_Class::Vector4(-158.4015f, 872.744f, 231.239f, 281.8446f),
        Mod_Class::Vector4(-203.0339f, 993.9344f, 229.9067f, 170.5246f),
        Mod_Class::Vector4(261.3582f, 53.34766f, 86.86005f, 112.5693f),
        Mod_Class::Vector4(-9.255273f, -33.10223f, 67.3112f, 170.3541f),
        Mod_Class::Vector4(-118.0738f, 15.28374f, 67.68005f, 185.8164f),
        Mod_Class::Vector4(-55.54819f, 112.7238f, 79.84457f, 36.34098f),
        Mod_Class::Vector4(-16.14182f, 348.6998f, 111.2587f, 185.8422f),
        Mod_Class::Vector4(512.7614f, 214.5401f, 102.8892f, 79.30675f),
        Mod_Class::Vector4(-303.4641f, 163.318f, 86.68427f, 195.2101f),
        Mod_Class::Vector4(-477.1502f, 182.252f, 82.03768f, 79.51382f),
        Mod_Class::Vector4(-96.92668f, -342.335f, 40.3636f, 227.6679f),
        Mod_Class::Vector4(96.90714f, -246.5079f, 45.79247f, 219.79f),
        Mod_Class::Vector4(78.0203f, -240.652f, 46.40194f, 253.2796f),
        Mod_Class::Vector4(333.0154f, -195.3859f, 52.50391f, 224.6233f),
        Mod_Class::Vector4(955.6845f, -687.8796f, 55.86848f, 146.0258f),
        Mod_Class::Vector4(912.7341f, -654.8762f, 56.21679f, 275.1885f),
        Mod_Class::Vector4(903.1922f, -641.8429f, 56.5079f, 73.38454f),
        Mod_Class::Vector4(873.175f, -613.0998f, 56.6581f, 357.458f),
        Mod_Class::Vector4(839.5805f, -580.3686f, 55.49578f, 321.4151f),
        Mod_Class::Vector4(825.0772f, -521.6014f, 54.95789f, 119.8508f),
        Mod_Class::Vector4(896.8047f, -466.8496f, 57.32214f, 207.8782f),
        Mod_Class::Vector4(917.1431f, -457.6846f, 59.27655f, 119.2411f),
        Mod_Class::Vector4(932.3779f, -448.6634f, 59.52022f, 296.9828f),
        Mod_Class::Vector4(954.8691f, -441.865f, 61.23558f, 47.42667f),
        Mod_Class::Vector4(968.7847f, -432.1448f, 62.18409f, 211.815f),
        Mod_Class::Vector4(1425.48f, 1154.443f, 113.2876f, 90.80857f)
    };

    inline const std::vector<Mod_Class::Vector4> Worker_Autoshop = {
        Mod_Class::Vector4(1138.573f, -785.1884f, 57.59872f, 167.1082f),
        Mod_Class::Vector4(544.0156f, -173.4207f, 54.48134f, 340.1063f),
        Mod_Class::Vector4(2515.484f, 4217.121f, 39.929f, 144.665f),
        Mod_Class::Vector4(-67.9494f, 6432.331f, 31.48058f, 326.9482f),
        Mod_Class::Vector4(255.0459f, 2582.047f, 45.13689f, 307.621f),
        Mod_Class::Vector4(1993.807f, 3793.491f, 32.18077f, 215.6984f),
        Mod_Class::Vector4(1688.451f, 3286.147f, 41.14651f, 66.41962f),
        Mod_Class::Vector4(2343.264f, 3114.95f, 48.2087f, 152.7309f),
        Mod_Class::Vector4(-82.67906f, -1325.488f, 29.27505f, 339.8256f),
        Mod_Class::Vector4(-22.95398f, -1674.278f, 29.49172f, 324.6906f),
        Mod_Class::Vector4(1181.487f, 2636.379f, 37.7949f, 147.4034f),
        Mod_Class::Vector4(107.9624f, 6629.401f, 31.78723f, 34.92216f)
    };       //"Autoshop Worker 2"), 
    inline const std::vector<Mod_Class::Vector4> Worker_Waiter = {
        Mod_Class::Vector4(-3022.146f, 39.75996f, 10.11778f, 251.9171f),
        Mod_Class::Vector4(1982.751f, 3053.365f, 47.21507f, 237.2689f)
    };       //"Waiter") ; 
    inline const std::vector<Mod_Class::Vector4> Worker_Sweatshop = {
        Mod_Class::Vector4(1736.674f, -1609.645f, 112.4697f, 251.9171f),
            Mod_Class::Vector4(1561.137f, -2133.279f, 77.4785f, 251.9171f),
            Mod_Class::Vector4(1459.511f, -1935.92f, 71.30696f, 251.9171f),
            Mod_Class::Vector4(1455.132f, -1682.857f, 66.06307f, 251.9171f),
            Mod_Class::Vector4(1193.554f, -1240.154f, 36.32576f, 251.9171f),
            Mod_Class::Vector4(1122.821f, -1303.704f, 34.71646f, 251.9171f),
            Mod_Class::Vector4(994.2419f, -1555.895f, 30.75485f, 251.9171f),
            Mod_Class::Vector4(918.1321f, -1516.955f, 30.96606f, 251.9171f),
            Mod_Class::Vector4(903.4687f, -1590.887f, 30.22392f, 251.9171f),
            Mod_Class::Vector4(804.6454f, -1666.87f, 30.86449f, 251.9171f),
            Mod_Class::Vector4(746.9606f, -1862.089f, 29.29224f, 251.9171f),
            Mod_Class::Vector4(1025.895f, -1686.251f, 33.57116f, 251.9171f),
            Mod_Class::Vector4(928.8152f, -1726.541f, 32.15963f, 251.9171f),
            Mod_Class::Vector4(897.4868f, -1864.518f, 30.61937f, 251.9171f),
            Mod_Class::Vector4(1087.357f, -1970.058f, 31.01467f, 251.9171f),
            Mod_Class::Vector4(973.9832f, -1978.706f, 30.63801f, 251.9171f),
            Mod_Class::Vector4(890.3286f, -2001.457f, 30.61759f, 251.9171f),
            Mod_Class::Vector4(953.8917f, -2117.238f, 30.55156f, 251.9171f),
            Mod_Class::Vector4(879.512f, -2166.26f, 32.27139f, 251.9171f),
            Mod_Class::Vector4(840.3463f, -2292.076f, 30.51253f, 251.9171f),
            Mod_Class::Vector4(864.4549f, -2361.586f, 31.51551f, 251.9171f),
            Mod_Class::Vector4(943.5316f, -2169.565f, 30.5664f, 251.9171f),
            Mod_Class::Vector4(1002.891f, -2161.235f, 30.55158f, 251.9171f),
            Mod_Class::Vector4(1041.598f, -2170.343f, 31.50933f, 251.9171f),
            Mod_Class::Vector4(1019.803f, -2381.706f, 30.49956f, 251.9171f),
            Mod_Class::Vector4(1095.563f, -2227.028f, 31.304f, 251.9171f),
            Mod_Class::Vector4(1091.22f, -2279.994f, 30.14508f, 251.9171f),
            Mod_Class::Vector4(1083.314f, -2413.066f, 30.23936f, 251.9171f),
            Mod_Class::Vector4(923.9042f, -2533.111f, 28.30268f, 251.9171f),
            Mod_Class::Vector4(1211.444f, -3103.413f, 6.027918f, 251.9171f),
            Mod_Class::Vector4(1195.812f, -3254.429f, 7.095187f, 251.9171f),
            Mod_Class::Vector4(755.6094f, -3181.837f, 7.405778f, 251.9171f),
            Mod_Class::Vector4(821.003f, -3196.436f, 5.900819f, 251.9171f),
            Mod_Class::Vector4(814.2813f, -2982.313f, 6.02089f, 251.9171f)
    };       //"Sweatshop Worker  
    inline const std::vector<Mod_Class::Vector4> Worker_Shopkeeper = {
        Mod_Class::Vector4(1727.791f, 6415.5f, 35.03722f, 236.6747f),
            Mod_Class::Vector4(1697.339f, 4923.185f, 42.06368f, 320.4615f),
            Mod_Class::Vector4(1959.632f, 3740.195f, 32.34374f, 296.0751f),
            Mod_Class::Vector4(2677.702f, 3279.555f, 55.23104f, 354.9082f),
            Mod_Class::Vector4(1392.897f, 3606.55f, 34.98093f, 181.8305f),
            Mod_Class::Vector4(549.17f, 2671.394f, 42.15946f, 80.96091f),
            Mod_Class::Vector4(1165.094f, 2711.289f, 38.15771f, 167.705f),
            Mod_Class::Vector4(2557.217f, 380.7556f, 108.6229f, 349.9854f),
            Mod_Class::Vector4(-3039.342f, 584.2296f, 7.908843f, 18.4436f),
            Mod_Class::Vector4(-2965.881f, 391.8284f, 15.04331f, 84.51514f),
            Mod_Class::Vector4(-1819.316f, 793.3266f, 138.0849f, 128.9414f),
            Mod_Class::Vector4(-1220.953f, -908.2629f, 12.32635f, 31.62823f),
            Mod_Class::Vector4(-706.053f, -914.5494f, 19.21514f, 82.03596f),
            Mod_Class::Vector4(-47.39658f, -1758.836f, 29.42102f, 28.16017f),
            Mod_Class::Vector4(24.2935f, -1347.371f, 29.48629f, 278.3273f),
            Mod_Class::Vector4(372.4779f, 326.4888f, 103.5664f, 251.1972f),
            Mod_Class::Vector4(1165.163f, -323.1492f, 69.20242f, 101.1147f),
            Mod_Class::Vector4(1133.975f, -983.3416f, 46.4158f, 285.5776f)
    };       //"Shopkeeper (Male)"), 
    inline const std::vector<Mod_Class::Vector4> Worker_Doctor = {
        Mod_Class::Vector4(-498.4334f, -336.1266f, 34.50177f, 260.0309f),
            Mod_Class::Vector4(-448.8101f, -340.8905f, 34.50174f, 71.48569f),
            Mod_Class::Vector4(-444.4344f, -360.8369f, 33.49535f, 202.3012f),
            Mod_Class::Vector4(-507.7543f, -350.8057f, 35.20736f, 175.4921f),
            Mod_Class::Vector4(299.0754f, -584.7549f, 43.26083f, 31.88034f),
            Mod_Class::Vector4(355.4822f, -596.1416f, 28.77366f, 243.7838f),
            Mod_Class::Vector4(343.2381f, -1398.023f, 32.50926f, 56.42395f),
            Mod_Class::Vector4(295.1708f, -1449.108f, 29.9666f, 342.1343f),
            Mod_Class::Vector4(391.0455f, -1432.821f, 29.43532f, 246.2128f),
            Mod_Class::Vector4(1102.689f, -1529.41f, 34.89371f, 191.0677f),
            Mod_Class::Vector4(1151.229f, -1529.005f, 35.18423f, 319.4206f),
            Mod_Class::Vector4(1816.119f, 3679.592f, 34.27674f, 46.59311f),
            Mod_Class::Vector4(1827.241f, 3692.945f, 34.22424f, 30.81271f),
            Mod_Class::Vector4(-246.6019f, 6331.854f, 32.42619f, 215.443f)
    };       //"Doctor"), 
    inline const std::vector<Mod_Class::Vector4> Worker_Maid = {
        Mod_Class::Vector4(74.20151f, -1028.342f, 29.47368f, 213.4145f),
            Mod_Class::Vector4(-775.8405f, -2235.184f, 5.935775f, 59.81636f),
            Mod_Class::Vector4(-821.5007f, -2103.311f, 8.960504f, 353.6512f),
            Mod_Class::Vector4(-70.87366f, 358.9036f, 112.4451f, 227.5854f),
            Mod_Class::Vector4(-33.33993f, 363.8051f, 113.908f, 136.6148f),
            Mod_Class::Vector4(18.42962f, 341.8936f, 115.3874f, 144.6268f),
            Mod_Class::Vector4(-1275.37f, 374.1922f, 77.58377f, 355.0824f)
    };       //"Maid
    inline const std::vector<Mod_Class::Vector4> Worker_Security = {
        Mod_Class::Vector4(-117.671f, 6448.627f, 31.05948f, 134.7083f),
            Mod_Class::Vector4(2550.519f, 342.6139f, 108.0741f, 87.43266f),
            Mod_Class::Vector4(1064.405f, -1728.37f, 35.19252f, 200.746f),
            Mod_Class::Vector4(952.5815f, -2080.921f, 30.33508f, 83.92099f),
            Mod_Class::Vector4(163.1477f, -1608.789f, 28.95174f, 301.8476f),
            Mod_Class::Vector4(-1252.114f, -865.7639f, 11.98873f, 217.2558f),
            Mod_Class::Vector4(-2201.217f, -356.3726f, 12.75363f, 266.5727f),
            Mod_Class::Vector4(-1073.944f, -182.7193f, 37.54315f, 242.3141f),
            Mod_Class::Vector4(-742.4987f, -262.4792f, 36.55564f, 21.95997f),
            Mod_Class::Vector4(-302.9223f, -372.287f, 29.59321f, 233.3253f),
            Mod_Class::Vector4(96.73369f, -167.1032f, 54.54427f, 71.51151f),
            Mod_Class::Vector4(173.5536f, -846.8428f, 30.61277f, 339.7813f)
    };       //"Armoured Van Security 2"), 
    inline const std::vector<Mod_Class::Vector4> Worker_Guard = {
        Mod_Class::Vector4(2572.041f, 2718.056f, 42.16391f, 129.5934f),
            Mod_Class::Vector4(1219.512f, 2393.812f, 65.47562f, 172.7095f),
            Mod_Class::Vector4(818.2979f, 2367.369f, 51.38051f, 166.84f),
            Mod_Class::Vector4(2676.273f, 1611.337f, 23.99239f, 270.9893f),
            Mod_Class::Vector4(-129.5193f, -2175.594f, 9.808171f, 107.5226f),
            Mod_Class::Vector4(126.0953f, -2537.874f, 5.492153f, 90.73464f),
            Mod_Class::Vector4(641.3249f, -3010.168f, 5.719178f, 1.711147f),
            Mod_Class::Vector4(817.7762f, -3144.448f, 5.393185f, 184.152f),
            Mod_Class::Vector4(1894.648f, -1021.06f, 78.08004f, 168.9922f)
    };       //"Security Guard"), 
    inline const std::vector<Mod_Class::Vector4> Worker_Scientist = {
        Mod_Class::Vector4(2137.336f, 2906.663f, 59.76971f, 55.80349f),
            Mod_Class::Vector4(2122.384f, 2921.195f, 50.91202f, 320.7472f),
            Mod_Class::Vector4(2078.61f, 2945.86f, 56.4167f, 181.6763f),
            Mod_Class::Vector4(2044.698f, 2944.561f, 60.02338f, 282.4404f),
            Mod_Class::Vector4(2008.205f, 2932.849f, 59.47688f, 259.2144f),
            Mod_Class::Vector4(1965.265f, 2918.207f, 56.1685f, 159.0523f)
    };        //"Scientist"),  
    inline const std::vector<Mod_Class::Vector4> Worker_Chemical = {
        Mod_Class::Vector4(2751.409f, 1467.832f, 49.05055f, 70.61932f),
            Mod_Class::Vector4(2794.029f, 1673.659f, 20.78217f, 172.1612f),
            Mod_Class::Vector4(2733.363f, 1581.026f, 66.53803f, 3.543856f),
            Mod_Class::Vector4(2739.592f, 1544.221f, 42.89051f, 237.7711f),
            Mod_Class::Vector4(2748.854f, 1505.891f, 38.28401f, 152.154f),
            Mod_Class::Vector4(2664.208f, 1477.163f, 35.2615f, 34.45109f),
            Mod_Class::Vector4(2702.427f, 1483.406f, 44.4654f, 81.48576f),
            Mod_Class::Vector4(2716.197f, 1500.537f, 42.24483f, 179.7581f),
            Mod_Class::Vector4(2772.207f, 1518.493f, 30.77918f, 257.5858f),
            Mod_Class::Vector4(2801.599f, 1454.122f, 34.34266f, 111.4636f)
    };       //"Chemical Plant Worker"),  
    inline const std::vector<Mod_Class::Vector4> Worker_Construct = {
        Mod_Class::Vector4(-450.5587f, -1036.252f, 23.09341f, 39.48218f),
            Mod_Class::Vector4(-490.6296f, -942.8484f, 23.51029f, 147.3915f),
            Mod_Class::Vector4(-149.3207f, -959.513f, 20.82236f, 160.9155f),
            Mod_Class::Vector4(-132.5916f, -1098.141f, 21.23154f, 132.2186f),
            Mod_Class::Vector4(98.88792f, -450.8947f, 41.56817f, 342.08f),
            Mod_Class::Vector4(104.5644f, -349.3134f, 41.93143f, 94.52675f)
    };       //"construction Worker 2"), 
    inline const std::vector<Mod_Class::Vector4> Worker_Dock = {
        Mod_Class::Vector4(-326.8799f, -2617.591f, 5.603117f, 135.2283f),
            Mod_Class::Vector4(-505.1059f, -2765.766f, 5.612922f, 314.6254f),
            Mod_Class::Vector4(-301.3838f, -2419.142f, 5.613175f, 146.1276f),
            Mod_Class::Vector4(-117.8903f, -2660.294f, 5.618917f, 358.9177f),
            Mod_Class::Vector4(266.0363f, -2996.771f, 5.346468f, 171.727f),
            Mod_Class::Vector4(517.1625f, -2951.327f, 5.654205f, 268.6839f),
            Mod_Class::Vector4(924.679f, -3009.876f, 5.503459f, 270.0103f),
            Mod_Class::Vector4(1031.972f, -2914.75f, 5.50889f, 79.1702f),
            Mod_Class::Vector4(1261.785f, -3094.253f, 5.51305f, 34.06389f),
            Mod_Class::Vector4(1044.572f, -3237.142f, 5.503559f, 91.10924f),
    };       //"Dock Worker"),  
    inline const std::vector<Mod_Class::Vector4> Worker_Airport = {
        Mod_Class::Vector4(-1260.416f, -2465.789f, 13.53846f, 150.3708f),
            Mod_Class::Vector4(-1136.307f, -2565.843f, 13.54877f, 239.837f),
            Mod_Class::Vector4(-1247.719f, -2759.173f, 13.5597f, 150.0197f),
            Mod_Class::Vector4(-1774.23f, -2806.793f, 13.54927f, 153.7328f),
            Mod_Class::Vector4(-1647.934f, -3128.432f, 13.60499f, 285.4133f),
            Mod_Class::Vector4(-1262.489f, -3376.311f, 13.55233f, 330.3223f),
            Mod_Class::Vector4(-965.5756f, -3007.905f, 13.5535f, 28.93888f),
    };       //Airport
    inline const std::vector<Mod_Class::Vector4> Worker_Handyman = {
        Mod_Class::Vector4(833.5146f, -280.2225f, 66.37661f, 239.6148f),
            Mod_Class::Vector4(1075.906f, -684.5606f, 57.71888f, 30.70767f),
            Mod_Class::Vector4(-916.4821f, -111.1297f, 37.96105f, 295.2327f),
            Mod_Class::Vector4(-114.3289f, -394.8227f, 35.97801f, 252.818f),
            Mod_Class::Vector4(-1670.235f, -600.6372f, 33.82233f, 66.71965f),
            Mod_Class::Vector4(-809.2332f, -915.7718f, 18.17719f, 346.4547f),
            Mod_Class::Vector4(-900.3068f, -860.772f, 16.3537f, 214.3627f),
            Mod_Class::Vector4(-1714.627f, -258.9235f, 52.60183f, 141.2126f),
    };       //"Latino Handyman Male"), 
    inline const std::vector<Mod_Class::Vector4> Worker_Metro = {
        Mod_Class::Vector4(117.6408f, -1729.686f, 30.11062f, 145.3675f),
            Mod_Class::Vector4(-207.5786f, -1017.771f, 30.13827f, 137.811f),
            Mod_Class::Vector4(-500.6882f, -660.5969f, 20.03399f, 176.1281f),
            Mod_Class::Vector4(-1340.413f, -459.3785f, 23.27035f, 118.5435f),
            Mod_Class::Vector4(-810.3533f, -148.9955f, 28.17534f, 18.19424f),
            Mod_Class::Vector4(-306.8699f, -329.439f, 18.28813f, 276.2242f),
            Mod_Class::Vector4(247.4429f, -1204.116f, 38.92488f, 293.6903f),
            Mod_Class::Vector4(-533.9517f, -1267.302f, 26.9016f, 140.6523f),
            Mod_Class::Vector4(-871.7253f, -2321.781f, -3.507766f, 55.49453f),
            Mod_Class::Vector4(-1093.533f, -2709.069f, 0.8148932f, 232.3231f),
    };       //"LS Metro Worker Male"),  
    inline const std::vector<Mod_Class::Vector4> Worker_Transport = {
        Mod_Class::Vector4(772.4866f, -941.0552f, 25.69374f, 174.2538f),
            Mod_Class::Vector4(784.7866f, -778.5135f, 26.37265f, 359.7194f),
            Mod_Class::Vector4(805.5536f, -1353.864f, 26.34939f, 1.794775f),
            Mod_Class::Vector4(438.6497f, -2028.266f, 23.40673f, 222.4093f),
            Mod_Class::Vector4(-252.9165f, -881.4698f, 30.71332f, 250.5484f),
            Mod_Class::Vector4(-562.1918f, -844.0425f, 27.27311f, 268.5222f),
            Mod_Class::Vector4(-1166.271f, -401.646f, 35.44949f, 98.17386f),
            Mod_Class::Vector4(-1483.472f, -634.3616f, 30.36706f, 305.0129f),
            Mod_Class::Vector4(-1407.018f, -570.2193f, 30.32949f, 118.4672f),
            Mod_Class::Vector4(-1523.434f, -465.9171f, 35.33706f, 121.1337f),
            Mod_Class::Vector4(-741.6723f, -753.1192f, 26.65259f, 1.035129f),
            Mod_Class::Vector4(-709.4644f, -828.9621f, 23.4892f, 87.2354f),
            Mod_Class::Vector4(-693.6379f, -667.7115f, 30.77847f, 267.3748f),
            Mod_Class::Vector4(-507.1399f, -667.337f, 33.0463f, 269.1283f),
            Mod_Class::Vector4(118.4946f, -786.554f, 31.31796f, 68.02338f),
            Mod_Class::Vector4(459.9696f, -634.295f, 28.49378f, 32.34509f),
    };       //"Transport Worker Male"),  
    inline const std::vector<Mod_Class::Vector4> Worker_Postal = {

        Mod_Class::Vector4(126.8316f, 217.908f, 107.2581f, 250.0984f),
            Mod_Class::Vector4(-63.64765f, 38.78681f, 72.05331f, 246.6971f),
            Mod_Class::Vector4(-306.1648f, 253.3288f, 87.87576f, 286.7962f),
            Mod_Class::Vector4(-433.5657f, 5.962925f, 46.09057f, 86.90429f),
            Mod_Class::Vector4(-630.7167f, 752.2339f, 178.5925f, 66.96705f),
            Mod_Class::Vector4(-1191.528f, -1263.148f, 6.772604f, 19.49872f),
            Mod_Class::Vector4(-996.5602f, -1131.017f, 2.042427f, 31.10395f),
    };       //"Postal Worker Male 2"),  
    inline const std::vector<Mod_Class::Vector4> Worker_UPS = {

        Mod_Class::Vector4(775.7664f, -983.2467f, 26.1865f, 179.6391f),
            Mod_Class::Vector4(970.2875f, -1458.307f, 31.24547f, 357.9949f),
            Mod_Class::Vector4(908.9388f, -1758.108f, 30.55537f, 82.37654f),
            Mod_Class::Vector4(708.7218f, -2064.523f, 29.24054f, 266.0231f),
            Mod_Class::Vector4(899.3294f, -2427.047f, 28.41091f, 170.9303f),
            Mod_Class::Vector4(626.4791f, -2650.233f, 6.002013f, 25.25125f),
            Mod_Class::Vector4(171.0083f, -2567.712f, 5.877536f, 134.8465f),
            Mod_Class::Vector4(6.724895f, -2075.361f, 10.17716f, 357.7553f),
    };       //"UPS Driver 2"),
    inline const std::vector<Mod_Class::Vector4> Worker_Vendor = {
        Mod_Class::Vector4(-1692.355f, -1136.184f, 13.1523f, 7.620972f),
            Mod_Class::Vector4(-1682.627f, -1124.328f, 13.15217f, 156.3842f),
            Mod_Class::Vector4(-1638.467f, -1083.328f, 13.07891f, 250.2687f),
            Mod_Class::Vector4(-1630.095f, -1075.994f, 13.06109f, 170.5576f),
            Mod_Class::Vector4(-1693.571f, -1072.634f, 13.01736f, 40.26046f),
            Mod_Class::Vector4(-1720.081f, -1103.823f, 13.01784f, 88.03056f),
            Mod_Class::Vector4(-1772.086f, -1160.577f, 13.01805f, 113.3456f),
            Mod_Class::Vector4(-1784.682f, -1175.788f, 13.01775f, 52.88898f),
            Mod_Class::Vector4(-1835.216f, -1233.972f, 13.01727f, 10.32578f),
            Mod_Class::Vector4(-1856.75f, -1224.386f, 13.01728f, 322.1722f),
    };       //"Street Vendor Young"),   
    inline const std::vector<Mod_Class::Vector4> Worker_Window = {
        Mod_Class::Vector4(-74.24763f, -837.0442f, 318.9297f, 167.2113f),
            Mod_Class::Vector4(-148.4851f, -611.0936f, 204.009f, 36.52973f),
            Mod_Class::Vector4(-100.5659f, -548.9984f, 173.528f, 326.2725f),
            Mod_Class::Vector4(162.6209f, -730.3214f, 255.4475f, 158.5101f),
            Mod_Class::Vector4(129.6409f, -720.5817f, 263.644f, 353.4834f),
            Mod_Class::Vector4(102.8595f, -643.2682f, 263.6401f, 261.434f),
    };       //"Window Cleaner"),  

    inline const std::vector<Mod_Class::Vector4> JetSki = {
        Mod_Class::Vector4(212.627f, 3630.045f, 29.9478f, 165.2639f),
        Mod_Class::Vector4(3424.472f, 5193.411f, 0.6613104f, 275.3657f),
        Mod_Class::Vector4(3067.812f, 638.7896f, 0.3254618f, 354.6844f),
        Mod_Class::Vector4(628.3226f, -2122.594f, -0.06220001f, 174.2746f)
    };       //"JetSki"), 

    inline const std::vector<Mod_Class::Vector4> OffRoadRace01 = {
        Mod_Class::Vector4(-1573.766f, 3090.736f, 30.70401f, 7.923703f),
        Mod_Class::Vector4(-1612.333f, 3194.164f, 29.70836f, 24.25381f),
        Mod_Class::Vector4(-1627.943f, 3187.001f, 29.59254f, 169.4351f),
        Mod_Class::Vector4(-1596.471f, 3146.43f, 29.75003f, 216.409f),
        Mod_Class::Vector4(-1578.321f, 2938.288f, 32.46555f, 193.4308f),
        Mod_Class::Vector4(-1447.88f, 2741.831f, 11.2647f, 197.5895f),
        Mod_Class::Vector4(-1501.37f, 2684.001f, 3.191243f, 88.94603f),
        Mod_Class::Vector4(-1627.528f, 2710.553f, 5.176663f, 103.4545f),
        Mod_Class::Vector4(-1725.799f, 2748.991f, 5.00828f, 104.025f),
        Mod_Class::Vector4(-2160.634f, 2730.127f, 3.995766f, 50.44249f),
        Mod_Class::Vector4(-2584.121f, 2877.74f, 3.796169f, 68.0451f),
        Mod_Class::Vector4(-2884.217f, 3187.55f, 10.46736f, 41.10115f),
        Mod_Class::Vector4(-2899.272f, 3182.975f, 10.81549f, 226.0815f),
        Mod_Class::Vector4(-2812.017f, 3118.884f, 8.932123f, 233.299f),
        Mod_Class::Vector4(-2657.327f, 2986.998f, 8.475378f, 205.1365f),
        Mod_Class::Vector4(-2557.48f, 2865.591f, 2.521069f, 240.187f),
        Mod_Class::Vector4(-2356.98f, 2841.752f, 3.348562f, 267.1766f),
        Mod_Class::Vector4(-2166.792f, 2736.821f, 4.362955f, 223.5836f),
        Mod_Class::Vector4(-1844.768f, 2690.219f, 3.537222f, 271.2152f),
        Mod_Class::Vector4(-1555.259f, 2712.102f, 4.116089f, 236.3789f),
        Mod_Class::Vector4(-1459.733f, 2684.367f, 3.303248f, 274.8381f),
        Mod_Class::Vector4(-1438.947f, 2728.815f, 9.611741f, 20.52527f),
        Mod_Class::Vector4(-1482.055f, 2850.693f, 26.6391f, 34.27589f),
        Mod_Class::Vector4(-1581.356f, 3036.075f, 32.53102f, 353.6025f)
    };
    inline const std::vector<Mod_Class::Vector4> OffRoadRace02 = {
        Mod_Class::Vector4(-462.391f, 3022.21f, 28.40036f, 313.114f),
        Mod_Class::Vector4(-272.8297f, 3095.584f, 34.38621f, 302.639f),
        Mod_Class::Vector4(12.49784f, 3269.169f, 40.96146f, 335.1027f),
        Mod_Class::Vector4(107.1125f, 3397.141f, 36.66495f, 8.812644f),
        Mod_Class::Vector4(134.8132f, 3415.844f, 40.02129f, 243.3611f),
        Mod_Class::Vector4(227.9139f, 3344.033f, 39.13525f, 194.6835f),
        Mod_Class::Vector4(221.3962f, 3280.408f, 40.68347f, 169.897f),
        Mod_Class::Vector4(181.2409f, 3240.672f, 41.41757f, 141.7103f),
        Mod_Class::Vector4(26.04806f, 3041.013f, 40.35786f, 126.7756f),
        Mod_Class::Vector4(-172.475f, 2963.227f, 30.90143f, 101.0182f),
        Mod_Class::Vector4(-336.0371f, 2956.438f, 26.28792f, 97.28018f),
        Mod_Class::Vector4(-463.7291f, 2973.831f, 25.10873f, 73.1357f)
    };
    inline const std::vector<Mod_Class::Vector4> OffRoadRace03 = {
        Mod_Class::Vector4(-246.7437f, 4227.788f, 44.22093f, 88.70379f),
        Mod_Class::Vector4(-442.6657f, 4310.995f, 60.11999f, 47.96756f),
        Mod_Class::Vector4(-542.5441f, 4358.369f, 64.7117f, 101.0533f),
        Mod_Class::Vector4(-734.0334f, 4413.731f, 20.70769f, 77.96465f),
        Mod_Class::Vector4(-882.9547f, 4387.652f, 19.15052f, 122.8844f),
        Mod_Class::Vector4(-1094.925f, 4381.365f, 12.11559f, 85.9125f),
        Mod_Class::Vector4(-1274.828f, 4355.382f, 6.493629f, 100.2827f),
        Mod_Class::Vector4(-1362.314f, 4303.132f, 2.091456f, 110.5179f),
        Mod_Class::Vector4(-1624.499f, 4405.334f, 1.869654f, 28.06654f),
        Mod_Class::Vector4(-1853.843f, 4502.354f, 21.63335f, 109.9912f),
        Mod_Class::Vector4(-1912.896f, 4482.269f, 28.62659f, 93.04143f),
        Mod_Class::Vector4(-1893.607f, 4428.335f, 44.1927f, 242.4966f),
        Mod_Class::Vector4(-1614.563f, 4200.422f, 82.80534f, 265.1578f),
        Mod_Class::Vector4(-1420.428f, 4199.886f, 47.63276f, 229.7081f),
        Mod_Class::Vector4(-1352.643f, 4125.354f, 62.40678f, 257.9967f),
        Mod_Class::Vector4(-1108.262f, 4283.507f, 91.09012f, 242.1806f),
        Mod_Class::Vector4(-976.4009f, 4143.866f, 127.7988f, 284.5882f),
        Mod_Class::Vector4(-659.5837f, 4012.206f, 127.7423f, 265.3335f),
        Mod_Class::Vector4(-345.1731f, 4009.185f, 46.76369f, 289.7841f),
        Mod_Class::Vector4(-264.4113f, 3932.506f, 41.40203f, 220.5557f),
        Mod_Class::Vector4(-219.4442f, 3958.519f, 36.85928f, 346.6211f),
        Mod_Class::Vector4(-218.2338f, 4161.347f, 41.95908f, 342.4479f)
    };
    inline const std::vector<Mod_Class::Vector4> OffRoadRace04 = {
        Mod_Class::Vector4(2737.655f, 2743.196f, 41.08186f, 300.0414f),
        Mod_Class::Vector4(2880.482f, 2745.462f, 68.57726f, 229.783f),
        Mod_Class::Vector4(2994.119f, 2681.638f, 74.66668f, 313.514f),
        Mod_Class::Vector4(3068.115f, 2773.374f, 76.51849f, 6.837749f),
        Mod_Class::Vector4(3055.643f, 2876.528f, 85.3677f, 304.5084f),
        Mod_Class::Vector4(3073.354f, 2980.721f, 91.20333f, 13.69699f),
        Mod_Class::Vector4(2987.849f, 2990.086f, 86.409f, 158.836f),
        Mod_Class::Vector4(2872.208f, 2913.032f, 77.55762f, 42.19868f),
        Mod_Class::Vector4(2708.277f, 2962.484f, 36.27277f, 98.92899f),
        Mod_Class::Vector4(2601.988f, 2862.675f, 35.80437f, 178.1778f),
        Mod_Class::Vector4(2697.39f, 2847.054f, 38.85565f, 268.2838f),
        Mod_Class::Vector4(2742.297f, 2911.1f, 35.81622f, 57.11665f),
        Mod_Class::Vector4(2627.528f, 2909.389f, 36.02975f, 317.5483f),
        Mod_Class::Vector4(2718.012f, 2945.823f, 35.64244f, 261.9158f),
        Mod_Class::Vector4(2808.185f, 2827.385f, 41.43419f, 160.7458f),
        Mod_Class::Vector4(2786.199f, 2792.07f, 39.8413f, 126.6713f),
        Mod_Class::Vector4(2744.489f, 2747.907f, 41.75266f, 298.9925f)
    };

    inline const std::vector<Mod_Class::Vector4> Service_Baywatch = {
        Mod_Class::Vector4(-1175.706f, -1774.746f, 3.363378f, 304.6927f),
        Mod_Class::Vector4(-1287.01f, -1759.955f, 1.672546f, 295.8521f),
        Mod_Class::Vector4(-1367.334f, -1629.258f, 1.649302f, 120.9917f),
        Mod_Class::Vector4(-1428.135f, -1518.865f, 1.663456f, 296.1766f),
        Mod_Class::Vector4(-1457.268f, -1386.405f, 2.275759f, 199.2531f),
        Mod_Class::Vector4(-1524.885f, -1273.191f, 1.530929f, 278.7048f),
        Mod_Class::Vector4(-1553.199f, -1151.16f, 1.866233f, 223.5885f),
        Mod_Class::Vector4(-1805.487f, -861.1481f, 6.189745f, 202.9933f),
        Mod_Class::Vector4(-1893.655f, -714.954f, 6.738693f, 140.5407f),
        Mod_Class::Vector4(-1998.289f, -552.5966f, 11.23209f, 234.004f)
    };            //"Baywatch 
    inline const std::vector<Mod_Class::Vector4> Service_Coastguard = {
        Mod_Class::Vector4(1900.911f, 4210.698f, 31.12156f, 234.004f),
        Mod_Class::Vector4(456.3666f, 3941.582f, 29.83598f, 234.004f),
        Mod_Class::Vector4(-274.0639f, -3168.564f, 1.20f, 234.004f),
        Mod_Class::Vector4(1919.113f, -3195.016f, 1.20f, 234.004f),
        Mod_Class::Vector4(3095.027f, -2285.647f, 1.20f, 234.004f),
        Mod_Class::Vector4(3324.883f, -928.3412f, 1.20f, 234.004f),
        Mod_Class::Vector4(3462.442f, 669.5615f, 1.20f, 234.004f),
        Mod_Class::Vector4(3461.571f, 1551.177f, 1.20f, 234.004f),
        Mod_Class::Vector4(4046.482f, 2779.351f, 1.20f, 234.004f),
        Mod_Class::Vector4(4252.938f, 3943.124f, 1.20f, 234.004f),
        Mod_Class::Vector4(4028.5f, 5284.229f, 1.20f, 234.004f),
        Mod_Class::Vector4(3197.774f, 6780.198f, 1.20f, 234.004f),
        Mod_Class::Vector4(2577.655f, 6975.242f, 1.20f, 234.004f),
        Mod_Class::Vector4(1584.373f, 7135.975f, 1.20f, 234.004f),
        Mod_Class::Vector4(752.0983f, 7195.581f, 1.20f, 234.004f),
    };       //"US Coastguard
    inline const std::vector<Mod_Class::Vector4> Service_Cops = {
        Mod_Class::Vector4(885.5582f, -2615.697f, 50.64429f, 278.7308f),
        Mod_Class::Vector4(203.3962f, -2666.317f, 17.77028f, 269.1859f),
        Mod_Class::Vector4(-373.5676f, -2359.221f, 62.95405f, 234.2403f),
        Mod_Class::Vector4(-416.3635f, -1002.121f, 36.88079f, 180.3557f),
        Mod_Class::Vector4(-142.9952f, -489.4464f, 28.90267f, 90.18279f),
        Mod_Class::Vector4(263.6426f, -504.648f, 33.6673f, 89.44656f),
        Mod_Class::Vector4(658.7974f, -572.0912f, 35.72264f, 62.07106f),
        Mod_Class::Vector4(1298.609f, 597.3955f, 79.88807f, 136.4441f),
        Mod_Class::Vector4(1744.206f, 1860.102f, 74.69196f, 174.4608f),
        Mod_Class::Vector4(2644.47f, 3147.029f, 50.34586f, 135.5797f),
        Mod_Class::Vector4(2820.983f, 4262.163f, 49.99089f, 201.1554f),
        Mod_Class::Vector4(2542.731f, 5371.196f, 44.30971f, 192.7441f),
        Mod_Class::Vector4(905.6749f, 6484.458f, 21.066f, 266.5843f),
        Mod_Class::Vector4(-287.8203f, 6080.083f, 30.98392f, 315.2855f),
        Mod_Class::Vector4(-822.1944f, 5455.459f, 33.60496f, 302.0413f),
        Mod_Class::Vector4(-1990.362f, 4519.978f, 56.79668f, 313.5679f),
        Mod_Class::Vector4(-2387.44f, 3921.145f, 24.41055f, 340.2222f),
        Mod_Class::Vector4(-2629.613f, 2777.201f, 16.40953f, 352.1142f),
        Mod_Class::Vector4(-2983.182f, 427.1111f, 14.73897f, 356.4609f),
        Mod_Class::Vector4(-2408.366f, -246.0178f, 15.25864f, 61.36377f),
        Mod_Class::Vector4(-712.5493f, -489.1255f, 24.75532f, 88.78899f),
        Mod_Class::Vector4(-398.3365f, -892.6438f, 36.99687f, 2.379511f),
        Mod_Class::Vector4(349.1497f, -1179.372f, 38.40684f, 89.36625f),
        Mod_Class::Vector4(881.6455f, -1168.795f, 42.78446f, 92.00111f),
        Mod_Class::Vector4(620.7553f, -584.2747f, 35.70321f, 241.3658f),
        Mod_Class::Vector4(35.09534f, -522.4681f, 33.79306f, 271.1531f),
        Mod_Class::Vector4(-580.5308f, -536.8923f, 24.96111f, 270.6866f),
        Mod_Class::Vector4(-1164.99f, -682.7447f, 10.80028f, 300.4947f),
        Mod_Class::Vector4(-1938.348f, -501.9031f, 11.5878f, 230.8896f),
        Mod_Class::Vector4(-2511.576f, -202.5297f, 18.51174f, 240.959f),
        Mod_Class::Vector4(-3107.269f, 1229.96f, 19.99887f, 173.2392f),
        Mod_Class::Vector4(-2246.985f, 4275.212f, 46.0254f, 145.9837f),
        Mod_Class::Vector4(-1787.779f, 4738.555f, 56.77055f, 135.9421f),
        Mod_Class::Vector4(-487.1145f, 5868.34f, 33.32526f, 148.7284f),
        Mod_Class::Vector4(1645.693f, 6401.292f, 29.01801f, 70.58336f),
        Mod_Class::Vector4(2542.887f, 5440.158f, 44.27225f, 18.48835f),
        Mod_Class::Vector4(2720.861f, 4745.983f, 44.15805f, 12.34523f),
        Mod_Class::Vector4(2893.44f, 4158.5f, 49.99942f, 18.04636f),
        Mod_Class::Vector4(2803.914f, 3404.103f, 55.59621f, 335.1538f),
        Mod_Class::Vector4(2159.228f, 2692.351f, 48.39897f, 310.3872f),
        Mod_Class::Vector4(2274.467f, 1177.887f, 77.4653f, 41.29153f),
        Mod_Class::Vector4(2615.018f, 295.7539f, 97.67361f, 351.01f),
        Mod_Class::Vector4(1743.362f, -889.3596f, 69.89281f, 302.4699f),
        Mod_Class::Vector4(1070.263f, -1189.859f, 55.55549f, 273.7319f),
        Mod_Class::Vector4(266.552f, -1222.569f, 38.0509f, 269.8226f),
    };       //><!--Cops
    inline const std::vector<Mod_Class::Vector4> Service_CopsBike = {
        Mod_Class::Vector4(2820.983f, 4262.163f, 49.99089f, 201.1554f),
        Mod_Class::Vector4(2542.731f, 5371.196f, 44.30971f, 192.7441f),
        Mod_Class::Vector4(905.6749f, 6484.458f, 21.066f, 266.5843f),
        Mod_Class::Vector4(-287.8203f, 6080.083f, 30.98392f, 315.2855f),
        Mod_Class::Vector4(-822.1944f, 5455.459f, 33.60496f, 302.0413f),
        Mod_Class::Vector4(-1990.362f, 4519.978f, 56.79668f, 313.5679f),
        Mod_Class::Vector4(-2246.985f, 4275.212f, 46.0254f, 145.9837f),
        Mod_Class::Vector4(-1787.779f, 4738.555f, 56.77055f, 135.9421f),
        Mod_Class::Vector4(-487.1145f, 5868.34f, 33.32526f, 148.7284f),
        Mod_Class::Vector4(1645.693f, 6401.292f, 29.01801f, 70.58336f),
        Mod_Class::Vector4(2542.887f, 5440.158f, 44.27225f, 18.48835f),
        Mod_Class::Vector4(2720.861f, 4745.983f, 44.15805f, 12.34523f),
        Mod_Class::Vector4(2893.44f, 4158.5f, 49.99942f, 18.04636f)
    };       //><!-- PoliceBike
    inline const std::vector<Mod_Class::Vector4> Service_CopsRanger = {
        Mod_Class::Vector4(-1493.802f, 4979.706f, 62.91706f, 351.3716f),
        Mod_Class::Vector4(-1564.614f, 4385.387f, 4.26155f, 26.0204f),
        Mod_Class::Vector4(-889.2991f, 4427.76f, 20.53571f, 69.94745f),
        Mod_Class::Vector4(-773.6549f, 4520.953f, 93.5034f, 267.5718f),
        Mod_Class::Vector4(-1035.605f, 4576.456f, 122.0881f, 207.1876f),
        Mod_Class::Vector4(-1280.47f, 4608.851f, 122.7791f, 261.6023f),
        Mod_Class::Vector4(-1127.258f, 4682.028f, 240.7662f, 169.1925f),
        Mod_Class::Vector4(-1008.586f, 4706.519f, 246.7317f, 65.47046f),
        Mod_Class::Vector4(-1290.714f, 4936.681f, 152.4774f, 174.5883f),
        Mod_Class::Vector4(-1031.845f, 4916.573f, 205.4106f, 133.588f),
        Mod_Class::Vector4(-596.4041f, 5025.744f, 140.5351f, 353.1016f)
    };       //><!-- Ranger
    inline const std::vector<Mod_Class::Vector4> Service_Sherif = {
        Mod_Class::Vector4(885.5582f, -2615.697f, 50.64429f, 278.7308f),
        Mod_Class::Vector4(203.3962f, -2666.317f, 17.77028f, 269.1859f),
        Mod_Class::Vector4(-373.5676f, -2359.221f, 62.95405f, 234.2403f),
        Mod_Class::Vector4(-416.3635f, -1002.121f, 36.88079f, 180.3557f),
        Mod_Class::Vector4(-142.9952f, -489.4464f, 28.90267f, 90.18279f),
        Mod_Class::Vector4(263.6426f, -504.648f, 33.6673f, 89.44656f),
        Mod_Class::Vector4(658.7974f, -572.0912f, 35.72264f, 62.07106f),
        Mod_Class::Vector4(1298.609f, 597.3955f, 79.88807f, 136.4441f),
        Mod_Class::Vector4(1744.206f, 1860.102f, 74.69196f, 174.4608f),
        Mod_Class::Vector4(2644.47f, 3147.029f, 50.34586f, 135.5797f),
        Mod_Class::Vector4(2820.983f, 4262.163f, 49.99089f, 201.1554f),
        Mod_Class::Vector4(2542.731f, 5371.196f, 44.30971f, 192.7441f),
        Mod_Class::Vector4(905.6749f, 6484.458f, 21.066f, 266.5843f),
        Mod_Class::Vector4(-287.8203f, 6080.083f, 30.98392f, 315.2855f),
        Mod_Class::Vector4(-822.1944f, 5455.459f, 33.60496f, 302.0413f),
        Mod_Class::Vector4(-1990.362f, 4519.978f, 56.79668f, 313.5679f),
        Mod_Class::Vector4(-2387.44f, 3921.145f, 24.41055f, 340.2222f),
        Mod_Class::Vector4(-2629.613f, 2777.201f, 16.40953f, 352.1142f),
        Mod_Class::Vector4(-2983.182f, 427.1111f, 14.73897f, 356.4609f),
        Mod_Class::Vector4(-2408.366f, -246.0178f, 15.25864f, 61.36377f),
        Mod_Class::Vector4(-712.5493f, -489.1255f, 24.75532f, 88.78899f),
        Mod_Class::Vector4(-398.3365f, -892.6438f, 36.99687f, 2.379511f),
        Mod_Class::Vector4(349.1497f, -1179.372f, 38.40684f, 89.36625f),
        Mod_Class::Vector4(881.6455f, -1168.795f, 42.78446f, 92.00111f),
        Mod_Class::Vector4(620.7553f, -584.2747f, 35.70321f, 241.3658f),
        Mod_Class::Vector4(35.09534f, -522.4681f, 33.79306f, 271.1531f),
        Mod_Class::Vector4(-580.5308f, -536.8923f, 24.96111f, 270.6866f),
        Mod_Class::Vector4(-1164.99f, -682.7447f, 10.80028f, 300.4947f),
        Mod_Class::Vector4(-1938.348f, -501.9031f, 11.5878f, 230.8896f),
        Mod_Class::Vector4(-2511.576f, -202.5297f, 18.51174f, 240.959f),
        Mod_Class::Vector4(-3107.269f, 1229.96f, 19.99887f, 173.2392f),
        Mod_Class::Vector4(-2246.985f, 4275.212f, 46.0254f, 145.9837f),
        Mod_Class::Vector4(-1787.779f, 4738.555f, 56.77055f, 135.9421f),
        Mod_Class::Vector4(-487.1145f, 5868.34f, 33.32526f, 148.7284f),
        Mod_Class::Vector4(1645.693f, 6401.292f, 29.01801f, 70.58336f),
        Mod_Class::Vector4(2542.887f, 5440.158f, 44.27225f, 18.48835f),
        Mod_Class::Vector4(2720.861f, 4745.983f, 44.15805f, 12.34523f),
        Mod_Class::Vector4(2893.44f, 4158.5f, 49.99942f, 18.04636f),
        Mod_Class::Vector4(2803.914f, 3404.103f, 55.59621f, 335.1538f),
        Mod_Class::Vector4(2159.228f, 2692.351f, 48.39897f, 310.3872f),
        Mod_Class::Vector4(2274.467f, 1177.887f, 77.4653f, 41.29153f),
        Mod_Class::Vector4(2615.018f, 295.7539f, 97.67361f, 351.01f),
        Mod_Class::Vector4(1743.362f, -889.3596f, 69.89281f, 302.4699f),
        Mod_Class::Vector4(1070.263f, -1189.859f, 55.55549f, 273.7319f),
        Mod_Class::Vector4(266.552f, -1222.569f, 38.0509f, 269.8226f)
    };       //><!-- Sherif
    inline const std::vector<Mod_Class::Vector4> Service_Fib = {
        Mod_Class::Vector4(124.8999f, -720.1405f, 32.75769f, 340.4963f),
        Mod_Class::Vector4(132.8888f, -722.7589f, 32.75735f, 340.4963f),
        Mod_Class::Vector4(140.2559f, -725.1739f, 32.75784f, 340.4963f),
        Mod_Class::Vector4(148.2134f, -727.7819f, 32.75822f, 340.4963f),
        Mod_Class::Vector4(151.4105f, -730.2962f, 32.75987f, 159.6303f),
        Mod_Class::Vector4(143.8329f, -727.6848f, 32.7599f, 159.6304f),
        Mod_Class::Vector4(136.2731f, -725.0797f, 32.75871f, 159.6304f),
        Mod_Class::Vector4(128.5793f, -722.4284f, 32.76021f, 159.6304f),
        Mod_Class::Vector4(120.7546f, -719.5478f, 32.75972f, 161.0089f),
        Mod_Class::Vector4(113.7038f, -716.8285f, 32.76033f, 161.0155f),
        Mod_Class::Vector4(110.3745f, -714.157f, 32.75887f, 340.0062f),
        Mod_Class::Vector4(103.6866f, -694.1055f, 32.74104f, 160.5572f),
        Mod_Class::Vector4(107.0196f, -695.1913f, 32.74342f, 160.5571f),
        Mod_Class::Vector4(111.1312f, -696.534f, 32.74039f, 160.5572f),
        Mod_Class::Vector4(114.4097f, -697.6046f, 32.74321f, 160.5571f),
        Mod_Class::Vector4(118.619f, -698.9508f, 32.74128f, 160.905f),
        Mod_Class::Vector4(122.539f, -700.1477f, 32.74237f, 161.6465f),
        Mod_Class::Vector4(125.8455f, -702.1788f, 32.74369f, 161.686f),
        Mod_Class::Vector4(129.9737f, -703.5176f, 32.74564f, 160.6104f),
        Mod_Class::Vector4(133.7075f, -704.7408f, 32.74757f, 160.6105f),
        Mod_Class::Vector4(145.1564f, -699.0904f, 32.75421f, 250.3092f),
        Mod_Class::Vector4(146.2141f, -695.4435f, 32.75328f, 252.3628f),
        Mod_Class::Vector4(148.6901f, -688.0548f, 32.75203f, 249.764f),
        Mod_Class::Vector4(149.8707f, -684.3236f, 32.75465f, 251.1089f),
        Mod_Class::Vector4(155.8789f, -682.1313f, 32.75422f, 160.3401f),
        Mod_Class::Vector4(159.394f, -683.2919f, 32.75308f, 160.3402f),
        Mod_Class::Vector4(163.1044f, -684.5927f, 32.75218f, 159.2708f),
        Mod_Class::Vector4(169.2833f, -686.3806f, 32.75238f, 160.0061f),
        Mod_Class::Vector4(173.0347f, -687.5805f, 32.74957f, 160.8067f),
        Mod_Class::Vector4(179.2498f, -695.2624f, 32.75071f, 72.96658f),
        Mod_Class::Vector4(178.1708f, -698.6674f, 32.75278f, 71.0178f),
        Mod_Class::Vector4(175.3772f, -706.3841f, 32.75247f, 71.30013f),
        Mod_Class::Vector4(174.2273f, -709.7647f, 32.75602f, 69.83701f),
        Mod_Class::Vector4(165.253f, -733.755f, 32.75826f, 70.5134f),
        Mod_Class::Vector4(164.3231f, -737.161f, 32.75834f, 70.5134f),
        Mod_Class::Vector4(162.8038f, -740.7974f, 32.75814f, 69.8709f),
        Mod_Class::Vector4(161.4511f, -744.9138f, 32.75976f, 74.06393f),
        Mod_Class::Vector4(155.2419f, -748.9347f, 32.75949f, 339.7729f),
        Mod_Class::Vector4(151.0513f, -747.5115f, 32.75947f, 340.5012f),
        Mod_Class::Vector4(148.0087f, -746.1507f, 32.75831f, 340.5012f),
        Mod_Class::Vector4(141.0646f, -743.7266f, 32.75826f, 338.631f),
        Mod_Class::Vector4(137.5325f, -742.0901f, 32.75802f, 339.5825f),
        Mod_Class::Vector4(133.8466f, -740.9481f, 32.75931f, 338.8475f),
        Mod_Class::Vector4(119.1344f, -735.6913f, 32.7584f, 339.97f),
        Mod_Class::Vector4(115.5711f, -734.0814f, 32.75903f, 340.7244f),
        Mod_Class::Vector4(108.545f, -731.7458f, 32.75801f, 340.7243f),
        Mod_Class::Vector4(104.27f, -730.391f, 32.75842f, 343.5851f),
        Mod_Class::Vector4(100.4326f, -728.9741f, 32.75946f, 340.1993f),
        Mod_Class::Vector4(96.46036f, -727.2465f, 32.75974f, 342.7584f),
        Mod_Class::Vector4(93.8289f, -720.4455f, 32.75797f, 250.9863f),
        Mod_Class::Vector4(95.17917f, -716.4265f, 32.75877f, 250.9863f),
        Mod_Class::Vector4(96.42334f, -712.7228f, 32.75986f, 250.9863f),
        Mod_Class::Vector4(97.63802f, -708.955f, 32.76009f, 249.8051f)
    };       //><!-- fib
    inline const std::vector<Mod_Class::Vector4> Service_Swat = {
        Mod_Class::Vector4(-119.9115f, 6434.275f, 31.11884f, 76.0892f),
        Mod_Class::Vector4(-2985.351f, 481.0876f, 14.88591f, 340.2791f),
        Mod_Class::Vector4(213.41f, 185.9918f, 105.2675f, 42.60518f)
    };       //><!-- swat
    inline const std::vector<Mod_Class::Vector4> Service_Military = {
        Mod_Class::Vector4(-1899.622f, 3229.268f, 33.47933f, 240.4016f),
        Mod_Class::Vector4(-1803.691f, 3296.952f, 33.47214f, 59.49804f),
        Mod_Class::Vector4(-1987.941f, 3114.901f, 33.3334f, 238.1281f),
        Mod_Class::Vector4(-2298.659f, 3301.444f, 33.35372f, 98.11511f),
        Mod_Class::Vector4(-2175.917f, 3364.38f, 33.65299f, 267.6297f)
    };       //military
    inline const std::vector<Mod_Class::Vector4> Service_Medic = {
        Mod_Class::Vector4(-480.4834f, -350.4613f, 34.13201f, 169.3226f),
        Mod_Class::Vector4(375.7192f, -583.7938f, 28.5012f, 268.1963f),
        Mod_Class::Vector4(314.8461f, -1448.607f, 29.57309f, 231.6201f),
        Mod_Class::Vector4(1128.826f, -1507.548f, 34.46217f, 267.5413f),
        Mod_Class::Vector4(1842.941f, 3706.448f, 33.35268f, 348.876f),
        Mod_Class::Vector4(-239.1304f, 6332.855f, 32.16411f, 224.5303f)
    };      //medic
    inline const std::vector<Mod_Class::Vector4> Service_Fireman = {
        Mod_Class::Vector4(-370.2138f, 6128.188f, 31.52059f, 43.32635f),
        Mod_Class::Vector4(1696.062f, 3588.495f, 35.69079f, 203.5357f),
        Mod_Class::Vector4(209.5965f, -1646.76f, 29.87245f, 318.9238f),
        Mod_Class::Vector4(1204.332f, -1469.507f, 34.92859f, 357.4668f),
        Mod_Class::Vector4(-640.5964f, -101.5987f, 38.10654f, 127.0878f)
    };      //fireman

    inline const std::vector<Mod_Class::Vector4> Flight_Civi = {
        Mod_Class::Vector4(-3376.623f, 7834.382f, 1500.00f, 217.4295f),
        Mod_Class::Vector4(4364.612f, -4151.208f, 1500.00f, 42.93307f),
        Mod_Class::Vector4(-3292.792f, -4034.441f, 1500.00f, 311.4861f),
        Mod_Class::Vector4(3585.601f, 7976.706f, 1500.00f, 140.3225f)
    };       //civilian
    inline const std::vector<Mod_Class::Vector4> Flight_Milatary = {
        Mod_Class::Vector4(-3376.623f, 7834.382f, 700.00f, 217.4295f),
        Mod_Class::Vector4(4364.612f, -4151.208f, 700.00f, 42.93307f),
        Mod_Class::Vector4(-3292.792f, -4034.441f, 700.00f, 311.4861f),
        Mod_Class::Vector4(3585.601f, 7976.706f, 700.00f, 140.3225f),
    };       //milatary
    inline const std::vector<Mod_Class::Vector4> Flight_HeliPerto = {
        Mod_Class::Vector4(-745.0335f, -1434.13f, 5.675035f, 49.38052f),
        Mod_Class::Vector4(-744.5621f, -1434.631f, 45.5694f, 43.56923f),
        Mod_Class::Vector4(-943.0097f, -1372.587f, 88.47835f, 76.8955f),
        Mod_Class::Vector4(-1380.798f, -1231.121f, 120.3375f, 64.56821f),
        Mod_Class::Vector4(-1937.764f, -718.4302f, 124.1025f, 41.56572f),
        Mod_Class::Vector4(-2005.697f, -10.6858f, 183.4718f, 350.5649f),
        Mod_Class::Vector4(-1887.984f, 252.9273f, 219.2129f, 332.1073f),
        Mod_Class::Vector4(-1440.777f, 532.8215f, 241.145f, 289.4188f),
        Mod_Class::Vector4(-824.9135f, 722.5916f, 296.2533f, 284.8902f),
        Mod_Class::Vector4(-489.9325f, 952.3074f, 396.2867f, 329.8929f),
        Mod_Class::Vector4(-140.4692f, 1033.914f, 412.1446f, 256.8935f),
        Mod_Class::Vector4(516.86f, 1063.885f, 403.47f, 279.1731f),
        Mod_Class::Vector4(620.8156f, 13.97498f, 298.2937f, 164.5377f),
        Mod_Class::Vector4(402.175f, -584.6495f, 256.7945f, 155.1357f),
        Mod_Class::Vector4(173.9926f, -954.7323f, 237.2449f, 138.4467f),
        Mod_Class::Vector4(-284.1717f, -1343.872f, 140.4055f, 133.4898f),
        Mod_Class::Vector4(-528.8258f, -1504.724f, 124.409f, 89.10454f),
        Mod_Class::Vector4(-714.8882f, -1458.062f, 42.30001f, 58.55215f),
    };       //helitours
    inline const std::vector<Mod_Class::Vector4> Flight_HeliPaleto = {
        Mod_Class::Vector4(-286.1589f, 6130.172f, 32.13292f, 275.265f),
        Mod_Class::Vector4(-286.3647f, 6130.907f, 65.98f, 281.1871f),
        Mod_Class::Vector4(-235.833f, 6276.704f, 110.6021f, 353.3344f),
        Mod_Class::Vector4(23.64182f, 6835.598f, 86.64565f, 320.9841f),
        Mod_Class::Vector4(284.416f, 6887.176f, 101.6019f, 226.6046f),
        Mod_Class::Vector4(763.9923f, 6577.445f, 93.83253f, 252.6691f),
        Mod_Class::Vector4(1505.827f, 6548.389f, 108.8764f, 272.7405f),
        Mod_Class::Vector4(1802.909f, 6568.977f, 149.3561f, 279.932f),
        Mod_Class::Vector4(2484.531f, 6498.886f, 200.3775f, 250.4998f),
        Mod_Class::Vector4(3039.205f, 6285.432f, 198.2972f, 247.7497f),
        Mod_Class::Vector4(3278.987f, 5914.606f, 227.383f, 185.5986f),
        Mod_Class::Vector4(3275.25f, 5330.985f, 118.3367f, 176.5877f),
        Mod_Class::Vector4(3189.232f, 5115.614f, 95.28926f, 118.7072f),
        Mod_Class::Vector4(2804.662f, 5091.914f, 127.3515f, 83.45394f),
        Mod_Class::Vector4(2266.839f, 5147.165f, 131.4157f, 85.08824f),
        Mod_Class::Vector4(1800.733f, 5002.501f, 145.9994f, 125.2208f),
        Mod_Class::Vector4(1480.974f, 4630.318f, 183.4221f, 143.8588f),
        Mod_Class::Vector4(901.9067f, 4327.457f, 197.9002f, 108.8094f),
        Mod_Class::Vector4(171.0265f, 4324.955f, 207.0748f, 82.35104f),
        Mod_Class::Vector4(-279.3649f, 4390.429f, 196.3075f, 82.40254f),
        Mod_Class::Vector4(-852.1649f, 4395.291f, 184.6133f, 96.01467f),
        Mod_Class::Vector4(-1271.238f, 4444.289f, 164.0461f, 73.29852f),
        Mod_Class::Vector4(-1553.718f, 4725.6f, 175.09f, 21.14607f),
        Mod_Class::Vector4(-1528.674f, 5186.567f, 162.9194f, 313.75f),
        Mod_Class::Vector4(-1104.559f, 5507.558f, 144.9734f, 301.4052f),
        Mod_Class::Vector4(-600.4811f, 5832.47f, 156.2213f, 309.3331f),
        Mod_Class::Vector4(-360.4607f, 6078.532f, 136.8584f, 301.1647f),
        Mod_Class::Vector4(-316.0546f, 6116.282f, 64.80506f, 281.8811f),
    };      //PaletoHeli

    inline const std::vector<Mod_Class::Vector4> Animals_Boar = {
        Mod_Class::Vector4(-457.3879f, 5553.581f, 73.99891f, 170.4394f),
        Mod_Class::Vector4(-494.3865f, 5189.813f, 89.39753f, 324.6375f),
        Mod_Class::Vector4(-695.0361f, 5464.335f, 46.07887f, 22.68201f),
        Mod_Class::Vector4(1635.211f, 4946.255f, 42.4776f, 309.0715f),
        Mod_Class::Vector4(1222.848f, 4495.256f, 49.80619f, 159.4206f),
        Mod_Class::Vector4(1058.898f, 4241.627f, 37.00926f, 231.3649f),
        Mod_Class::Vector4(287.0659f, 4261.199f, 39.60912f, 275.8864f),
        Mod_Class::Vector4(31.35694f, 4340.92f, 42.37447f, 144.4754f),
        Mod_Class::Vector4(-368.3591f, 4368.038f, 52.54329f, 353.8307f),
        Mod_Class::Vector4(2193.633f, 4682.529f, 34.95401f, 225.1884f)
    };           //a_c_boar
    inline const std::vector<Mod_Class::Vector4> Animals_CatsDogs = {
        Mod_Class::Vector4(-489.1449f, 6272.717f, 13.33084f, 146.1511f),
        Mod_Class::Vector4(-298.5837f, 6300.868f, 31.47709f, 310.8734f),
        Mod_Class::Vector4(-253.243f, 6228.751f, 31.4237f, 136.6564f),
        Mod_Class::Vector4(-170.8394f, 6410.968f, 36.1613f, 309.1762f),
        Mod_Class::Vector4(-7.483267f, 6582.724f, 31.45495f, 307.8637f),
        Mod_Class::Vector4(-69.15816f, 6407.708f, 31.48155f, 119.0731f),
        Mod_Class::Vector4(1649.878f, 4867.57f, 41.90494f, 270.5852f),
        Mod_Class::Vector4(-1323.155f, -1175.789f, 4.86331f, 6.297443f),
        Mod_Class::Vector4(-1264.917f, -1121.156f, 7.457192f, 9.68405f),
        Mod_Class::Vector4(-1567.084f, -438.8763f, 36.95732f, 342.0412f),
        Mod_Class::Vector4(-1663.211f, -403.2176f, 44.65012f, 328.2743f),
        Mod_Class::Vector4(-1482.063f, -335.0168f, 45.90718f, 222.3334f),
        Mod_Class::Vector4(-1411.828f, -254.482f, 46.37918f, 198.0449f),
        Mod_Class::Vector4(-1412.658f, -461.7616f, 34.48635f, 120.2687f),
        Mod_Class::Vector4(-1306.679f, -403.2025f, 36.41523f, 296.8628f),
        Mod_Class::Vector4(-1324.421f, -582.2607f, 29.36177f, 208.0897f),
        Mod_Class::Vector4(-1404.671f, -633.0682f, 28.66234f, 190.164f),
        Mod_Class::Vector4(-1191.879f, -917.8907f, 6.633331f, 177.2337f),
        Mod_Class::Vector4(-964.8581f, -893.8589f, 2.145377f, 122.1884f),
        Mod_Class::Vector4(-1094.882f, -1638.895f, 4.398429f, 218.6515f),
        Mod_Class::Vector4(-695.9647f, -1148.954f, 10.81242f, 123.7849f),
        Mod_Class::Vector4(-573.2047f, -780.1418f, 30.67539f, 82.87112f),
        Mod_Class::Vector4(-467.4827f, -721.5107f, 32.72823f, 270.6811f),
        Mod_Class::Vector4(-603.4603f, 175.6338f, 65.03928f, 107.3593f),
        Mod_Class::Vector4(-480.6446f, 72.93433f, 58.3337f, 102.4298f),
        Mod_Class::Vector4(-160.9944f, 206.0385f, 90.54567f, 85.81742f),
        Mod_Class::Vector4(-134.6189f, -13.40307f, 58.43617f, 346.3363f),
        Mod_Class::Vector4(56.63927f, -62.42125f, 67.63075f, 174.5408f),
        Mod_Class::Vector4(52.52608f, -102.7701f, 56.30117f, 241.1132f),
        Mod_Class::Vector4(224.4882f, 90.73195f, 92.99115f, 242.7487f),
        Mod_Class::Vector4(178.0649f, 7.548378f, 73.42571f, 69.11054f),
        Mod_Class::Vector4(145.3046f, -95.86935f, 64.55049f, 252.004f),
        Mod_Class::Vector4(68.41623f, -87.2534f, 62.48888f, 67.16145f),
        Mod_Class::Vector4(-28.27929f, -42.18899f, 68.96458f, 67.99091f),
        Mod_Class::Vector4(-160.5599f, 12.8439f, 64.55468f, 64.67293f),
        Mod_Class::Vector4(154.9679f, 299.9555f, 109.2783f, 272.365f),
        Mod_Class::Vector4(306.7009f, 272.5739f, 105.6552f, 158.6221f),
        Mod_Class::Vector4(105.6946f, -244.0652f, 51.39948f, 56.58199f),
        Mod_Class::Vector4(33.62473f, -1415.058f, 29.3807f, 273.1532f),
        Mod_Class::Vector4(-143.623f, -1435.251f, 30.98906f, 137.5871f),
        Mod_Class::Vector4(-124.3528f, -1617.652f, 31.98614f, 310.5232f),
        Mod_Class::Vector4(-239.9151f, -1644.622f, 33.54083f, 193.2142f),
        Mod_Class::Vector4(57.41949f, -1831.992f, 24.27117f, 58.92987f),
        Mod_Class::Vector4(207.5628f, -1693.97f, 29.21246f, 48.28707f),
        Mod_Class::Vector4(262.2509f, -1761.088f, 28.73582f, 47.30854f),
        Mod_Class::Vector4(356.5831f, -1868.168f, 26.89423f, 140.4836f),
        Mod_Class::Vector4(365.5281f, -2089.871f, 21.04716f, 315.9386f),
        Mod_Class::Vector4(1232.821f, -644.1865f, 66.87959f, 11.07453f),
        Mod_Class::Vector4(1019.167f, -500.7501f, 60.69093f, 19.97879f),
        Mod_Class::Vector4(809.7609f, -126.2644f, 77.24301f, 56.15232f)
    };      //cats/dogs
    inline const std::vector<Mod_Class::Vector4> Animals_Pigeon = {
        Mod_Class::Vector4(-1798.327f, -367.8435f, 63.32634f, 193.4475f),
        Mod_Class::Vector4(-1754.362f, -398.6084f, 61.47853f, 271.401f),
        Mod_Class::Vector4(-1699.881f, -447.604f, 51.85827f, 284.0296f),
        Mod_Class::Vector4(-1648.967f, -364.9341f, 57.85902f, 90.00666f),
        Mod_Class::Vector4(-1500.419f, -365.9177f, 53.64492f, 270.9501f),
        Mod_Class::Vector4(-1556.568f, -222.7807f, 61.25249f, 272.3614f),
        Mod_Class::Vector4(-1482.511f, -194.8814f, 61.88908f, 242.8922f),
        Mod_Class::Vector4(-1351.707f, -207.7835f, 56.73883f, 254.2633f),
        Mod_Class::Vector4(-1131.186f, -338.4612f, 49.96766f, 267.795f),
        Mod_Class::Vector4(-1154.988f, -370.9339f, 60.99239f, 82.19715f),
        Mod_Class::Vector4(-1170.928f, -469.0142f, 63.362f, 170.2042f),
        Mod_Class::Vector4(-1432.225f, -700.3183f, 34.43598f, 266.5981f),
        Mod_Class::Vector4(-1260.698f, -773.0103f, 28.08051f, 288.7174f),
        Mod_Class::Vector4(-1277.13f, -1036.979f, 30.61119f, 276.1534f),
        Mod_Class::Vector4(-1250.884f, -1349.212f, 11.00681f, 271.3377f),
        Mod_Class::Vector4(-1036.955f, -1564.975f, 13.71508f, 115.3018f),
        Mod_Class::Vector4(-174.3833f, -1286.126f, 51.57734f, 191.2564f),
        Mod_Class::Vector4(-68.70186f, -1329.357f, 39.16204f, 204.9683f),
        Mod_Class::Vector4(-16.61767f, -1551.997f, 37.85777f, 236.8366f),
        Mod_Class::Vector4(196.3551f, -1878.706f, 29.22336f, 91.73615f),
        Mod_Class::Vector4(472.7628f, -1890.018f, 31.78282f, 291.9175f)
    };     //a_c_pigeon
    inline const std::vector<Mod_Class::Vector4> Animals_Rat = {
        Mod_Class::Vector4(461.2985f, -3104.381f, 6.070058f, 291.4764f),
        Mod_Class::Vector4(-1199.754f, -2704.224f, 13.95425f, 223.3566f),
        Mod_Class::Vector4(-347.7987f, -2661.436f, 6.000296f, 359.5485f),
        Mod_Class::Vector4(-76.08307f, -2666.825f, 6.00089f, 65.05595f),
        Mod_Class::Vector4(-443.0275f, -2180.255f, 10.31819f, 100.1932f),
        Mod_Class::Vector4(875.7438f, -1351.802f, 26.31284f, 262.73f),
        Mod_Class::Vector4(682.5385f, -1213.703f, 24.96063f, 181.9295f),
        Mod_Class::Vector4(690.9706f, -1016.897f, 22.62444f, 1.884157f),
        Mod_Class::Vector4(727.1188f, -927.6669f, 24.61855f, 53.66885f),
        Mod_Class::Vector4(1143.96f, -785.0414f, 57.58156f, 250.645f),
        Mod_Class::Vector4(1536.905f, 3798.235f, 34.45097f, 115.1182f),
        Mod_Class::Vector4(2055.688f, 3172.045f, 45.16896f, 199.4242f),
        Mod_Class::Vector4(2192.997f, 5600.538f, 53.66485f, 321.3761f),
        Mod_Class::Vector4(66.26553f, 6663.012f, 31.78686f, 11.51797f)
    };     //a_c_rat
    inline const std::vector<Mod_Class::Vector4> Animals_Cow = {
            Mod_Class::Vector4(417.9343f, 6478.052f, 28.8074f, 0.0f),
            Mod_Class::Vector4(2227.181f, 4911.849f, 40.6702f, 0.0f),
            Mod_Class::Vector4(2213.208f, 4925.513f, 40.74488f, 0.0f),
            Mod_Class::Vector4(2239.021f, 4903.998f, 40.64403f, 0.0f),
            Mod_Class::Vector4(2254.72f, 4882.05f, 40.87927f, 0.0f),
            Mod_Class::Vector4(2502.236f, 4731.86f, 34.30383f, 0.0f),
            Mod_Class::Vector4(2496.951f, 4737.613f, 34.30383f, 0.0f),
            Mod_Class::Vector4(2488.061f, 4745.833f, 34.30383f, 0.0f),
            Mod_Class::Vector4(2478.211f, 4743.216f, 34.30384f, 0.0f),
            Mod_Class::Vector4(2462.051f, 4734.207f, 34.30384f, 0.0f),
            Mod_Class::Vector4(2465.021f, 4726.047f, 34.30384f, 0.0f),
            Mod_Class::Vector4(2472.982f, 4713.502f, 34.30384f, 0.0f),
            Mod_Class::Vector4(2452.201f, 4742.365f, 34.30384f, 0.0f),
            Mod_Class::Vector4(2457.568f, 4754.12f, 34.30385f, 0.0f),
            Mod_Class::Vector4(2441.434f, 4759.145f, 34.3058f, 0.0f),
            Mod_Class::Vector4(2442.434f, 4767.811f, 34.30868f, 0.0f),
            Mod_Class::Vector4(2421.559f, 4778.803f, 34.47688f, 0.0f),
            Mod_Class::Vector4(2415.927f, 4809.829f, 35.71259f, 0.0f),
            Mod_Class::Vector4(2397.146f, 4804.948f, 36.39542f, 0.0f),
            Mod_Class::Vector4(2382.756f, 4787.905f, 35.70205f, 0.0f),
            Mod_Class::Vector4(1355.888f, 1253.27f, 105.045f, 0.0f),
            Mod_Class::Vector4(1421.018f, 1292.063f, 111.9903f, 0.0f),
            Mod_Class::Vector4(1414.824f, 1338.969f, 107.1353f, 0.0f),
            Mod_Class::Vector4(1433.681f, 1385.947f, 106.8216f, 0.0f),
            Mod_Class::Vector4(1388.754f, 1428.129f, 104.5997f, 0.0f)
    };      //a_c_cow
    inline const std::vector<Mod_Class::Vector4> Animals_Coyote = {
        Mod_Class::Vector4(1781.178f, 3067.974f, 62.37364f, 123.2384f),
        Mod_Class::Vector4(1572.388f, 2910.075f, 56.93121f, 247.4637f),
        Mod_Class::Vector4(1448.025f, 2790.733f, 52.44666f, 63.9786f),
        Mod_Class::Vector4(1172.84f, 2728.583f, 37.99408f, 283.2423f),
        Mod_Class::Vector4(1120.176f, 2626.74f, 37.98522f, 128.8985f),
        Mod_Class::Vector4(1019.712f, 2651.524f, 39.56373f, 218.314f),
        Mod_Class::Vector4(971.1495f, 2725.413f, 39.47706f, 196.6791f),
        Mod_Class::Vector4(563.2943f, 2804.677f, 42.179f, 235.5823f),
        Mod_Class::Vector4(562.98f, 2668.865f, 42.0967f, 9.277174f),
        Mod_Class::Vector4(390.2578f, 2571.469f, 43.49282f, 356.8945f),
        Mod_Class::Vector4(353.8606f, 2558.211f, 43.48626f, 33.24611f),
        Mod_Class::Vector4(191.44f, 3073.951f, 43.05728f, 351.493f),
        Mod_Class::Vector4(245.3919f, 3176.349f, 42.6951f, 328.9407f),
        Mod_Class::Vector4(923.3562f, 3653.927f, 32.49792f, 149.906f),
        Mod_Class::Vector4(1379.035f, 3617.868f, 34.88105f, 224.4082f),
        Mod_Class::Vector4(1905.982f, 3734.859f, 32.41202f, 48.93122f),
        Mod_Class::Vector4(1965.386f, 3758.618f, 32.22155f, 229.2195f)
    };      //a_c_coyote
    inline const std::vector<Mod_Class::Vector4> Animals_Crow = {
        Mod_Class::Vector4(-1778.111f, -240.8525f, 51.25969f, 89.9939f),
        Mod_Class::Vector4(-1780.717f, -199.4209f, 55.69526f, 270.0832f),
        Mod_Class::Vector4(-1681.285f, -149.9413f, 59.02122f, 269.9794f),
        Mod_Class::Vector4(-1636.64f, -130.9335f, 58.81951f, 151.6588f),
        Mod_Class::Vector4(-290.1838f, 2854.484f, 54.41695f, 128.2115f),
        Mod_Class::Vector4(405.3126f, -1486.106f, 34.87928f, 4.64691f)
    };      //a_c_crow
    inline const std::vector<Mod_Class::Vector4> Animals_DeerRabit = {
        Mod_Class::Vector4(-540.7523f, 5979.117f, 34.85002f, 32.85591f),
        Mod_Class::Vector4(-546.3254f, 5891.349f, 33.02752f, 89.67336f),
        Mod_Class::Vector4(-619.1426f, 5787.263f, 28.79116f, 172.7761f),
        Mod_Class::Vector4(-762.7892f, 5932.308f, 20.22102f, 115.5313f),
        Mod_Class::Vector4(-874.0002f, 6013.388f, 35.57697f, 114.3561f),
        Mod_Class::Vector4(-687.7157f, 5653.694f, 32.24801f, 194.4881f),
        Mod_Class::Vector4(-522.7726f, 5578.903f, 65.4232f, 266.7195f),
        Mod_Class::Vector4(-465.5789f, 5699.212f, 68.66573f, 47.65134f),
        Mod_Class::Vector4(-486.9351f, 5534.415f, 75.63812f, 58.07087f),
        Mod_Class::Vector4(-732.8253f, 5365.237f, 60.18141f, 107.3803f),
        Mod_Class::Vector4(-782.1372f, 5289.694f, 86.45531f, 160.2472f),
        Mod_Class::Vector4(-904.5177f, 5279.477f, 84.45411f, 166.775f),
        Mod_Class::Vector4(-1148.836f, 5169.071f, 95.37173f, 115.7366f),
        Mod_Class::Vector4(-1257.694f, 4941.357f, 169.565f, 248.0916f),
        Mod_Class::Vector4(-1414.645f, 4898.25f, 112.3443f, 114.9287f),
        Mod_Class::Vector4(-1608.565f, 4678.01f, 39.21826f, 240.4865f),
        Mod_Class::Vector4(-1481.673f, 4627.572f, 48.55896f, 270.5523f),
        Mod_Class::Vector4(-1591.385f, 4496.293f, 20.21319f, 188.9801f),
        Mod_Class::Vector4(-1425.511f, 4407.443f, 47.12846f, 316.8277f),
        Mod_Class::Vector4(-1214.433f, 4439.974f, 29.94384f, 37.86443f),
        Mod_Class::Vector4(-614.5055f, 4903.279f, 186.1149f, 52.75925f),
        Mod_Class::Vector4(-446.6541f, 4806.495f, 230.9601f, 263.0022f),
        Mod_Class::Vector4(-137.5665f, 4567.001f, 118.2301f, 218.6852f),
        Mod_Class::Vector4(59.70969f, 4681.479f, 179.562f, 55.75858f),
        Mod_Class::Vector4(479.309f, 4487.017f, 126.7762f, 332.2285f),
        Mod_Class::Vector4(1531.167f, 4834.677f, 72.88008f, 154.3012f),
        Mod_Class::Vector4(1479.59f, 5205.152f, 183.1102f, 304.9509f),
        Mod_Class::Vector4(1703.529f, 5239.249f, 125.6967f, 346.0668f),
        Mod_Class::Vector4(1913.865f, 5449.821f, 176.0958f, 123.9867f),
        Mod_Class::Vector4(2583.419f, 6176.759f, 164.7064f, 42.45876f),
        Mod_Class::Vector4(2643.596f, 6337.706f, 114.4633f, 330.2474f),
        Mod_Class::Vector4(2987.127f, 6255.812f, 76.31998f, 155.676f),
        Mod_Class::Vector4(3137.004f, 6084.535f, 92.65406f, 96.80786f),
        Mod_Class::Vector4(3374.18f, 5445.407f, 15.87068f, 157.421f),
        Mod_Class::Vector4(3727.86f, 3611.223f, 32.58834f, 194.4491f),
        Mod_Class::Vector4(3061.042f, 2373.278f, 66.70252f, 89.79482f),
        Mod_Class::Vector4(2958.032f, 2108.912f, 28.74703f, 129.394f),
        Mod_Class::Vector4(2710.875f, 1067.349f, 21.40227f, 172.1084f),
        Mod_Class::Vector4(2940.977f, 798.3766f, 25.40315f, 163.4013f),
        Mod_Class::Vector4(2815.99f, 666.3555f, 42.62372f, 36.26171f),
        Mod_Class::Vector4(2387.526f, -1109.01f, 59.21403f, 20.22232f),
        Mod_Class::Vector4(2275.714f, -1407.633f, 111.9474f, 78.67244f),
        Mod_Class::Vector4(2444.656f, -1688.364f, 46.02353f, 203.4291f),
        Mod_Class::Vector4(2550.898f, -1880.101f, 32.41238f, 87.75346f),
        Mod_Class::Vector4(2322.274f, -1954.51f, 54.69868f, 328.8488f),
        Mod_Class::Vector4(2016.918f, -1877.154f, 116.3597f, 353.763f),
        Mod_Class::Vector4(1892.684f, -2575.366f, 34.31363f, 188.3276f),
        Mod_Class::Vector4(1607.339f, -2589.137f, 55.9791f, 17.28388f),
        Mod_Class::Vector4(-2235.257f, -79.56699f, 109.7868f, 14.99429f),
        Mod_Class::Vector4(-374.6635f, 1128.37f, 321.9959f, 279.0736f),
        Mod_Class::Vector4(439.5944f, 1023.119f, 233.4403f, 239.8481f),
        Mod_Class::Vector4(423.6472f, 756.1078f, 190.3729f, 127.0718f),
        Mod_Class::Vector4(509.3311f, 576.3101f, 159.4695f, 207.3073f)
    };      //a_c_deer/a_c_rabbit_01
    inline const std::vector<Mod_Class::Vector4> Animals_Hen = {
        Mod_Class::Vector4(3294.645f, 5188.46f, 18.41536f, 0.0f),
        Mod_Class::Vector4(2234.094f, 5608.012f, 54.64093f, 0.0f),
        Mod_Class::Vector4(2256.062f, 5158.674f, 57.96902f, 0.0f),
        Mod_Class::Vector4(1697.929f, 4874.469f, 42.03117f, 0.0f),
        Mod_Class::Vector4(1648.552f, 4781.981f, 42.11193f, 0.0f),
        Mod_Class::Vector4(1717.678f, 4679.414f, 43.65579f, 0.0f),
        Mod_Class::Vector4(1667.145f, 4680.101f, 43.05535f, 0.0f),
        Mod_Class::Vector4(1677.29f, 4653.63f, 43.37117f, 0.0f),
        Mod_Class::Vector4(1364.512f, 4359.951f, 44.4988f, 0.0f),
        Mod_Class::Vector4(740.5996f, 4170.04f, 41.0878f, 0.0f),
        Mod_Class::Vector4(1366.07f, 3648.678f, 33.78039f, 0.0f),
        Mod_Class::Vector4(1441.558f, 3630.086f, 34.97598f, 0.0f),
        Mod_Class::Vector4(1424.652f, 3665.129f, 39.72842f, 0.0f),
        Mod_Class::Vector4(1503.234f, 3699.392f, 39.05916f, 0.0f),
        Mod_Class::Vector4(1641.75f, 3729.399f, 35.06714f, 0.0f),
        Mod_Class::Vector4(1648.607f, 3810.293f, 38.65067f, 0.0f),
        Mod_Class::Vector4(1669.977f, 3743.251f, 34.86417f, 0.0f),
        Mod_Class::Vector4(1745.342f, 3700.265f, 34.34354f, 0.0f),
        Mod_Class::Vector4(1779.095f, 3642.883f, 34.47246f, 0.0f),
        Mod_Class::Vector4(1782.287f, 3745.965f, 34.65663f, 0.0f),
        Mod_Class::Vector4(1746.644f, 3785.375f, 34.83487f, 0.0f),
        Mod_Class::Vector4(1778.128f, 3802.267f, 38.36934f, 0.0f),
        Mod_Class::Vector4(1811.733f, 3853.763f, 34.53526f, 0.0f),
        Mod_Class::Vector4(1719.855f, 3851.263f, 34.79908f, 0.0f),
        Mod_Class::Vector4(1712.258f, 3844.736f, 35.09302f, 0.0f),
        Mod_Class::Vector4(1737.591f, 3899.409f, 35.559f, 0.0f),
        Mod_Class::Vector4(1781.677f, 3907.481f, 39.80395f, 0.0f),
        Mod_Class::Vector4(1815.851f, 3907.366f, 37.2175f, 0.0f),
        Mod_Class::Vector4(1885.031f, 3911.95f, 33.09767f, 0.0f),
        Mod_Class::Vector4(1920.32f, 3890.656f, 32.65907f, 0.0f),
        Mod_Class::Vector4(1903.048f, 3876.147f, 32.4305f, 0.0f),
        Mod_Class::Vector4(1859.193f, 3852.417f, 33.03402f, 0.0f),
        Mod_Class::Vector4(1871.298f, 3806.77f, 32.64043f, 0.0f),
        Mod_Class::Vector4(1894.649f, 3785.76f, 32.77509f, 0.0f),
        Mod_Class::Vector4(1947.112f, 3803.384f, 32.03712f, 0.0f),
        Mod_Class::Vector4(1915.621f, 3822.773f, 32.43993f, 0.0f),
        Mod_Class::Vector4(1939.32f, 3851.287f, 32.16716f, 0.0f),
        Mod_Class::Vector4(1975.69f, 3814.874f, 33.42525f, 0.0f),
        Mod_Class::Vector4(2184.301f, 3503.538f, 45.41576f, 0.0f),
        Mod_Class::Vector4(2190.204f, 3340.191f, 45.70337f, 0.0f),
        Mod_Class::Vector4(2152.329f, 3390.411f, 45.40681f, 0.0f),
        Mod_Class::Vector4(2168.019f, 3379.724f, 46.43439f, 0.0f),
        Mod_Class::Vector4(2379.093f, 3350.109f, 47.95228f, 0.0f),
        Mod_Class::Vector4(2484.173f, 3446.39f, 51.06676f, 0.0f),
        Mod_Class::Vector4(2482.338f, 3722.635f, 43.92163f, 0.0f),
        Mod_Class::Vector4(2412.371f, 4034.768f, 36.81679f, 0.0f),
        Mod_Class::Vector4(2552.169f, 4281.502f, 41.61633f, 0.0f),
        Mod_Class::Vector4(2637.038f, 4245.829f, 44.80367f, 0.0f),
        Mod_Class::Vector4(2726.922f, 4143.099f, 44.28887f, 0.0f),
        Mod_Class::Vector4(2734.81f, 4274.33f, 48.5205f, 0.0f),
        Mod_Class::Vector4(1541.871f, 2239.158f, 77.69897f, 0.0f),
        Mod_Class::Vector4(1379.956f, 2164.427f, 97.81518f, 0.0f),
        Mod_Class::Vector4(768.7703f, 2177.563f, 52.37225f, 0.0f),
        Mod_Class::Vector4(730.4855f, 2332.482f, 50.53867f, 0.0f),
        Mod_Class::Vector4(-264.924f, 2206.832f, 130.0993f, 0.0f),
        Mod_Class::Vector4(-33.62269f, 1943.332f, 190.1862f, 0.0f),
        Mod_Class::Vector4(201.6048f, 2437.004f, 60.46714f, 0.0f),
        Mod_Class::Vector4(380.8315f, 2574.337f, 43.51957f, 0.0f),
        Mod_Class::Vector4(470.6082f, 2607.824f, 44.47719f, 0.0f),
        Mod_Class::Vector4(498.1459f, 2605.617f, 43.69965f, 0.0f),
        Mod_Class::Vector4(995.9922f, 2719.427f, 40.08806f, 0.0f),
        Mod_Class::Vector4(982.1971f, 2669.811f, 40.06126f, 0.0f),
        Mod_Class::Vector4(1582.44f, 2906.777f, 56.95695f, 0.0f)
    };     //a_c_hen
    inline const std::vector<Mod_Class::Vector4> Animals_Lion = {
        Mod_Class::Vector4(661.5698f, 5612.078f, 716.1574f, 231.2322f),
        Mod_Class::Vector4(985.664f, 5640.936f, 628.7191f, 264.3497f),
        Mod_Class::Vector4(722.2346f, 5274.907f, 553.4761f, 204.2183f),
        Mod_Class::Vector4(136.9531f, 5172.29f, 553.2682f, 135.7912f),
        Mod_Class::Vector4(83.88232f, 5684.837f, 493.1975f, 40.70573f),
        Mod_Class::Vector4(773.9695f, 5948.048f, 450.6795f, 329.4138f),
        Mod_Class::Vector4(2876.706f, 5910.7f, 369.5696f, 279.8868f),
        Mod_Class::Vector4(2783.151f, 6002.458f, 357.2812f, 39.0136f),
        Mod_Class::Vector4(2934.188f, 5614.261f, 243.6154f, 148.7178f),
        Mod_Class::Vector4(-1214.425f, 3848.331f, 490.2165f, 177.0983f),
        Mod_Class::Vector4(-966.5247f, 3824.745f, 427.8647f, 277.0794f),
        Mod_Class::Vector4(-2357.528f, 1282.13f, 330.8891f, 225.1253f),
    };     //a_c_mtlion-mountain lion
    inline const std::vector<Mod_Class::Vector4> Animals_Pig = {
        Mod_Class::Vector4(434.6616f, 6509.293f, 28.37131f, 0.0f),
        Mod_Class::Vector4(2155.208f, 5002.346f, 41.37879f, 0.0f),
        Mod_Class::Vector4(2150.277f, 4997.573f, 41.36464f, 0.0f),
        Mod_Class::Vector4(2146.562f, 4994.063f, 41.35011f, 0.0f),
        Mod_Class::Vector4(2141.951f, 4989.576f, 41.39429f, 0.0f),
        Mod_Class::Vector4(2184.549f, 4977.354f, 41.39772f, 0.0f),
        Mod_Class::Vector4(2180.546f, 4972.885f, 41.33164f, 0.0f),
        Mod_Class::Vector4(2176.846f, 4968.851f, 41.31844f, 0.0f),
        Mod_Class::Vector4(2173.024f, 4964.73f, 41.3524f, 0.0f),
        Mod_Class::Vector4(2174.25f, 4960.258f, 41.34821f, 0.0f),
        Mod_Class::Vector4(2167.813f, 4965.707f, 41.37321f, 0.0f),
        Mod_Class::Vector4(2383.506f, 5057.748f, 46.44459f, 0.0f),
        Mod_Class::Vector4(2383.948f, 5051.404f, 46.4409f, 0.0f),
        Mod_Class::Vector4(2378.454f, 5048.563f, 46.44463f, 0.0f),
        Mod_Class::Vector4(2374.309f, 5054.471f, 46.44463f, 0.0f),
        Mod_Class::Vector4(-49.16756f, 2875.243f, 58.92621f, 0.0f),
        Mod_Class::Vector4(-143.4491f, 1912.423f, 197.3212f, 0.0f),
        Mod_Class::Vector4(1953.505f, 3806.679f, 32.30476f, 0.0f),
        Mod_Class::Vector4(1581.271f, 2167.549f, 79.28706f, 0.0f)
    };     //a_c_pig
    inline const std::vector<Mod_Class::Vector4> Animals_Fish = {
        Mod_Class::Vector4(1829.751f, -2962.983f, -41.09711f, 0.0f),
        Mod_Class::Vector4(881.9769f, -3480.864f, -12.39751f, 0.0f),
        Mod_Class::Vector4(271.4858f, -2290.783f, -8.27566f, 0.0f),
        Mod_Class::Vector4(-199.2741f, -2862.99f, -11.28995f, 0.0f),
        Mod_Class::Vector4(-1892.526f, -1307.415f, -35.69325f, 0.0f),
        Mod_Class::Vector4(-2843.658f, -574.4394f, -44.94706f, 0.0f),
        Mod_Class::Vector4(-3189.769f, 3026.521f, -30.46286f, 0.0f),
        Mod_Class::Vector4(-3252.511f, 3681.582f, -23.06396f, 0.0f),
        Mod_Class::Vector4(-3374.703f, 504.2789f, -24.57951f, 0.0f),
        Mod_Class::Vector4(-3163.912f, 3003.868f, -38.98509f, 0.0f),
        Mod_Class::Vector4(2655.749f, -1395.955f, -12.85984f, 0.0f),
        Mod_Class::Vector4(3164.551f, -364.2288f, -19.23776f,0.0f),
        Mod_Class::Vector4(3886.64f, 3041.357f, -16.14589f, 0.0f),
        Mod_Class::Vector4(4279.323f, 2971.412f, -170.3207f, 0.0f),
        Mod_Class::Vector4(4218.59f, 3616.418f, -34.40534f, 0.0f),
        Mod_Class::Vector4(3401.174f, 6310.327f, -44.94764f, 0.0f),
        Mod_Class::Vector4(3269.4f, 6419.564f, -46.06504f, 0.0f),
        Mod_Class::Vector4(2649.136f, 6661.476f, -17.16622f, 0.0f),
        Mod_Class::Vector4(747.8029f, 7393.903f, -108.1086f, 0.0f),
        Mod_Class::Vector4(-951.4739f, 6692.083f, -32.37279f, 0.0f),
    };      //Fish/sharks
    inline const std::vector<Mod_Class::Vector4> Animals_Hawk = {
        Mod_Class::Vector4(-2505.106f, 757.7692f, 402.0063f, 0.0f),
        Mod_Class::Vector4(-2338.906f, 1359.295f, 434.8655f, 0.0f),
        Mod_Class::Vector4(-1208.171f, 1196.468f, 393.5298f, 0.0f),
        Mod_Class::Vector4(-917.9607f, 1425.409f, 398.0696f, 0.0f),
        Mod_Class::Vector4(-465.1019f, 1526.887f, 491.0108f, 0.0f),
        Mod_Class::Vector4(758.509f, 1274.176f, 546.1901f, 0.0f),
        Mod_Class::Vector4(1789.931f, 686.2056f, 367.2453f, 0.0f),
        Mod_Class::Vector4(2215.134f, 245.5946f, 359.8406f, 0.0f),
        Mod_Class::Vector4(2046.679f, -1554.435f, 343.4529f, 0.0f),
        Mod_Class::Vector4(2900.099f, 2383.188f, 270.8425f, 0.0f),
        Mod_Class::Vector4(3293.974f, 3141.153f, 353.1701f, 0.0f),
        Mod_Class::Vector4(3444.243f, 4197.86f, 340.2985f, 0.0f),
        Mod_Class::Vector4(2877.255f, 5911.345f, 469.6395f, 0.0f),
        Mod_Class::Vector4(450.718f, 5566.614f, 906.1833f, 0.0f),
        Mod_Class::Vector4(-1213.257f, 3848.571f, 590.4387f, 0.0f)
    };      //a_c_chickenhawk
    inline const std::vector<Mod_Class::Vector4> Animals_Corm = {
        Mod_Class::Vector4(-647.1717f, 6381.847f, 55.23498f, 116.049f),
        Mod_Class::Vector4(-996.1914f, 6127.102f, 65.05244f, 134.0498f),
        Mod_Class::Vector4(-1386.921f, 5662.692f, 47.45169f, 144.4735f),
        Mod_Class::Vector4(-1762.023f, 5236.699f, 55.13129f, 131.9612f),
        Mod_Class::Vector4(-2233.242f, 4773.679f, 45.847f, 141.0407f),
        Mod_Class::Vector4(-2531.957f, 4265.873f, 47.47537f, 155.767f),
        Mod_Class::Vector4(-2917.601f, 3701.053f, 38.22935f, 142.8838f),
        Mod_Class::Vector4(-2998.329f, 3139.244f, 74.07671f, 213.4786f),
        Mod_Class::Vector4(-2752.106f, 2674.014f, 26.49481f, 181.8097f),
        Mod_Class::Vector4(-2876.323f, 2343.454f, 32.5507f, 141.9623f),
        Mod_Class::Vector4(-3161.823f, 1995.468f, 46.15065f, 162.9095f),
        Mod_Class::Vector4(-3308.383f, 1324.952f, 24.35565f, 170.2323f),
        Mod_Class::Vector4(-3257.926f, 801.7152f, 19.8493f, 208.8283f),
        Mod_Class::Vector4(-3165.103f, 389.472f, 21.80201f, 178.8124f),
        Mod_Class::Vector4(-3060.918f, 39.02373f, 41.1531f, 225.9778f),
        Mod_Class::Vector4(-2584.827f, -262.5694f, 20.47069f, 240.8913f),
        Mod_Class::Vector4(-1946.684f, -760.1068f, 17.09371f, 227.7444f),
        Mod_Class::Vector4(-1756.316f, -1033.566f, 48.26628f, 208.7735f),
        Mod_Class::Vector4(-1576.124f, -1275.015f, 56.18793f, 226.497f),
        Mod_Class::Vector4(-1365.415f, -1603.034f, 22.2108f, 204.662f),
        Mod_Class::Vector4(-1285.784f, -2006.483f, 29.93159f, 141.3346f),
        Mod_Class::Vector4(-1678.79f, -2464.347f, 31.70895f, 138.5401f),
        Mod_Class::Vector4(-1955.164f, -3219.351f, 27.96449f, 229.7054f),
        Mod_Class::Vector4(-1491.28f, -3433.852f, 24.46868f, 255.0693f),
        Mod_Class::Vector4(-450.818f, -2932.367f, 59.03496f, 315.9116f),
        Mod_Class::Vector4(-170.4312f, -2751.726f, 35.55687f, 281.9165f),
        Mod_Class::Vector4(84.32108f, -3011.168f, 38.66256f, 186.9482f),
        Mod_Class::Vector4(381.5255f, -3088.718f, 43.53959f, 184.7814f),
        Mod_Class::Vector4(810.2408f, -3349.875f, 76.97131f, 255.1599f),
        Mod_Class::Vector4(1011.955f, -2818.816f, 67.02275f, 275.2491f),
        Mod_Class::Vector4(1381.353f, -2785.423f, 25.2271f, 275.3469f),
        Mod_Class::Vector4(1899.568f, -2698.206f, 29.57582f, 290.0086f),
        Mod_Class::Vector4(2253.048f, -2338.232f, 22.41039f, 327.0099f),
        Mod_Class::Vector4(2695.794f, -1842.093f, 60.28313f, 350.8695f),
        Mod_Class::Vector4(2617.608f, -1242.502f, 42.30254f, 353.048f),
        Mod_Class::Vector4(2812.688f, -885.5068f, 39.93338f, 336.1742f),
        Mod_Class::Vector4(3090.899f, -303.8704f, 28.63768f, 331.2384f),
        Mod_Class::Vector4(3137.391f, 290.1704f, 31.95886f, 10.3887f),
        Mod_Class::Vector4(2952.225f, 871.7095f, 49.21233f, 27.73952f),
        Mod_Class::Vector4(3045.487f, 1832.076f, 51.5413f, 328.3755f),
        Mod_Class::Vector4(3373.457f, 2541.495f, 30.65476f, 342.1697f),
        Mod_Class::Vector4(3592.438f, 2930.6f, 55.46889f, 321.836f),
        Mod_Class::Vector4(3891.745f, 3392.547f, 49.76966f, 337.126f),
        Mod_Class::Vector4(3812.255f, 3768.048f, 42.65887f, 308.2817f),
        Mod_Class::Vector4(3995.321f, 4042.65f, 28.32089f, 353.3696f),
        Mod_Class::Vector4(3945.367f, 4453.691f, 21.29278f, 24.97192f),
        Mod_Class::Vector4(3637.679f, 4847.447f, 11.86491f, 35.3928f),
        Mod_Class::Vector4(3398.107f, 5422.701f, 35.40386f, 282.6931f),
        Mod_Class::Vector4(3462.258f, 5879.85f, 29.49525f, 359.8459f),
        Mod_Class::Vector4(3425.451f, 6118.301f, 37.708f, 22.10388f),
        Mod_Class::Vector4(3049.092f, 6444.611f, 35.03535f, 62.56868f),
        Mod_Class::Vector4(2403.384f, 6718.95f, 39.0113f, 69.30715f),
        Mod_Class::Vector4(1678.953f, 6731.902f, 71.92032f, 96.16738f),
        Mod_Class::Vector4(622.5536f, 6737.898f, 21.04184f, 47.28201f),
        Mod_Class::Vector4(145.2582f, 7054.913f, 40.39904f, 76.91423f),
        Mod_Class::Vector4(-147.7463f, 6729.933f, 13.17056f, 153.3098f),
    };      //a_c_cormorant

    inline const std::vector<Mod_Class::Vector4> YanktonVeh = {
        Mod_Class::Vector4(5349.33f, -5199.588f, 82.53371f, 359.9582f),
        Mod_Class::Vector4(5342.033f, -5190.025f, 82.52918f, 279.9539f),
        Mod_Class::Vector4(5353.034f, -5218.646f, 82.56881f, 272.0059f),
        Mod_Class::Vector4(5434.19f, -5144.919f, 77.98462f, 359.235f),
        Mod_Class::Vector4(5533.231f, -5130.195f, 78.7478f, 86.32229f),
        Mod_Class::Vector4(5489.795f, -5213.68f, 78.17661f, 0.03953937f),
        Mod_Class::Vector4(5330.385f, -5117.069f, 78.37f, 89.91409f),
        Mod_Class::Vector4(5200.818f, -5112.665f, 81.00806f, 256.4373f),
        Mod_Class::Vector4(5076.764f, -5097.154f, 86.51511f, 92.37791f),
        Mod_Class::Vector4(4922.343f, -5077.724f, 93.46674f, 255.5045f),
        Mod_Class::Vector4(4802.533f, -5084.878f, 104.4445f, 92.2748f),
        Mod_Class::Vector4(4734.521f, -5158.188f, 106.9049f, 355.8596f),
        Mod_Class::Vector4(4613.652f, -5077.257f, 106.8439f, 241.8371f),
        Mod_Class::Vector4(4518.823f, -5092.079f, 110.2318f, 110.5459f),
        Mod_Class::Vector4(4387.06f, -5191.558f, 110.5836f, 358.3198f),
        Mod_Class::Vector4(4402.611f, -5023.318f, 111.3078f, 170.7627f),
        Mod_Class::Vector4(4278.562f, -5077.321f, 110.4314f, 265.8921f),
        Mod_Class::Vector4(4066.314f, -5055.012f, 108.3266f, 86.1267f),
        Mod_Class::Vector4(3903.697f, -5031.179f, 110.8148f, 257.4004f),
        Mod_Class::Vector4(3735.925f, -4966.002f, 111.041f, 65.27551f),
        Mod_Class::Vector4(3662.927f, -4975.617f, 111.141f, 350.5125f),
        Mod_Class::Vector4(3680.137f, -4894.989f, 111.5294f, 173.6839f),
        Mod_Class::Vector4(3591.777f, -4900.473f, 111.4092f, 247.5843f),
        Mod_Class::Vector4(3527.802f, -4788.388f, 111.8003f, 354.5734f),
        Mod_Class::Vector4(3547.425f, -4662.932f, 113.9405f, 166.4226f),
        Mod_Class::Vector4(3374.261f, -4846.967f, 111.5169f, 84.54334f),
        Mod_Class::Vector4(3335.508f, -4927.531f, 111.2219f, 354.6419f),
        Mod_Class::Vector4(3212.379f, -4852.711f, 111.5485f, 354.8022f),
        Mod_Class::Vector4(3209.163f, -4776.607f, 111.5591f, 258.9726f),
        Mod_Class::Vector4(3209.417f, -4727.386f, 111.9298f, 264.1234f),
        Mod_Class::Vector4(3262.463f, -4689.186f, 112.7509f, 103.9134f),
        Mod_Class::Vector4(3117.954f, -4829.271f, 111.5413f, 265.3655f)
    };

    inline const std::vector<Mod_Class::Vector4> Cayo_Beach = {
        Mod_Class::Vector4(4893.338f, -4903.796f, 3.486674f, 179.7596f),
        Mod_Class::Vector4(4898.212f, -4913.461f, 3.362877f, 62.6438f),
        Mod_Class::Vector4(4889.125f, -4913.463f, 3.364484f, 243.0125f),
        Mod_Class::Vector4(4886.227f, -4922.317f, 3.370104f, 156.813f),
        Mod_Class::Vector4(4889.59f, -4928.318f, 3.380038f, 314.8568f),
        Mod_Class::Vector4(4898.494f, -4931.63f, 3.367776f, 95.74232f),
        Mod_Class::Vector4(4870.61f, -4930.148f, 2.789379f, 333.0222f),
        Mod_Class::Vector4(4874.745f, -4925.462f, 3.178774f, 132.1784f),
        Mod_Class::Vector4(4869.804f, -4927.207f, 2.743952f, 247.7478f)
    };
    inline const std::vector<Mod_Class::Vector4> Cayo_Guard = {
        Mod_Class::Vector4(4877.928f, -4488.06f, 26.93383f, 7.88381f),
        Mod_Class::Vector4(5032.213f, -4630.636f, 21.68462f, 75.61213f),
        Mod_Class::Vector4(5153.693f, -4933.251f, 30.87342f, 142.8952f),
        Mod_Class::Vector4(5148.306f, -5053.395f, 20.39156f, 85.7536f),
        Mod_Class::Vector4(5465.802f, -5236.399f, 43.96178f, 184.7819f),
        Mod_Class::Vector4(5360.864f, -5437.077f, 66.17649f, 221.3451f),
        Mod_Class::Vector4(5125.446f, -5526.457f, 70.9704f, 199.5584f),
        Mod_Class::Vector4(4887.5f, -5458.02f, 47.52377f, 182.3656f),
        Mod_Class::Vector4(5042.819f, -5114.771f, 22.94463f, 88.81671f),
        Mod_Class::Vector4(5140.625f, -5243.813f, 26.29192f, 253.1926f)
    };
    inline const std::vector<Mod_Class::Vector4> Cayo_GuardVeh = {
        Mod_Class::Vector4(5151.242f, -4988.032f, 11.07006f, 330.7662f),
        Mod_Class::Vector4(5234.622f, -5044.32f, 14.78756f, 217.541f),
        Mod_Class::Vector4(5395.034f, -5117.525f, 12.82211f, 260.8773f),
        Mod_Class::Vector4(5480.951f, -5154.387f, 13.003f, 243.3344f),
        Mod_Class::Vector4(5422.944f, -5336.357f, 29.1772f, 184.6251f),
        Mod_Class::Vector4(5371.362f, -5443.372f, 47.44936f, 103.1909f),
        Mod_Class::Vector4(5334.503f, -5356.212f, 39.44836f, 42.72601f),
        Mod_Class::Vector4(5379.229f, -5581.523f, 51.64316f, 16.55149f),
        Mod_Class::Vector4(5250.379f, -5440.512f, 63.21391f, 46.61808f),
        Mod_Class::Vector4(5158.693f, -5564.97f, 41.48776f, 115.0785f),
        Mod_Class::Vector4(4951.867f, -5668.801f, 20.83409f, 315.0575f),
        Mod_Class::Vector4(5020.304f, -5659.498f, 19.54258f, 80.51956f),
        Mod_Class::Vector4(4790.595f, -5569.141f, 23.19196f, 258.7796f),
        Mod_Class::Vector4(4930.438f, -5462.304f, 30.63404f, 138.0855f),
        Mod_Class::Vector4(4940.436f, -5306.102f, 5.363968f, 354.3278f),
        Mod_Class::Vector4(4955.303f, -5191.416f, 1.901235f, 289.481f),
        Mod_Class::Vector4(5062.519f, -5233.131f, 4.048297f, 201.6604f),
        Mod_Class::Vector4(5165.552f, -5163.518f, 1.599737f, 0.206256f),
        Mod_Class::Vector4(5140.043f, -5144.51f, 1.572914f, 267.457f),
        Mod_Class::Vector4(5160.295f, -5081.718f, 2.027128f, 12.37001f),
        Mod_Class::Vector4(5227.267f, -5128.13f, 6.823656f, 196.9126f),
        Mod_Class::Vector4(5043.173f, -4884.606f, 14.96475f, 57.48603f),
        Mod_Class::Vector4(4995.452f, -4753.767f, 12.47045f, 343.0041f),
        Mod_Class::Vector4(4976.23f, -4700.542f, 7.567879f, 323.5304f),
        Mod_Class::Vector4(5077.751f, -4680.26f, 2.163868f, 55.20174f),
        Mod_Class::Vector4(5124.599f, -4623.691f, 2.020308f, 252.7671f),
        Mod_Class::Vector4(5132.404f, -4582.143f, 4.136497f, 42.58467f),
        Mod_Class::Vector4(4969.585f, -4511.583f, 8.316021f, 59.19208f),
        Mod_Class::Vector4(4863.543f, -4406.074f, 6.154335f, 177.9412f),
        Mod_Class::Vector4(4642.67f, -4471.657f, 3.802634f, 101.2704f),
        Mod_Class::Vector4(4509.105f, -4608.875f, 7.677932f, 28.56013f),
        Mod_Class::Vector4(5233.419f, -5043.578f, 14.87521f, 43.09966f),
        Mod_Class::Vector4(5165.328f, -5169.925f, 1.41904f, 176.6293f),
        Mod_Class::Vector4(4941.741f, -5249.38f, 1.856673f, 191.2316f),
        Mod_Class::Vector4(4971.292f, -5701.965f, 19.36028f, 38.00845f),
        Mod_Class::Vector4(5255.248f, -5503.7f, 50.02805f, 289.521f),
        Mod_Class::Vector4(5383.012f, -5666.684f, 49.45168f, 348.699f),
        Mod_Class::Vector4(5250.007f, -5268.963f, 24.84689f, 50.79947f),
        Mod_Class::Vector4(5044.055f, -4904.506f, 14.52278f, 277.0196f),
        Mod_Class::Vector4(4953.167f, -4745.344f, 7.760445f, 340.7749f),
        Mod_Class::Vector4(4928.463f, -4485.532f, 7.438392f, 56.79505f),
        Mod_Class::Vector4(4500.685f, -4494.414f, 3.665595f, 287.3625f)
    };
    inline const std::vector<Mod_Class::Vector4> Cayo_Workers = {
        Mod_Class::Vector4(5170.325f, -4675.89f, 2.435122f, 66.67837f),
        Mod_Class::Vector4(5179.303f, -4649.774f, 2.530395f, 64.63232f),
        Mod_Class::Vector4(5127.161f, -4613.125f, 2.567649f, 134.3626f),
        Mod_Class::Vector4(5403.269f, -5174.491f, 31.46002f, 30.90309f),
        Mod_Class::Vector4(5408.926f, -5216.411f, 34.45446f, 232.4724f),
        Mod_Class::Vector4(5382.5f, -5255.195f, 34.15533f, 168.2274f),
        Mod_Class::Vector4(5327.994f, -5265.26f, 33.17245f, 216.49f),
        Mod_Class::Vector4(5312.92f, -5200.948f, 31.73465f, 43.35777f),
        Mod_Class::Vector4(5283.029f, -5239.302f, 30.83397f, 226.2264f),
        Mod_Class::Vector4(5211.092f, -5125.889f, 6.214875f, 297.0678f),
        Mod_Class::Vector4(5182.966f, -5148.639f, 3.549981f, 93.57137f),
        Mod_Class::Vector4(5117.133f, -5172.37f, 2.296359f, 90.88295f),
        Mod_Class::Vector4(5012.493f, -5201.086f, 2.517188f, 332.5578f),
        Mod_Class::Vector4(4957.826f, -5133.129f, 2.44458f, 126.1573f),
        Mod_Class::Vector4(4902.437f, -5180.579f, 2.445158f, 256.659f),
        Mod_Class::Vector4(4949.478f, -5319.582f, 8.065354f, 190.8848f),
        Mod_Class::Vector4(5310.973f, -5600.635f, 64.51008f, 298.4847f)
    };

    inline const std::vector<Mod_Class::Vector4> CopsOnPatrol = {
        Mod_Class::Vector4(-394.8712f, 5987.242f, 31.23644f, 137.743f),
        Mod_Class::Vector4(-589.504f, 5660.459f, 38.00223f, 154.7489f),
        Mod_Class::Vector4(-970.8676f, 5406.894f, 39.32494f, 110.4479f),
        Mod_Class::Vector4(-1312.168f, 5197.71f, 57.7121f, 170.5467f),
        Mod_Class::Vector4(-1912.74f, 4613.743f, 56.6665f, 136.1981f),
        Mod_Class::Vector4(-2332.955f, 4102.044f, 34.31093f, 161.9755f),
        Mod_Class::Vector4(-2690.888f, 2453.453f, 16.32133f, 169.1286f),
        Mod_Class::Vector4(-3068.407f, 1388.924f, 20.38018f, 150.499f),
        Mod_Class::Vector4(-3110.377f, 795.5115f, 18.03421f, 212.8304f),
        Mod_Class::Vector4(-2847.284f, 55.16071f, 14.03356f, 252.6973f),
        Mod_Class::Vector4(-2400.721f, -261.9758f, 14.77213f, 240.7372f),
        Mod_Class::Vector4(-1924.38f, -514.1334f, 11.45463f, 232.4852f),
        Mod_Class::Vector4(-1426.035f, -772.7139f, 10.7571f, 281.7244f),
        Mod_Class::Vector4(-1008.391f, -593.8707f, 18.00854f, 297.0173f),
        Mod_Class::Vector4(-582.6405f, -547.8249f, 25.0461f, 270.6662f),
        Mod_Class::Vector4(-416.0467f, -829.056f, 38.48112f, 181.7126f),
        Mod_Class::Vector4(-429.7287f, -1073.597f, 39.38478f, 173.1839f),
        Mod_Class::Vector4(-88.20789f, -1232.365f, 36.90318f, 265.8213f),
        Mod_Class::Vector4(890.7316f, -1202.069f, 46.32738f, 274.6949f),
        Mod_Class::Vector4(1464.219f, -1050.51f, 55.26758f, 299.405f),
        Mod_Class::Vector4(2149.118f, -565.8964f, 94.59676f, 311.0464f),
        Mod_Class::Vector4(2609.982f, 290.5139f, 97.5564f, 348.2012f),
        Mod_Class::Vector4(1984.961f, 1658.797f, 71.01709f, 19.28443f),
        Mod_Class::Vector4(2088.883f, 2625.039f, 51.84667f, 311.2102f),
        Mod_Class::Vector4(2323.866f, 2827.958f, 40.8583f, 308.018f),
        Mod_Class::Vector4(2805.268f, 3404.815f, 55.47346f, 336.7848f),
        Mod_Class::Vector4(2899.065f, 4124.424f, 50.08463f, 18.66524f),
        Mod_Class::Vector4(2684.958f, 4907.412f, 44.33824f, 12.87171f),
        Mod_Class::Vector4(2418.038f, 5749.263f, 45.18233f, 28.76237f),
        Mod_Class::Vector4(1977.457f, 6263.674f, 45.21947f, 26.58558f),
        Mod_Class::Vector4(1510.187f, 6446.735f, 22.32313f, 71.73681f),
        Mod_Class::Vector4(437.937f, 6575.301f, 26.70975f, 82.35296f),
        Mod_Class::Vector4(-83.65768f, 6303.471f, 30.98907f, 134.5836f)
    };
    inline const std::vector<Mod_Class::Vector4> RangersOnPatrol = {
        Mod_Class::Vector4(-1293.673f, 4494.106f, 20.58409f, 292.0183f),
        Mod_Class::Vector4(-1178.848f, 4464.489f, 22.12055f, 223.882f),
        Mod_Class::Vector4(-978.9658f, 4424.257f, 18.17138f, 277.2969f),
        Mod_Class::Vector4(-881.5007f, 4413.713f, 20.53524f, 217.3883f),
        Mod_Class::Vector4(-777.9758f, 4400.937f, 17.60112f, 275.5142f),
        Mod_Class::Vector4(-602.1019f, 4366.186f, 46.281f, 253.283f),
        Mod_Class::Vector4(-515.4304f, 4360.043f, 67.23169f, 263.3065f),
        Mod_Class::Vector4(-347.9384f, 4262.4f, 43.75414f, 228.5496f),
        Mod_Class::Vector4(-287.5003f, 4225.528f, 42.43953f, 268.8033f),
        Mod_Class::Vector4(-153.517f, 4256.249f, 44.56781f, 314.6894f),
        Mod_Class::Vector4(-145.1843f, 4293.134f, 38.87434f, 88.74877f),
        Mod_Class::Vector4(-249.6895f, 4394.849f, 41.87869f, 8.487266f),
        Mod_Class::Vector4(-417.3254f, 4526.998f, 97.31594f, 53.3997f),
        Mod_Class::Vector4(-571.6215f, 4536.679f, 77.84266f, 89.20762f),
        Mod_Class::Vector4(-727.8802f, 4552.677f, 79.56893f, 149.3363f),
        Mod_Class::Vector4(-897.5674f, 4533.807f, 115.368f, 58.88343f),
        Mod_Class::Vector4(-1060.448f, 4604.615f, 119.0654f, 102.8088f),
        Mod_Class::Vector4(-1158.658f, 4630.63f, 145.2369f, 40.73964f),
        Mod_Class::Vector4(-1298.495f, 4617.949f, 118.2277f, 50.38947f),
        Mod_Class::Vector4(-1285.191f, 4690.343f, 79.85976f, 92.15211f),
        Mod_Class::Vector4(-1456.307f, 4705.057f, 39.88514f, 107.5465f),
        Mod_Class::Vector4(-1556.354f, 4614.396f, 21.49115f, 154.2038f),
        Mod_Class::Vector4(-1490.267f, 4472.361f, 17.07588f, 277.0578f),
        Mod_Class::Vector4(-1322.501f, 4480.612f, 22.52247f, 297.27f)
    };

    inline const std::vector<Mod_Class::Vector4> AmbulanceStarts = {
        Mod_Class::Vector4(345.997f, -1499.324f, 29.10899f, 129.4425f),
        Mod_Class::Vector4(352.5213f, -644.6024f, 28.99671f, 148.8457f),
        Mod_Class::Vector4(-1545.056f, -158.9708f, 54.8252f, 130.8122f),
        Mod_Class::Vector4(1183.667f, -1439.131f, 34.75734f, 269.7065f),
        Mod_Class::Vector4(1803.922f, 3649.984f, 34.0734f, 207.0468f),
        Mod_Class::Vector4(-184.7601f, 6345.665f, 31.21086f, 315.0266f)
    };
    inline const std::vector<Mod_Class::Vector4> FireStarts = {
        Mod_Class::Vector4(206.7451f, -1607.381f, 29.38388f, 54.94406f),
        Mod_Class::Vector4(-670.6158f, -56.91853f, 38.65288f, 111.0066f),
        Mod_Class::Vector4(-1311.508f, 2480.006f, 23.69703f, 133.9563f),
        Mod_Class::Vector4(1233.949f, -1437.727f, 35.38113f, 286.4684f),
        Mod_Class::Vector4(1687.579f, 3521.061f, 36.32011f, 207.8307f),
        Mod_Class::Vector4(-350.9323f, 6176.161f, 31.36358f, 311.1929f)
    };
    inline const std::vector<Mod_Class::Vector4> DeliveryStarts = {
        Mod_Class::Vector4(-335.7433f, -2690.851f, 6.285177f, 316.7236f),
        Mod_Class::Vector4(30.13136f, 27.50258f, 70.36028f, 160.5689f),
        Mod_Class::Vector4(-3190.336f, 908.914f, 14.27942f, 260.8866f),
        Mod_Class::Vector4(1067.992f, -227.914f, 69.34801f, 245.6661f),
        Mod_Class::Vector4(1998.634f, 4643.438f, 40.75179f, 234.0808f),
        Mod_Class::Vector4(-419.1237f, 6052.995f, 30.96981f, 40.67022f)
    };
    inline const std::vector<Mod_Class::Vector4> GroupSixStarts = {
        Mod_Class::Vector4(838.3964f, -1600.772f, 31.59866f, 173.3715f),
        Mod_Class::Vector4(-244.0465f, 254.0381f, 91.60336f, 267.1381f),
        Mod_Class::Vector4(-2022.125f, -421.2141f, 10.99299f, 49.02102f),
        Mod_Class::Vector4(1182.725f, -1068.627f, 41.19003f, 21.30373f),
        Mod_Class::Vector4(2497.474f, 4135.372f, 38.06038f, 237.9974f),
        Mod_Class::Vector4(-20.35295f, 6366.861f, 30.94088f, 135.2917f)
    };

    inline const std::vector<Mod_Class::Vector4> Jogger01 = {
        Mod_Class::Vector4(228.6289f, -1394.52f, 30.494f,0.0f),
        Mod_Class::Vector4(252.5324f, -1400.599f, 30.53424f,0.0f),
        Mod_Class::Vector4(273.3281f, -1378.727f, 31.95101f,0.0f),
        Mod_Class::Vector4(273.2798f, -1359.458f, 31.93511f,0.0f),
        Mod_Class::Vector4(250.2143f, -1339.669f, 31.92071f,0.0f),
        Mod_Class::Vector4(235.2781f, -1346.481f, 30.5051f,0.0f),
        Mod_Class::Vector4(219.2509f, -1365.954f, 30.56017f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger02 = {
        Mod_Class::Vector4(-227.1508f, -2023.395f, 27.75543f,0.0f),
        Mod_Class::Vector4(-222.3802f, -2007.24f, 27.75543f,0.0f),
        Mod_Class::Vector4(-219.4253f, -1989.297f, 27.75542f,0.0f),
        Mod_Class::Vector4(-221.2715f, -1971.702f, 27.75571f,0.0f),
        Mod_Class::Vector4(-224.2942f, -1960.297f, 27.75689f,0.0f),
        Mod_Class::Vector4(-240.3955f, -1966.939f, 29.94605f,0.0f),
        Mod_Class::Vector4(-239.069f, -1973.878f, 29.94605f,0.0f),
        Mod_Class::Vector4(-237.4634f, -1992.5f, 29.94605f,0.0f),
        Mod_Class::Vector4(-240.9862f, -2009.94f, 29.94605f,0.0f),
        Mod_Class::Vector4(-249.9569f, -2026.076f, 29.94605f,0.0f),
        Mod_Class::Vector4(-263.3784f, -2040.735f, 29.94605f,0.0f),
        Mod_Class::Vector4(-277.9292f, -2048.336f, 29.94605f,0.0f),
        Mod_Class::Vector4(-273.3261f, -2064.927f, 27.75543f,0.0f),
        Mod_Class::Vector4(-246.0456f, -2048.949f, 27.75543f,0.0f),
        Mod_Class::Vector4(-235.4299f, -2037.349f, 27.75543f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger03 = {
        Mod_Class::Vector4(-924.767f, -2571.403f, 13.97616f,0.0f),
        Mod_Class::Vector4(-943.3739f, -2565.557f, 13.93645f,0.0f),
        Mod_Class::Vector4(-961.3f, -2544.967f, 13.98062f,0.0f),
        Mod_Class::Vector4(-967.3834f, -2523.3f, 13.98103f,0.0f),
        Mod_Class::Vector4(-965.3172f, -2502.885f, 13.98098f,0.0f),
        Mod_Class::Vector4(-960.5615f, -2492.263f, 13.98057f,0.0f),
        Mod_Class::Vector4(-947.3313f, -2478.542f, 13.9807f,0.0f),
        Mod_Class::Vector4(-932.3168f, -2470.56f, 13.9807f,0.0f),
        Mod_Class::Vector4(-913.9728f, -2467.62f, 13.98073f,0.0f),
        Mod_Class::Vector4(-889.0792f, -2472.986f, 13.98049f,0.0f),
        Mod_Class::Vector4(-872.939f, -2489.196f, 13.98072f,0.0f),
        Mod_Class::Vector4(-866.3092f, -2501.952f, 13.98075f,0.0f),
        Mod_Class::Vector4(-863.3466f, -2512.478f, 13.98059f,0.0f),
        Mod_Class::Vector4(-863.6301f, -2528.947f, 13.98072f,0.0f),
        Mod_Class::Vector4(-869.4406f, -2546.69f, 13.97835f,0.0f),
        Mod_Class::Vector4(-884.2811f, -2561.323f, 13.98074f,0.0f),
        Mod_Class::Vector4(-896.1907f, -2568.416f, 13.98074f,0.0f),
        Mod_Class::Vector4(-903.6213f, -2570.235f, 13.98074f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger04 = {
        Mod_Class::Vector4(-287.7649f, -1638.534f, 31.84882f,0.0f),
        Mod_Class::Vector4(-298.8279f, -1656.257f, 31.84881f,0.0f),
        Mod_Class::Vector4(-317.5655f, -1644.264f, 31.85344f,0.0f),
        Mod_Class::Vector4(-303.9065f, -1622.695f, 31.84882f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger05 = {
        Mod_Class::Vector4(1476.682f, -1984.691f, 70.69158f,0.0f),
        Mod_Class::Vector4(1453.445f, -1972.131f, 70.44451f,0.0f),
        Mod_Class::Vector4(1434.379f, -1986.595f, 65.75795f,0.0f),
        Mod_Class::Vector4(1423.388f, -2007.92f, 61.90174f,0.0f),
        Mod_Class::Vector4(1433.237f, -2031.683f, 57.47531f,0.0f),
        Mod_Class::Vector4(1469.974f, -2042.295f, 57.02632f,0.0f),
        Mod_Class::Vector4(1478.932f, -2002.187f, 68.38514f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger06 = {
        Mod_Class::Vector4(129.9129f, -988.9407f, 29.32248f,0.0f),
        Mod_Class::Vector4(169.9703f, -880.6992f, 30.55882f,0.0f),
        Mod_Class::Vector4(174.1833f, -881.5703f, 30.89416f,0.0f),
        Mod_Class::Vector4(186.1561f, -849.1542f, 31.16665f,0.0f),
        Mod_Class::Vector4(193.5296f, -847.7554f, 30.91245f,0.0f),
        Mod_Class::Vector4(263.498f, -872.455f, 29.17216f,0.0f),
        Mod_Class::Vector4(211.1392f, -1018.212f, 29.30549f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger07 = {
        Mod_Class::Vector4(356.3345f, 160.7301f, 103.0043f,0.0f),
        Mod_Class::Vector4(222.6689f, 208.8755f, 105.5123f,0.0f),
        Mod_Class::Vector4(266.2624f, 328.2007f, 105.5289f,0.0f),
        Mod_Class::Vector4(339.1058f, 311.9287f, 104.5361f,0.0f),
        Mod_Class::Vector4(404.6719f, 292.2426f, 102.9655f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger08 = {
        Mod_Class::Vector4(-68.89455f, -402.1517f, 37.29737f,0.0f),
        Mod_Class::Vector4(-103.1039f, -389.6021f, 36.63163f,0.0f),
        Mod_Class::Vector4(-108.889f, -409.1098f, 35.77497f,0.0f),
        Mod_Class::Vector4(-127.2451f, -411.5541f, 34.58294f,0.0f),
        Mod_Class::Vector4(-139.3882f, -421.2568f, 33.74562f,0.0f),
        Mod_Class::Vector4(-148.7219f, -435.5255f, 33.47985f,0.0f),
        Mod_Class::Vector4(-153.0547f, -451.4209f, 33.79173f,0.0f),
        Mod_Class::Vector4(-145.8188f, -464.7188f, 33.17519f,0.0f),
        Mod_Class::Vector4(-132.132f, -472.3099f, 33.07674f,0.0f),
        Mod_Class::Vector4(-121.9619f, -474.8518f, 33.34896f,0.0f),
        Mod_Class::Vector4(-89.17182f, -474.3718f, 34.96899f,0.0f),
        Mod_Class::Vector4(-77.55576f, -466.7515f, 36.39326f,0.0f),
        Mod_Class::Vector4(-67.24388f, -449.3546f, 38.11158f,0.0f),
        Mod_Class::Vector4(-64.59761f, -437.8882f, 38.43552f,0.0f),
        Mod_Class::Vector4(-64.19228f, -419.8323f, 38.09665f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger09 = {
        Mod_Class::Vector4(-736.3101f, 90.46006f, 55.58132f,0.0f),
        Mod_Class::Vector4(-737.0633f, 69.59921f, 54.30896f,0.0f),
        Mod_Class::Vector4(-734.0124f, 47.01559f, 47.47584f,0.0f),
        Mod_Class::Vector4(-728.4005f, 29.74567f, 42.26787f,0.0f),
        Mod_Class::Vector4(-703.6444f, 36.59576f, 43.22058f,0.0f),
        Mod_Class::Vector4(-681.6513f, 46.41314f, 43.09964f,0.0f),
        Mod_Class::Vector4(-661.1816f, 46.04203f, 41.12265f,0.0f),
        Mod_Class::Vector4(-658.776f, 85.53405f, 52.46266f,0.0f),
        Mod_Class::Vector4(-662.4477f, 103.3301f, 56.80659f,0.0f),
        Mod_Class::Vector4(-662.0488f, 119.3575f, 57.01698f,0.0f),
        Mod_Class::Vector4(-675.6852f, 115.9964f, 56.75283f,0.0f),
        Mod_Class::Vector4(-709.5087f, 98.95238f, 56.07108f,0.0f),
        Mod_Class::Vector4(-718.9947f, 95.15092f, 55.8739f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger10 = {
        Mod_Class::Vector4(-1765.645f, -1149.159f, 13.07916f,0.0f),
        Mod_Class::Vector4(-1837.407f, -1227.053f, 13.01728f,0.0f),
        Mod_Class::Vector4(-1869.622f, -1210.43f, 13.01711f,0.0f),
        Mod_Class::Vector4(-1831.916f, -1162.537f, 13.01727f,0.0f),
        Mod_Class::Vector4(-1806.807f, -1181.257f, 13.01744f,0.0f),
        Mod_Class::Vector4(-1797.633f, -1177.67f, 13.01751f,0.0f),
        Mod_Class::Vector4(-1786.751f, -1169.576f, 13.01768f,0.0f),
        Mod_Class::Vector4(-1660.035f, -1023.637f, 13.01778f,0.0f),
        Mod_Class::Vector4(-1652.489f, -1014.507f, 13.01739f,0.0f),
        Mod_Class::Vector4(-1659.945f, -1009.417f, 13.01739f,0.0f),
        Mod_Class::Vector4(-1709.898f, -1070.201f, 13.01735f,0.0f),
        Mod_Class::Vector4(-1709.359f, -1083.783f, 13.10089f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger11 = {
        Mod_Class::Vector4(-2891.325f, -8.690169f, 7.963134f,0.0f),
        Mod_Class::Vector4(-2910.282f, -37.03131f, 3.024998f,0.0f),
        Mod_Class::Vector4(-2999.717f, 0.8205602f, 4.733732f,0.0f),
        Mod_Class::Vector4(-2997.566f, 30.52503f, 7.300454f,0.0f),
        Mod_Class::Vector4(-2995.444f, 36.81783f, 7.95881f,0.0f),
        Mod_Class::Vector4(-2992.152f, 35.16978f, 8.5967f,0.0f),
        Mod_Class::Vector4(-2987.468f, 42.83352f, 11.6085f,0.0f),
        Mod_Class::Vector4(-2939.735f, 20.68083f, 11.60792f,0.0f),
        Mod_Class::Vector4(-2943.227f, 12.65156f, 11.60476f,0.0f),
        Mod_Class::Vector4(-2918.954f, 1.69491f, 11.60532f,0.0f),
        Mod_Class::Vector4(-2891.381f, -6.391256f, 11.60316f,0.0f),
        Mod_Class::Vector4(-2888.387f, 2.114674f, 11.608f,0.0f),
        Mod_Class::Vector4(-2886.561f, 0.7008348f, 11.608f,0.0f),
        Mod_Class::Vector4(-2888.892f, -7.902122f, 7.959469f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger12 = {
        Mod_Class::Vector4(-1486.228f, 875.5378f, 182.6471f,0.0f),
        Mod_Class::Vector4(-1478.33f, 831.1494f, 181.7178f,0.0f),
        Mod_Class::Vector4(-1514.694f, 814.3276f, 181.9242f,0.0f),
        Mod_Class::Vector4(-1521.786f, 816.0013f, 181.8818f,0.0f),
        Mod_Class::Vector4(-1532.458f, 826.3513f, 181.4863f,0.0f),
        Mod_Class::Vector4(-1543.011f, 817.2687f, 182.2451f,0.0f),
        Mod_Class::Vector4(-1549.201f, 782.2504f, 188.5506f,0.0f),
        Mod_Class::Vector4(-1558.725f, 777.4117f, 189.1925f,0.0f),
        Mod_Class::Vector4(-1584.688f, 765.293f, 189.1942f,0.0f),
        Mod_Class::Vector4(-1592.872f, 784.2383f, 189.194f,0.0f),
        Mod_Class::Vector4(-1578.12f, 790.5488f, 189.1929f,0.0f),
        Mod_Class::Vector4(-1585.357f, 804.7038f, 185.9943f,0.0f),
        Mod_Class::Vector4(-1575.385f, 809.5252f, 185.9944f,0.0f),
        Mod_Class::Vector4(-1578.809f, 818.0173f, 185.9939f,0.0f),
        Mod_Class::Vector4(-1534.582f, 848.1694f, 181.7705f,0.0f),
        Mod_Class::Vector4(-1521.602f, 854.8638f, 181.5947f,0.0f),
        Mod_Class::Vector4(-1496.966f, 870.4911f, 181.9422f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger13 = {
        Mod_Class::Vector4(-1893.8f, 1974.631f, 143.1386f,0.0f),
        Mod_Class::Vector4(-1929.31f, 1969.096f, 148.8142f,0.0f),
        Mod_Class::Vector4(-1966.108f, 1968.237f, 154.9804f,0.0f),
        Mod_Class::Vector4(-1982.965f, 1961.467f, 160.8532f,0.0f),
        Mod_Class::Vector4(-1987.9f, 1950.067f, 167.1869f,0.0f),
        Mod_Class::Vector4(-1982.987f, 1941.103f, 171.1532f,0.0f),
        Mod_Class::Vector4(-1945.131f, 1917.294f, 173.789f,0.0f),
        Mod_Class::Vector4(-1938.31f, 1890.808f, 179.907f,0.0f),
        Mod_Class::Vector4(-1954.827f, 1842.859f, 180.2473f,0.0f),
        Mod_Class::Vector4(-1957.488f, 1830.848f, 178.8064f,0.0f),
        Mod_Class::Vector4(-1945.764f, 1820.129f, 172.0853f,0.0f),
        Mod_Class::Vector4(-1937.965f, 1823.133f, 170.6982f,0.0f),
        Mod_Class::Vector4(-1920.848f, 1840.997f, 166.5749f,0.0f),
        Mod_Class::Vector4(-1899.503f, 1851.748f, 160.8903f,0.0f),
        Mod_Class::Vector4(-1879.112f, 1865.361f, 156.9021f,0.0f),
        Mod_Class::Vector4(-1841.115f, 1891.895f, 146.2764f,0.0f),
        Mod_Class::Vector4(-1836.474f, 1901.321f, 145.8237f,0.0f),
        Mod_Class::Vector4(-1839.368f, 1912.564f, 147.3022f,0.0f),
        Mod_Class::Vector4(-1853.069f, 1930.572f, 150.2391f,0.0f),
        Mod_Class::Vector4(-1878.708f, 1956.751f, 145.8794f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger14 = {
        Mod_Class::Vector4(-319.6601f, 2786.814f, 59.43f,0.0f),
        Mod_Class::Vector4(-337.5543f, 2800.789f, 58.15808f,0.0f),
        Mod_Class::Vector4(-338.9051f, 2804.992f, 58.13386f,0.0f),
        Mod_Class::Vector4(-327.3314f, 2822.454f, 58.19631f,0.0f),
        Mod_Class::Vector4(-317.4219f, 2826.94f, 58.47928f,0.0f),
        Mod_Class::Vector4(-312.7925f, 2831.25f, 58.25769f,0.0f),
        Mod_Class::Vector4(-310.0566f, 2831.212f, 58.38048f,0.0f),
        Mod_Class::Vector4(-297.7459f, 2823.444f, 59.15673f,0.0f),
        Mod_Class::Vector4(-299.6138f, 2818.963f, 59.19112f,0.0f),
        Mod_Class::Vector4(-295.6808f, 2811.254f, 58.98975f,0.0f),
        Mod_Class::Vector4(-308.6064f, 2790.959f, 59.41709f,0.0f),
        Mod_Class::Vector4(-316.4038f, 2787.014f, 59.56699f,0.0f),
        Mod_Class::Vector4(-323.0881f, 2789.975f, 59.20899f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger15 = {
        Mod_Class::Vector4(-2768.271f, 2695.774f, 1.370201f,0.0f),
        Mod_Class::Vector4(-2755.266f, 2703.515f, 1.416718f,0.0f),
        Mod_Class::Vector4(-2735.553f, 2738.595f, 1.462122f,0.0f),
        Mod_Class::Vector4(-2730.177f, 2799.426f, 1.757612f,0.0f),
        Mod_Class::Vector4(-2717.147f, 2824.657f, 1.186048f,0.0f),
        Mod_Class::Vector4(-2730.011f, 2855.175f, 1.459975f,0.0f),
        Mod_Class::Vector4(-2720.936f, 2897.158f, 1.232428f,0.0f),
        Mod_Class::Vector4(-2723.055f, 2915.156f, 1.214248f,0.0f),
        Mod_Class::Vector4(-2717.156f, 2934.323f, 1.675791f,0.0f),
        Mod_Class::Vector4(-2736.917f, 2953.923f, 2.776649f,0.0f),
        Mod_Class::Vector4(-2746.004f, 2954.125f, 2.354859f,0.0f),
        Mod_Class::Vector4(-2751.835f, 2943.838f, 2.075438f,0.0f),
        Mod_Class::Vector4(-2752.229f, 2914.945f, 1.281913f,0.0f),
        Mod_Class::Vector4(-2752.62f, 2887.3f, 1.572614f,0.0f),
        Mod_Class::Vector4(-2756.117f, 2854.283f, 1.468493f,0.0f),
        Mod_Class::Vector4(-2764.645f, 2779.508f, 2.047434f,0.0f),
        Mod_Class::Vector4(-2769.536f, 2743.653f, 2.138904f,0.0f),
        Mod_Class::Vector4(-2776.014f, 2720.484f, 2.238141f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger16 = {
        Mod_Class::Vector4(1061.091f, -558.9828f, 59.28479f,0.0f),
        Mod_Class::Vector4(1066.203f, -597.2649f, 56.83318f,0.0f),
        Mod_Class::Vector4(1062.106f, -610.6114f, 56.76826f,0.0f),
        Mod_Class::Vector4(1022.904f, -655.5869f, 58.68858f,0.0f),
        Mod_Class::Vector4(1020.39f, -657.876f, 58.61199f,0.0f),
        Mod_Class::Vector4(1020.476f, -698.0944f, 56.81086f,0.0f),
        Mod_Class::Vector4(1056.699f, -719.1822f, 56.815f,0.0f),
        Mod_Class::Vector4(1088.558f, -738.0333f, 56.76314f,0.0f),
        Mod_Class::Vector4(1132.372f, -738.0198f, 56.74362f,0.0f),
        Mod_Class::Vector4(1143.484f, -710.3257f, 56.80364f,0.0f),
        Mod_Class::Vector4(1127.766f, -660.5972f, 56.68017f,0.0f),
        Mod_Class::Vector4(1126.506f, -644.8978f, 56.77164f,0.0f),
        Mod_Class::Vector4(1119.372f, -633.5688f, 56.78326f,0.0f),
        Mod_Class::Vector4(1118.719f, -612.4344f, 56.74827f,0.0f),
        Mod_Class::Vector4(1124.979f, -604.9899f, 56.74682f,0.0f),
        Mod_Class::Vector4(1139.324f, -591.7932f, 56.75398f,0.0f),
        Mod_Class::Vector4(1142.248f, -582.8869f, 56.75351f,0.0f),
        Mod_Class::Vector4(1133.203f, -563.3502f, 56.99999f,0.0f),
        Mod_Class::Vector4(1125.851f, -551.4424f, 56.93082f,0.0f),
        Mod_Class::Vector4(1105.572f, -540.5275f, 57.76503f,0.0f),
        Mod_Class::Vector4(1105.599f, -540.5577f, 57.76052f,0.0f),
        Mod_Class::Vector4(1100.637f, -540.5255f, 57.95548f,0.0f),
        Mod_Class::Vector4(1100.362f, -527.494f, 63.07243f,0.0f),
        Mod_Class::Vector4(1073.51f, -530.7902f, 62.03668f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger17 = {
        Mod_Class::Vector4(1163.911f, 280.2455f, 82.19042f,0.0f),
        Mod_Class::Vector4(991.5728f, -11.44712f, 81.85177f,0.0f),
        Mod_Class::Vector4(993.7879f, -40.10574f, 81.92294f,0.0f),
        Mod_Class::Vector4(1011.639f, -65.61469f, 82.19008f,0.0f),
        Mod_Class::Vector4(1038.523f, -82.89301f, 82.19008f,0.0f),
        Mod_Class::Vector4(1072.831f, -82.7739f, 82.16786f,0.0f),
        Mod_Class::Vector4(1095.682f, -69.53146f, 82.08484f,0.0f),
        Mod_Class::Vector4(1265.938f, 178.9096f, 81.98807f,0.0f),
        Mod_Class::Vector4(1273.632f, 195.978f, 81.91003f,0.0f),
        Mod_Class::Vector4(1274.658f, 222.6223f, 81.90385f,0.0f),
        Mod_Class::Vector4(1261.318f, 257.1254f, 82.07339f,0.0f),
        Mod_Class::Vector4(1235.155f, 278.5591f, 82.08091f,0.0f),
        Mod_Class::Vector4(1209.412f, 284.0538f, 82.0095f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger18 = {
        Mod_Class::Vector4(2493.767f, -317.9808f, 92.99265f,0.0f),
        Mod_Class::Vector4(2465.75f, -331.269f, 92.99268f,0.0f),
        Mod_Class::Vector4(2445.703f, -353.545f, 92.98891f,0.0f),
        Mod_Class::Vector4(2446.853f, -417.4889f, 92.99274f,0.0f),
        Mod_Class::Vector4(2474.773f, -444.7306f, 92.99303f,0.0f),
        Mod_Class::Vector4(2480.923f, -437.5063f, 92.99287f,0.0f),
        Mod_Class::Vector4(2479.751f, -420.7701f, 93.73516f,0.0f),
        Mod_Class::Vector4(2481.842f, -406.8932f, 93.73528f,0.0f),
        Mod_Class::Vector4(2494.202f, -390.2369f, 94.11994f,0.0f),
        Mod_Class::Vector4(2493.491f, -374.688f, 94.11996f,0.0f),
        Mod_Class::Vector4(2481.127f, -358.7106f, 93.73526f,0.0f),
        Mod_Class::Vector4(2481.344f, -341.2011f, 93.00871f,0.0f),
        Mod_Class::Vector4(2480.642f, -324.369f, 92.99266f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger19 = {
        Mod_Class::Vector4(1443.998f, 1032.925f, 114.2406f,0.0f),
        Mod_Class::Vector4(1507.861f, 1033.247f, 114.2185f,0.0f),
        Mod_Class::Vector4(1514.412f, 1043.134f, 114.2258f,0.0f),
        Mod_Class::Vector4(1514.912f, 1101.076f, 114.2287f,0.0f),
        Mod_Class::Vector4(1502.632f, 1178.213f, 114.2156f,0.0f),
        Mod_Class::Vector4(1484.8f, 1185.216f, 114.1505f,0.0f),
        Mod_Class::Vector4(1434.625f, 1186.282f, 114.1913f,0.0f),
        Mod_Class::Vector4(1433.847f, 1092.753f, 114.2267f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger20 = {
        Mod_Class::Vector4(2692.736f, 1705.75f, 24.68079f,0.0f),
        Mod_Class::Vector4(2806.105f, 1705.584f, 24.68113f,0.0f),
        Mod_Class::Vector4(2818.727f, 1704.424f, 24.69106f,0.0f),
        Mod_Class::Vector4(2823.846f, 1699.423f, 24.71452f,0.0f),
        Mod_Class::Vector4(2824.438f, 1696.413f, 24.69556f,0.0f),
        Mod_Class::Vector4(2824.696f, 1647.154f, 24.64242f,0.0f),
        Mod_Class::Vector4(2782.65f, 1647.183f, 24.60208f,0.0f),
        Mod_Class::Vector4(2780.294f, 1653.693f, 24.53028f,0.0f),
        Mod_Class::Vector4(2711.461f, 1654.09f, 24.53372f,0.0f),
        Mod_Class::Vector4(2711.587f, 1647.229f, 24.60396f,0.0f),
        Mod_Class::Vector4(2698.269f, 1646.656f, 24.60472f,0.0f),
        Mod_Class::Vector4(2695.426f, 1649.674f, 24.61012f,0.0f),
        Mod_Class::Vector4(2694.013f, 1653.814f, 24.62069f,0.0f),
        Mod_Class::Vector4(2694.363f, 1691.255f, 24.69635f,0.0f),
        Mod_Class::Vector4(2696.989f, 1695.163f, 24.7006f,0.0f),
        Mod_Class::Vector4(2702.095f, 1696.548f, 24.66678f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger21 = {
        Mod_Class::Vector4(1623.121f, 3228.294f, 40.41154f,0.0f),
        Mod_Class::Vector4(1548.318f, 3147.528f, 40.53161f,0.0f),
        Mod_Class::Vector4(1099.019f, 3015.776f, 40.56151f,0.0f),
        Mod_Class::Vector4(1074.616f, 3035.108f, 41.24891f,0.0f),
        Mod_Class::Vector4(1085.017f, 3076.249f, 40.42923f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger22 = {
        Mod_Class::Vector4(1090.78f, 3566.191f, 34.09589f,0.0f),
        Mod_Class::Vector4(1091.477f, 3610.838f, 33.05823f,0.0f),
        Mod_Class::Vector4(1047.076f, 3610.903f, 33.11738f,0.0f),
        Mod_Class::Vector4(1012.615f, 3597.394f, 33.21322f,0.0f),
        Mod_Class::Vector4(1017.906f, 3568.242f, 33.92956f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger23 = {
        Mod_Class::Vector4(73.27388f, 3633.642f, 39.70792f,0.0f),
        Mod_Class::Vector4(27.01976f, 3700.822f, 39.70713f,0.0f),
        Mod_Class::Vector4(28.15174f, 3713.856f, 39.71289f,0.0f),
        Mod_Class::Vector4(35.53751f, 3726.467f, 39.65743f,0.0f),
        Mod_Class::Vector4(73.20634f, 3740.686f, 39.71008f,0.0f),
        Mod_Class::Vector4(83.90422f, 3739.935f, 39.69468f,0.0f),
        Mod_Class::Vector4(99.68319f, 3726.861f, 39.67576f,0.0f),
        Mod_Class::Vector4(102.9181f, 3719.429f, 39.70041f,0.0f),
        Mod_Class::Vector4(82.71038f, 3679.274f, 39.71919f,0.0f),
        Mod_Class::Vector4(81.40222f, 3636.785f, 39.69534f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger24 = {
        Mod_Class::Vector4(1041.883f, 2191.695f, 44.96709f,0.0f),
        Mod_Class::Vector4(1066.888f, 2213.252f, 46.80863f,0.0f),
        Mod_Class::Vector4(1031.368f, 2213.759f, 51.05772f,0.0f),
        Mod_Class::Vector4(989.4823f, 2218.621f, 47.55013f,0.0f),
        Mod_Class::Vector4(997.8649f, 2204.891f, 46.05443f,0.0f),
        Mod_Class::Vector4(1021.423f, 2190.472f, 45.28568f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger25 = {
        Mod_Class::Vector4(2440.191f, 4837.629f, 36.53263f,0.0f),
        Mod_Class::Vector4(2428.567f, 4921.247f, 43.66103f,0.0f),
        Mod_Class::Vector4(2472.179f, 4965.375f, 45.16649f,0.0f),
        Mod_Class::Vector4(2480.896f, 4990.179f, 46.22219f,0.0f),
        Mod_Class::Vector4(2478.137f, 5002.943f, 45.85592f,0.0f),
        Mod_Class::Vector4(2466.199f, 5016.405f, 45.56878f,0.0f),
        Mod_Class::Vector4(2416.468f, 4969.382f, 46.13856f,0.0f),
        Mod_Class::Vector4(2386.791f, 4938.182f, 42.70732f,0.0f),
        Mod_Class::Vector4(2363.594f, 4912.43f, 41.9899f,0.0f),
        Mod_Class::Vector4(2373.377f, 4895.569f, 41.92224f,0.0f),
        Mod_Class::Vector4(2394.373f, 4874.57f, 40.84945f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger26 = {
        Mod_Class::Vector4(234.6885f, 6418.486f, 30.96218f,0.0f),
        Mod_Class::Vector4(248.8196f, 6415.337f, 31.88116f,0.0f),
        Mod_Class::Vector4(269.739f, 6414.965f, 32.11745f,0.0f),
        Mod_Class::Vector4(288.8002f, 6420.939f, 31.35575f,0.0f),
        Mod_Class::Vector4(298.797f, 6432.084f, 31.80929f,0.0f),
        Mod_Class::Vector4(301.9339f, 6444.203f, 32.29673f,0.0f),
        Mod_Class::Vector4(306.1744f, 6493.814f, 29.37009f,0.0f),
        Mod_Class::Vector4(250.2143f, 6489.353f, 30.67807f,0.0f),
        Mod_Class::Vector4(171.8803f, 6482.01f, 31.94304f,0.0f),
        Mod_Class::Vector4(175.2863f, 6475.943f, 31.89293f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger27 = {
        Mod_Class::Vector4(157.3289f, 7044.97f, 1.865713f,0.0f),
        Mod_Class::Vector4(102.7529f, 7073.901f, 1.931986f,0.0f),
        Mod_Class::Vector4(52.24357f, 7079.25f, 2.17193f,0.0f),
        Mod_Class::Vector4(23.56722f, 7052.823f, 1.409035f,0.0f),
        Mod_Class::Vector4(31.16364f, 7023.305f, 7.387625f,0.0f),
        Mod_Class::Vector4(41.1493f, 7013.06f, 8.625368f,0.0f),
        Mod_Class::Vector4(36.24067f, 6995.254f, 8.021345f,0.0f),
        Mod_Class::Vector4(73.45621f, 6951.467f, 11.52127f,0.0f),
        Mod_Class::Vector4(76.90339f, 6968.756f, 10.14844f,0.0f),
        Mod_Class::Vector4(96.15324f, 6976.542f, 9.490364f,0.0f),
        Mod_Class::Vector4(144.0458f, 6980.392f, 8.019959f,0.0f),
        Mod_Class::Vector4(157.614f, 6990.637f, 4.969121f,0.0f),
        Mod_Class::Vector4(158.9223f, 7011.254f, 3.681879f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger28 = {
        Mod_Class::Vector4(-576.4569f, 5452.922f, 60.71923f,0.0f),
        Mod_Class::Vector4(-560.6669f, 5474.996f, 61.77381f,0.0f),
        Mod_Class::Vector4(-552.685f, 5494.2f, 59.80086f,0.0f),
        Mod_Class::Vector4(-550.2758f, 5515.276f, 59.87648f,0.0f),
        Mod_Class::Vector4(-572.0354f, 5544.016f, 52.74706f,0.0f),
        Mod_Class::Vector4(-601.4049f, 5515.799f, 49.60851f,0.0f),
        Mod_Class::Vector4(-620.7578f, 5506.275f, 51.13645f,0.0f),
        Mod_Class::Vector4(-634.4025f, 5477.448f, 53.29848f,0.0f),
        Mod_Class::Vector4(-637.6897f, 5453.631f, 52.85682f,0.0f),
        Mod_Class::Vector4(-595.5697f, 5458.982f, 59.10485f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger29 = {
        Mod_Class::Vector4(-334.3983f, 6183.464f, 31.42284f,0.0f),
        Mod_Class::Vector4(-305.0548f, 6212.236f, 31.45675f,0.0f),
        Mod_Class::Vector4(-302.0125f, 6213.075f, 31.39697f,0.0f),
        Mod_Class::Vector4(-284.0596f, 6234.494f, 31.49339f,0.0f),
        Mod_Class::Vector4(-237.9272f, 6281.979f, 31.45799f,0.0f),
        Mod_Class::Vector4(-252.1601f, 6297.677f, 31.45717f,0.0f),
        Mod_Class::Vector4(-301.6298f, 6251.044f, 31.51244f,0.0f),
        Mod_Class::Vector4(-305.8697f, 6247.805f, 31.43438f,0.0f),
        Mod_Class::Vector4(-318.1996f, 6232.045f, 31.48331f,0.0f),
        Mod_Class::Vector4(-322.5253f, 6227.77f, 31.46884f,0.0f),
        Mod_Class::Vector4(-360.4957f, 6191.922f, 31.48243f,0.0f)
    };
    inline const std::vector<Mod_Class::Vector4> Jogger30 = {
        Mod_Class::Vector4(-1445.911f, 4228.153f, 49.88695f,0.0f),
        Mod_Class::Vector4(-1437.855f, 4232.769f, 48.72689f,0.0f),
        Mod_Class::Vector4(-1414.334f, 4225.317f, 42.9243f,0.0f),
        Mod_Class::Vector4(-1406.202f, 4234.257f, 39.57491f,0.0f),
        Mod_Class::Vector4(-1398.107f, 4235.384f, 37.1693f,0.0f),
        Mod_Class::Vector4(-1381.473f, 4242.933f, 32.96693f,0.0f),
        Mod_Class::Vector4(-1379.1f, 4227.457f, 27.85471f,0.0f),
        Mod_Class::Vector4(-1375.508f, 4221.704f, 26.20435f,0.0f),
        Mod_Class::Vector4(-1371.023f, 4221.62f, 24.55573f,0.0f),
        Mod_Class::Vector4(-1369.318f, 4234.283f, 21.74896f,0.0f),
        Mod_Class::Vector4(-1365.844f, 4237.374f, 20.58922f,0.0f),
        Mod_Class::Vector4(-1362.55f, 4222.789f, 18.0125f,0.0f),
        Mod_Class::Vector4(-1357.766f, 4223.158f, 16.33216f,0.0f),
        Mod_Class::Vector4(-1355.488f, 4230.613f, 14.08321f,0.0f),
        Mod_Class::Vector4(-1349.775f, 4261.309f, 7.204568f,0.0f),
        Mod_Class::Vector4(-1350.807f, 4280.167f, 3.489815f,0.0f),
        Mod_Class::Vector4(-1366.992f, 4291.422f, 2.879005f,0.0f),
        Mod_Class::Vector4(-1375.258f, 4295.798f, 2.808748f,0.0f),
        Mod_Class::Vector4(-1409.907f, 4301.811f, 5.031199f,0.0f),
        Mod_Class::Vector4(-1511.659f, 4307.015f, 5.628844f,0.0f),
        Mod_Class::Vector4(-1585.516f, 4343.747f, 3.159351f,0.0f),
        Mod_Class::Vector4(-1610.404f, 4373.366f, 2.441379f,0.0f),
        Mod_Class::Vector4(-1644.269f, 4431.979f, 3.232418f,0.0f),
        Mod_Class::Vector4(-1677.754f, 4452.332f, 2.484089f,0.0f),
        Mod_Class::Vector4(-1734.826f, 4452.425f, 4.763266f,0.0f),
        Mod_Class::Vector4(-1783.387f, 4475.105f, 11.17609f,0.0f),
        Mod_Class::Vector4(-1815.323f, 4479.708f, 17.87292f,0.0f),
        Mod_Class::Vector4(-1842.674f, 4500.0f, 22.1328f,0.0f),
        Mod_Class::Vector4(-1855.061f, 4500.765f, 22.36915f,0.0f),
        Mod_Class::Vector4(-1878.805f, 4481.325f, 26.10547f,0.0f),
        Mod_Class::Vector4(-1912.77f, 4482.177f, 29.16429f,0.0f),
        Mod_Class::Vector4(-1927.905f, 4460.231f, 34.65511f,0.0f),
        Mod_Class::Vector4(-1905.194f, 4437.292f, 42.7122f,0.0f),
        Mod_Class::Vector4(-1870.033f, 4417.005f, 48.25819f,0.0f),
        Mod_Class::Vector4(-1739.497f, 4344.018f, 62.30252f,0.0f),
        Mod_Class::Vector4(-1701.276f, 4303.689f, 69.18857f,0.0f),
        Mod_Class::Vector4(-1659.563f, 4215.886f, 82.93988f,0.0f),
        Mod_Class::Vector4(-1637.42f, 4205.126f, 84.06075f,0.0f),
        Mod_Class::Vector4(-1587.657f, 4200.398f, 81.1502f,0.0f),
        Mod_Class::Vector4(-1567.076f, 4205.095f, 78.5675f,0.0f),
        Mod_Class::Vector4(-1566.948f, 4205.121f, 78.53695f,0.0f),
        Mod_Class::Vector4(-1489.583f, 4226.147f, 57.02686f,0.0f),
        Mod_Class::Vector4(-1461.699f, 4225.801f, 52.18763f,0.0f)
    };

    inline std::vector<std::string> PrePed_01 = {};
    inline std::vector<std::string> PrePed_02 = {};
    inline std::vector<std::string> PrePed_03 = {};
    inline std::vector<std::string> PrePed_04 = {};
    inline std::vector<std::string> PrePed_05 = {};
    inline std::vector<std::string> PrePed_06 = {};
    inline std::vector<std::string> PrePed_07 = {};
    inline std::vector<std::string> PrePed_08 = {};
    inline std::vector<std::string> PrePed_09 = {};
    inline std::vector<std::string> PrePed_10 = {};
    inline std::vector<std::string> PrePed_11 = {};
    inline std::vector<std::string> PrePed_12 = {};
    inline std::vector<std::string> PrePed_13 = {};
    inline std::vector<std::string> PrePed_14 = {};
    inline std::vector<std::string> PrePed_15 = {};

    inline std::vector<std::string> PreVeh_01 = {};
    inline std::vector<std::string> PreVeh_02 = {};
    inline std::vector<std::string> PreVeh_03 = {};
    inline std::vector<std::string> PreVeh_04 = {};
    inline const std::vector<std::string> PreVeh_05 = {
        "BULLDOZER",  //
        "UTILLITRUCK",  //<!-- Utility Truck cherry picker variant -->
        "UTILLITRUCK2",  //<!-- Utility Truck flatbed variant -->
        "UTILLITRUCK3",  //<!-- Utility Truck pick-up variant -->
        "RUBBLE",  //
        "TIPTRUCK",  //<!-- Tipper 4-wheel variant -->
        "TIPTRUCK2",  //<!-- Tipper 6-wheel variant -->
        "MIXER",  //
        "MIXER2"  //<!-- Mixer 8-wheel variant -->
    };
    inline const std::vector<std::string> PreVeh_06 = {
        "BENSON",  //
        "BIFF",  //
        "FLATBED",  //
        "HAULER",  //
        "HAULER2",  //<!-- Hauler Custom -->
        "MULE",  //
        "MULE2",  //<!-- Mule ramp door variant -->
        "PACKER",  //
        "PHANTOM",  //
        "POUNDER",  //
        "POUNDER2",  //<!-- Pounder Custom -->
        "benson2", //  Commercial
        "phantom4", // Commercial
        "towtruck3", // Utility
        "towtruck4" // Utility
    };
    inline const std::vector<std::string> PreVeh_07 = {
        "BF400",  //
        "MANCHEZ",  //
        "MANCHEZ2",  //<!-- Manchez Scout -->
        "MANCHEZ3",  //<!-- Manchez Scout C -->
        "SANCHEZ",  //<!-- Sanchez livery variant -->
        "SANCHEZ2",  //
        "BLAZER",  //
        "BLAZER3",  //<!-- Hot Rod Blazer -->
        "BLAZER4"  //<!-- Street Blazer -->
    };
    inline const std::vector<std::string> PreVeh_08 = {
        "FBI",  //<!-- FIB Buffalo -->
        "FBI2",  //<!-- FIB Granger -->
        "POLICE4",  //<!-- Unmarked Cruiser -->
        "FIRETRUK",  //
        "POLICEB",  //<!-- Police Bike -->
        "PRANGER",  //<!-- Park Ranger -->
        "SHERIFF",  //<!-- Sheriff Cruiser -->
        "SHERIFF2"  //<!-- Sheriff SUV -->
        "POLICE2",  //<!-- Police Cruiser Buffalo -->
        "POLICE",  //<!-- Police Cruiser Stanier -->
        "POLICE3",  //<!-- Police Cruiser Interceptor -->
        "POLICET",  //<!-- Police Transporter -->
        "RIOT"  //<!-- Police Riot -->
    };
    inline const std::vector<std::string> PreVeh_09 = {
        "APC",  //
        "BARRACKS",  //
        "BARRACKS2",  //<!-- Barracks Semi -->
        "BARRAGE",  //
        "CHERNOBOG",  //
        "CRUSADER",  //
        "HALFTRACK",  //
        "RHINO",  //
        "KHANJALI",  //<!-- TM-02 Khanjali -->
        "VETIR"  //
    };
    inline std::vector<std::string> PreVeh_10 = {};
    inline std::vector<std::string> PreVeh_11 = {};
    inline const std::vector<std::string> PreVeh_12 = {
        "ASEA2",  //<!-- Asea North Yankton variant -->
        "EMPEROR3",  //<!-- Emperor North Yankton variant -->
        "RANCHERXL2",  //<!-- Rancher XL North Yankton variant -->
        "SADLER2",  //<!-- Sadler North Yankton variant -->
    };
    inline const std::vector<std::string> PreVeh_13 = {
        "MANCHEZ2",  //<!-- Manchez Scout -->
        "MANCHEZ3",  //<!-- Manchez Scout C -->
        "VETIR",  //
        "JUBILEE",  //
        "WINKY",  //
        "BRIOSO2",  //<!-- Brioso 300 -->
        "WEEVIL",  //
        "SQUADDIE",
        "VERUS",  //
    };

    inline const std::vector<Mod_Class::Vector4> Yankton = {
        Mod_Class::Vector4(3117.137f, -4816.728f, 111.9227f, 212.9807f),
        Mod_Class::Vector4(3131.799f, -4836.524f, 111.9058f, 198.7815f),
        Mod_Class::Vector4(3148.702f, -4820.137f, 111.9146f, 249.9113f),
        Mod_Class::Vector4(3178.172f, -4841.895f, 111.8646f, 299.6696f),
        Mod_Class::Vector4(3200.373f, -4845.981f, 112.0913f, 247.4838f),
        Mod_Class::Vector4(3223.586f, -4843.15f, 112.1707f, 354.5657f),
        Mod_Class::Vector4(3181.008f, -4819.975f, 112.0145f, 190.3557f),
        Mod_Class::Vector4(3222.215f, -4674.802f, 112.8715f, 197.025f),
        Mod_Class::Vector4(3243.955f, -4668.963f, 115.2206f, 181.1275f),
        Mod_Class::Vector4(3257.933f, -4610.864f, 115.9861f, 343.0366f),
        Mod_Class::Vector4(3264.459f, -4588.892f, 117.5749f, 173.6842f),
        Mod_Class::Vector4(3260.968f, -4558.606f, 117.9432f, 248.7276f),
        Mod_Class::Vector4(3301.682f, -4618.307f, 115.9189f, 4.819291f),
        Mod_Class::Vector4(3280.166f, -4648.12f, 114.2587f, 82.46803f),
        Mod_Class::Vector4(3279.144f, -4831.918f, 111.9073f, 182.5369f),
        Mod_Class::Vector4(3328.324f, -4854.863f, 112.1375f, 98.93055f),
        Mod_Class::Vector4(3473.881f, -4887.713f, 111.4212f, 351.9137f),
        Mod_Class::Vector4(3582.752f, -4877.548f, 111.9127f, 47.78808f),
        Mod_Class::Vector4(3548.751f, -4651.457f, 114.1456f, 240.0113f),
        Mod_Class::Vector4(3557.25f, -4684.192f, 114.5897f, 102.8192f),
        Mod_Class::Vector4(3505.793f, -4675.259f, 114.1213f, 311.8708f),
        Mod_Class::Vector4(3639.636f, -4895.301f, 112.0969f, 213.9055f),
        Mod_Class::Vector4(3658.735f, -4887.635f, 112.0766f, 290.1415f),
        Mod_Class::Vector4(5437.08f, -5181.434f, 78.71245f, 62.03126f),
        Mod_Class::Vector4(5344.413f, -5225.215f, 82.7921f, 316.0345f),
        Mod_Class::Vector4(5343.557f, -5199.927f, 83.26007f, 262.4173f),
        Mod_Class::Vector4(5339.12f, -5215.233f, 82.6674f, 257.5849f),
        Mod_Class::Vector4(5308.893f, -5221.452f, 83.51344f, 190.0524f),
        Mod_Class::Vector4(5295.236f, -5211.909f, 82.74987f, 152.9725f),
        Mod_Class::Vector4(5291.073f, -5192.674f, 83.51875f, 69.66159f),
        Mod_Class::Vector4(5309.561f, -5172.745f, 83.5139f, 275.4609f),
        Mod_Class::Vector4(5321.748f, -5176.215f, 83.23198f, 267.6423f),
        Mod_Class::Vector4(5322.566f, -5195.457f, 83.51897f, 273.5714f)
    };
    inline const std::vector<Mod_Class::Vector4> CayoSpPoint = {
            Mod_Class::Vector4(4877.928f, -4488.06f, 26.93383f, 7.88381f),
            Mod_Class::Vector4(5032.213f, -4630.636f, 21.68462f, 75.61213f),
            Mod_Class::Vector4(5153.693f, -4933.251f, 30.87342f, 142.8952f),
            Mod_Class::Vector4(5148.306f, -5053.395f, 20.39156f, 85.7536f),
            Mod_Class::Vector4(5465.802f, -5236.399f, 43.96178f, 184.7819f),
            Mod_Class::Vector4(5360.864f, -5437.077f, 66.17649f, 221.3451f),
            Mod_Class::Vector4(5125.446f, -5526.457f, 70.9704f, 199.5584f),
            Mod_Class::Vector4(4887.5f, -5458.02f, 47.52377f, 182.3656f),
            Mod_Class::Vector4(5042.819f, -5114.771f, 22.94463f, 88.81671f),
            Mod_Class::Vector4(5140.625f, -5243.813f, 26.29192f, 253.1926f),
            Mod_Class::Vector4(4494.132f, -4525.502f, 4.412366f, 282.329f),
            Mod_Class::Vector4(4439.948f, -4454.131f, 4.328461f, 198.5052f),
            Mod_Class::Vector4(4495.687f, -4732.734f, 10.90475f, 41.29239f),
            Mod_Class::Vector4(4366.333f, -4573.288f, 4.207751f, 21.11482f),
            Mod_Class::Vector4(4071.851f, -4673.698f, 4.223663f, 108.1717f),
            Mod_Class::Vector4(3906.395f, -4702.547f, 4.345607f, 33.34339f),
            Mod_Class::Vector4(4811.667f, -4303.64f, 5.325986f, 52.86508f),
            Mod_Class::Vector4(4877.05f, -4484.966f, 10.15364f, 338.2997f),
            Mod_Class::Vector4(5171.623f, -4591.228f, 3.701788f, 81.79738f),
            Mod_Class::Vector4(5166.074f, -4653.924f, 2.689936f, 241.2462f),
            Mod_Class::Vector4(5166.617f, -4710.746f, 2.160436f, 188.2125f),
            Mod_Class::Vector4(5135.673f, -4606.935f, 2.663276f, 196.01f),
            Mod_Class::Vector4(5064.55f, -4595.777f, 2.853349f, 353.9287f),
            Mod_Class::Vector4(5091.98f, -4654.807f, 1.841831f, 249.8059f),
            Mod_Class::Vector4(5087.485f, -4681.362f, 2.364768f, 222.4894f),
            Mod_Class::Vector4(5031.378f, -4628.378f, 21.68462f, 84.22202f),
            Mod_Class::Vector4(4874.386f, -4927.992f, 3.147279f, 90.48167f),
            Mod_Class::Vector4(4902.145f, -4941.349f, 3.361645f, 209.0067f),
            Mod_Class::Vector4(4891.903f, -4910.392f, 3.365285f, 325.3576f),
            Mod_Class::Vector4(5088.147f, -4892.757f, 17.07693f, 141.0943f),
            Mod_Class::Vector4(5147.582f, -4955.208f, 14.1842f, 306.4781f),
            Mod_Class::Vector4(5191.797f, -5010.228f, 13.95532f, 309.4144f),
            Mod_Class::Vector4(5441.739f, -5116.977f, 13.17772f, 114.4946f),
            Mod_Class::Vector4(5587.902f, -5222.841f, 14.35066f, 227.1182f),
            Mod_Class::Vector4(5468.49f, -5237.662f, 43.96177f, 286.5111f),
            Mod_Class::Vector4(5402.339f, -5173.656f, 31.43869f, 250.9344f),
            Mod_Class::Vector4(5330.212f, -5266.004f, 32.50994f, 146.6625f),
            Mod_Class::Vector4(5263.13f, -5254.454f, 25.44569f, 169.5686f),
            Mod_Class::Vector4(5264.313f, -5430.777f, 65.5978f, 252.7824f),
            Mod_Class::Vector4(5221.144f, -5394.252f, 67.51835f, 9.77068f),
            Mod_Class::Vector4(5311.626f, -5595.218f, 64.44119f, 167.3269f),
            Mod_Class::Vector4(5484.578f, -5854.652f, 20.01427f, 203.205f),
            Mod_Class::Vector4(5105.451f, -5523.863f, 54.20301f, 293.2558f),
            Mod_Class::Vector4(5125.341f, -5526.231f, 70.97034f, 137.1469f),
            Mod_Class::Vector4(5099.011f, -5722.109f, 15.77461f, 117.5884f),
            Mod_Class::Vector4(4979.47f, -5708.737f, 19.88695f, 58.10868f),
            Mod_Class::Vector4(4990.638f, -5883.896f, 20.55511f, 220.5347f),
            Mod_Class::Vector4(4908.758f, -5833.568f, 28.21668f, 356.1158f),
            Mod_Class::Vector4(4964.564f, -5603.83f, 23.72427f, 196.7985f),
            Mod_Class::Vector4(4887.661f, -5460.129f, 30.74339f, 230.2796f),
            Mod_Class::Vector4(4904.563f, -5342.741f, 20.43572f, 167.6105f),
            Mod_Class::Vector4(4954.223f, -5320.233f, 8.177876f, 45.14056f),
            Mod_Class::Vector4(4893.883f, -5287.493f, 8.498549f, 76.56836f),
            Mod_Class::Vector4(4963.055f, -5282.41f, 6.153166f, 150.0025f),
            Mod_Class::Vector4(4919.834f, -5236.972f, 2.522677f, 214.5785f),
            Mod_Class::Vector4(4837.975f, -5177.048f, 2.194079f, 309.8742f),
            Mod_Class::Vector4(4887.364f, -5170.045f, 2.462478f, 317.8425f),
            Mod_Class::Vector4(4934.43f, -5176.531f, 2.460481f, 47.9263f),
            Mod_Class::Vector4(4994.617f, -5166.621f, 2.692156f, 290.538f),
            Mod_Class::Vector4(4959.891f, -5112.796f, 2.906743f, 325.6087f),
            Mod_Class::Vector4(5046.526f, -5117.724f, 20.34463f, 242.2283f),
            Mod_Class::Vector4(5111.161f, -5183.47f, 2.368666f, 190.5521f),
            Mod_Class::Vector4(5134.058f, -5127.317f, 2.110643f, 175.9367f),
            Mod_Class::Vector4(5185.667f, -5133.359f, 3.338254f, 261.6295f),
            Mod_Class::Vector4(5214.341f, -5125.928f, 6.22332f, 138.2965f),
            Mod_Class::Vector4(5145.925f, -5043.219f, 4.805843f, 294.0948f),
            Mod_Class::Vector4(5170.325f, -4675.89f, 2.435122f, 66.67837f),
            Mod_Class::Vector4(5179.303f, -4649.774f, 2.530395f, 64.63232f),
            Mod_Class::Vector4(5127.161f, -4613.125f, 2.567649f, 134.3626f),
            Mod_Class::Vector4(5403.269f, -5174.491f, 31.46002f, 30.90309f),
            Mod_Class::Vector4(5408.926f, -5216.411f, 34.45446f, 232.4724f),
            Mod_Class::Vector4(5382.5f, -5255.195f, 34.15533f, 168.2274f),
            Mod_Class::Vector4(5327.994f, -5265.26f, 33.17245f, 216.49f),
            Mod_Class::Vector4(5312.92f, -5200.948f, 31.73465f, 43.35777f),
            Mod_Class::Vector4(5283.029f, -5239.302f, 30.83397f, 226.2264f),
            Mod_Class::Vector4(5211.092f, -5125.889f, 6.214875f, 297.0678f),
            Mod_Class::Vector4(5182.966f, -5148.639f, 3.549981f, 93.57137f),
            Mod_Class::Vector4(5117.133f, -5172.37f, 2.296359f, 90.88295f),
            Mod_Class::Vector4(5012.493f, -5201.086f, 2.517188f, 332.5578f),
            Mod_Class::Vector4(4957.826f, -5133.129f, 2.44458f, 126.1573f),
            Mod_Class::Vector4(4902.437f, -5180.579f, 2.445158f, 256.659f),
            Mod_Class::Vector4(4949.478f, -5319.582f, 8.065354f, 190.8848f),
            Mod_Class::Vector4(5310.973f, -5600.635f, 64.51008f, 298.4847f),
            Mod_Class::Vector4(5018.089f, -5174.079f, 2.606125f, 207.4259f),
            Mod_Class::Vector4(5041.188f, -5117.157f, 22.94859f, 133.7521f),
            Mod_Class::Vector4(4961.709f, -5108.097f, 2.982063f, 336.7988f),
            Mod_Class::Vector4(4873.991f, -5174.502f, 2.438294f, 309.3781f),
            Mod_Class::Vector4(4834.461f, -5175.737f, 2.169081f, 108.4202f),
            Mod_Class::Vector4(4864.909f, -5160.665f, 2.791046f, 272.405f),
            Mod_Class::Vector4(4887.225f, -5181.831f, 2.438293f, 252.0248f),
            Mod_Class::Vector4(4904.118f, -5187.469f, 2.43825f, 338.149f),
            Mod_Class::Vector4(5012.132f, -5199.121f, 2.517245f, 303.1538f),
            Mod_Class::Vector4(5137.046f, -5103.176f, 2.197638f, 165.8812f),
            Mod_Class::Vector4(4996.087f, -5187.851f, 2.523123f, 121.5532f),
            Mod_Class::Vector4(5147.148f, -5053.37f, 20.39559f, 89.6064f),
            Mod_Class::Vector4(5117.839f, -5172.103f, 2.30431f, 57.59507f),
            Mod_Class::Vector4(5133.637f, -5118.043f, 2.113857f, 166.755f),
            Mod_Class::Vector4(4913.793f, -5200.564f, 2.469321f, 213.1365f),
            Mod_Class::Vector4(5142.1f, -5241.874f, 26.29656f, 0.5f),
            Mod_Class::Vector4(4983.042f, -5196.473f, 2.50345f, 123.4069f),
            Mod_Class::Vector4(5133.731f, -5141.614f, 2.147834f, 181.026f),
            Mod_Class::Vector4(5254.448f, -5258.097f, 25.31619f, 129.8113f),
            Mod_Class::Vector4(5212.377f, -5225.483f, 17.39517f, 0.5f),
            Mod_Class::Vector4(5179.297f, -5146.072f, 3.289174f, 86.07165f),
            Mod_Class::Vector4(5213.439f, -5122.497f, 6.122335f, 129.5457f),
            Mod_Class::Vector4(5117.228f, -5149.584f, 2.21032f, 91.92164f),
            Mod_Class::Vector4(5299.635f, -5225.373f, 32.21928f, 100.7981f),
            Mod_Class::Vector4(5217.679f, -5207.616f, 16.40578f, 352.9662f),
            Mod_Class::Vector4(5324.687f, -5262.405f, 32.82066f, 0.5f),
            Mod_Class::Vector4(5220.702f, -5191.855f, 14.355f, 352.4796f),
            Mod_Class::Vector4(5322.195f, -5196.333f, 31.55055f, 230.9573f),
            Mod_Class::Vector4(5401.839f, -5171.006f, 31.39126f, 134.3677f),
            Mod_Class::Vector4(5465.827f, -5235.692f, 43.96646f, 0.5f),
            Mod_Class::Vector4(5565.909f, -5185.084f, 10.92833f, 0.5f),
            Mod_Class::Vector4(5589.67f, -5219.979f, 14.35063f, 286.0875f),
            Mod_Class::Vector4(5596.038f, -5163.533f, -100.5f, 247.9607f),
            Mod_Class::Vector4(4894.263f, -4913.141f, 3.36446f, 4.1f),
            Mod_Class::Vector4(4890.318f, -4923.923f, 3.368097f, 71.5f)
    };
    inline const std::vector<Mod_Class::Vector4> SpPoint = {
        Mod_Class::Vector4(-1160.148f, -1607.229f, 4.282094f, 33.58816f),
        Mod_Class::Vector4(-1246.173f, -1578.978f, 4.075636f, 88.40285f),
        Mod_Class::Vector4(-1300.651f, -1693.796f, 2.652158f, 119.986f),
        Mod_Class::Vector4(-1197.284f, -1673.913f, 4.368378f, 336.6819f),
        Mod_Class::Vector4(-1231.23f, -1774.339f, 2.698436f, 307.819f),
        Mod_Class::Vector4(-1081.606f, -1699.635f, 4.51774f, 341.5313f),
        Mod_Class::Vector4(-1321.38f, -1803.161f, 0.5787229f, 338.6356f),
        Mod_Class::Vector4(-1277.734f, -1796.447f, -100.0f, 190.3f),
        Mod_Class::Vector4(-1329.865f, -1621.267f, 3.853039f, 125.3387f),
        Mod_Class::Vector4(-1368.747f, -1588.793f, 2.370532f, 177.0662f),
        Mod_Class::Vector4(-1380.893f, -1418.045f, 3.565593f, 323.6023f),
        Mod_Class::Vector4(-1279.822f, -1427.41f, 4.510245f, 212.68f),
        Mod_Class::Vector4(-1255.639f, -1592.376f, 4.094669f, 227.7035f),
        Mod_Class::Vector4(-1224.641f, -1502.119f, 4.337264f, 236.9933f),
        Mod_Class::Vector4(-1431.731f, -1508.598f, 3.715238f, 85.04395f),
        Mod_Class::Vector4(-1308.609f, -1529.277f, 4.314957f, 74.17694f),
        Mod_Class::Vector4(-1322.848f, -1734.16f, 1.786219f, 247.0966f),
        Mod_Class::Vector4(-1427.198f, -1658.383f, -0.3996229f, 276.3645f),
        Mod_Class::Vector4(-1270.877f, -1811.516f, 1.774477f, 192.7982f),
        Mod_Class::Vector4(-1178.216f, -1781.372f, 4.050908f, 319.6324f),
        Mod_Class::Vector4(-1153.027f, -1606.098f, 4.380119f, 56.83902f),
        Mod_Class::Vector4(-1109.917f, -1688.4f, 4.375373f, 119.264f),
        Mod_Class::Vector4(-1050.216f, -1619.146f, 4.389634f, 203.3658f),
        Mod_Class::Vector4(-1108.875f, -1527.476f, 6.779634f, 211.7134f),
        Mod_Class::Vector4(-1198.382f, -1673.201f, 4.36664f, 310.3611f),
        Mod_Class::Vector4(-1170.423f, -1433.136f, 4.453862f, 216.7254f),
        Mod_Class::Vector4(-1314.11f, -1352.265f, 4.469654f, 25.83949f),
        Mod_Class::Vector4(-1346.334f, -1276.67f, 4.897387f, 190.3171f),
        Mod_Class::Vector4(-1359.945f, -1193.812f, 4.450387f, 349.2703f),
        Mod_Class::Vector4(-1241.474f, -1253.23f, 5.328512f, 105.528f),
        Mod_Class::Vector4(-1369.884f, -1117.181f, 4.500574f, 260.4205f),
        Mod_Class::Vector4(-1290.337f, -1108.623f, 6.826903f, 50.96396f),
        Mod_Class::Vector4(-1423.398f, -1023.807f, 4.997945f, 239.7593f),
        Mod_Class::Vector4(-1332.74f, -1028.393f, 7.703401f, 32.42556f),
        Mod_Class::Vector4(-1484.517f, -960.1639f, 7.692502f, 45.27397f),
        Mod_Class::Vector4(-1384.187f, -944.0807f, 10.06455f, 333.1175f),
        Mod_Class::Vector4(-1577.719f, -970.7444f, 17.41236f, 134.7335f),
        Mod_Class::Vector4(-1589.911f, -1069.783f, 13.01727f, 66.19942f),
        Mod_Class::Vector4(-1526.156f, -1224.26f, 2.271887f, 198.1657f),
        Mod_Class::Vector4(-1647.783f, -1125.91f, 18.34311f, 226.7262f),
        Mod_Class::Vector4(-1817.684f, -1200.282f, 19.16987f, 272.2027f),
        Mod_Class::Vector4(-1722.691f, -1102.711f, 13.10247f, 232.1385f),
        Mod_Class::Vector4(-1741.421f, -1000.758f, 4.251456f, 283.4004f),
        Mod_Class::Vector4(-1656.441f, -1023.758f, 13.01742f, 134.6409f),
        Mod_Class::Vector4(-1789.288f, -867.3212f, 7.367817f, 26.9756f),
        Mod_Class::Vector4(-1766.264f, -710.6727f, 14.04142f, 128.1337f),
        Mod_Class::Vector4(-1840.649f, -786.7416f, 6.942594f, 209.3775f),
        Mod_Class::Vector4(-1928.198f, -787.6534f, 1.400905f, 124.8805f),
        Mod_Class::Vector4(-1853.948f, -643.4832f, 10.74218f, 51.13507f),
        Mod_Class::Vector4(-1693.429f, -782.542f, 10.15547f, 31.77343f),
        Mod_Class::Vector4(-2019.225f, -671.4921f, 1.732529f, 35.30247f),
        Mod_Class::Vector4(-2073.122f, -556.3633f, 4.322869f, 112.1614f),
        Mod_Class::Vector4(-1918.171f, -581.4932f, 11.82719f, 74.45322f),
        Mod_Class::Vector4(-1941.187f, -683.3286f, 6.042047f, 317.4851f),
        Mod_Class::Vector4(-2017.408f, -403.2584f, 10.99738f, 102.571f),
        Mod_Class::Vector4(-2073.494f, -322.6716f, 13.31618f, 110.8201f),
        Mod_Class::Vector4(-1920.867f, -395.7564f, 48.28661f, 144.3688f),
        Mod_Class::Vector4(-1932.222f, -256.2742f, 39.38351f, 163.2952f),
        Mod_Class::Vector4(-2006.573f, -292.1909f, 31.14633f, 32.56577f),
        Mod_Class::Vector4(-1830.16f, -393.1055f, 57.13855f, 341.9896f),
        Mod_Class::Vector4(-1812.373f, -487.2023f, 40.97498f, 99.4837f),
        Mod_Class::Vector4(-1801.349f, -284.9655f, 42.74314f, 49.44889f),
        Mod_Class::Vector4(-1750.369f, -388.2991f, 49.33112f, 306.9421f),
        Mod_Class::Vector4(-1733.029f, -542.143f, 37.22449f, 46.17191f),
        Mod_Class::Vector4(-1652.144f, -473.3973f, 38.76246f, 156.1328f),
        Mod_Class::Vector4(-1582.329f, -541.8163f, 35.48005f, 318.3726f),
        Mod_Class::Vector4(-1688.893f, -614.0651f, 32.71557f, 160.953f),
        Mod_Class::Vector4(-1590.418f, -652.4891f, 29.94338f, 234.872f),
        Mod_Class::Vector4(-1516.227f, -630.6576f, 29.60688f, 124.8291f),
        Mod_Class::Vector4(-1514.848f, -720.5037f, 27.28335f, 44.38182f),
        Mod_Class::Vector4(-1467.341f, -779.6733f, 23.88621f, 141.6295f),
        Mod_Class::Vector4(-1426.177f, -608.0167f, 30.68489f, 216.1941f),
        Mod_Class::Vector4(-1429.254f, -685.5729f, 30.09999f, 351.6236f),
        Mod_Class::Vector4(-1370.448f, -786.2045f, 19.34618f, 46.06882f),
        Mod_Class::Vector4(-1509.341f, -849.4481f, 23.72846f, 146.3204f),
        Mod_Class::Vector4(-1338.667f, -684.4074f, 25.90955f, 337.9835f),
        Mod_Class::Vector4(-1267.564f, -887.0582f, 11.46313f, 312.6759f),
        Mod_Class::Vector4(-1291.891f, -963.3849f, 10.90977f, 17.93775f),
        Mod_Class::Vector4(-1243.466f, -1037.107f, 8.533915f, 24.88162f),
        Mod_Class::Vector4(-1205.129f, -946.3865f, 8.115028f, 78.52157f),
        Mod_Class::Vector4(-1209.501f, -1145.148f, 7.699383f, 246.5961f),
        Mod_Class::Vector4(-1152.507f, -1092.617f, 2.150213f, 78.05627f),
        Mod_Class::Vector4(-1176.931f, -1326.262f, 5.043202f, 91.40005f),
        Mod_Class::Vector4(-1278.753f, -1280.306f, -100.0f, 286.1835f),
        Mod_Class::Vector4(-280.1419f, -2078.309f, 27.75568f, 120.8461f),
        Mod_Class::Vector4(-362.931f, -2096.714f, -100.0f, 249.8338f),
        Mod_Class::Vector4(-1233.953f, -2060.108f, 14.38426f, 322.4592f),
        Mod_Class::Vector4(-1177.911f, -1969.751f, 12.2126f, 245.5379f),
        Mod_Class::Vector4(-958.8653f, -2038.964f, 9.571634f, 275.1023f),
        Mod_Class::Vector4(-1065.295f, -2082.96f, 13.29153f, 124.204f),
        Mod_Class::Vector4(-1158.608f, -2165.972f, 13.38066f, 105.9783f),
        Mod_Class::Vector4(-990.8157f, -2278.67f, 8.95359f, 230.7598f),
        Mod_Class::Vector4(-878.8334f, -2183.131f, 8.937191f, 216.7394f),
        Mod_Class::Vector4(-891.5108f, -2402.83f, 14.02515f, 147.8056f),
        Mod_Class::Vector4(-893.0229f, -2317.104f, -3.507768f, 8.885142f),
        Mod_Class::Vector4(-978.1707f, -2465.764f, 13.75622f, 149.0023f),
        Mod_Class::Vector4(-900.1584f, -2491.51f, 14.54965f, 27.85674f),
        Mod_Class::Vector4(-1033.629f, -2381.482f, 14.0936f, 173.6633f),
        Mod_Class::Vector4(-955.9147f, -2386.496f, -100.0f, 149.8728f),
        Mod_Class::Vector4(1450.433f, -1731.397f, 68.03314f, 41.98439f),
        Mod_Class::Vector4(1600.253f, -1712.9f, 88.12589f, 185.5337f),
        Mod_Class::Vector4(1568.778f, -1595.55f, 90.31343f, 334.3277f),
        Mod_Class::Vector4(1715.997f, -1560.912f, 112.6362f, 265.2239f),
        Mod_Class::Vector4(1729.931f, -1664.9f, 112.5535f, 55.15057f),
        Mod_Class::Vector4(1677.571f, -1857.563f, 108.353f, 227.1044f),
        Mod_Class::Vector4(1544.524f, -2091.144f, 77.13461f, 115.2182f),
        Mod_Class::Vector4(1397.054f, -2203.803f, 61.26979f, 11.66307f),
        Mod_Class::Vector4(1432.708f, -2318.181f, 66.93765f, 0.1958369f),
        Mod_Class::Vector4(1090.301f, -2258.336f, 30.16828f, 154.4966f),
        Mod_Class::Vector4(1050.76f, -2359.522f, 30.58618f, 359.6519f),
        Mod_Class::Vector4(1257.031f, -2301.23f, 50.42583f, 297.5381f),
        Mod_Class::Vector4(1213.246f, -2201.788f, 41.42298f, 174.4906f),
        Mod_Class::Vector4(1181.73f, -2088.975f, 42.835f, 108.8092f),
        Mod_Class::Vector4(1075.413f, -2130.978f, 32.65754f, 356.5745f),
        Mod_Class::Vector4(1069.265f, -2051.669f, 30.54184f, 328.8749f),
        Mod_Class::Vector4(1253.046f, -1965.152f, 43.31088f, 277.0399f),
        Mod_Class::Vector4(1162.939f, -1835.688f, 37.32333f, 309.8178f),
        Mod_Class::Vector4(1253.974f, -1801.581f, 41.43707f, 101.9945f),
        Mod_Class::Vector4(1165.914f, -1757.395f, 36.09859f, 5.626177f),
        Mod_Class::Vector4(1211.297f, -1635.897f, 46.98957f, 15.0685f),
        Mod_Class::Vector4(1339.797f, -1769.144f, 58.84056f, 110.8002f),
        Mod_Class::Vector4(1299.746f, -1624.184f, 52.31812f, 219.0709f),
        Mod_Class::Vector4(1370.415f, -1683.915f, 59.39519f, 28.85051f),
        Mod_Class::Vector4(1338.409f, -1524.272f, 54.58279f, 175.8651f),
        Mod_Class::Vector4(1264.839f, -1511.525f, 40.75233f, 196.139f),
        Mod_Class::Vector4(1162.592f, -1484.728f, 34.84315f, 45.85416f),
        Mod_Class::Vector4(1215.056f, -1389.57f, 35.3749f, 298.4576f),
        Mod_Class::Vector4(1064.018f, -1447.581f, 36.74253f, 272.2317f),
        Mod_Class::Vector4(962.9564f, -1491.263f, 31.03523f, 283.0984f),
        Mod_Class::Vector4(811.0013f, -1355.856f, 26.39643f, 139.9369f),
        Mod_Class::Vector4(852.3708f, -1452.39f, 28.46454f, 153.5606f),
        Mod_Class::Vector4(782.0834f, -1276.112f, 26.38883f, 245.5533f),
        Mod_Class::Vector4(708.6996f, -1387.042f, 26.28415f, 95.50644f),
        Mod_Class::Vector4(729.1082f, -1202.147f, 27.59183f, 314.4826f),
        Mod_Class::Vector4(866.4579f, -1218.872f, 25.93666f, 150.9242f),
        Mod_Class::Vector4(812.4778f, -1108.296f, 22.87424f, 358.1263f),
        Mod_Class::Vector4(805.5677f, -992.9066f, 26.17185f, 93.29649f),
        Mod_Class::Vector4(719.1799f, -1068.157f, 22.22762f, 76.04496f),
        Mod_Class::Vector4(867.8777f, -949.1575f, 26.28246f, 284.0382f),
        Mod_Class::Vector4(799.3265f, -910.1976f, 25.25154f, 64.5854f),
        Mod_Class::Vector4(788.2667f, -779.5413f, 26.43379f, 76.76219f),
        Mod_Class::Vector4(676.5705f, -893.8166f, 23.46652f, 48.36354f),
        Mod_Class::Vector4(792.6351f, -680.9716f, 28.78763f, 182.0778f),
        Mod_Class::Vector4(712.2411f, -718.2731f, 26.09179f, 222.572f),
        Mod_Class::Vector4(871.4885f, -477.5969f, 57.6135f, 27.29279f),
        Mod_Class::Vector4(802.2733f, -487.6502f, 29.98962f, 66.31482f),
        Mod_Class::Vector4(762.3665f, -605.8344f, 29.01363f, 289.0056f),
        Mod_Class::Vector4(647.2089f, -405.4547f, 25.90333f, 141.224f),
        Mod_Class::Vector4(793.6388f, -251.5794f, 66.11258f, 262.0274f),
        Mod_Class::Vector4(740.2285f, -348.7549f, 44.64523f, 102.3112f),
        Mod_Class::Vector4(842.9829f, -326.1672f, 58.63135f, 78.39604f),
        Mod_Class::Vector4(774.1849f, -157.5243f, 74.47166f, 194.3f),
        Mod_Class::Vector4(717.7997f, -231.8359f, 66.49796f, 145.0598f),
        Mod_Class::Vector4(879.2205f, -133.0256f, 78.19176f, 321.4662f),
        Mod_Class::Vector4(954.9133f, -139.376f, 74.48351f, 261.024f),
        Mod_Class::Vector4(770.9991f, -20.69291f, 81.40639f, 55.6139f),
        Mod_Class::Vector4(918.6093f, -299.0002f, 65.7274f, 89.47182f),
        Mod_Class::Vector4(1075.878f, -221.7357f, 57.22911f, 100.7295f),
        Mod_Class::Vector4(1167.627f, -326.1849f, 69.27177f, 253.1378f),
        Mod_Class::Vector4(1182.85f, -419.4162f, 67.44855f, 160.1736f),
        Mod_Class::Vector4(1095.917f, -363.7542f, 67.05442f, 154.2719f),
        Mod_Class::Vector4(1241.207f, -370.6926f, 69.08267f, 357.5793f),
        Mod_Class::Vector4(1295.678f, -450.1477f, 69.11702f, 39.42892f),
        Mod_Class::Vector4(1196.354f, -500.0268f, 65.35512f, 239.1896f),
        Mod_Class::Vector4(1244.402f, -565.6254f, 69.36629f, 327.5226f),
        Mod_Class::Vector4(1358.867f, -507.7113f, 74.07481f, 238.6464f),
        Mod_Class::Vector4(1271.949f, -679.5294f, 65.78483f, 221.1033f),
        Mod_Class::Vector4(1170.739f, -673.777f, 60.85263f, 8.802817f),
        Mod_Class::Vector4(1157.536f, -826.6323f, 55.04485f, 261.9964f),
        Mod_Class::Vector4(1229.198f, -774.131f, 59.95905f, 111.6313f),
        Mod_Class::Vector4(1065.049f, -721.359f, 56.7688f, 251.442f),
        Mod_Class::Vector4(961.0184f, -668.5934f, 58.42073f, 252.7814f),
        Mod_Class::Vector4(944.5909f, -590.6015f, 57.93015f, 263.7933f),
        Mod_Class::Vector4(1065.475f, -587.393f, 56.98307f, 176.1875f),
        Mod_Class::Vector4(1087.19f, -483.9626f, 65.1468f, 43.63801f),
        Mod_Class::Vector4(990.569f, -528.5084f, 60.1135f, 187.5177f),
        Mod_Class::Vector4(1029.239f, -420.6697f, 65.71067f, 103.3361f),
        Mod_Class::Vector4(878.2419f, 536.1291f, 125.7603f, 256.0516f),
        Mod_Class::Vector4(780.4013f, 569.2122f, 127.5153f, 308.715f),
        Mod_Class::Vector4(-1652.492f, -268.9684f, 53.03486f, 238.35f),
        Mod_Class::Vector4(-1796.219f, -262.315f, 44.68269f, 225.691f),
        Mod_Class::Vector4(-1862.262f, -346.5329f, 49.84129f, 207.6463f),
        Mod_Class::Vector4(-1746.119f, -373.1069f, 46.04745f, 348.238f),
        Mod_Class::Vector4(-1758.126f, -177.5893f, 59.93489f, 53.74375f),
        Mod_Class::Vector4(-1851.886f, -211.0984f, 39.37838f, 30.06215f),
        Mod_Class::Vector4(-1647.251f, -157.372f, 57.61746f, 114.5786f),
        Mod_Class::Vector4(-1657.056f, -12.40816f, 61.96356f, 225.4638f),
        Mod_Class::Vector4(-1855.837f, 87.75642f, 79.74529f, 317.2931f),
        Mod_Class::Vector4(-2227.431f, 177.6394f, 174.6018f, 246.6147f),
        Mod_Class::Vector4(-2183.896f, 284.1322f, 169.6021f, 263.2045f),
        Mod_Class::Vector4(-2266.481f, 266.8381f, 184.6013f, 236.3674f),
        Mod_Class::Vector4(-2340.92f, 224.7503f, 169.6533f, 147.9599f),
        Mod_Class::Vector4(-2291.11f, 419.6725f, 174.6017f, 269.9671f),
        Mod_Class::Vector4(-2351.723f, 354.5746f, 174.5702f, 316.094f),
        Mod_Class::Vector4(-1992.776f, 597.1656f, 117.9074f, 244.9395f),
        Mod_Class::Vector4(-1918.98f, 427.659f, 102.579f, 288.3187f),
        Mod_Class::Vector4(-1942.294f, 537.5837f, 119.4511f, 71.42182f),
        Mod_Class::Vector4(-1863.526f, 663.243f, 129.1108f, 47.40017f),
        Mod_Class::Vector4(-1950.522f, 671.437f, 126.8631f, 49.11973f),
        Mod_Class::Vector4(-1821.452f, 805.2283f, 138.6922f, 350.8116f),
        Mod_Class::Vector4(-1596.12f, 763.6357f, 188.776f, 67.02236f),
        Mod_Class::Vector4(-1537.647f, 824.0611f, 181.5576f, 132.0971f),
        Mod_Class::Vector4(-1390.973f, 604.0109f, 130.5611f, 103.6059f),
        Mod_Class::Vector4(-1380.87f, 733.273f, 182.4565f, 346.0296f),
        Mod_Class::Vector4(-1273.141f, 606.6987f, 139.2841f, 177.0211f),
        Mod_Class::Vector4(-1208.797f, 648.6027f, 144.6223f, 184.7298f),
        Mod_Class::Vector4(-1187.657f, 561.1202f, 100.0236f, 282.7813f),
        Mod_Class::Vector4(-1061.68f, 732.2233f, 165.4498f, 328.4958f),
        Mod_Class::Vector4(-1123.518f, 796.3937f, 167.7469f, 256.4597f),
        Mod_Class::Vector4(-974.0649f, 689.8514f, 158.0351f, 36.62312f),
        Mod_Class::Vector4(-952.0835f, 799.6948f, 178.4169f, 358.3044f),
        Mod_Class::Vector4(-854.5779f, 790.907f, 191.7423f, 343.4804f),
        Mod_Class::Vector4(-800.5696f, 886.0236f, 203.1893f, 150.7404f),
        Mod_Class::Vector4(-757.3545f, 774.8885f, 212.2914f, 21.35574f),
        Mod_Class::Vector4(-679.4247f, 798.2404f, 198.0051f, 179.3822f),
        Mod_Class::Vector4(-668.9477f, 906.9561f, 230.1238f, 229.8917f),
        Mod_Class::Vector4(-538.2089f, 785.8329f, 196.6117f, 117.694f),
        Mod_Class::Vector4(-398.9189f, 666.7883f, 163.8354f, 90.2931f),
        Mod_Class::Vector4(-510.514f, 671.3224f, 150.273f, 163.8439f),
        Mod_Class::Vector4(-472.1857f, 537.1354f, 124.354f, 0.0f),
        Mod_Class::Vector4(-385.3415f, 515.0933f, 120.8225f, 227.8424f),
        Mod_Class::Vector4(-355.368f, 423.3936f, 110.8382f, 345.9255f),
        Mod_Class::Vector4(-506.4408f, 454.185f, 96.69381f, 276.8076f),
        Mod_Class::Vector4(-245.8695f, 393.0556f, 112.4406f, 260.9666f),
        Mod_Class::Vector4(-60.18164f, 494.9249f, 144.5688f, 247.2409f),
        Mod_Class::Vector4(-88.42611f, 889.886f, 236.1728f, 212.5896f),
        Mod_Class::Vector4(56.37422f, 1050.121f, 218.6296f, 295.7127f),
        Mod_Class::Vector4(-449.0672f, 1062.479f, 327.6815f, 175.8242f),
        Mod_Class::Vector4(-399.2907f, 1148.496f, 325.853f, 200.4087f),
        Mod_Class::Vector4(-480.5667f, 1133.815f, 320.0966f, 190.5652f),
        Mod_Class::Vector4(-294.9129f, 1429.549f, 339.3169f, 336.8831f),
        Mod_Class::Vector4(-407.2495f, 1581.665f, 353.7131f, 73.89459f),
        Mod_Class::Vector4(-149.5202f, 1453.246f, 292.8072f, 199.7669f),
        Mod_Class::Vector4(-266.3375f, 1547.674f, 336.4588f, 141.5186f),
        Mod_Class::Vector4(779.201f, 1187.419f, 325.5869f, 66.41692f),
        Mod_Class::Vector4(307.273f, 1108.102f, 216.9276f, 75.9652f),
        Mod_Class::Vector4(276.0082f, 1187.72f, 226.0305f, 14.18411f),
        Mod_Class::Vector4(191.0497f, 1224.417f, 225.5948f, 106.2378f),
        Mod_Class::Vector4(294.2169f, 953.3748f, 208.6888f, 254.3083f),
        Mod_Class::Vector4(229.4137f, 675.6113f, 189.6827f, 210.8005f),
        Mod_Class::Vector4(221.4684f, 513.708f, 140.7564f, 359.1328f),
        Mod_Class::Vector4(218.7429f, 302.6817f, 105.5856f, 248.4243f),
        Mod_Class::Vector4(336.653f, 312.7571f, 104.6787f, 170.513f),
        Mod_Class::Vector4(127.0963f, 341.097f, 111.944f, 32.08784f),
        Mod_Class::Vector4(2824.941f, -743.6797f, 1.471339f, 16.6061f),
        Mod_Class::Vector4(2835.425f, -626.2703f, 1.730462f, 227.3414f),
        Mod_Class::Vector4(2575.149f, -289.9889f, 93.07821f, 324.0676f),
        Mod_Class::Vector4(2521.409f, -414.0672f, 94.12376f, 222.7773f),
        Mod_Class::Vector4(2571.536f, 304.6294f, 108.6065f, 20.04023f),
        Mod_Class::Vector4(2572.306f, 478.2309f, 108.6772f, 91.36018f),
        Mod_Class::Vector4(2746.039f, 1453.321f, 24.48774f, 299.1059f),
        Mod_Class::Vector4(2757.865f, 1528.199f, 32.49879f, 87.19512f),
        Mod_Class::Vector4(2666.189f, 1508.934f, 24.50084f, 299.6714f),
        Mod_Class::Vector4(2853.234f, 1474.861f, 24.61952f, 107.3717f),
        Mod_Class::Vector4(2720.579f, 1647.611f, 24.57493f, 269.4894f),
        Mod_Class::Vector4(2473.841f, 1572.31f, 32.72038f, 354.3351f),
        Mod_Class::Vector4(2357.949f, 1845.58f, 101.2663f, 166.731f),
        Mod_Class::Vector4(2319.202f, 2551.041f, 47.69345f, 227.7995f),
        Mod_Class::Vector4(2526.939f, 2584.094f, 37.94465f, 8.938714f),
        Mod_Class::Vector4(2595.807f, 2801.963f, 34.00152f, 323.103f),
        Mod_Class::Vector4(2739.255f, 2782.027f, 35.73802f, 303.735f),
        Mod_Class::Vector4(2570.977f, 2720.95f, 42.9959f, 209.3307f),
        Mod_Class::Vector4(-2956.631f, 11.69463f, 6.931808f, 156.18f),
        Mod_Class::Vector4(-2876.279f, 21.03024f, 11.60808f, 41.72112f),
        Mod_Class::Vector4(-3012.55f, -51.12709f, 0.310649f, 38.1624f),
        Mod_Class::Vector4(-3038.164f, 38.733f, 8.971894f, 41.44547f),
        Mod_Class::Vector4(-3096.169f, 119.0552f, 6.728017f, 87.99979f),
        Mod_Class::Vector4(-3091.035f, 352.2566f, 7.519391f, 67.82193f),
        Mod_Class::Vector4(-3075.979f, 447.3828f, 6.362554f, 50.79964f),
        Mod_Class::Vector4(-2964.959f, 452.5694f, 15.30891f, 148.5125f),
        Mod_Class::Vector4(-3057.164f, 532.517f, 7.604911f, 255.576f),
        Mod_Class::Vector4(-3047.145f, 614.4224f, 7.323409f, 264.085f),
        Mod_Class::Vector4(-2982.056f, 719.5752f, 28.49753f, 22.28972f),
        Mod_Class::Vector4(-3165.79f, 762.5814f, 3.421354f, 180.3855f),
        Mod_Class::Vector4(-3237.243f, 914.8962f, 16.88076f, 110.9341f),
        Mod_Class::Vector4(-3295.146f, 984.6699f, 2.889409f, 0.8584108f),
        Mod_Class::Vector4(-3353.275f, 1037.395f, -0.4267793f, 0.1203664f),
        Mod_Class::Vector4(-3270.502f, 1210.821f, 2.343407f, 180.0034f),
        Mod_Class::Vector4(-3264.688f, 1110.545f, 2.304754f, 320.7578f),
        Mod_Class::Vector4(-3187.552f, 1221.516f, 9.986886f, 167.8331f),
        Mod_Class::Vector4(-2542.358f, 2317.119f, 33.21531f, 63.28617f),
        Mod_Class::Vector4(-1955.376f, 2367.43f, 32.54905f, 161.8323f),
        Mod_Class::Vector4(-1841.089f, 2195.876f, 97.38118f, 304.6146f),
        Mod_Class::Vector4(-1837.205f, 2270.878f, 73.74523f, 312.3881f),
        Mod_Class::Vector4(-1895.852f, 2143.426f, 121.225f, 65.59644f),
        Mod_Class::Vector4(-1859.108f, 2072.094f, 140.9959f, 129.7641f),
        Mod_Class::Vector4(-1790.499f, 2119.865f, 132.356f, 90.9618f),
        Mod_Class::Vector4(-1916.931f, 1944.778f, 158.3994f, 296.9663f),
        Mod_Class::Vector4(-1701.855f, 1957.936f, 131.0938f, 56.90914f),
        Mod_Class::Vector4(-1721.216f, 2029.074f, 112.8439f, 156.9609f),
        Mod_Class::Vector4(-1097.618f, 2700.906f, 18.90455f, 84.88656f),
        Mod_Class::Vector4(-328.0197f, 2825.509f, 58.02246f, 111.1101f),
        Mod_Class::Vector4(181.3483f, 2793.319f, 45.6552f, 24.21892f),
        Mod_Class::Vector4(331.855f, 2873.202f, 43.45045f, 156.6868f),
        Mod_Class::Vector4(361.1784f, 2976.71f, 40.4106f, 122.3371f),
        Mod_Class::Vector4(282.1306f, 2568.33f, 45.2464f, 241.7109f),
        Mod_Class::Vector4(203.8961f, 2702.276f, 42.54163f, 175.5621f),
        Mod_Class::Vector4(391.2553f, 2633.707f, 44.6586f, 32.33579f),
        Mod_Class::Vector4(470.7168f, 2610.214f, 42.72048f, 9.760907f),
        Mod_Class::Vector4(586.6243f, 2742.652f, 42.07542f, 275.8898f),
        Mod_Class::Vector4(754.2651f, 2783.679f, 66.97653f, 216.7942f),
        Mod_Class::Vector4(848.8434f, 2382.375f, 54.18682f, 285.6466f),
        Mod_Class::Vector4(914.1945f, 2294.065f, 48.86418f, 187.3512f),
        Mod_Class::Vector4(980.6591f, 2667.654f, 40.06087f, 354.2927f),
        Mod_Class::Vector4(1182.588f, 2701.389f, 38.15746f, 236.7878f),
        Mod_Class::Vector4(1116.655f, 2641.605f, 38.14867f, 2.974739f),
        Mod_Class::Vector4(1777.552f, 3325.553f, 41.43348f, 345.9209f),
        Mod_Class::Vector4(1832.452f, 3443.146f, 41.04421f, 354.7577f),
        Mod_Class::Vector4(1964.699f, 3257.751f, 45.65916f, 168.9078f),
        Mod_Class::Vector4(1987.721f, 3047.302f, 46.74506f, 237.7831f),
        Mod_Class::Vector4(2370.224f, 3156.767f, 48.20884f, 39.61424f),
        Mod_Class::Vector4(2343.113f, 3046.043f, 48.15176f, 273.6578f),
        Mod_Class::Vector4(2398.234f, 3315.428f, 47.70992f, 282.5903f),
        Mod_Class::Vector4(2164.31f, 3396.292f, 45.43284f, 295.356f),
        Mod_Class::Vector4(2259.422f, 3437.281f, 64.76982f, 128.1591f),
        Mod_Class::Vector4(2179.717f, 3498.747f, 45.46162f, 354.1017f),
        Mod_Class::Vector4(2062.606f, 3452.479f, 43.75446f, 37.58577f),
        Mod_Class::Vector4(2486.352f, 3760.736f, 42.24755f, 176.6024f),
        Mod_Class::Vector4(2616.738f, 3665.922f, 102.1075f, 62.15446f),
        Mod_Class::Vector4(2418.972f, 4019.551f, 36.7912f, 209.7724f),
        Mod_Class::Vector4(2483.769f, 4102.82f, 38.12365f, 182.0906f),
        Mod_Class::Vector4(2565.83f, 4244.567f, 41.4447f, 328.7588f),
        Mod_Class::Vector4(2702.66f, 4330.201f, 45.85205f, 10.36979f),
        Mod_Class::Vector4(2904.14f, 4593.71f, 48.02999f, 80.57688f),
        Mod_Class::Vector4(2859.294f, 4663.227f, 47.93969f, 195.7032f),
        Mod_Class::Vector4(2227.497f, 4790.701f, 40.40303f, 345.2054f),
        Mod_Class::Vector4(1684.557f, 4817.428f, 42.01131f, 117.5796f),
        Mod_Class::Vector4(1668.184f, 4897.533f, 42.05532f, 203.0841f),
        Mod_Class::Vector4(1717.725f, 4677.343f, 43.65575f, 290.9685f),
        Mod_Class::Vector4(1428.173f, 4379.375f, 44.27631f, 216.4638f),
        Mod_Class::Vector4(1370.321f, 4317.032f, 38.06339f, 42.11711f),
        Mod_Class::Vector4(1240.904f, 4350.808f, 34.24231f, 94.9155f),
        Mod_Class::Vector4(-271.7308f, 6400.089f, 31.30641f, 222.9104f),
        Mod_Class::Vector4(-335.076f, 6493.833f, 2.34665f, 119.0187f),
        Mod_Class::Vector4(-401.1573f, 6383.861f, 14.14575f, 136.2842f),
        Mod_Class::Vector4(-640.2075f, 6236.555f, 2.976151f, 172.2602f),
        Mod_Class::Vector4(-437.9801f, 6272.952f, 30.06834f, 249.4151f),
        Mod_Class::Vector4(-661.4758f, 6157.757f, 2.040393f, 141.1119f),
        Mod_Class::Vector4(-703.632f, 5802.625f, 17.31226f, 352.4189f),
        Mod_Class::Vector4(-739.5485f, 5602.697f, 41.65934f, 180.9679f),
        Mod_Class::Vector4(-594.1973f, 5364.056f, 70.43559f, 20.45568f),
        Mod_Class::Vector4(-630.548f, 5208.631f, 83.00797f, 80.07411f),
        Mod_Class::Vector4(-468.9976f, 5358.746f, 80.79279f, 4.032477f),
        Mod_Class::Vector4(-514.1689f, 5266.845f, 80.48373f, 212.6361f),
        Mod_Class::Vector4(-455.2321f, 6008.505f, 31.48877f, 260.9404f),
        Mod_Class::Vector4(-379.7126f, 6033.835f, 31.49892f, 100.5203f),
        Mod_Class::Vector4(-321.3374f, 6232.379f, 31.52865f, 281.4824f),
        Mod_Class::Vector4(-416.6474f, 6137.146f, 31.53211f, 227.9525f),
        Mod_Class::Vector4(-249.6663f, 6067.666f, 31.37034f, 140.0739f),
        Mod_Class::Vector4(-246.1973f, 6155.588f, 31.42052f, 184.0397f),
        Mod_Class::Vector4(-250.0735f, 6271.455f, 31.43178f, 146.0887f),
        Mod_Class::Vector4(-182.6544f, 6334.627f, 31.4791f, 137.9106f),
        Mod_Class::Vector4(-152.0446f, 6259.825f, 31.48942f, 321.7107f),
        Mod_Class::Vector4(-68.66537f, 6270.102f, 31.33991f, 153.4193f),
        Mod_Class::Vector4(-70.80379f, 6437.074f, 31.63992f, 149.3367f),
        Mod_Class::Vector4(-168.8526f, 6436.67f, 31.9113f, 33.98012f),
        Mod_Class::Vector4(-106.8976f, 6533.95f, 29.83228f, 22.53628f),
        Mod_Class::Vector4(-17.19193f, 6502.194f, 31.50745f, 277.7401f),
        Mod_Class::Vector4(107.219f, 6612.1f, 31.97963f, 176.6421f),
        Mod_Class::Vector4(155.6443f, 6508.133f, 31.7202f, 50.47895f),
        Mod_Class::Vector4(-97.19097f, 6350.258f, 31.58107f, 227.7804f),
        Mod_Class::Vector4(291.5666f, 6515.816f, 29.77631f, 240.3053f),
        Mod_Class::Vector4(381.5781f, 6526.341f, 28.18776f, 297.2371f),
        Mod_Class::Vector4(509.6346f, 6512.681f, 29.83138f, 358.1497f),
        Mod_Class::Vector4(1087.457f, 6511.739f, 20.55505f, 184.4623f),
        Mod_Class::Vector4(1300.798f, 6609.131f, 2.210964f, 166.6302f),
        Mod_Class::Vector4(1427.748f, 6551.687f, 15.48245f, 259.8033f),
        Mod_Class::Vector4(1581.274f, 6453.915f, 25.31938f, 146.6987f),
        Mod_Class::Vector4(1691.058f, 6427.246f, 32.54766f, 235.5572f),
        Mod_Class::Vector4(488.016f, 5586.718f, 794.0623f, 207.1104f),
        Mod_Class::Vector4(709.0751f, 4184.547f, 40.70778f, 34.69099f),
        Mod_Class::Vector4(713.3973f, 4092.791f, 34.72971f, 183.6691f),
        Mod_Class::Vector4(-18.10457f, 3768.18f, 31.31539f, 0.0f),
        Mod_Class::Vector4(396.4519f, 3578.591f, 33.29235f, 292.9981f),
        Mod_Class::Vector4(915.2141f, 3565.18f, 33.80116f, 296.1426f),
        Mod_Class::Vector4(915.4491f, 3643.504f, 32.65174f, 224.7724f),
        Mod_Class::Vector4(1361.951f, 3603.041f, 34.94891f, 248.2975f),
        Mod_Class::Vector4(1261.829f, 3548.285f, 34.62054f, 191.3703f),
        Mod_Class::Vector4(1229.425f, 3622.139f, 33.48791f, 194.691f),
        Mod_Class::Vector4(1431.933f, 3669.91f, 39.73352f, 21.39104f),
        Mod_Class::Vector4(1553.329f, 3801.798f, 34.25249f, 349.7805f),
        Mod_Class::Vector4(1691.517f, 3866.717f, 34.91164f, 110.7219f),
        Mod_Class::Vector4(1544.495f, 3722.99f, 34.59937f, 213.8932f),
        Mod_Class::Vector4(1795.776f, 3949.233f, 33.90714f, 275.9398f),
        Mod_Class::Vector4(1829.368f, 3833.267f, 33.35374f, 28.27547f),
        Mod_Class::Vector4(1904.727f, 3708.882f, 32.73225f, 290.9872f),
        Mod_Class::Vector4(1950.306f, 3845.622f, 32.18547f, 249.8298f),
        Mod_Class::Vector4(1985.265f, 3705.139f, 32.3974f, 332.6318f),
        Mod_Class::Vector4(2016.912f, 3773.148f, 32.20602f, 265.4035f),
        Mod_Class::Vector4(1825.867f, 3656.211f, 34.08326f, 253.2209f),
        Mod_Class::Vector4(1741.156f, 3710.271f, 34.1827f, 21.51038f),
        Mod_Class::Vector4(1632.203f, 3597.311f, 35.43903f, 211.6864f)
    };

    inline const std::vector<std::string> Weapons_List = {
        //Meelee
        "WEAPON_unarmed",  //0xA2719263",---0
        "WEAPON_dagger",  //0x92A27487",
        "WEAPON_bat",  //0x958A4A8F",
        "WEAPON_bottle",  //0xF9E6AA4B",
        "WEAPON_crowbar",  //0x84BD7BFD",
        "WEAPON_flashlight",  //0x8BB05FD7",
        "WEAPON_golfclub",  //0x440E4788",
        "WEAPON_hammer",  //0x4E875F73",
        "WEAPON_hatchet",  //0xF9DCBF2D",
        "WEAPON_knuckle",  //0xD8DF3C3C",
        "WEAPON_knife",  //0x99B507EA",
        "WEAPON_machete",  //0xDD5DF8D9",
        "WEAPON_switchblade",  //0xDFE37640",
        "WEAPON_nightstick",  //0x678B81B1",
        "WEAPON_wrench",  //0x19044EE0",
        "WEAPON_battleaxe",  //0xCD274149",
        "WEAPON_poolcue",  //0x94117305",
        "WEAPON_stone_hatchet",  //0x3813FC08"--17
        "weapon_candycane",
        //HandGuns
        "WEAPON_pistol",  //0x1B06D571",-------18
        "WEAPON_pistol_mk2",  //0xBFE256D4",---------19
        "WEAPON_combatpistol",  //0x5EF9FEC4",
        "WEAPON_appistol",  //0x22D8FE39",
        "WEAPON_pistol50",  //0x99AEEB3B",
        "WEAPON_snspistol",  //0xBFD21232",
        "WEAPON_snspistol_mk2",  //0x88374054",---24
        "WEAPON_heavypistol",  //0xD205520E",
        "WEAPON_vintagepistol",  //0x83839C4",
        "WEAPON_marksmanpistol",  //0xDC4DB296",
        "WEAPON_revolver",  //0xC1B3C3D1",
        "WEAPON_revolver_mk2",  //0xCB96392F",----29
        "WEAPON_doubleaction",  //0x97EA20B8",
        "WEAPON_ceramicpistol",  //0x2B5EF5EC",
        "WEAPON_navyrevolver",  //0x917F6C8C"
        "WEAPON_GADGETPISTOL",  //0xAF3696A1",
        "WEAPON_stungun",  //0x3656C8C1",
        "WEAPON_flaregun",  //0x47757124",
        "WEAPON_raypistol",  //0xAF3696A1",--36
        "WEAPON_STUNGUN_MP",//---------------37
        //Smg
        "WEAPON_microsmg",  //0x13532244",---38
        "WEAPON_smg",  //0x2BE6766B",
        "WEAPON_smg_mk2",  //0x78A97CD0",-----40
        "WEAPON_assaultsmg",  //0xEFE7E2DF",
        "WEAPON_combatpdw",  //0xA3D4D34",
        "WEAPON_machinepistol",  //0xDB1AA450",
        "WEAPON_minismg",  //0xBD248B55",
        "WEAPON_raycarbine",  //0x476BF155"--45
        //ShotGun
        "WEAPON_pumpshotgun",  //0x1D073A89",---46
        "WEAPON_pumpshotgun_mk2",  //0x555AF99A",-----------47
        "WEAPON_sawnoffshotgun",  //0x7846A318",
        "WEAPON_assaultshotgun",  //0xE284C527",
        "WEAPON_bullpupshotgun",  //0x9D61E50F",
        "WEAPON_musket",  //0xA89CB99E",
        "WEAPON_heavyshotgun",  //0x3AABBBAA",
        "WEAPON_dbshotgun",  //0xEF951FBB",
        "WEAPON_autoshotgun",  //0x12E82D3D"--54
        "WEAPON_COMBATSHOTGUN",  //0x5A96BA4--55
        //riflles
        "WEAPON_assaultrifle",  //0xBFEFFF6D",----56
        "WEAPON_assaultrifle_mk2",  //0x394F415C",-------57
        "WEAPON_carbinerifle",  //0x83BF0278",
        "WEAPON_carbinerifle_mk2",  //0xFAD1F1C9",------59
        "WEAPON_advancedrifle",  //0xAF113F99",
        "WEAPON_specialcarbine",  //0xC0A3098D",
        "WEAPON_specialcarbine_mk2",  //0x969C3D67",------62
        "WEAPON_bullpuprifle",  //0x7F229F94",
        "WEAPON_bullpuprifle_mk2",  //0x84D6FAFD",----64
        "WEAPON_compactrifle",  //0x624FE830"--65
        "weapon_militaryrifle",  //0x624FE830"--66
        "weapon_heavyrifle",  //0xC78D71B4
        "weapon_tacticalrifle", //| 0xD1D5F52B---68
        //Mg
        "WEAPON_mg",  //0x9D07F764",---69
        "WEAPON_combatmg",  //0x7FD62962",
        "WEAPON_combatmg_mk2",  //0xDBBD7280",------71
        "WEAPON_gusenberg",  //0x61012683"--72
        //sniper
        "WEAPON_sniperrifle",  //0x5FC3C11",-------73
        "WEAPON_heavysniper",  //0xC472FE2",
        "WEAPON_heavysniper_mk2",  //0xA914799",---75
        "WEAPON_marksmanrifle",  //0xC734385A",
        "WEAPON_marksmanrifle_mk2",  //0x6A6C02E0"--77
        "weapon_precisionrifle", //| 0x6E7DDDEC--78
        //Heavey
        "WEAPON_rpg",  //0xB1CA77B1",---79
        "WEAPON_grenadelauncher",  //0xA284510B",
        "WEAPON_grenadelauncher_smoke",  //0x4DD2DC56",
        "WEAPON_minigun",  //0x42BF8A85",
        "WEAPON_railgun",  //0x6D544C99",
        "WEAPON_hominglauncher",  //0x63AB0442",
        "WEAPON_compactlauncher",  //0x781FE4A",
        "WEAPON_rayminigun",  //0xB62D1F67"--86
        "WEAPON_EMPLAUNCHER",  // 0xDB26713A--87
        "weapon_railgunxm3",
        //throw
        "WEAPON_grenade",  //0x93E220BD",----88
        "WEAPON_smokegrenade",  //0xFDBC8A50",
        "WEAPON_flare",  //0x497FACC3",
        "WEAPON_molotov",  //0x24B17070",
        "WEAPON_stickybomb",  //0x2C3731D9",
        "WEAPON_proxmine",  //0xAB564B93",
        "WEAPON_pipebomb",  //0xBA45E8B8",--94
        //other
        "WEAPON_METALDETECTOR",//-------------95
        "WEAPON_petrolcan",  //0x34A67B97",
        "WEAPON_fireextinguisher",  //0x60EC506",
        "WEAPON_parachute",  //0xFBAB5776",
        "WEAPON_FERTILIZERCAN",//100
        "WEAPON_hazardcan",  //0xBA536372"--
        "WEAPON_bzgas",  //0xA0973D5E",
        "WEAPON_ball",  //0x23C9F95C",
        "WEAPON_snowball",  //0x787F0BB",
        "WEAPON_firework",  //0x7F7497E5",---------104
        "WEAPON_BATTLERIFLE",
        "WEAPON_SNOWLAUNCHER",
        "COMPONENT_COMBATPISTOL_VARMOD_XMAS23",
        "COMPONENT_SPECIALCARBINE_VARMOD_XMAS23",
        "COMPONENT_HEAVYSNIPER_VARMOD_XMAS23"
    };
    inline const std::vector<std::string> WeapAdd_List = {
        "COMPONENT_ADVANCEDRIFLE_CLIP_01",//0xFA8FA10F,
        "COMPONENT_ADVANCEDRIFLE_CLIP_02",//0x8EC1C979,
        "COMPONENT_ADVANCEDRIFLE_VARMOD_LUXE",//0x377CD377,
        "COMPONENT_APPISTOL_CLIP_01",//0x31C4B22A,
        "COMPONENT_APPISTOL_CLIP_02",//0x249A17D5,
        "COMPONENT_APPISTOL_VARMOD_LUXE",//0x9B76C72C,
        "COMPONENT_ASSAULTRIFLE_CLIP_01",//0xBE5EEA16,
        "COMPONENT_ASSAULTRIFLE_CLIP_02",//0xB1214F9B,
        "COMPONENT_ASSAULTRIFLE_CLIP_03",//0xDBF0A53D,
        "COMPONENT_ASSAULTRIFLE_MK2_CAMO",//0x911B24AF,
        "COMPONENT_ASSAULTRIFLE_MK2_CAMO_02",//0x37E5444B,
        "COMPONENT_ASSAULTRIFLE_MK2_CAMO_03",//0x538B7B97,
        "COMPONENT_ASSAULTRIFLE_MK2_CAMO_04",//0x25789F72,
        "COMPONENT_ASSAULTRIFLE_MK2_CAMO_05",//0xC5495F2D,
        "COMPONENT_ASSAULTRIFLE_MK2_CAMO_06",//0xCF8B73B1,
        "COMPONENT_ASSAULTRIFLE_MK2_CAMO_07",//0xA9BB2811,
        "COMPONENT_ASSAULTRIFLE_MK2_CAMO_08",//0xFC674D54,
        "COMPONENT_ASSAULTRIFLE_MK2_CAMO_09",//0x7C7FCD9B,
        "COMPONENT_ASSAULTRIFLE_MK2_CAMO_10",//0xA5C38392,
        "COMPONENT_ASSAULTRIFLE_MK2_CAMO_IND_01",//0xB9B15DB0,
        "COMPONENT_ASSAULTRIFLE_MK2_CLIP_01",//0x8610343F,
        "COMPONENT_ASSAULTRIFLE_MK2_CLIP_02",//0xD12ACA6F,
        "COMPONENT_ASSAULTRIFLE_MK2_CLIP_ARMORPIERCING",//0xA7DD1E58,
        "COMPONENT_ASSAULTRIFLE_MK2_CLIP_FMJ",//0x63E0A098,
        "COMPONENT_ASSAULTRIFLE_MK2_CLIP_INCENDIARY",//0xFB70D853,
        "COMPONENT_ASSAULTRIFLE_MK2_CLIP_TRACER",//0xEF2C78C1,
        "COMPONENT_ASSAULTRIFLE_VARMOD_LUXE",//0x4EAD7533,
        "COMPONENT_ASSAULTSHOTGUN_CLIP_01",//0x94E81BC7,
        "COMPONENT_ASSAULTSHOTGUN_CLIP_02",//0x86BD7F72,
        "COMPONENT_ASSAULTSMG_CLIP_01",//0x8D1307B0,
        "COMPONENT_ASSAULTSMG_CLIP_02",//0xBB46E417,
        "COMPONENT_ASSAULTSMG_VARMOD_LOWRIDER",//0x278C78AF,
        "COMPONENT_AT_AR_AFGRIP",//0xC164F53,
        "COMPONENT_AT_AR_AFGRIP_02",//0x9D65907A,
        "COMPONENT_AT_AR_BARREL_01",//0x43A49D26,
        "COMPONENT_AT_AR_BARREL_02",//0x5646C26A,
        "COMPONENT_AT_AR_FLSH",//0x7BC4CDDC,
        "COMPONENT_AT_AR_SUPP",//0x837445AA,
        "COMPONENT_AT_AR_SUPP_02",//0xA73D4664,
        "COMPONENT_AT_BP_BARREL_01",//0x659AC11B,
        "COMPONENT_AT_BP_BARREL_02",//0x3BF26DC7,
        "COMPONENT_AT_CR_BARREL_01",//0x833637FF,
        "COMPONENT_AT_CR_BARREL_02",//0x8B3C480B,
        "COMPONENT_AT_MG_BARREL_01",//0xC34EF234,
        "COMPONENT_AT_MG_BARREL_02",//0xB5E2575B,
        "COMPONENT_AT_MRFL_BARREL_01",//0x381B5D89,
        "COMPONENT_AT_MRFL_BARREL_02",//0x68373DDC,
        "COMPONENT_AT_MUZZLE_01",//0xB99402D4,
        "COMPONENT_AT_MUZZLE_02",//0xC867A07B,
        "COMPONENT_AT_MUZZLE_03",//0xDE11CBCF,
        "COMPONENT_AT_MUZZLE_04",//0xEC9068CC,
        "COMPONENT_AT_MUZZLE_05",//0x2E7957A,
        "COMPONENT_AT_MUZZLE_06",//0x347EF8AC,
        "COMPONENT_AT_MUZZLE_07",//0x4DB62ABE,
        "COMPONENT_AT_MUZZLE_08",//0x5F7DCE4D,
        "COMPONENT_AT_MUZZLE_09",//0x6927E1A1,
        "COMPONENT_AT_PI_COMP",//0x21E34793,
        "COMPONENT_AT_PI_COMP_02",//0xAA8283BF,
        "COMPONENT_AT_PI_COMP_03",//0x27077CCB,
        "COMPONENT_AT_PI_FLSH",//0x359B7AAE,
        "COMPONENT_AT_PI_FLSH_02",//0x43FD595B,
        "COMPONENT_AT_PI_FLSH_03",//0x4A4965F3,
        "COMPONENT_AT_PI_RAIL",//0x8ED4BB70,
        "COMPONENT_AT_PI_RAIL_02",//0x47DE9258,
        "COMPONENT_AT_PI_SUPP",//0xC304849A,
        "COMPONENT_AT_PI_SUPP_02",//0x65EA7EBB,
        "COMPONENT_AT_SB_BARREL_01",//0xD9103EE1,
        "COMPONENT_AT_SB_BARREL_02",//0xA564D78B,
        "COMPONENT_AT_SCOPE_LARGE",//0xD2443DDC,
        "COMPONENT_AT_SCOPE_LARGE_FIXED_ZOOM",//0x1C221B1A,
        "COMPONENT_AT_SCOPE_LARGE_FIXED_ZOOM_MK2",//0x5B1C713C,
        "COMPONENT_AT_SCOPE_LARGE_MK2",//0x82C10383,
        "COMPONENT_AT_SCOPE_MACRO",//0x9D2FBF29,
        "COMPONENT_AT_SCOPE_MACRO_02",//0x3CC6BA57,
        "COMPONENT_AT_SCOPE_MACRO_02_MK2",//0xC7ADD105,
        "COMPONENT_AT_SCOPE_MACRO_02_SMG_MK2",//0xE502AB6B,
        "COMPONENT_AT_SCOPE_MACRO_MK2",//0x49B2945,
        "COMPONENT_AT_SCOPE_MAX",//0xBC54DA77,
        "COMPONENT_AT_SCOPE_MEDIUM",//0xA0D89C42,
        "COMPONENT_AT_SCOPE_MEDIUM_MK2",//0xC66B6542,
        "COMPONENT_AT_SCOPE_NV",//0xB68010B0,
        "COMPONENT_AT_SCOPE_SMALL",//0xAA2C45B4,
        "COMPONENT_AT_SCOPE_SMALL_02",//0x3C00AFED,
        "COMPONENT_AT_SCOPE_SMALL_MK2",//0x3F3C8181,
        "COMPONENT_AT_SCOPE_SMALL_SMG_MK2",//0x3DECC7DA,
        "COMPONENT_AT_SCOPE_THERMAL",//0x2E43DA41,
        "COMPONENT_AT_SC_BARREL_01",//0xE73653A9,
        "COMPONENT_AT_SC_BARREL_02",//0xF97F783B,
        "COMPONENT_AT_SIGHTS",//0x420FD713,
        "COMPONENT_AT_SIGHTS_SMG",//0x9FDB5652,
        "COMPONENT_AT_SR_BARREL_01",//0x909630B7,
        "COMPONENT_AT_SR_BARREL_02",//0x108AB09E,
        "COMPONENT_AT_SR_SUPP",//0xE608B35E,
        "COMPONENT_AT_SR_SUPP_03",//0xAC42DF71,
        "COMPONENT_BULLPUPRIFLE_CLIP_01",//0xC5A12F80,
        "COMPONENT_BULLPUPRIFLE_CLIP_02",//0xB3688B0F,
        "COMPONENT_BULLPUPRIFLE_MK2_CAMO",//0xAE4055B7,
        "COMPONENT_BULLPUPRIFLE_MK2_CAMO_02",//0xB905ED6B,
        "COMPONENT_BULLPUPRIFLE_MK2_CAMO_03",//0xA6C448E8,
        "COMPONENT_BULLPUPRIFLE_MK2_CAMO_04",//0x9486246C,
        "COMPONENT_BULLPUPRIFLE_MK2_CAMO_05",//0x8A390FD2,
        "COMPONENT_BULLPUPRIFLE_MK2_CAMO_06",//0x2337FC5,
        "COMPONENT_BULLPUPRIFLE_MK2_CAMO_07",//0xEFFFDB5E,
        "COMPONENT_BULLPUPRIFLE_MK2_CAMO_08",//0xDDBDB6DA,
        "COMPONENT_BULLPUPRIFLE_MK2_CAMO_09",//0xCB631225,
        "COMPONENT_BULLPUPRIFLE_MK2_CAMO_10",//0xA87D541E,
        "COMPONENT_BULLPUPRIFLE_MK2_CAMO_IND_01",//0xC5E9AE52,
        "COMPONENT_BULLPUPRIFLE_MK2_CLIP_01",//0x18929DA,
        "COMPONENT_BULLPUPRIFLE_MK2_CLIP_02",//0xEFB00628,
        "COMPONENT_BULLPUPRIFLE_MK2_CLIP_ARMORPIERCING",//0xFAA7F5ED,
        "COMPONENT_BULLPUPRIFLE_MK2_CLIP_FMJ",//0x43621710,
        "COMPONENT_BULLPUPRIFLE_MK2_CLIP_INCENDIARY",//0xA99CF95A,
        "COMPONENT_BULLPUPRIFLE_MK2_CLIP_TRACER",//0x822060A9,
        "COMPONENT_BULLPUPRIFLE_VARMOD_LOW",//0xA857BC78,
        "COMPONENT_CARBINERIFLE_CLIP_01",//0x9FBE33EC,
        "COMPONENT_CARBINERIFLE_CLIP_02",//0x91109691,
        "COMPONENT_CARBINERIFLE_CLIP_03",//0xBA62E935,
        "COMPONENT_CARBINERIFLE_MK2_CAMO",//0x4BDD6F16,
        "COMPONENT_CARBINERIFLE_MK2_CAMO_02",//0x406A7908,
        "COMPONENT_CARBINERIFLE_MK2_CAMO_03",//0x2F3856A4,
        "COMPONENT_CARBINERIFLE_MK2_CAMO_04",//0xE50C424D,
        "COMPONENT_CARBINERIFLE_MK2_CAMO_05",//0xD37D1F2F,
        "COMPONENT_CARBINERIFLE_MK2_CAMO_06",//0x86268483,
        "COMPONENT_CARBINERIFLE_MK2_CAMO_07",//0xF420E076,
        "COMPONENT_CARBINERIFLE_MK2_CAMO_08",//0xAAE14DF8,
        "COMPONENT_CARBINERIFLE_MK2_CAMO_09",//0x9893A95D,
        "COMPONENT_CARBINERIFLE_MK2_CAMO_10",//0x6B13CD3E,
        "COMPONENT_CARBINERIFLE_MK2_CAMO_IND_01",//0xDA55CD3F,
        "COMPONENT_CARBINERIFLE_MK2_CLIP_01",//0x4C7A391E,
        "COMPONENT_CARBINERIFLE_MK2_CLIP_02",//0x5DD5DBD5,
        "COMPONENT_CARBINERIFLE_MK2_CLIP_ARMORPIERCING",//0x255D5D57,
        "COMPONENT_CARBINERIFLE_MK2_CLIP_FMJ",//0x44032F11,
        "COMPONENT_CARBINERIFLE_MK2_CLIP_INCENDIARY",//0x3D25C2A7,
        "COMPONENT_CARBINERIFLE_MK2_CLIP_TRACER",//0x1757F566,
        "COMPONENT_CARBINERIFLE_VARMOD_LUXE",//0xD89B9658,
        "COMPONENT_COMBATMG_CLIP_01",//0xE1FFB34A,
        "COMPONENT_COMBATMG_CLIP_02",//0xD6C59CD6,
        "COMPONENT_COMBATMG_MK2_CAMO",//0x4A768CB5,
        "COMPONENT_COMBATMG_MK2_CAMO_02",//0xCCE06BBD,
        "COMPONENT_COMBATMG_MK2_CAMO_03",//0xBE94CF26,
        "COMPONENT_COMBATMG_MK2_CAMO_04",//0x7609BE11,
        "COMPONENT_COMBATMG_MK2_CAMO_05",//0x48AF6351,
        "COMPONENT_COMBATMG_MK2_CAMO_06",//0x9186750A,
        "COMPONENT_COMBATMG_MK2_CAMO_07",//0x84555AA8,
        "COMPONENT_COMBATMG_MK2_CAMO_08",//0x1B4C088B,
        "COMPONENT_COMBATMG_MK2_CAMO_09",//0xE046DFC,
        "COMPONENT_COMBATMG_MK2_CAMO_10",//0x28B536E,
        "COMPONENT_COMBATMG_MK2_CAMO_IND_01",//0xD703C94D,
        "COMPONENT_COMBATMG_MK2_CLIP_01",//0x492B257C,
        "COMPONENT_COMBATMG_MK2_CLIP_02",//0x17DF42E9,
        "COMPONENT_COMBATMG_MK2_CLIP_ARMORPIERCING",//0x29882423,
        "COMPONENT_COMBATMG_MK2_CLIP_FMJ",//0x57EF1CC8,
        "COMPONENT_COMBATMG_MK2_CLIP_INCENDIARY",//0xC326BDBA,
        "COMPONENT_COMBATMG_MK2_CLIP_TRACER",//0xF6649745,
        "COMPONENT_COMBATMG_VARMOD_LOWRIDER",//0x92FECCDD,
        "COMPONENT_COMBATPDW_CLIP_01",//0x4317F19E,
        "COMPONENT_COMBATPDW_CLIP_02",//0x334A5203,
        "COMPONENT_COMBATPDW_CLIP_03",//0x6EB8C8DB,
        "COMPONENT_COMBATPISTOL_CLIP_01",//0x721B079,
        "COMPONENT_COMBATPISTOL_CLIP_02",//0xD67B4F2D,
        "COMPONENT_COMBATPISTOL_VARMOD_LOWRIDER",//0xC6654D72,
        "COMPONENT_COMPACTRIFLE_CLIP_01",//0x513F0A63,
        "COMPONENT_COMPACTRIFLE_CLIP_02",//0x59FF9BF8,
        "COMPONENT_COMPACTRIFLE_CLIP_03",//0xC607740E,
        "COMPONENT_GRENADELAUNCHER_CLIP_01",//0x11AE5C97,
        "COMPONENT_GUSENBERG_CLIP_01",//0x1CE5A6A5,
        "COMPONENT_GUSENBERG_CLIP_02",//0xEAC8C270,
        "COMPONENT_HEAVYPISTOL_CLIP_01",//0xD4A969A,
        "COMPONENT_HEAVYPISTOL_CLIP_02",//0x64F9C62B,
        "COMPONENT_HEAVYPISTOL_VARMOD_LUXE",//0x7A6A7B7B,
        "COMPONENT_HEAVYSHOTGUN_CLIP_01",//0x324F2D5F,
        "COMPONENT_HEAVYSHOTGUN_CLIP_02",//0x971CF6FD,
        "COMPONENT_HEAVYSHOTGUN_CLIP_03",//0x88C7DA53,
        "COMPONENT_HEAVYSNIPER_CLIP_01",//0x476F52F4,
        "COMPONENT_HEAVYSNIPER_MK2_CAMO",//0xF8337D02,
        "COMPONENT_HEAVYSNIPER_MK2_CAMO_02",//0xC5BEDD65,
        "COMPONENT_HEAVYSNIPER_MK2_CAMO_03",//0xE9712475,
        "COMPONENT_HEAVYSNIPER_MK2_CAMO_04",//0x13AA78E7,
        "COMPONENT_HEAVYSNIPER_MK2_CAMO_05",//0x26591E50,
        "COMPONENT_HEAVYSNIPER_MK2_CAMO_06",//0x302731EC,
        "COMPONENT_HEAVYSNIPER_MK2_CAMO_07",//0xAC722A78,
        "COMPONENT_HEAVYSNIPER_MK2_CAMO_08",//0xBEA4CEDD,
        "COMPONENT_HEAVYSNIPER_MK2_CAMO_09",//0xCD776C82,
        "COMPONENT_HEAVYSNIPER_MK2_CAMO_10",//0xABC5ACC7,
        "COMPONENT_HEAVYSNIPER_MK2_CAMO_IND_01",//0x6C32D2EB,
        "COMPONENT_HEAVYSNIPER_MK2_CLIP_01",//0xFA1E1A28,
        "COMPONENT_HEAVYSNIPER_MK2_CLIP_02",//0x2CD8FF9D,
        "COMPONENT_HEAVYSNIPER_MK2_CLIP_ARMORPIERCING",//0xF835D6D4,
        "COMPONENT_HEAVYSNIPER_MK2_CLIP_EXPLOSIVE",//0x89EBDAA7,
        "COMPONENT_HEAVYSNIPER_MK2_CLIP_FMJ",//0x3BE948F6,
        "COMPONENT_HEAVYSNIPER_MK2_CLIP_INCENDIARY",//0xEC0F617,
        "COMPONENT_KNUCKLE_VARMOD_BALLAS",//0xEED9FD63,
        "COMPONENT_KNUCKLE_VARMOD_BASE",//0xF3462F33,
        "COMPONENT_KNUCKLE_VARMOD_DIAMOND",//0x9761D9DC,
        "COMPONENT_KNUCKLE_VARMOD_DOLLAR",//0x50910C31,
        "COMPONENT_KNUCKLE_VARMOD_HATE",//0x7DECFE30,
        "COMPONENT_KNUCKLE_VARMOD_KING",//0xE28BABEF,
        "COMPONENT_KNUCKLE_VARMOD_LOVE",//0x3F4E8AA6,
        "COMPONENT_KNUCKLE_VARMOD_PIMP",//0xC613F685,
        "COMPONENT_KNUCKLE_VARMOD_PLAYER",//0x8B808BB,
        "COMPONENT_KNUCKLE_VARMOD_VAGOS",//0x7AF3F785,
        "COMPONENT_MACHINEPISTOL_CLIP_01",//0x476E85FF,
        "COMPONENT_MACHINEPISTOL_CLIP_02",//0xB92C6979,
        "COMPONENT_MACHINEPISTOL_CLIP_03",//0xA9E9CAF4,
        "COMPONENT_MARKSMANRIFLE_CLIP_01",//0xD83B4141,
        "COMPONENT_MARKSMANRIFLE_CLIP_02",//0xCCFD2AC5,
        "COMPONENT_MARKSMANRIFLE_MK2_CAMO",//0x9094FBA0,
        "COMPONENT_MARKSMANRIFLE_MK2_CAMO_02",//0x7320F4B2,
        "COMPONENT_MARKSMANRIFLE_MK2_CAMO_03",//0x60CF500F,
        "COMPONENT_MARKSMANRIFLE_MK2_CAMO_04",//0xFE668B3F,
        "COMPONENT_MARKSMANRIFLE_MK2_CAMO_05",//0xF3757559,
        "COMPONENT_MARKSMANRIFLE_MK2_CAMO_06",//0x193B40E8,
        "COMPONENT_MARKSMANRIFLE_MK2_CAMO_07",//0x107D2F6C,
        "COMPONENT_MARKSMANRIFLE_MK2_CAMO_08",//0xC4E91841,
        "COMPONENT_MARKSMANRIFLE_MK2_CAMO_09",//0x9BB1C5D3,
        "COMPONENT_MARKSMANRIFLE_MK2_CAMO_10",//0x3B61040B,
        "COMPONENT_MARKSMANRIFLE_MK2_CAMO_IND_01",//0xB7A316DA,
        "COMPONENT_MARKSMANRIFLE_MK2_CLIP_01",//0x94E12DCE,
        "COMPONENT_MARKSMANRIFLE_MK2_CLIP_02",//0xE6CFD1AA,
        "COMPONENT_MARKSMANRIFLE_MK2_CLIP_ARMORPIERCING",//0xF46FD079,
        "COMPONENT_MARKSMANRIFLE_MK2_CLIP_FMJ",//0xE14A9ED3,
        "COMPONENT_MARKSMANRIFLE_MK2_CLIP_INCENDIARY",//0x6DD7A86E,
        "COMPONENT_MARKSMANRIFLE_MK2_CLIP_TRACER",//0xD77A22D2,
        "COMPONENT_MARKSMANRIFLE_VARMOD_LUXE",//0x161E9241,
        "COMPONENT_MG_CLIP_01",//0xF434EF84,
        "COMPONENT_MG_CLIP_02",//0x82158B47,
        "COMPONENT_MG_VARMOD_LOWRIDER",//0xD6DABABE,
        "COMPONENT_MICROSMG_CLIP_01",//0xCB48AEF0,
        "COMPONENT_MICROSMG_CLIP_02",//0x10E6BA2B,
        "COMPONENT_MICROSMG_VARMOD_LUXE",//0x487AAE09,
        "COMPONENT_MINISMG_CLIP_01",//0x84C8B2D3,
        "COMPONENT_MINISMG_CLIP_02",//0x937ED0B7,
        "COMPONENT_PISTOL50_CLIP_01",//0x2297BE19,
        "COMPONENT_PISTOL50_CLIP_02",//0xD9D3AC92,
        "COMPONENT_PISTOL50_VARMOD_LUXE",//0x77B8AB2F,
        "COMPONENT_PISTOL_CLIP_01",//0xFED0FD71,
        "COMPONENT_PISTOL_CLIP_02",//0xED265A1C,
        "COMPONENT_PISTOL_MK2_CAMO",//0x5C6C749C,
        "COMPONENT_PISTOL_MK2_CAMO_02",//0x15F7A390,
        "COMPONENT_PISTOL_MK2_CAMO_02_SLIDE",//0x1A1F1260,
        "COMPONENT_PISTOL_MK2_CAMO_03",//0x968E24DB,
        "COMPONENT_PISTOL_MK2_CAMO_03_SLIDE",//0xE4E00B70,
        "COMPONENT_PISTOL_MK2_CAMO_04",//0x17BFA99,
        "COMPONENT_PISTOL_MK2_CAMO_04_SLIDE",//0x2C298B2B,
        "COMPONENT_PISTOL_MK2_CAMO_05",//0xF2685C72,
        "COMPONENT_PISTOL_MK2_CAMO_05_SLIDE",//0xDFB79725,
        "COMPONENT_PISTOL_MK2_CAMO_06",//0xDD2231E6,
        "COMPONENT_PISTOL_MK2_CAMO_06_SLIDE",//0x6BD7228C,
        "COMPONENT_PISTOL_MK2_CAMO_07",//0xBB43EE76,
        "COMPONENT_PISTOL_MK2_CAMO_07_SLIDE",//0x9DDBCF8C,
        "COMPONENT_PISTOL_MK2_CAMO_08",//0x4D901310,
        "COMPONENT_PISTOL_MK2_CAMO_08_SLIDE",//0xB319A52C,
        "COMPONENT_PISTOL_MK2_CAMO_09",//0x5F31B653,
        "COMPONENT_PISTOL_MK2_CAMO_09_SLIDE",//0xC6836E12,
        "COMPONENT_PISTOL_MK2_CAMO_10",//0x697E19A0,
        "COMPONENT_PISTOL_MK2_CAMO_10_SLIDE",//0x43B1B173,
        "COMPONENT_PISTOL_MK2_CAMO_IND_01",//0x930CB951,
        "COMPONENT_PISTOL_MK2_CAMO_IND_01_SLIDE",//0x4ABDA3FA,
        "COMPONENT_PISTOL_MK2_CAMO_SLIDE",//0xB4FC92B0,
        "COMPONENT_PISTOL_MK2_CLIP_01",//0x94F42D62,
        "COMPONENT_PISTOL_MK2_CLIP_02",//0x5ED6C128,
        "COMPONENT_PISTOL_MK2_CLIP_FMJ",//0x4F37DF2A,
        "COMPONENT_PISTOL_MK2_CLIP_HOLLOWPOINT",//0x85FEA109,
        "COMPONENT_PISTOL_MK2_CLIP_INCENDIARY",//0x2BBD7A3A,
        "COMPONENT_PISTOL_MK2_CLIP_TRACER",//0x25CAAEAF,
        "COMPONENT_PISTOL_VARMOD_LUXE",//0xD7391086,
        "COMPONENT_PUMPSHOTGUN_MK2_CAMO",//0xE3BD9E44,
        "COMPONENT_PUMPSHOTGUN_MK2_CAMO_02",//0x17148F9B,
        "COMPONENT_PUMPSHOTGUN_MK2_CAMO_03",//0x24D22B16,
        "COMPONENT_PUMPSHOTGUN_MK2_CAMO_04",//0xF2BEC6F0,
        "COMPONENT_PUMPSHOTGUN_MK2_CAMO_05",//0x85627D,
        "COMPONENT_PUMPSHOTGUN_MK2_CAMO_06",//0xDC2919C5,
        "COMPONENT_PUMPSHOTGUN_MK2_CAMO_07",//0xE184247B,
        "COMPONENT_PUMPSHOTGUN_MK2_CAMO_08",//0xD8EF9356,
        "COMPONENT_PUMPSHOTGUN_MK2_CAMO_09",//0xEF29BFCA,
        "COMPONENT_PUMPSHOTGUN_MK2_CAMO_10",//0x67AEB165,
        "COMPONENT_PUMPSHOTGUN_MK2_CAMO_IND_01",//0x46411A1D,
        "COMPONENT_PUMPSHOTGUN_MK2_CLIP_01",//0xCD940141,
        "COMPONENT_PUMPSHOTGUN_MK2_CLIP_ARMORPIERCING",//0x4E65B425,
        "COMPONENT_PUMPSHOTGUN_MK2_CLIP_EXPLOSIVE",//0x3BE4465D,
        "COMPONENT_PUMPSHOTGUN_MK2_CLIP_HOLLOWPOINT",//0xE9582927,
        "COMPONENT_PUMPSHOTGUN_MK2_CLIP_INCENDIARY",//0x9F8A1BF5,
        "COMPONENT_PUMPSHOTGUN_VARMOD_LOWRIDER",//0xA2D79DDB,
        "COMPONENT_REVOLVER_CLIP_01",//0xE9867CE3,
        "COMPONENT_REVOLVER_MK2_CAMO",//0xC03FED9F,
        "COMPONENT_REVOLVER_MK2_CAMO_02",//0xB5DE24,
        "COMPONENT_REVOLVER_MK2_CAMO_03",//0xA7FF1B8,
        "COMPONENT_REVOLVER_MK2_CAMO_04",//0xF2E24289,
        "COMPONENT_REVOLVER_MK2_CAMO_05",//0x11317F27,
        "COMPONENT_REVOLVER_MK2_CAMO_06",//0x17C30C42,
        "COMPONENT_REVOLVER_MK2_CAMO_07",//0x257927AE,
        "COMPONENT_REVOLVER_MK2_CAMO_08",//0x37304B1C,
        "COMPONENT_REVOLVER_MK2_CAMO_09",//0x48DAEE71,
        "COMPONENT_REVOLVER_MK2_CAMO_10",//0x20ED9B5B,
        "COMPONENT_REVOLVER_MK2_CAMO_IND_01",//0xD951E867,
        "COMPONENT_REVOLVER_MK2_CLIP_01",//0xBA23D8BE,
        "COMPONENT_REVOLVER_MK2_CLIP_FMJ",//0xDC8BA3F,
        "COMPONENT_REVOLVER_MK2_CLIP_HOLLOWPOINT",//0x10F42E8F,
        "COMPONENT_REVOLVER_MK2_CLIP_INCENDIARY",//0xEFBF25,
        "COMPONENT_REVOLVER_MK2_CLIP_TRACER",//0xC6D8E476,
        "COMPONENT_REVOLVER_VARMOD_BOSS",//0x16EE3040,
        "COMPONENT_REVOLVER_VARMOD_GOON",//0x9493B80D,
        "COMPONENT_SAWNOFFSHOTGUN_VARMOD_LUXE",//0x85A64DF9,
        "COMPONENT_SMG_CLIP_01",//0x26574997,
        "COMPONENT_SMG_CLIP_02",//0x350966FB,
        "COMPONENT_SMG_CLIP_03",//0x79C77076,
        "COMPONENT_SMG_MK2_CAMO",//0xC4979067,
        "COMPONENT_SMG_MK2_CAMO_02",//0x3815A945,
        "COMPONENT_SMG_MK2_CAMO_03",//0x4B4B4FB0,
        "COMPONENT_SMG_MK2_CAMO_04",//0xEC729200,
        "COMPONENT_SMG_MK2_CAMO_05",//0x48F64B22,
        "COMPONENT_SMG_MK2_CAMO_06",//0x35992468,
        "COMPONENT_SMG_MK2_CAMO_07",//0x24B782A5,
        "COMPONENT_SMG_MK2_CAMO_08",//0xA2E67F01,
        "COMPONENT_SMG_MK2_CAMO_09",//0x2218FD68,
        "COMPONENT_SMG_MK2_CAMO_10",//0x45C5C3C5,
        "COMPONENT_SMG_MK2_CAMO_IND_01",//0x399D558F,
        "COMPONENT_SMG_MK2_CLIP_01",//0x4C24806E,
        "COMPONENT_SMG_MK2_CLIP_02",//0xB9835B2E,
        "COMPONENT_SMG_MK2_CLIP_FMJ",//0xB5A715F,
        "COMPONENT_SMG_MK2_CLIP_HOLLOWPOINT",//0x3A1BD6FA,
        "COMPONENT_SMG_MK2_CLIP_INCENDIARY",//0xD99222E5,
        "COMPONENT_SMG_MK2_CLIP_TRACER",//0x7FEA36EC,
        "COMPONENT_SMG_VARMOD_LUXE",//0x27872C90,
        "COMPONENT_SNIPERRIFLE_CLIP_01",//0x9BC64089,
        "COMPONENT_SNIPERRIFLE_VARMOD_LUXE",//0x4032B5E7,
        "COMPONENT_SNSPISTOL_CLIP_01",//0xF8802ED9,
        "COMPONENT_SNSPISTOL_CLIP_02",//0x7B0033B3,
        "COMPONENT_SNSPISTOL_MK2_CAMO",//0xF7BEEDD,
        "COMPONENT_SNSPISTOL_MK2_CAMO_02",//0x8A612EF6,
        "COMPONENT_SNSPISTOL_MK2_CAMO_02_SLIDE",//0x29366D21,
        "COMPONENT_SNSPISTOL_MK2_CAMO_03",//0x76FA8829,
        "COMPONENT_SNSPISTOL_MK2_CAMO_03_SLIDE",//0x3ADE514B,
        "COMPONENT_SNSPISTOL_MK2_CAMO_04",//0xA93C6CAC,
        "COMPONENT_SNSPISTOL_MK2_CAMO_04_SLIDE",//0xE64513E9,
        "COMPONENT_SNSPISTOL_MK2_CAMO_05",//0x9C905354,
        "COMPONENT_SNSPISTOL_MK2_CAMO_05_SLIDE",//0xCD7AEB9A,
        "COMPONENT_SNSPISTOL_MK2_CAMO_06",//0x4DFA3621,
        "COMPONENT_SNSPISTOL_MK2_CAMO_06_SLIDE",//0xFA7B27A6,
        "COMPONENT_SNSPISTOL_MK2_CAMO_07",//0x42E91FFF,
        "COMPONENT_SNSPISTOL_MK2_CAMO_07_SLIDE",//0xE285CA9A,
        "COMPONENT_SNSPISTOL_MK2_CAMO_08",//0x54A8437D,
        "COMPONENT_SNSPISTOL_MK2_CAMO_08_SLIDE",//0x2B904B19,
        "COMPONENT_SNSPISTOL_MK2_CAMO_09",//0x68C2746,
        "COMPONENT_SNSPISTOL_MK2_CAMO_09_SLIDE",//0x22C24F9C,
        "COMPONENT_SNSPISTOL_MK2_CAMO_10",//0x2366E467,
        "COMPONENT_SNSPISTOL_MK2_CAMO_10_SLIDE",//0x8D0D5ECD,
        "COMPONENT_SNSPISTOL_MK2_CAMO_IND_01",//0x441882E6,
        "COMPONENT_SNSPISTOL_MK2_CAMO_IND_01_SLIDE",//0x1F07150A,
        "COMPONENT_SNSPISTOL_MK2_CAMO_SLIDE",//0xE7EE68EA,
        "COMPONENT_SNSPISTOL_MK2_CLIP_01",//0x1466CE6,
        "COMPONENT_SNSPISTOL_MK2_CLIP_02",//0xCE8C0772,
        "COMPONENT_SNSPISTOL_MK2_CLIP_FMJ",//0xC111EB26,
        "COMPONENT_SNSPISTOL_MK2_CLIP_HOLLOWPOINT",//0x8D107402,
        "COMPONENT_SNSPISTOL_MK2_CLIP_INCENDIARY",//0xE6AD5F79,
        "COMPONENT_SNSPISTOL_MK2_CLIP_TRACER",//0x902DA26E,
        "COMPONENT_SNSPISTOL_VARMOD_LOWRIDER",//0x8033ECAF,
        "COMPONENT_SPECIALCARBINE_CLIP_01",//0xC6C7E581,
        "COMPONENT_SPECIALCARBINE_CLIP_02",//0x7C8BD10E,
        "COMPONENT_SPECIALCARBINE_CLIP_03",//0x6B59AEAA,
        "COMPONENT_SPECIALCARBINE_MK2_CAMO",//0xD40BB53B,
        "COMPONENT_SPECIALCARBINE_MK2_CAMO_02",//0x431B238B,
        "COMPONENT_SPECIALCARBINE_MK2_CAMO_03",//0x34CF86F4,
        "COMPONENT_SPECIALCARBINE_MK2_CAMO_04",//0xB4C306DD,
        "COMPONENT_SPECIALCARBINE_MK2_CAMO_05",//0xEE677A25,
        "COMPONENT_SPECIALCARBINE_MK2_CAMO_06",//0xDF90DC78,
        "COMPONENT_SPECIALCARBINE_MK2_CAMO_07",//0xA4C31EE,
        "COMPONENT_SPECIALCARBINE_MK2_CAMO_08",//0x89CFB0F7,
        "COMPONENT_SPECIALCARBINE_MK2_CAMO_09",//0x7B82145C,
        "COMPONENT_SPECIALCARBINE_MK2_CAMO_10",//0x899CAF75,
        "COMPONENT_SPECIALCARBINE_MK2_CAMO_IND_01",//0x5218C819,
        "COMPONENT_SPECIALCARBINE_MK2_CLIP_01",//0x16C69281,
        "COMPONENT_SPECIALCARBINE_MK2_CLIP_02",//0xDE1FA12C,
        "COMPONENT_SPECIALCARBINE_MK2_CLIP_ARMORPIERCING",//0x51351635,
        "COMPONENT_SPECIALCARBINE_MK2_CLIP_FMJ",//0x503DEA90,
        "COMPONENT_SPECIALCARBINE_MK2_CLIP_INCENDIARY",//0xDE011286,
        "COMPONENT_SPECIALCARBINE_MK2_CLIP_TRACER",//0x8765C68A,
        "COMPONENT_SPECIALCARBINE_VARMOD_LOWRIDER",//0x730154F2,
        "COMPONENT_SWITCHBLADE_VARMOD_BASE",//0x9137A500,
        "COMPONENT_SWITCHBLADE_VARMOD_VAR1",//0x5B3E7DB6,
        "COMPONENT_SWITCHBLADE_VARMOD_VAR2",//0xE7939662,
        "COMPONENT_VINTAGEPISTOL_CLIP_01",//0x45A3B6BB,
        "COMPONENT_VINTAGEPISTOL_CLIP_02",//0x33BA12E8

        "COMPONENT_AT_AR_FLSH",//
        "COMPONENT_AT_AR_SUPP",//
        "COMPONENT_MILITARYRIFLE_CLIP_01",//
        "COMPONENT_MILITARYRIFLE_CLIP_02",//
        "COMPONENT_MILITARYRIFLE_SIGHT_01",//
        "COMPONENT_AT_SCOPE_SMALL",//
        "COMPONENT_AT_AR_FLSH",//
        "COMPONENT_AT_AR_SUPP",//

        "COMPONENT_HEAVYRIFLE_CLIP_01",// | 0x5AF49386
        "COMPONENT_HEAVYRIFLE_CLIP_02",//",// | 0x6CBF371B
        "COMPONENT_HEAVYRIFLE_SIGHT_01",// | 0xB3E1C452
        "COMPONENT_AT_SCOPE_MEDIUM",// | 0xA0D89C42
        "COMPONENT_AT_AR_FLSH",// | 0x7BC4CDDC
        "COMPONENT_AT_AR_SUPP",// | 0x837445AA
        "COMPONENT_AT_AR_AFGRIP",// | 0xC164F53
        "COMPONENT_HEAVYRIFLE_CAMO1",// | 0xEC9FECD9
        "COMPONENT_APPISTOL_VARMOD_SECURITY",//
        "COMPONENT_MICROSMG_VARMOD_SECURITY",//
        "COMPONENT_PUMPSHOTGUN_VARMOD_SECURITY",//

        "COMPONENT_AT_AR_FLSH_REH", //| 0x9DB1E023
        "COMPONENT_TACTICALRIFLE_CLIP_02", //| 0x8594554F
        "COMPONENT_AT_AR_SUPP_02", ///| 0xA73D4664
        "COMPONENT_BATTLERIFLE_CLIP_01",
        "COMPONENT_BATTLERIFLE_CLIP_02",
        "COMPONENT_AT_AR_SUPP"
    };
    inline const std::vector<Mod_Class::HairSets> MHairsets = {
    Mod_Class::HairSets(1, 0, "H_FMM_1_0", "Buzzcut Dark Brown", -1, -1),
    Mod_Class::HairSets(1, 1, "H_FMM_1_1", "Buzzcut Light Brown", -1, -1),
    Mod_Class::HairSets(1, 2, "H_FMM_1_2", "Buzzcut Auburn", -1, -1),
    Mod_Class::HairSets(1, 3, "H_FMM_1_3", "Buzzcut Blond", -1, -1),
    Mod_Class::HairSets(1, 4, "H_FMM_1_4", "Buzzcut Black", -1, -1),
    Mod_Class::HairSets(2, 0, "H_FMM_2_0", "Faux Hawk Dark Brown", -1, -1),
    Mod_Class::HairSets(2, 1, "H_FMM_2_1", "Faux Hawk Light Brown", -1, -1),
    Mod_Class::HairSets(2, 2, "H_FMM_2_2", "Faux Hawk Auburn", -1, -1),
    Mod_Class::HairSets(2, 3, "H_FMM_2_3", "Faux Hawk Blond", -1, -1),
    Mod_Class::HairSets(2, 4, "H_FMM_2_4", "Faux Hawk Black", -1, -1),
    Mod_Class::HairSets(2, 5, "H_FMM_2_5", "Faux Hawk Purple", -1, -1),
    Mod_Class::HairSets(3, 0, "H_FMM_3_0", "Hipster Shaved Dark Brown", -1, -1),
    Mod_Class::HairSets(3, 1, "H_FMM_3_1", "Hipster Shaved Light Brown", -1, -1),
    Mod_Class::HairSets(3, 2, "H_FMM_3_2", "Hipster Shaved Auburn", -1, -1),
    Mod_Class::HairSets(3, 3, "H_FMM_3_3", "Hipster Shaved Blond", -1, -1),
    Mod_Class::HairSets(3, 4, "H_FMM_3_4", "Hipster Shaved Black", -1, -1),
    Mod_Class::HairSets(3, 5, "H_FMM_3_5", "Hipster Shaved Red", -1, -1),
    Mod_Class::HairSets(4, 0, "H_FMM_4_0", "Side Parting Spiked Dark Brown", -1, -1),
    Mod_Class::HairSets(4, 1, "H_FMM_4_1", "Side Parting Spiked Light Brown", -1, -1),
    Mod_Class::HairSets(4, 2, "H_FMM_4_2", "Side Parting Spiked Auburn", -1, -1),
    Mod_Class::HairSets(4, 3, "H_FMM_4_3", "Side Parting Spiked Blond", -1, -1),
    Mod_Class::HairSets(4, 4, "H_FMM_4_4", "Side Parting Spiked Black", -1, -1),
    Mod_Class::HairSets(4, 6, "H_FMM_4_6", "Side Parting Spiked Blue", -1, -1),
    Mod_Class::HairSets(5, 0, "H_FMM_5_0", "Shorter Cut Dark Brown", -1, -1),
    Mod_Class::HairSets(5, 1, "H_FMM_5_1", "Shorter Cut Light Brown", -1, -1),
    Mod_Class::HairSets(5, 2, "H_FMM_5_2", "Shorter Cut Auburn", -1, -1),
    Mod_Class::HairSets(5, 3, "H_FMM_5_3", "Shorter Cut Blond", -1, -1),
    Mod_Class::HairSets(5, 4, "H_FMM_5_4", "Shorter Cut Black", -1, -1),
    Mod_Class::HairSets(5, 5, "H_FMM_5_5", "Shorter Cut Green", -1, -1),
    Mod_Class::HairSets(6, 0, "H_FMM_6_0", "Biker Dark Brown", -1, -1),
    Mod_Class::HairSets(6, 1, "H_FMM_6_1", "Biker Light Brown", -1, -1),
    Mod_Class::HairSets(6, 2, "H_FMM_6_2", "Biker Auburn", -1, -1),
    Mod_Class::HairSets(6, 3, "H_FMM_6_3", "Biker Blond", -1, -1),
    Mod_Class::HairSets(6, 4, "H_FMM_6_4", "Biker Black", -1, -1),
    Mod_Class::HairSets(6, 5, "H_FMM_6_5", "Biker Purple Fade", -1, -1),
    Mod_Class::HairSets(7, 0, "H_FMM_7_0", "Ponytail Dark Brown", -1, -1),
    Mod_Class::HairSets(7, 1, "H_FMM_7_1", "Ponytail Light Brown", -1, -1),
    Mod_Class::HairSets(7, 2, "H_FMM_7_2", "Ponytail Auburn", -1, -1),
    Mod_Class::HairSets(7, 3, "H_FMM_7_3", "Ponytail Blond", -1, -1),
    Mod_Class::HairSets(7, 4, "H_FMM_7_4", "Ponytail Black", -1, -1),
    Mod_Class::HairSets(7, 6, "H_FMM_7_6", "Ponytail Purple", -1, -1),
    Mod_Class::HairSets(8, 0, "H_FMM_8_0", "Cornrows Dark Brown", -1, -1),
    Mod_Class::HairSets(8, 1, "H_FMM_8_1", "Cornrows Light Brown", -1, -1),
    Mod_Class::HairSets(8, 2, "H_FMM_8_2", "Cornrows Auburn", -1, -1),
    Mod_Class::HairSets(8, 3, "H_FMM_8_3", "Cornrows Blond", -1, -1),
    Mod_Class::HairSets(8, 4, "H_FMM_8_4", "Cornrows Black", -1, -1),
    Mod_Class::HairSets(9, 0, "H_FMM_9_0", "Slicked Dark Brown", -1, -1),
    Mod_Class::HairSets(9, 1, "H_FMM_9_1", "Slicked Light Brown", -1, -1),
    Mod_Class::HairSets(9, 2, "H_FMM_9_2", "Slicked Auburn", -1, -1),
    Mod_Class::HairSets(9, 3, "H_FMM_9_3", "Slicked Blond", -1, -1),
    Mod_Class::HairSets(9, 4, "H_FMM_9_4", "Slicked Black", -1, -1),
    Mod_Class::HairSets(9, 6, "H_FMM_9_6", "Slicked Red", -1, -1),
    Mod_Class::HairSets(10, 0, "H_FMM_10_0", "Short Brushed Dark Brown", -1, -1),
    Mod_Class::HairSets(10, 1, "H_FMM_10_1", "Short Brushed Light Brown", -1, -1),
    Mod_Class::HairSets(10, 2, "H_FMM_10_2", "Short Brushed Auburn", -1, -1),
    Mod_Class::HairSets(10, 3, "H_FMM_10_3", "Short Brushed Blond", -1, -1),
    Mod_Class::HairSets(10, 4, "H_FMM_10_4", "Short Brushed Black", -1, -1),
    Mod_Class::HairSets(11, 0, "H_FMM_11_0", "Spikey Dark Brown", -1, -1),
    Mod_Class::HairSets(11, 1, "H_FMM_11_1", "Spikey Light Brown", -1, -1),
    Mod_Class::HairSets(11, 2, "H_FMM_11_2", "Spikey Auburn", -1, -1),
    Mod_Class::HairSets(11, 3, "H_FMM_11_3", "Spikey Blond", -1, -1),
    Mod_Class::HairSets(11, 4, "H_FMM_11_4", "Spikey Black", -1, -1),
    Mod_Class::HairSets(11, 5, "H_FMM_11_5", "Spikey Blue", -1, -1),
    Mod_Class::HairSets(12, 0, "H_FMM_12_0", "Caesar Dark Brown", -1, -1),
    Mod_Class::HairSets(12, 1, "H_FMM_12_1", "Caesar Light Brown", -1, -1),
    Mod_Class::HairSets(12, 2, "H_FMM_12_2", "Caesar Auburn", -1, -1),
    Mod_Class::HairSets(12, 3, "H_FMM_12_3", "Caesar Blond", -1, -1),
    Mod_Class::HairSets(12, 4, "H_FMM_12_4", "Caesar Black", -1, -1),
    Mod_Class::HairSets(13, 0, "H_FMM_13_0", "Chopped Dark Brown", -1, -1),
    Mod_Class::HairSets(13, 1, "H_FMM_13_1", "Chopped Light Brown", -1, -1),
    Mod_Class::HairSets(13, 2, "H_FMM_13_2", "Chopped Auburn", -1, -1),
    Mod_Class::HairSets(13, 3, "H_FMM_13_3", "Chopped Blond", -1, -1),
    Mod_Class::HairSets(13, 4, "H_FMM_13_4", "Chopped Black", -1, -1),
    Mod_Class::HairSets(13, 5, "H_FMM_13_5", "Chopped Green", -1, -1),
    Mod_Class::HairSets(14, 0, "H_FMM_14_0", "Dreads Dark Brown", -1, -1),
    Mod_Class::HairSets(14, 1, "H_FMM_14_1", "Dreads Light Brown", -1, -1),
    Mod_Class::HairSets(14, 2, "H_FMM_14_2", "Dreads Auburn", -1, -1),
    Mod_Class::HairSets(14, 3, "H_FMM_14_3", "Dreads Blond", -1, -1),
    Mod_Class::HairSets(14, 4, "H_FMM_14_4", "Dreads Black", -1, -1),
    Mod_Class::HairSets(15, 0, "H_FMM_15_0", "Long Hair Dark Brown", -1, -1),
    Mod_Class::HairSets(15, 1, "H_FMM_15_1", "Long Hair Light Brown", -1, -1),
    Mod_Class::HairSets(15, 2, "H_FMM_15_2", "Long Hair Auburn", -1, -1),
    Mod_Class::HairSets(15, 3, "H_FMM_15_3", "Long Hair Blond", -1, -1),
    Mod_Class::HairSets(15, 4, "H_FMM_15_4", "Long Hair Black", -1, -1),
    Mod_Class::HairSets(15, 5, "H_FMM_15_5", "Long Hair Purple Fade", -1, -1),
    Mod_Class::HairSets(16, 0, "CLO_BBM_H_00", "Shaggy Curls Dark Brown", -1, -1),
    Mod_Class::HairSets(16, 1, "CLO_BBM_H_01", "Shaggy Curls Light Brown", -1, -1),
    Mod_Class::HairSets(16, 2, "CLO_BBM_H_02", "Shaggy Curls Auburn", -1, -1),
    Mod_Class::HairSets(16, 3, "CLO_BBM_H_03", "Shaggy Curls Blonde", -1, -1),
    Mod_Class::HairSets(16, 4, "CLO_BBM_H_04", "Shaggy Curls Black", -1, -1),
    Mod_Class::HairSets(17, 0, "CLO_BBM_H_05", "Surfer Dude Dark Brown", -1, -1),
    Mod_Class::HairSets(17, 1, "CLO_BBM_H_06", "Surfer Dude Light Brown", -1, -1),
    Mod_Class::HairSets(17, 2, "CLO_BBM_H_07", "Surfer Dude Auburn", -1, -1),
    Mod_Class::HairSets(17, 3, "CLO_BBM_H_08", "Surfer Dude Blonde", -1, -1),
    Mod_Class::HairSets(17, 4, "CLO_BBM_H_09", "Surfer Dude Black", -1, -1),
    Mod_Class::HairSets(18, 0, "CLO_BUS_H_0_0", "Short Side Part Dark Brown", -2086773, 224730392),
    Mod_Class::HairSets(18, 1, "CLO_BUS_H_0_1", "Short Side Part Light Brown", -2086773, 1988816738),
    Mod_Class::HairSets(18, 2, "CLO_BUS_H_0_2", "Short Side Part Auburn", -2086773, 736778786),
    Mod_Class::HairSets(18, 3, "CLO_BUS_H_0_3", "Short Side Part Blonde", -2086773, 439629494),
    Mod_Class::HairSets(18, 4, "CLO_BUS_H_0_4", "Short Side Part Black", -2086773, 1048444745),
    Mod_Class::HairSets(19, 0, "CLO_BUS_H_1_0", "High Slicked Sides Dark Brown", -2086773, 2140603469),
    Mod_Class::HairSets(19, 1, "CLO_BUS_H_1_1", "High Slicked Sides Light Brown", -2086773, -681528353),
    Mod_Class::HairSets(19, 2, "CLO_BUS_H_1_2", "High Slicked Sides Auburn", -2086773, 1006238992),
    Mod_Class::HairSets(19, 3, "CLO_BUS_H_1_3", "High Slicked Sides Blonde", -2086773, 214245031),
    Mod_Class::HairSets(19, 4, "CLO_BUS_H_1_4", "High Slicked Sides Black", -2086773, 689952604),
    Mod_Class::HairSets(20, 0, "CLO_HP_HR_0_0", "Long Slicked Dark Brown", -1398869298, 965649655),
    Mod_Class::HairSets(20, 1, "CLO_HP_HR_0_1", "Long Slicked Light Brown", -1398869298, 718800778),
    Mod_Class::HairSets(20, 2, "CLO_HP_HR_0_2", "Long Slicked Auburn", -1398869298, 1959959422),
    Mod_Class::HairSets(20, 3, "CLO_HP_HR_0_3", "Long Slicked Blonde", -1398869298, 1200177388),
    Mod_Class::HairSets(20, 4, "CLO_HP_HR_0_4", "Long Slicked Black", -1398869298, -1874439579),
    Mod_Class::HairSets(21, 0, "CLO_HP_HR_1_0", "Hipster Youth Dark Brown", -1398869298, -1679505893),
    Mod_Class::HairSets(21, 1, "CLO_HP_HR_1_1", "Hipster Youth Blonde", -1398869298, -1976229188),
    Mod_Class::HairSets(21, 2, "CLO_HP_HR_1_2", "Hipster Youth Auburn", -1398869298, 2037875009),
    Mod_Class::HairSets(21, 3, "CLO_HP_HR_1_3", "Hipster Youth Light Brown", -1398869298, -235146664),
    Mod_Class::HairSets(21, 4, "CLO_HP_HR_1_4", "Hipster Youth Black", -1398869298, -441853516),
    Mod_Class::HairSets(22, 0, "CLO_IND_H_0_0", "Mullet Dark Brown", -1, -1),
    Mod_Class::HairSets(22, 1, "CLO_IND_H_0_1", "Mullet Light Brown", -1, -1),
    Mod_Class::HairSets(22, 2, "CLO_IND_H_0_2", "Mullet Auburn", -1, -1),
    Mod_Class::HairSets(22, 3, "CLO_IND_H_0_3", "Mullet Blonde", -1, -1),
    Mod_Class::HairSets(22, 4, "CLO_IND_H_0_4", "Mullet Black", -1, -1),
    Mod_Class::HairSets(24, 0, "CLO_S1M_H_0_0", "Classic Cornrows", 62137527, 534771589),
    Mod_Class::HairSets(25, 0, "CLO_S1M_H_1_0", "Palm Cornrows", 62137527, -1340139519),
    Mod_Class::HairSets(26, 0, "CLO_S1M_H_2_0", "Lightning Cornrows", 62137527, -849980761),
    Mod_Class::HairSets(27, 0, "CLO_S1M_H_3_0", "Whipped Cornrows", 62137527, -551553478),
    Mod_Class::HairSets(28, 0, "CLO_S2M_H_0_0", "Zig Zag Cornrows", 1529191571, -1431204514),
    Mod_Class::HairSets(29, 0, "CLO_S2M_H_1_0", "Snail Cornrows", 1529191571, -1133334304),
    Mod_Class::HairSets(30, 0, "CLO_S2M_H_2_0", "Hightop", 1529191571, -1809784771),
    Mod_Class::HairSets(31, 0, "CLO_BIM_H_0_0", "Loose Swept Back", -240234547, 1431846777),
    Mod_Class::HairSets(32, 0, "CLO_BIM_H_1_0", "Undercut Swept Back", -240234547, -460168116),
    Mod_Class::HairSets(33, 0, "CLO_BIM_H_2_0", "Undercut Swept Side", -240234547, -311245907),
    Mod_Class::HairSets(34, 0, "CLO_BIM_H_3_0", "Spiked Mohawk", -240234547, -942031335),
    Mod_Class::HairSets(35, 0, "CLO_BIM_H_4_0", "Mod", -240234547, -644503216),
    Mod_Class::HairSets(36, 0, "CLO_BIM_H_5_0", "Layered Mod", -240234547, 211198653),
    Mod_Class::HairSets(37, 0, "CC_M_HS_1", "Buzzcut", 598190139, 739308497),
    Mod_Class::HairSets(38, 0, "CC_M_HS_2", "Faux Hawk", 598190139, 495343292),
    Mod_Class::HairSets(39, 0, "CC_M_HS_3", "Hipster", 598190139, -1686711653),
    Mod_Class::HairSets(40, 0, "CC_M_HS_4", "Side Parting", 598190139, 1187457341),
    Mod_Class::HairSets(41, 0, "CC_M_HS_5", "Shorter Cut", 598190139, 956403122),
    Mod_Class::HairSets(42, 0, "CC_M_HS_6", "Biker", 598190139, 1647042566),
    Mod_Class::HairSets(43, 0, "CC_M_HS_7", "Ponytail", 598190139, -461478743),
    Mod_Class::HairSets(44, 0, "CC_M_HS_8", "Cornrows", 598190139, -1883325653),
    Mod_Class::HairSets(45, 0, "CC_M_HS_9", "Slicked", 598190139, -2114248796),
    Mod_Class::HairSets(46, 0, "CC_M_HS_10", "Short Brushed", 598190139, 314228205),
    Mod_Class::HairSets(47, 0, "CC_M_HS_11", "Spikey", 598190139, 1503775674),
    Mod_Class::HairSets(48, 0, "CC_M_HS_12", "Caesar", 598190139, 1862399610),
    Mod_Class::HairSets(49, 0, "CC_M_HS_13", "Chopped", 598190139, 708472048),
    Mod_Class::HairSets(50, 0, "CC_M_HS_14", "Dreads", 598190139, -1207367545),
    Mod_Class::HairSets(51, 0, "CC_M_HS_15", "Long Hair", 598190139, 111650251),
    Mod_Class::HairSets(52, 0, "CLO_BBM_H_00", "Shaggy Curls Dark Brown", -1, -1),
    Mod_Class::HairSets(53, 0, "CLO_BBM_H_05", "Surfer Dude Dark Brown", -1, -1),
    Mod_Class::HairSets(54, 0, "CLO_BUS_H_0_0", "Short Side Part Dark Brown", -2086773, 224730392),
    Mod_Class::HairSets(55, 0, "CLO_BUS_H_1_0", "High Slicked Sides Dark Brown", -2086773, 2140603469),
    Mod_Class::HairSets(56, 0, "CLO_HP_HR_0_0", "Long Slicked Dark Brown", -1398869298, 965649655),
    Mod_Class::HairSets(57, 0, "CLO_HP_HR_1_0", "Hipster Youth Dark Brown", -1398869298, -1679505893),
    Mod_Class::HairSets(58, 0, "CLO_IND_H_0_0", "Mullet Dark Brown", -1, -1),
    Mod_Class::HairSets(59, 0, "CLO_S1M_H_0_0", "Classic Cornrows", 62137527, 534771589),
    Mod_Class::HairSets(60, 0, "CLO_S1M_H_1_0", "Palm Cornrows", 62137527, -1340139519),
    Mod_Class::HairSets(61, 0, "CLO_S1M_H_2_0", "Lightning Cornrows", 62137527, -849980761),
    Mod_Class::HairSets(62, 0, "CLO_S1M_H_3_0", "Whipped Cornrows", 62137527, -551553478),
    Mod_Class::HairSets(63, 0, "CLO_S2M_H_0_0", "Zig Zag Cornrows", 1529191571, -1431204514),
    Mod_Class::HairSets(64, 0, "CLO_S2M_H_1_0", "Snail Cornrows", 1529191571, -1133334304),
    Mod_Class::HairSets(65, 0, "CLO_S2M_H_2_0", "Hightop", 1529191571, -1809784771),
    Mod_Class::HairSets(66, 0, "CLO_BIM_H_0_0", "Loose Swept Back", -240234547, 1431846777),
    Mod_Class::HairSets(67, 0, "CLO_BIM_H_1_0", "Undercut Swept Back", -240234547, -460168116),
    Mod_Class::HairSets(68, 0, "CLO_BIM_H_2_0", "Undercut Swept Side", -240234547, -311245907),
    Mod_Class::HairSets(69, 0, "CLO_BIM_H_3_0", "Spiked Mohawk", -240234547, -942031335),
    Mod_Class::HairSets(70, 0, "CLO_BIM_H_4_0", "Mod", -240234547, -644503216),
    Mod_Class::HairSets(71, 0, "CLO_BIM_H_5_0", "Layered Mod", -240234547, 211198653),
    Mod_Class::HairSets(72, 0, "CLO_GRM_H_0_0", "Flattop", 1616273011, -1119221482),
    Mod_Class::HairSets(73, 0, "CLO_GRM_H_1_0", "Military Buzzcut", 1616273011, -1642199958),
    Mod_Class::HairSets(74, 0, "CLO_VWM_H_0_0", "Impotent Rage", 1347816957, -599666460),
    Mod_Class::HairSets(75, 0, "CLO_TRM_H_0_0", "Afro Faded", -1970774728, -416636904),
    Mod_Class::HairSets(76, 0, "CLO_FXM_H_0_0", "Top Knot", 601646824, 1334100948),
    Mod_Class::HairSets(77, 0, "CLO_SBM_H_0_0", "Two Block", 987639353, -1927370417),
    Mod_Class::HairSets(78, 0, "CLO_SBM_H_1_0", "Shaggy Mullet", 987639353, -1088161005)
    };
    inline const std::vector<Mod_Class::HairSets> FHairsets = {
        Mod_Class::HairSets(1, 0, "H_FMF_1_0","Short Chestnut", -1, -1),
        Mod_Class::HairSets(1, 1, "H_FMF_1_1","Short Blonde", -1, -1),
        Mod_Class::HairSets(1, 2, "H_FMF_1_2","Short Auburn", -1, -1),
        Mod_Class::HairSets(1, 3, "H_FMF_1_3","Short Black", -1, -1),
        Mod_Class::HairSets(1, 4, "H_FMF_1_4","Short Brown", -1, -1),
        Mod_Class::HairSets(1, 5, "H_FMF_1_5","Short Purple", -1, -1),

        Mod_Class::HairSets(2, 0, "H_FMF_2_0","Layered Bob Chestnut", -1, -1),
        Mod_Class::HairSets(2, 1, "H_FMF_2_1","Layered Bob Blonde", -1, -1),
        Mod_Class::HairSets(2, 2, "H_FMF_2_2","Layered Bob Auburn", -1, -1),
        Mod_Class::HairSets(2, 3, "H_FMF_2_3","Layered Bob Black", -1, -1),
        Mod_Class::HairSets(2, 4, "H_FMF_2_4","Layered Bob Brown", -1, -1),
        Mod_Class::HairSets(2, 5, "H_FMF_2_5","Layered Bob Green", -1, -1),

        Mod_Class::HairSets(3, 0, "H_FMF_3_0","Pigtails Chestnut", -1, -1),
        Mod_Class::HairSets(3, 1, "H_FMF_3_1","Pigtails Blonde", -1, -1),
        Mod_Class::HairSets(3, 2, "H_FMF_3_2","Pigtails Auburn", -1, -1),
        Mod_Class::HairSets(3, 3, "H_FMF_3_3","Pigtails Black", -1, -1),
        Mod_Class::HairSets(3, 4, "H_FMF_3_4","Pigtails Brown", -1, -1),

        Mod_Class::HairSets(4, 0, "H_FMF_4_0","Ponytail Chestnut", -1, -1),
        Mod_Class::HairSets(4, 1, "H_FMF_4_1","Ponytail Blonde", -1, -1),
        Mod_Class::HairSets(4, 2, "H_FMF_4_2","Ponytail Auburn", -1, -1),
        Mod_Class::HairSets(4, 3, "H_FMF_4_3","Ponytail Black", -1, -1),
        Mod_Class::HairSets(4, 4, "H_FMF_4_4","Ponytail Brown", -1, -1),
        Mod_Class::HairSets(4, 5, "H_FMF_4_5","Ponytail Blue", -1, -1),

        Mod_Class::HairSets(5, 0, "H_FMF_5_0","Braided Mohawk Chestnut", -1, -1),
        Mod_Class::HairSets(5, 1, "H_FMF_5_1","Braided Mohawk Blonde", -1, -1),
        Mod_Class::HairSets(5, 2, "H_FMF_5_2","Braided Mohawk Auburn", -1, -1),
        Mod_Class::HairSets(5, 3, "H_FMF_5_3","Braided Mohawk Black", -1, -1),
        Mod_Class::HairSets(5, 4, "H_FMF_5_4","Braided Mohawk Brown", -1, -1),
        Mod_Class::HairSets(5, 5, "H_FMF_5_5","Braided Mohawk Pink", -1, -1),

        Mod_Class::HairSets(6, 0, "H_FMF_6_0","Braids Chestnut", -1, -1),
        Mod_Class::HairSets(6, 1, "H_FMF_6_1","Braids Blonde", -1, -1),
        Mod_Class::HairSets(6, 2, "H_FMF_6_2","Braids Auburn", -1, -1),
        Mod_Class::HairSets(6, 3, "H_FMF_6_3","Braids Black", -1, -1),
        Mod_Class::HairSets(6, 4, "H_FMF_6_4","Braids Brown", -1, -1),

        Mod_Class::HairSets(7, 0, "H_FMF_7_0","Bob Chestnut", -1, -1),
        //Mod_Class::HairSets(7, 1, "H_FMF_7_1","Bob Blonde", -1, -1),
        //Mod_Class::HairSets(7, 2, "H_FMF_7_2","Bob Auburn", -1, -1),
        //Mod_Class::HairSets(7, 3, "H_FMF_7_3","Bob Black", -1, -1),
        //Mod_Class::HairSets(7, 4, "H_FMF_7_4","Bob Brown", -1, -1),
        //Mod_Class::HairSets(7, 5, "H_FMF_7_5","Bob Purple Fade", -1, -1),

        Mod_Class::HairSets(8, 0, "H_FMF_8_0","Faux Hawk Chestnut", -1, -1),
        Mod_Class::HairSets(8, 1, "H_FMF_8_1","Faux Hawk Blonde", -1, -1),
        Mod_Class::HairSets(8, 2, "H_FMF_8_2","Faux Hawk Auburn", -1, -1),
        Mod_Class::HairSets(8, 3, "H_FMF_8_3","Faux Hawk Black", -1, -1),
        Mod_Class::HairSets(8, 4, "H_FMF_8_4","Faux Hawk Brown", -1, -1),
        Mod_Class::HairSets(8, 5, "H_FMF_8_5","Faux Hawk Pink", -1, -1),

        Mod_Class::HairSets(9, 0, "H_FMF_9_0","French Twist Chestnut", -1, -1),
        Mod_Class::HairSets(9, 1, "H_FMF_9_1","French Twist Blonde", -1, -1),
        Mod_Class::HairSets(9, 2, "H_FMF_9_2","French Twist Auburn", -1, -1),
        Mod_Class::HairSets(9, 3, "H_FMF_9_3","French Twist Black", -1, -1),
        Mod_Class::HairSets(9, 4, "H_FMF_9_4","French Twist Brown", -1, -1),

        Mod_Class::HairSets(10, 0, "H_FMF_10_0","Long Bob Chestnut", -1, -1),
        Mod_Class::HairSets(10, 1, "H_FMF_10_1","Long Bob Blonde", -1, -1),
        Mod_Class::HairSets(10, 2, "H_FMF_10_2","Long Bob Auburn", -1, -1),
        Mod_Class::HairSets(10, 3, "H_FMF_10_3","Long Bob Black", -1, -1),
        Mod_Class::HairSets(10, 4, "H_FMF_10_4","Long Bob Brown", -1, -1),
        Mod_Class::HairSets(10, 6, "H_FMF_10_6","Long Bob Purple Fade", -1, -1),

        Mod_Class::HairSets(11, 0, "H_FMF_11_0","Loose Tied Chestnut", -1, -1),
        Mod_Class::HairSets(11, 1, "H_FMF_11_1","Loose Tied Blonde", -1, -1),
        Mod_Class::HairSets(11, 2, "H_FMF_11_2","Loose Tied Auburn", -1, -1),
        Mod_Class::HairSets(11, 3, "H_FMF_11_3","Loose Tied Black", -1, -1),
        Mod_Class::HairSets(11, 4, "H_FMF_11_4","Loose Tied Brown", -1, -1),
        Mod_Class::HairSets(11, 6, "H_FMF_11_6","Loose Tied Green", -1, -1),

        Mod_Class::HairSets(12, 0, "H_FMF_12_0","Pixie Chestnut", -1, -1),
        Mod_Class::HairSets(12, 1, "H_FMF_12_1","Pixie Blonde", -1, -1),
        Mod_Class::HairSets(12, 2, "H_FMF_12_2","Pixie Auburn", -1, -1),
        Mod_Class::HairSets(12, 3, "H_FMF_12_3","Pixie Black", -1, -1),
        Mod_Class::HairSets(12, 4, "H_FMF_12_4","Pixie Brown", -1, -1),
        Mod_Class::HairSets(12, 5, "H_FMF_12_5","Pixie Blue", -1, -1),

        Mod_Class::HairSets(13, 0, "H_FMF_13_0","Shaved Bangs Chestnut", -1, -1),
        Mod_Class::HairSets(13, 1, "H_FMF_13_1","Shaved Bangs Blonde", -1, -1),
        Mod_Class::HairSets(13, 2, "H_FMF_13_2","Shaved Bangs Auburn", -1, -1),
        Mod_Class::HairSets(13, 3, "H_FMF_13_3","Shaved Bangs Black", -1, -1),
        Mod_Class::HairSets(13, 4, "H_FMF_13_4","Shaved Bangs Brown", -1, -1),
        Mod_Class::HairSets(13, 5, "H_FMF_13_5","Shaved Bangs Blue Fade", -1, -1),

        Mod_Class::HairSets(14, 0, "H_FMF_14_0","Top Knot Chestnut", -1, -1),
        Mod_Class::HairSets(14, 1, "H_FMF_14_1","Top Knot Blonde", -1, -1),
        Mod_Class::HairSets(14, 2, "H_FMF_14_2","Top Knot Auburn", -1, -1),
        Mod_Class::HairSets(14, 3, "H_FMF_14_3","Top Knot Black", -1, -1),
        Mod_Class::HairSets(14, 4, "H_FMF_14_4","Top Knot Brown", -1, -1),

        Mod_Class::HairSets(15, 0, "H_FMF_15_0","Wavy Bob Chestnut", -1, -1),
        Mod_Class::HairSets(15, 1, "H_FMF_15_1","Wavy Bob Blonde", -1, -1),
        Mod_Class::HairSets(15, 2, "H_FMF_15_2","Wavy Bob Auburn", -1, -1),
        Mod_Class::HairSets(15, 3, "H_FMF_15_3","Wavy Bob Black", -1, -1),
        Mod_Class::HairSets(15, 4, "H_FMF_15_4","Wavy Bob Brown", -1, -1),
        Mod_Class::HairSets(15, 6, "H_FMF_15_6","Wavy Bob Red Fade", -1, -1),

        Mod_Class::HairSets(16, 0, "CLO_BBF_H_00","Pin Up Girl Chestnut", -1, -1),
        Mod_Class::HairSets(16, 1, "CLO_BBF_H_01","Pin Up Girl Blonde", -1, -1),
        Mod_Class::HairSets(16, 2, "CLO_BBF_H_02","Pin Up Girl Auburn", -1, -1),
        Mod_Class::HairSets(16, 3, "CLO_BBF_H_03","Pin Up Girl Black", -1, -1),
        Mod_Class::HairSets(16, 4, "CLO_BBF_H_04","Pin Up Girl Brown", -1, -1),

        Mod_Class::HairSets(17, 0, "CLO_BBF_H_05","Messy Bun Chestnut", -1398869298, -811206225),
        Mod_Class::HairSets(17, 1, "CLO_BBF_H_06","Messy Bun Blonde", -1398869298, -1586815686),
        Mod_Class::HairSets(17, 2, "CLO_BBF_H_07","Messy Bun Auburn", -1398869298, -1423429452),
        Mod_Class::HairSets(17, 3, "CLO_BBF_H_08","Messy Bun Black", -1398869298, -1697869815),
        Mod_Class::HairSets(17, 4, "CLO_BBF_H_09","Messy Bun Brown", -1398869298, -1470846183),

        Mod_Class::HairSets(18, 0, "CLO_VALF_H_0_0","Flapper Bob Chestnut", -1, -1),
        Mod_Class::HairSets(18, 1, "CLO_VALF_H_0_1","Flapper Bob Blonde", -1, -1),
        Mod_Class::HairSets(18, 2, "CLO_VALF_H_0_2","Flapper Bob Auburn", -1, -1),
        Mod_Class::HairSets(18, 3, "CLO_VALF_H_0_3","Flapper Bob Black", -1, -1),
        Mod_Class::HairSets(18, 4, "CLO_VALF_H_0_4","Flapper Bob Brown", -1, -1),
        Mod_Class::HairSets(18, 5, "CLO_VALF_H_0_5","Flapper Bob Blue", -1, -1),

        Mod_Class::HairSets(19, 0, "CLO_BUS_F_H_0_0","Tight Bun Black", -2086773, -1816086813),
        Mod_Class::HairSets(19, 1, "CLO_BUS_F_H_0_1","Tight Bun Brown", -2086773, -2113006722),
        Mod_Class::HairSets(19, 2, "CLO_BUS_F_H_0_2","Tight Bun Auburn", -2086773, -1398740829),
        Mod_Class::HairSets(19, 3, "CLO_BUS_F_H_0_3","Tight Bun Chestnut", -2086773, -131530830),
        Mod_Class::HairSets(19, 4, "CLO_BUS_F_H_0_4","Tight Bun Blonde", -2086773, -1101886458),

        Mod_Class::HairSets(20, 0, "CLO_BUS_F_H_1_0","Twisted Bob Chestnut", -1398869298, 558694786),
        Mod_Class::HairSets(20, 1, "CLO_BUS_F_H_1_1","Twisted Bob Black", -1398869298, 569279177),
        Mod_Class::HairSets(20, 2, "CLO_BUS_F_H_1_2","Twisted Bob Auburn", -1398869298, 544309199),
        Mod_Class::HairSets(20, 3, "CLO_BUS_F_H_1_3","Twisted Bob Brown", -1398869298, 1190448341),
        Mod_Class::HairSets(20, 4, "CLO_BUS_F_H_1_4","Twisted Bob Blonde", -1398869298, 885139568),

        Mod_Class::HairSets(21, 0, "CLO_HP_F_HR_0_0","Big Bangs Chestnut", -1, -1),
        Mod_Class::HairSets(21, 1, "CLO_HP_F_HR_0_1","Big Bangs Blonde", -1, -1),
        Mod_Class::HairSets(21, 2, "CLO_HP_F_HR_0_2","Big Bangs Auburn", -1, -1),
        Mod_Class::HairSets(21, 3, "CLO_HP_F_HR_0_3","Big Bangs Black", -1, -1),
        Mod_Class::HairSets(21, 4, "CLO_HP_F_HR_0_4","Big Bangs Brown", -1, -1),

        Mod_Class::HairSets(22, 0, "CLO_HP_F_HR_1_0","Braided Top Knot Chestnut", -1398869298, -1845683606),
        Mod_Class::HairSets(22, 1, "CLO_HP_F_HR_1_1","Braided Top Knot Blonde", -1398869298, -1555317497),
        Mod_Class::HairSets(22, 2, "CLO_HP_F_HR_1_2","Braided Top Knot Auburn", -1398869298, 1704673699),
        Mod_Class::HairSets(22, 3, "CLO_HP_F_HR_1_3","Braided Top Knot Black", -1398869298, 1993401358),
        Mod_Class::HairSets(22, 4, "CLO_HP_F_HR_1_4","Braided Top Knot Brown", -1398869298, 1227065524),

        Mod_Class::HairSets(23, 0, "CLO_INDF_H_0_0","Mullet Chestnut", -1, -1),
        Mod_Class::HairSets(23, 1, "CLO_INDF_H_0_1","Mullet Blonde", -1, -1),
        Mod_Class::HairSets(23, 2, "CLO_INDF_H_0_2","Mullet Auburn", -1, -1),
        Mod_Class::HairSets(23, 3, "CLO_INDF_H_0_3","Mullet Black", -1, -1),
        Mod_Class::HairSets(23, 4, "CLO_INDF_H_0_4","Mullet Brown", -1, -1),

        Mod_Class::HairSets(25, 0, "CLO_S1F_H_0_0","Pinched Cornrows", 62137527, -1325458477),
        Mod_Class::HairSets(26, 0, "CLO_S1F_H_1_0","Leaf Cornrows", 62137527, -566725051),
        Mod_Class::HairSets(27, 0, "CLO_S1F_H_2_0","Zig Zag Cornrows", 62137527, -787850263),
        Mod_Class::HairSets(28, 0, "CLO_S1F_H_3_0","Pigtail Bangs", 1529191571, 2039295216),
        Mod_Class::HairSets(29, 0, "CLO_S2F_H_0_0","Wave Braids", 1529191571, 2039295216),
        Mod_Class::HairSets(30, 0, "CLO_S2F_H_1_0","Coil Braids", 1529191571, 1800147054),
        Mod_Class::HairSets(31, 0, "CLO_S2F_H_2_0","Rolled Quiff", 1529191571, -2019505897),
        Mod_Class::HairSets(32, 0, "CLO_BIF_H_0_0","Loose Swept Back", -240234547, -328340062),
        Mod_Class::HairSets(33, 0, "CLO_BIF_H_1_0","Undercut Swept Back", -240234547, 1657725123),
        Mod_Class::HairSets(34, 0, "CLO_BIF_H_2_0","Undercut Swept Side", -240234547, -1517964336),
        Mod_Class::HairSets(35, 0, "CLO_BIF_H_3_0","Spiked Mohawk", -240234547, 1677522529),
        Mod_Class::HairSets(36, 0, "CLO_BIF_H_4_0","Bandana and Braid", 598190139, -1362677538),
        Mod_Class::HairSets(37, 0, "CLO_BIF_H_6_0","Skinbyrd", -240234547, 1841934566),
        Mod_Class::HairSets(38, 0, "CLO_BIF_H_5_0","Layered Mod", -240234547, 1742494019),
        Mod_Class::HairSets(39, 0, "CC_F_HS_1","Short", 598190139, 104062694),
        Mod_Class::HairSets(40, 0, "CC_F_HS_2","Layered Bob", 598190139, 869579299),
        Mod_Class::HairSets(41, 0, "CC_F_HS_3","Pigtails", 598190139, 1201332655),
        Mod_Class::HairSets(42, 0, "CC_F_HS_4","Ponytail", 598190139, 1028967715),
        Mod_Class::HairSets(43, 0, "CC_F_HS_5","Braided Mohawk", 598190139, -1651634800),
        Mod_Class::HairSets(44, 0, "CC_F_HS_6","Braids", 598190139, -892278763),
        Mod_Class::HairSets(45, 0, "CC_F_HS_7","Bob", 598190139, -1032005779),
        Mod_Class::HairSets(46, 0, "CC_F_HS_8","Faux Hawk", 598190139, -255675400),
        Mod_Class::HairSets(47, 0, "CC_F_HS_9","French Twist", 598190139, 1890137027),
        Mod_Class::HairSets(48, 0, "CC_F_HS_10","Long Bob", 598190139, -406805808),
        Mod_Class::HairSets(49, 0, "CC_F_HS_11","Loose Tied", 598190139, -592540500),
        Mod_Class::HairSets(50, 0, "CC_F_HS_12","Pixie", 598190139, 205417419),
        Mod_Class::HairSets(51, 0, "CC_F_HS_13","Shaved Bangs", 598190139, -2127276619),
        Mod_Class::HairSets(52, 0, "CC_F_HS_14","Top Knot", 598190139, -1362677538),
        Mod_Class::HairSets(53, 0, "CC_F_HS_15","Wavy Bob", 598190139, -1549722990),
        Mod_Class::HairSets(54, 0, "CLO_BBF_H_05","Messy Bun Chestnut", -1398869298, -811206225),
        Mod_Class::HairSets(55, 0, "CLO_BBF_H_00","Pin Up Girl Chestnut", -1, -1),
        Mod_Class::HairSets(56, 0, "CLO_BUS_F_H_0_0","Tight Bun Black", -2086773, -1816086813),
        Mod_Class::HairSets(57, 0, "CLO_BUS_F_H_1_0","Twisted Bob Chestnut", -1398869298, 558694786),
        Mod_Class::HairSets(58, 0, "CLO_VALF_H_0_0","Flapper Bob Chestnut", -1, -1),
        Mod_Class::HairSets(59, 0, "CLO_HP_F_HR_0_0","Big Bangs Chestnut", -1, -1),
        Mod_Class::HairSets(60, 0, "CLO_HP_F_HR_1_0","Braided Top Knot Chestnut", -1398869298, -1845683606),
        Mod_Class::HairSets(61, 0, "CLO_INDF_H_0_0","Mullet Chestnut", -1, -1),
        Mod_Class::HairSets(62, 0, "CLO_S1F_H_0_0","Pinched Cornrows", 62137527, -1325458477),
        Mod_Class::HairSets(63, 0, "CLO_S1F_H_1_0","Leaf Cornrows", 62137527, -566725051),
        Mod_Class::HairSets(64, 0, "CLO_S1F_H_2_0","Zig Zag Cornrows", 62137527, -787850263),
        Mod_Class::HairSets(65, 0, "CLO_S1F_H_3_0","Pigtail Bangs", 1529191571, 2039295216),
        Mod_Class::HairSets(66, 0, "CLO_S2F_H_0_0","Wave Braids", 1529191571, 2039295216),
        Mod_Class::HairSets(67, 0, "CLO_S2F_H_1_0","Coil Braids", 1529191571, 1800147054),
        Mod_Class::HairSets(68, 0, "CLO_S2F_H_2_0","Rolled Quiff", 1529191571, -2019505897),
        Mod_Class::HairSets(69, 0, "CLO_BIF_H_0_0","Loose Swept Back", -240234547, -328340062),
        Mod_Class::HairSets(70, 0, "CLO_BIF_H_1_0","Undercut Swept Back", -240234547, 1657725123),
        Mod_Class::HairSets(71, 0, "CLO_BIF_H_2_0","Undercut Swept Side", -240234547, -1517964336),
        Mod_Class::HairSets(72, 0, "CLO_BIF_H_3_0","Spiked Mohawk", -240234547, 1677522529),
        Mod_Class::HairSets(73, 0, "CLO_BIF_H_4_0","Bandana and Braid", 598190139, -1362677538),
        Mod_Class::HairSets(74, 0, "CLO_BIF_H_5_0","Layered Mod", -240234547, 1742494019),
        Mod_Class::HairSets(75, 0, "CLO_BIF_H_6_0","Skinbyrd", -240234547, 1841934566),
        Mod_Class::HairSets(76, 0, "CLO_GRF_H_0_0","Neat Bun", 1616273011, 687338866),
        Mod_Class::HairSets(77, 0, "CLO_GRF_H_1_0","Short Bob", 1616273011, 1827923343),
        Mod_Class::HairSets(78, 0, "CLO_VWF_H_0_0","Impotent Rage", 1347816957, 987747946),
        Mod_Class::HairSets(79, 0, "CLO_TRF_H_0_0","Afro", -1970774728, -2025496493),
        Mod_Class::HairSets(80, 0, "CLO_FXF_H_0_0","Pixie Wavy", 601646824, -974054285),
        Mod_Class::HairSets(81, 0, "CLO_SBF_H_0_0","Short Tucked Bob", 987639353, -606892013),
        Mod_Class::HairSets(82, 0, "CLO_SBF_H_1_0","Shaggy Mullet", 987639353, -1514684318),
        Mod_Class::HairSets(83, 0, "CLO_X6F_H_0_0","Buzzcut", 1841427399, 606012624)
    };

    inline const std::vector<std::string> M_Walks = {
        "Default",
        "move_action@generic@core",
        "move_f@arrogant@a",
        "move_f@chubby@a",
        "move_f@depressed@a",
        "move_f@fat@a",
        "move_f@generic",
        "move_f@heels@c",
        "move_f@heels@d",
        "move_f@multiplayer",
        "move_f@sad@a",
        "move_f@sexy@a",
        "move_injured_generic",
        "move_m@business@a",
        "move_m@business@b",
        "move_m@business@c",
        "move_m@casual@a",
        "move_m@casual@b",
        "move_m@casual@c",
        "move_m@casual@d",
        "move_m@casual@e",
        "move_m@casual@f",
        "move_m@confident",
        "move_m@depressed@b",
        "move_m@drunk@slightlydrunk",
        "move_m@fat@a",
        "move_m@gangster@generic",
        "move_m@generic",
        "move_m@hobo@b",
        "move_m@injured",
        "move_m@multiplayer",
        "move_m@shadyped@a",
        "move_m@swagger",
        "move_m@swagger@b",
        "move_m@tool_belt@a",
        "move_p_m_one",
        "move_p_m_two",
        "move_p_m_zero"
    };
    inline const std::vector<std::string> F_Walks = {
        "Default",
        "move_action@generic@core",
        "move_f@arrogant@a",
        "move_f@chubby@a",
        "move_f@depressed@a",
        "move_f@fat@a",
        "move_f@generic",
        "move_f@heels@c",
        "move_f@heels@d",
        "move_f@multiplayer",
        "move_f@sad@a",
        "move_f@sexy@a",
        "move_m@business@a",
        "move_m@business@c",
        "move_m@casual@a",
        "move_m@casual@b",
        "move_m@casual@c",
        "move_m@casual@d",
        "move_m@casual@f",
        "move_m@confident",
        "move_m@depressed@b",
        "move_m@fat@a",
        "move_m@gangster@generic",
        "move_m@generic",
        "move_m@multiplayer",
        "move_m@shadyped@a",
        "move_m@swagger",
        "move_m@swagger@b",
        "move_m@tool_belt@a",
        "move_p_m_one",
        "move_p_m_two",
        "move_p_m_zero"
    };
    inline const std::vector<std::string> FaceAn = {
        "Default",
        "mood_aiming_1",
        "mood_angry_1",
        "mood_drivefast_1",
        "mood_drunk_1",
        "mood_happy_1",
        "mood_injured_1",
        "mood_knockout_1",
        "mood_normal_1",
        "mood_skydive_1",
        "mood_sleeping_1",
        "mood_smug_1",
        "mood_stressed_1",
        "mood_sulk_1",
        "mood_excited_1",
        "mood_frustrated_1",
        "mood_talking_1"
    };
    inline const std::vector<std::string> VoicesMale = {
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
    inline const std::vector<std::string> VoicesFemale = {
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

    inline const Mod_Class::AnimList SitUps = Mod_Class::AnimList(Mod_Class::AnimatedActions("amb@world_human_sit_ups@male@enter", "enter"), Mod_Class::AnimatedActions("amb@world_human_sit_ups@male@exit", "exit"), std::vector<Mod_Class::AnimatedActions>{ Mod_Class::AnimatedActions("amb@world_human_sit_ups@male@idle_a", "idle_a"), Mod_Class::AnimatedActions("amb@world_human_sit_ups@male@idle_b", "idle_b"), Mod_Class::AnimatedActions("amb@world_human_sit_ups@male@idle_c", "idle_c") });
    inline const Mod_Class::AnimList PushUps = Mod_Class::AnimList(Mod_Class::AnimatedActions("amb@world_human_push_ups@male@enter", "enter"), Mod_Class::AnimatedActions("amb@world_human_push_ups@male@exit", "exit"), std::vector<Mod_Class::AnimatedActions>{ Mod_Class::AnimatedActions("amb@world_human_push_ups@male@base", "base"), Mod_Class::AnimatedActions("amb@world_human_push_ups@male@idle_a", "idle_a"), Mod_Class::AnimatedActions("amb@world_human_push_ups@male@idle_a", "idle_b"), Mod_Class::AnimatedActions("amb@world_human_push_ups@male@idle_a", "idle_c"), Mod_Class::AnimatedActions("amb@world_human_push_ups@male@idle_a", "idle_d"), Mod_Class::AnimatedActions("amb@world_human_push_ups@male@idle_a", "idle_e") });
    inline const Mod_Class::AnimList SunbathebackF = Mod_Class::AnimList(Mod_Class::AnimatedActions("amb@world_human_sunbathe@female@back@enter", "enter"), Mod_Class::AnimatedActions("amb@world_human_sunbathe@female@back@exit", "exit"), { Mod_Class::AnimatedActions("amb@world_human_sunbathe@female@back@base" , "base"), Mod_Class::AnimatedActions("amb@world_human_sunbathe@female@back@idle_a" , "idle_a"), Mod_Class::AnimatedActions("amb@world_human_sunbathe@female@back@idle_a" , "idle_b"), Mod_Class::AnimatedActions("amb@world_human_sunbathe@female@back@idle_a" , "idle_c") });
    inline const Mod_Class::AnimList SunbathefrontF = Mod_Class::AnimList(Mod_Class::AnimatedActions("amb@world_human_sunbathe@female@front@enter", "enter"), Mod_Class::AnimatedActions("amb@world_human_sunbathe@female@front@exit", "exit"), { Mod_Class::AnimatedActions("amb@world_human_sunbathe@female@front@base" , "base"),Mod_Class::AnimatedActions("amb@world_human_sunbathe@female@front@idle_a" , "idle_a"),Mod_Class::AnimatedActions("amb@world_human_sunbathe@female@front@idle_a" , "idle_b"),Mod_Class::AnimatedActions("amb@world_human_sunbathe@female@front@idle_a" , "idle_c") });
    inline const Mod_Class::AnimList SunbathebackM = Mod_Class::AnimList(Mod_Class::AnimatedActions("amb@world_human_sunbathe@male@back@enter", "enter"), Mod_Class::AnimatedActions("amb@world_human_sunbathe@male@back@exit", "exit"), { Mod_Class::AnimatedActions("amb@world_human_sunbathe@male@back@base" , "base"),		Mod_Class::AnimatedActions("amb@world_human_sunbathe@male@back@idle_a" , "idle_a"),	Mod_Class::AnimatedActions("amb@world_human_sunbathe@male@back@idle_a" , "idle_b"),	Mod_Class::AnimatedActions("amb@world_human_sunbathe@male@back@idle_a" , "idle_c") });
    inline const Mod_Class::AnimList SunbathefrontM = Mod_Class::AnimList(Mod_Class::AnimatedActions("amb@world_human_sunbathe@male@front@enter", "enter"), Mod_Class::AnimatedActions("amb@world_human_sunbathe@male@front@exit", "exit"), { Mod_Class::AnimatedActions("amb@world_human_sunbathe@male@front@base" , "base"),	Mod_Class::AnimatedActions("amb@world_human_sunbathe@male@front@idle_a" , "idle_a"),	Mod_Class::AnimatedActions("amb@world_human_sunbathe@male@front@idle_a" , "idle_b"),	Mod_Class::AnimatedActions("amb@world_human_sunbathe@male@front@idle_a" , "idle_c") });

    inline const std::vector<Mod_Class::Tattoo> MaleTshirt = {
        Mod_Class::Tattoo("", "ClearOverlay", "Clear Overlay"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_CREW_M_000_A", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_CREW_M_000_B", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_CREW_M_000_C", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_CREW_M_000_D", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_CREW_M_000_E", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_CREW_M_000_F", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tshirt_Award_000", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tshirt_Award_001", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tshirt_Award_002", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_001", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_002", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_003", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_004", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_005", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_006", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_007", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_008", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_009", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_010", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_011", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_012", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_013", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_014", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_015", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_016", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_017", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_018", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_020", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_022", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_023", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_024", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_027", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_028", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_029", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_031", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_032", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_034", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_035", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_036", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_038", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_039", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_040", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_041", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_042", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_043", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_044", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_045", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_046", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_047", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_OGA_000_m", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_OGA_001_m", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_OGA_002_m", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_OGA_003_m", ""),
        Mod_Class::Tattoo("mpxmas_604490_overlays", "MP_IHeartLC_000_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_000_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_001_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_002_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_003_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_004_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_005_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_006_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_007_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_008_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_009_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_010_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_011_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_012_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_013_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_014_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_015_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_016_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_017_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_018_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_019_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_020_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_021_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_022_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_023_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_024_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_025_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_026_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_027_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_028_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_029_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_030_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_031_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_032_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_033_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_034_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_035_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_036_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_037_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_038_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_039_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_040_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_041_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_042_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_043_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_044_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_045_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_046_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_047_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_048_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_049_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_050_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_051_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_052_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_053_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_054_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_055_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_056_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_057_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_058_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_059_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_060_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_061_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_062_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_063_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_064_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_065_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_066_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_067_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_068_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_069_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_070_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_071_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_072_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_073_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_074_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_075_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_076_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_077_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_078_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_079_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_080_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_081_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_082_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_083_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_084_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_085_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_086_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_087_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_088_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_089_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_090_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_091_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_092_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_093_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_094_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_095_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_096_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_097_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_098_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_099_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_100_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_101_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_102_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_103_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_104_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_105_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_106_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_107_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_108_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_109_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_110_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_111_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_112_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_113_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_114_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_115_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_116_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_117_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_118_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_119_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_120_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_121_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_122_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_123_M", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_124_M", ""),
        Mod_Class::Tattoo("mpChristmas3_overlays", "MP_Christmas3_Tee_000_M", ""),
        Mod_Class::Tattoo("mpChristmas3_overlays", "MP_Christmas3_Tee_001_M", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_A", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_B", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_C", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_D", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_E", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_F", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_G", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_H", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_I", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_J", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_K", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_L", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_M", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_N", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_O", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_P", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_Q", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_R", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_S", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_M_Tshirt_T", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_000", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_001", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_002", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_003", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_004", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_005", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_006", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_007", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_008", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_009", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_010", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_011", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_012", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_013", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_014", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_015", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_016", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_017", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_018", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_019", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_020", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_021", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Tshirt_022", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_000", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_001", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_002", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_003", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_004", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_005", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_006", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_007", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_008", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_009", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_010", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_011", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_012", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_M_Retro_013", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Rstar_M_Tshirt_000", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Rstar_M_Tshirt_001", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Rstar_M_Tshirt_002", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Award_000", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_000", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_001", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_002", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_003", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_004", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_005", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_006", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_007", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_008", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_009", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_010", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_011", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_012", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_013", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_014", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_015", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_016", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_017", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_018", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_019", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_020", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_021", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_022", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_023", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_024", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_025", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_M_Tshirt_026", ""),
        Mod_Class::Tattoo("mpPilot_overlays", "MP_Fli_M_Tshirt_000", ""),
        Mod_Class::Tattoo("mpLTS_overlays", "FM_LTS_M_Tshirt_000", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_000_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_001_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_002_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_003_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_004_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_005_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_006_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_007_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_008_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_009_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_010_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_011_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_012_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_013_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_014_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_015_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_016_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_017_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_018_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_019_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_020_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_021_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_022_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_023_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_024_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_025_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_026_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_027_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_028_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_029_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_030_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_031_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_032_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_033_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_034_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_035_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_036_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_037_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_038_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_039_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_040_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_041_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_042_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_043_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_044_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_045_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_046_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_047_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_048_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_049_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_050_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_051_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_052_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_053_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_054_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_055_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_056_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_057_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_058_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_059_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_060_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_061_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_062_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_063_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_064_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_065_M", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_066_M", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_M_Tshirt_004", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_M_Tshirt_005", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_M_Tshirt_006", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_M_Tshirt_007", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_M_Tshirt_008", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_M_Tshirt_009", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_M_Tshirt_010", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_M_Tshirt_011", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_M_Tshirt_012", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_M_Tshirt_013", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Fli_M_Tshirt_000", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Elite_M_Tshirt", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Elite_M_Tshirt_1", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Elite_M_Tshirt_2", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_000_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_001_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_002_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_003_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_004_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_005_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_006_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_007_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_008_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_009_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_010_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_011_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_012_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_013_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_014_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_015_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_016_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_017_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_018_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_019_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_020_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_021_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_022_M", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_023_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_000_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_001_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_002_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_003_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_006_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_007_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_008_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_009_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_012_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_013_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_014_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_015_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_VDG_000_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_VDG_001_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_VDG_002_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_VDG_004_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_VDG_005_M", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_VDG_006_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_LC_004_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_LC_005_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_LC_010_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_LC_011_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_ENEMA_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_Per_001_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SC_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_LB_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_LC_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_ENEMA_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_Per_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_SN_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_SC_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_DS_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_Vap_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_DIS_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_DIS_001_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_DIX_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_DIX_001_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_DIX_002_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_001_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_002_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_003_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_004_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_005_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_006_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_007_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_000_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_001_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_002_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_003_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_004_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_005_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_006_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_007_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_008_M", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_009_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_000_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_001_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_002_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_003_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_004_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_005_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_006_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_000_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_001_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_002_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_003_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_004_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_005_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_006_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_007_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_008_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_009_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_010_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_011_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_012_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_000_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_001_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_002_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_003_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_004_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_005_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_006_M", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_007_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Broker_000_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Broker_001_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Broker_002_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Broker_003_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Broker_004_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Broker_005_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Magnetics_000_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Magnetics_001_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Magnetics_002_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Magnetics_003_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Magnetics_004_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Magnetics_005_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_000_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_001_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_002_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_003_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_004_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_005_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_006_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_007_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_008_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_009_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_010_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Bennys_000_M", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Bennys_001_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_000_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_001_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_002_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_003_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_004_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_005_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_006_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_007_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_008_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_009_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_010_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_011_M", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_012_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_Securoserv_000_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_teams_000_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_teams_001_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_teams_002_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_teams_003_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_000_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_001_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_002_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_003_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_004_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_005_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_006_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_007_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_008_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_009_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_010_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_011_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_012_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_013_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_014_M", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_015_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Award_000_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Award_001_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_000_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_001_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_002_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_003_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_004_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_005_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_006_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_007_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_008_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_009_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_010_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_011_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_012_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_013_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_014_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_015_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_016_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_017_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_000_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_001_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_002_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_003_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_004_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_005_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_006_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_007_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_008_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_009_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_010_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_011_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_012_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_013_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_014_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_015_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_016_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_017_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_018_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_019_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_020_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_021_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_022_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_023_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_024_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_025_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_026_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_027_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_028_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_029_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_030_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_031_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_032_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_033_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_034_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_035_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_036_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_037_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_038_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_039_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_040_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_041_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_042_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_043_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_044_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_045_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_046_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_047_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_048_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_049_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_050_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_051_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_052_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_053_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_054_M", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_055_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_000_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_001_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_002_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_003_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_004_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_005_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_006_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_007_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_008_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_009_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_010_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_011_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_012_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_013_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_014_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_015_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_016_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_017_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_018_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_019_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_020_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_021_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_022_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_023_M", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_024_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_000_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_001_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_002_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_003_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_004_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_005_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_006_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_007_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_008_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_009_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_010_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_011_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_012_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_013_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_014_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_015_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_016_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_017_M", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_018_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_000_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_001_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_002_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_003_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_004_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_005_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_006_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_007_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_008_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_009_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_010_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_011_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_012_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_013_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_014_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_015_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_016_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_017_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_018_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_019_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_020_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_021_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_022_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_023_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_024_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_025_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_026_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_027_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_028_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_029_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_030_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_031_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_032_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_033_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_034_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_035_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_036_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_037_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_038_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_039_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_040_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_041_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_042_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_043_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_044_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_045_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_046_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_047_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_048_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_049_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_050_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_051_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_052_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_053_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_054_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_055_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_056_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_057_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_058_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_059_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_060_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_061_M", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_062_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_000_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_001_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_002_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_003_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_004_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_005_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_006_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_007_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_008_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_009_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_010_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_011_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_012_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_013_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_014_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_015_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_016_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_017_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_018_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_019_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_020_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_021_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_022_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_023_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_024_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_025_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_026_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_027_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_028_M", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_029_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_000_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_001_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_002_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_003_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_004_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_005_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_006_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_007_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_008_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_009_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_010_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_011_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_012_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_013_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_014_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_015_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_016_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_017_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_018_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_019_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_020_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_021_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_022_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_023_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_024_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_025_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_026_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_027_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_028_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_029_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_030_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_031_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_032_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_033_M", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_034_M", ""),
        Mod_Class::Tattoo("mpSum2_overlays", "MP_Sum2_Tee_000_M", ""),
        Mod_Class::Tattoo("mpSum2_overlays", "MP_Sum2_Tee_001_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_000_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_001_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_002_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_003_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_004_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_005_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_006_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_007_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_008_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_009_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_010_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_011_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_012_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_013_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_014_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_015_M", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_016_M", ""),
        Mod_Class::Tattoo("mpSecurity_overlays", "MP_Security_Tee_000_M", ""),
        Mod_Class::Tattoo("mpSecurity_overlays", "MP_Security_Tee_001_M", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_000_M", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_001_M", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_002_M", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_003_M", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_004_M", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_005_M", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_006_M", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_007_M", "")
    };
    inline const std::vector<Mod_Class::Tattoo> FemaleTshirt = {
        Mod_Class::Tattoo("", "ClearOverlay", "Clear Overlay"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_CREW_F_000_A", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_CREW_F_000_B", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_CREW_F_000_C", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_CREW_F_000_D", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tshirt_Award_F_000", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tshirt_Award_F_001", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tshirt_Award_F_002", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_048", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_049", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_050", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_051", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_052", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_053", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_054", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_055", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_056", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_057", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_058", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_059", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_060", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_061", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_062", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_066", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_067", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_068", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_069", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_070", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_027_f", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_028_F", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_034_f", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_036_F", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_branding_039_f", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_OGA_000_f", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_OGA_001_f", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_OGA_002_f", ""),
        Mod_Class::Tattoo("multiplayer_overlays", "mp_fm_OGA_003_f", ""),
        Mod_Class::Tattoo("mpxmas_604490_overlays", "MP_IHeartLC_001_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_000_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_001_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_002_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_003_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_004_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_005_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_006_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_007_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_008_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_009_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_010_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_011_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_012_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_013_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_014_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_015_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_016_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_017_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_018_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_019_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_020_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_021_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_022_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_023_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_024_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_025_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_026_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_027_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_028_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_029_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_030_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_031_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_032_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_033_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_034_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_035_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_036_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_037_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_038_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_039_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_040_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_041_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_042_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_043_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_044_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_045_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_046_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_047_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_048_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_049_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_050_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_051_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_052_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_053_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_054_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_055_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_056_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_057_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_058_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_059_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_060_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_061_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_062_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_063_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_064_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_065_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_066_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_067_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_068_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_069_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_070_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_071_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_072_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_073_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_074_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_075_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_076_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_077_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_078_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_079_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_080_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_081_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_082_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_083_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_084_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_085_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_086_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_087_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_088_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_089_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_090_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_091_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_092_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_093_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_094_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_095_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_096_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_097_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_098_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_099_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_100_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_101_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_102_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_103_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_104_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_105_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_106_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_107_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_108_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_109_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_110_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_111_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_112_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_113_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_114_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_115_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_116_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_117_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_118_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_119_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_120_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_121_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_122_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_123_F", ""),
        Mod_Class::Tattoo("mpChristmas2018_overlays", "MP_Christmas2018_Tee_124_F", ""),
        Mod_Class::Tattoo("mpChristmas3_overlays", "MP_Christmas3_Tee_000_F", ""),
        Mod_Class::Tattoo("mpChristmas3_overlays", "MP_Christmas3_Tee_001_F", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_A", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_B", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_C", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_D", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_E", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_F", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_G", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_H", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_I", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_J", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_K", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_L", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_M", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_N", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_O", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_P", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_Q", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_R", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_S", ""),
        Mod_Class::Tattoo("mpValentines_overlays", "MP_Val_F_Tshirt_T", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_000", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_001", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_002", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_003", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_004", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_005", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_006", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_007", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_008", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_009", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_010", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_011", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_012", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_013", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_014", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_015", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_016", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_017", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_018", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_019", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_020", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_021", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Tshirt_022", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_000", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_001", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_002", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_003", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_004", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_005", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_006", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_007", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_008", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_009", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_010", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_011", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_012", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Hip_F_Retro_013", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Rstar_F_Tshirt_000", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Rstar_F_Tshirt_001", ""),
        Mod_Class::Tattoo("mpHipster_overlays", "FM_Rstar_F_Tshirt_002", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Award_000", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_000", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_001", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_002", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_003", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_004", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_005", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_006", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_007", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_008", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_009", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_010", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_011", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_012", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_013", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_014", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_015", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_016", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_017", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_018", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_019", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_020", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_021", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_022", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_023", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_024", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_025", ""),
        Mod_Class::Tattoo("mpIndependence_overlays", "FM_Ind_F_Tshirt_026", ""),
        Mod_Class::Tattoo("mpPilot_overlays", "MP_Fli_F_Tshirt_000", ""),
        Mod_Class::Tattoo("mpLTS_overlays", "FM_LTS_F_Tshirt_000", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_000_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_001_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_002_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_003_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_004_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_005_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_006_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_007_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_008_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_009_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_010_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_011_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_012_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_013_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_014_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_015_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_016_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_017_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_018_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_019_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_020_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_021_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_022_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_023_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_024_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_025_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_026_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_027_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_028_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_029_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_030_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_031_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_032_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_033_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_034_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_035_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_036_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_037_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_038_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_039_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_040_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_041_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_042_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_043_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_044_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_045_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_046_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_047_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_048_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_049_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_050_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_051_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_052_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_053_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_054_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_055_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_056_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_057_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_058_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_059_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_060_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_061_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_062_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_063_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_064_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_065_F", ""),
        Mod_Class::Tattoo("mpHeist4_overlays", "MP_Heist4_Tee_066_F", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_F_Tshirt_004", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_F_Tshirt_005", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_F_Tshirt_006", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_F_Tshirt_007", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_F_Tshirt_008", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_F_Tshirt_009", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_F_Tshirt_010", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_F_Tshirt_011", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_F_Tshirt_012", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Award_F_Tshirt_013", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Fli_F_Tshirt_000", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Elite_F_Tshirt", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Elite_F_Tshirt_1", ""),
        Mod_Class::Tattoo("mpHeist_overlays", "MP_Elite_F_Tshirt_2", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_000_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_001_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_002_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_003_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_004_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_005_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_006_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_007_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_008_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_009_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_010_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_011_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_012_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_013_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_014_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_015_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_016_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_017_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_018_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_019_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_020_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_021_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_022_F", ""),
        Mod_Class::Tattoo("mpHeist3_overlays", "mpHeist3_Tee_023_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_000_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_001_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_002_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_003_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_006_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_007_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_008_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_009_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_012_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_013_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_014_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_LC_015_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_VDG_000_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_VDG_001_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_VDG_002_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_VDG_004_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_VDG_005_F", ""),
        Mod_Class::Tattoo("mpLuxe2_overlays", "MP_LUXE_VDG_006_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_LC_004_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_LC_005_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_LC_010_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_LC_011_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_Enema_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_Per_001_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_LB_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_LC_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_ENEMA_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_Per_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_SN_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_SC_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_DS_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_Vap_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_DIS_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FAKE_DIS_001_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_DIX_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_DIX_001_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_DIX_002_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_001_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_002_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_003_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_004_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_005_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_006_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SN_007_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_LUXE_SC_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_000_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_001_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_002_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_003_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_004_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_005_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_006_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_007_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_008_F", ""),
        Mod_Class::Tattoo("mpLuxe_overlays", "MP_FILM_009_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_000_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_001_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_002_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_003_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_004_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_005_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Chianski_006_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_000_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_001_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_002_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_003_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_004_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_005_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_006_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_007_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_008_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_009_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_010_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_011_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Hntr_012_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_000_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_001_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_002_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_003_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_004_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_005_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_006_F", ""),
        Mod_Class::Tattoo("mpLowrider2_overlays", "MP_Dense_007_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Broker_000_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Broker_001_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Broker_002_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Broker_003_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Broker_004_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Broker_005_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Magnetics_000_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Magnetics_001_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Magnetics_002_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Magnetics_003_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Magnetics_004_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Magnetics_005_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_000_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_001_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_002_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_003_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_004_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_005_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_006_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_007_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Trickster_010_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Bennys_000_F", ""),
        Mod_Class::Tattoo("mpLowrider_overlays", "MP_Bennys_001_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_000_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_001_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_002_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_003_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_004_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_005_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_006_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_007_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_008_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_009_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_010_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_011_F", ""),
        Mod_Class::Tattoo("mpHalloween_overlays", "HW_Tee_012_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_Securoserv_000_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_teams_000_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_teams_001_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_teams_002_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_teams_003_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_000_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_001_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_002_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_003_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_004_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_005_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_006_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_007_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_008_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_009_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_010_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_011_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_012_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_013_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_014_F", ""),
        Mod_Class::Tattoo("mpExecutive_overlays", "MP_exec_prizes_015_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Award_000_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Award_001_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_000_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_001_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_002_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_003_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_004_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_005_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_006_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_007_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_008_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_009_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_010_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_011_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_012_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_013_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_014_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_015_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_016_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Rank_017_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_000_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_001_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_002_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_003_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_004_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_005_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_006_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_007_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_008_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_009_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_010_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_011_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_012_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_013_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_014_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_015_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_016_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_017_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_018_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_019_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_020_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_021_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_022_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_023_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_024_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_025_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_026_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_027_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_028_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_029_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_030_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_031_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_032_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_033_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_034_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_035_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_036_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_037_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_038_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_039_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_040_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_041_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_042_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_043_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_044_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_045_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_046_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_047_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_048_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_049_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_050_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_051_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_052_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_053_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_054_F", ""),
        Mod_Class::Tattoo("mpBiker_overlays", "MP_Biker_Tee_055_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_000_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_001_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_002_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_003_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_004_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_005_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_006_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_007_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_008_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_009_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_010_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_011_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_012_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_013_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_014_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_015_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_016_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_017_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_018_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_019_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_020_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_021_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_022_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_023_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_024_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_025_F", ""),
        Mod_Class::Tattoo("mpGunrunning_overlays", "MP_Gunrunning_Award_026_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_000_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_001_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_002_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_003_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_004_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_005_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_006_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_007_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_008_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_009_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_010_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_011_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_012_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_013_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_014_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_015_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_016_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_017_F", ""),
        Mod_Class::Tattoo("mpSmuggler_overlays", "MP_Smuggler_Graphic_018_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_000_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_001_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_002_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_003_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_004_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_005_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_006_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_007_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_008_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_009_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_010_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_011_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_012_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_013_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_014_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_015_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_016_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_017_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_018_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_019_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_020_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_021_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_022_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_023_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_024_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_025_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_026_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_027_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_028_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_029_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_030_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_031_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_032_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_033_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_034_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_035_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_036_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_037_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_038_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_039_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_040_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_041_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_042_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_043_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_044_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_045_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_046_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_047_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_048_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_049_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_050_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_051_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_052_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_053_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_054_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_055_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_056_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_057_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_058_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_059_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_060_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_061_F", ""),
        Mod_Class::Tattoo("mpBattle_overlays", "MP_Battle_Clothing_062_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_000_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_001_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_002_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_003_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_004_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_005_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_006_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_007_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_008_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_009_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_010_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_011_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_012_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_013_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_014_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_015_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_016_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_017_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_018_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_019_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_020_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_021_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_022_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_023_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_024_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_025_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_026_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_027_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_028_F", ""),
        Mod_Class::Tattoo("mpVinewood_overlays", "MP_Vinewood_Tee_029_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_000_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_001_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_002_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_003_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_004_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_005_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_006_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_007_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_008_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_009_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_010_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_011_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_012_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_013_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_014_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_015_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_016_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_017_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_018_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_019_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_020_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_021_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_022_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_023_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_024_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_025_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_026_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_027_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_028_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_029_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_030_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_031_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_032_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_033_F", ""),
        Mod_Class::Tattoo("mpSum_overlays", "mpSum_Tee_034_F", ""),
        Mod_Class::Tattoo("mpSum2_overlays", "MP_Sum2_Tee_000_F", ""),
        Mod_Class::Tattoo("mpSum2_overlays", "MP_Sum2_Tee_001_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_000_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_001_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_002_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_003_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_004_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_005_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_006_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_007_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_008_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_009_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_010_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_011_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_012_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_013_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_014_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_015_F", ""),
        Mod_Class::Tattoo("mpTuner_overlays", "MP_Tuner_Tee_016_F", ""),
        Mod_Class::Tattoo("mpSecurity_overlays", "MP_Security_Tee_000_F", ""),
        Mod_Class::Tattoo("mpSecurity_overlays", "MP_Security_Tee_001_F", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_000_F", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_001_F", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_002_F", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_003_F", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_004_F", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_005_F", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_006_F", ""),
        Mod_Class::Tattoo("mp2023_01_overlays", "MP_2023_01_Tee_007_F", "")
    };

    inline const std::vector<Mod_Class::Tattoo> maleTats01 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_004_M", "Rearview"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_012_M", "Tempesta Girl"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_018_M", "Gearhead"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_020_M", "V8 Demon"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_021_M", "Devil in the Back Seat"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_023_M", "Dewbauchee Stylized"),//

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_006_M", "Painted Micro SMG"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_007_M", "Weapon King"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_035_M", "Sniff Sniff"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_036_M", "Charm Pattern"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_037_M", "Witch & Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_038_M", "Pumpkin Bug"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_039_M", "Sinner"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_057_M", "Gray Demon"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_004_M", "Hood Heart"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_008_M", "Los Santos Tag"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_013_M", "Blessed Boombox"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_014_M", "Chamberlain Hills"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_015_M", "Smoking Barrels"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_026_M", "Dollar Guns Crossed"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_021_M", "Skull Surfer"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_020_M", "Speaker Tower"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_019_M", "Record Shot"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_018_M", "Record Head"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_017_M", "Tropical Sorcerer"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_016_M", "Rose Panther"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_015_M", "Paradise Ukulele"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_014_M", "Paradise Nap"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_013_M", "Wild Dancers"),//

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_039_M", "Space Rangers"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_038_M", "Robot Bubblegum"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_036_M", "LS Shield"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_030_M", "Howitzer"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_028_M", "Bananas Gone Bad"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_027_M", "Epsilon"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_024_M", "Mount Chiliad"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_023_M", "Bigfoot"),//

        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_032_M", "Play Your Ace"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_029_M", "The Table"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_021_M", "Show Your Hand"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_017_M", "Roll the Dice"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_015_M", "The Jolly Joker"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_011_M", "Life's a Gamble"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_010_M", "Photo Finish"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_009_M", "Till Death Do Us Part"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_008_M", "Snake Eyes"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_007_M", "777"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_006_M", "Wheel of Suits"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_001_M", "Jackpot"),//

        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_027_M", "Molon Labe"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_024_M", "Dragon Slayer"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_022_M", "Spartan and Horse"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_021_M", "Spartan and Lion"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_016_M", "Odin and Raven"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_015_M", "Samurai Combat"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_011_M", "Weathered Skull"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_010_M", "Spartan Shield"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_009_M", "Norse Rune"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_005_M", "Ghost Dragon"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_002_M", "Kabuto"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_025_M", "Claimed By The Beast"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_024_M", "Pirate Captain"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_022_M", "X Marks The Spot"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_018_M", "Finders Keepers"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_017_M", "Framed Tall Ship"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_016_M", "Skull Compass"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_013_M", "Torn Wings"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_009_M", "Tall Ship Conflict"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_006_M", "Never Surrender"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_003_M", "Give Nothing Back"),

        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_007_M", "Eagle Eyes"),
        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_005_M", "Parachute Belle"),
        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_004_M", "Balloon Pioneer"),
        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_002_M", "Winged Bombshell"),
        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_001_M", "Pilot Skull"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_022_M", "Explosive Heart"),//
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_019_M", "Pistol Wings"),//
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_018_M", "Dual Wield Skull"),//
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_014_M", "Backstabber"),//
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_013_M", "Wolf Insignia"),//
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_009_M", "Butterfly Knife"),//
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_001_M", "Crossed Weapons"),//
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_000_M", "Bullet Proof"),//

        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_011_M", "Talk Shit Get Hit"),//
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_010_M", "Take the Wheel"),//
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_009_M", "Serpents of Destruction"),//
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_002_M", "Tuned to Death"),//
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_001_M", "Power Plant"),//
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_000_M", "Block Back"),//

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_043_M", "Ride Forever"),//
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_030_M", "Brothers For Life"),//
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_021_M", "Flaming Reaper"),//
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_017_M", "Clawed Beast"),//
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_011_M", "R.I.P. My Brothers"),//
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_008_M", "Freedom Wheels"),//
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_006_M", "Chopper Freedom"),//

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_048_M", "Racing Doll"),//
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_046_M", "Full Throttle"),//
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_041_M", "Brapp"),//
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_040_M", "Monkey Chopper"),//
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_037_M", "Big Grills"),//
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_034_M", "Feather Road Kill"),//
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_030_M", "Man's Ruin"),//
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_029_M", "Majestic Finish"),//
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_026_M", "Winged Wheel"),//
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_024_M", "Road Kill"),//

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_032_M", "Reign Over"),//
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_031_M", "Dead Pretty"),//
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_008_M", "Love the Game"),//
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_000_M", "SA Assault"),//

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_021_M", "Sad Angel"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_014_M", "Love is Blind"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_010_M", "Bad Angel"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_009_M", "Amazon"),//

        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_029_M", "Geometric Design"),//   
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_022_M", "Cloaked Angel"),//  
        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_024_M", "Feather Mural"),//    
        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_006_M", "Adorned Wolf"),//   

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_015", "Japanese Warrior"),//  
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_011", "Roaring Tiger"),//      
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_006", "Carp Shaded"),//   
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_005", "Carp Outline"),//   

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_046", "Triangles"),// 
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_041", "Tooth"),// 
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_032", "Paper Plane"),// 
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_031", "Skateboard"),//   
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_030", "Shark Fin"),//
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_025", "Watch Your Step"),//  
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_024", "Pyamid"),//   
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_012", "Antlers"),//  
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_011", "Infinity"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_000", "Crossed Arrows"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_M_Back_000", "Makin' Paper"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_Back_000", "Ship Arms"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_045", "Skulls and Rose"),//
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_030", "Lucky Celtic Dogs"),//
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_020", "Dragon"),//
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_019", "The Wages of Sin"),//Survival Award
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_016", "Evil Clown"),//
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_013", "Eagle and Serpent"),//
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_011", "LS Script"),//
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_009", "Skull on the Cross"),//

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_019", "Clown Dual Wield Dollars"),//
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_018", "Clown Dual Wield"),//
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_017", "Clown and Gun"),//
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_016", "Clown"),//
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_014", "Trust No One"),//Car Bomb Award
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_008", "Los Santos Customs"),//Mod a Car Award
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_005", "Angel"),//Win Every Game Mode Award -- Unknowen
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_046", "Zip?"),//Zip???
        Mod_Class::Tattoo("mpchristmas2018_overlays", "MP_Christmas2018_Tat_000_M", "Unknowen")//
    };
    inline const std::vector<Mod_Class::Tattoo> maleTats02 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_024_M", "Futo Smoke"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_025_M", "Benefactor Demon"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_026_M", "Widowmaker"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_027_M", "Engine Heart"),//

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_004_M", "Herbal Bouquet"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_005_M", "Cash Krampus"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_006_M", "All In One Night"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_007_M", "A Little Present For You"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_014_M", "Masked Machete Killer"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_015_M", "Killer"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_016_M", "Powwer"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_017_M", "Two Headed Beast"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_018_M", "Dudes"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_019_M", "Fooligan Jester"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_020_M", "Vile Smile"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_021_M", "Demon Skull Jester"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_022_M", "Fatal Incursion Outline"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_023_M", "Many-Headed Beast"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_024_M", "Demon Stitches"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_025_M", "Collector"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_040_M", "Monkey"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_041_M", "Dragon"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_042_M", "Snake"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_043_M", "Goat"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_044_M", "Rat"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_045_M", "Rabbit"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_046_M", "Ox"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_047_M", "Pig"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_048_M", "Rooster"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_049_M", "Dog"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_050_M", "Horse"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_051_M", "Tiger"),

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_003_M", "Bullet Mouth"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_004_M", "Smoking Barrel"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_040_M", "Carved Pumpkin"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_041_M", "Branched Werewolf"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_042_M", "Winged Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_058_M", "Shrieking Dragon"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_059_M", "Swords & City"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_016_M", "All From The Same Tree"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_017_M", "King of the Jungle"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_018_M", "Night Owl"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_023_M", "Techno Glitch"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_022_M", "Paradise Sirens"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_035_M", "LS Panic"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_033_M", "LS City"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_026_M", "Dignity"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_025_M", "Davis"),

        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_022_M", "Blood Money"),
        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_003_M", "Royal Flush"),
        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_000_M", "In the Pocket"),

        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_026_M", "Spartan Skull"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_020_M", "Medusa's Gaze"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_019_M", "Strike Force"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_003_M", "Native Warrior"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_000_M", "Thor - Goblin"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_021_M", "Dead Tales"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_019_M", "Lost At Sea"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_007_M", "No Honor"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_000_M", "Bless The Dead"),

        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_000_M", "Turbulence"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_028_M", "Micro SMG Chain"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_020_M", "Crowned Weapons"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_017_M", "Dog Tags"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_012_M", "Dollar Daggers"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_060_M", "We Are The Mods!"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_059_M", "Faggio"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_058_M", "Reaper Vulture"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_050_M", "Unforgiven"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_041_M", "No Regrets"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_034_M", "Brotherhood of Bikes"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_032_M", "Western Eagle"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_029_M", "Bone Wrench"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_026_M", "American Dream"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_023_M", "Western MC"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_019_M", "Gruesome Talons"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_018_M", "Skeletal Chopper"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_013_M", "Demon Crossbones"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_005_M", "Made In America"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_001_M", "Both Barrels"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_000_M", "Demon Rider"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_044_M", "Ram Skull"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_033_M", "Sugar Skull Trucker"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_027_M", "Punk Road Hog"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_019_M", "Engine Heart"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_018_M", "Vintage Bully"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_011_M", "Wheels of Death"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_019_M", "Death Behind"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_012_M", "Royal Kiss"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_026_M", "Royal Takeover"),
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_013_M", "Love Gamble"),
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_002_M", "Holy Mary"),
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_001_M", "King Fight"),

        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_027_M", "Cobra Dawn"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_025_M", "Reaper Sway"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_012_M", "Geometric Galaxy"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_002_M", "The Howler"),

        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_015_M", "Smoking Sisters"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_014_M", "Ancient Queen"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_008_M", "Flying Eye"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_007_M", "Eye of the Griffin"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_019", "Royal Dagger Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_018", "Royal Dagger Outline"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_017", "Loose Lips Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_016", "Loose Lips Outline"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_009", "Time To Die"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_047", "Cassette"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_033", "Stag"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_013", "Boombox"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_002", "Chemistry"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_M_Chest_001", "$$$"),
        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_M_Chest_000", "Rich"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_Chest_001", "Tribal Shark"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_Chest_000", "Tribal Hammerhead"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_044", "Stone Cross"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_034", "Flaming Shamrock"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_025", "LS Bold"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_024", "Flaming Cross"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_010", "LS Flames"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_013", "Seven Deadly Sins"),//Kill 1000 Players Award
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_012", "Embellished Scroll"),//Kill 500 Players Award
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_011", "Blank Scroll"),////Kill 100 Players Award?
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_003", "Blackjack")
    };
    inline const std::vector<Mod_Class::Tattoo> maleTats03 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_028_M", "Sabre Turbo Eyes"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_029_M", "Turbo Dragon"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_030_M", "Fooligan Hellfire"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_031_M", "Hot Rod Demon"),//

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_005_M", "Concealed"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_043_M", "Cursed Saki"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_044_M", "Smouldering Bat & Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_060_M", "Blaine County"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_061_M", "Angry Possum"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_062_M", "Floral Demon"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_024_M", "Beatbox Silhouette"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_025_M", "Davis Flames"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_030_M", "Radio Tape"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_004_M", "Skeleton Breeze"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_037_M", "LadyBug"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_029_M", "Fatal Incursion"),

        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_031_M", "Gambling Royalty"),
        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_024_M", "Cash Mouth"),
        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_016_M", "Rose and Aces"),
        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_012_M", "Skull of Suits"),

        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_008_M", "Spartan Warrior"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_015_M", "Jolly Roger"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_010_M", "See You In Hell"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_002_M", "Dead Lies"),

        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_006_M", "Bombs Away"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_029_M", "Win Some Lose Some"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_010_M", "Cash Money"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_052_M", "Biker Mount"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_039_M", "Gas Guzzler"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_031_M", "Gear Head"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_010_M", "Skull Of Taurus"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_003_M", "Web Rider"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_014_M", "Bat Cat of Spades"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_012_M", "Punk Biker"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_016_M", "Two Face"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_011_M", "Lady Liberty"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_004_M", "Gun Mic"),

        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_003_M", "Abstract Skull"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_028", "Executioner"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_013", "Lizard"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_035", "Sewn Heart"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_029", "Sad"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_006", "Feather Birds"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_M_Stomach_000", "Refined Hustler"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_Stom_001", "Wheel"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_Stom_000", "Swordfish"),


        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_036", "Way of the Gun"),//500 Pistol kills Award
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_029", "Trinity Knot"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_012", "Los Santos Bills"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_004", "Faith"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_004", "Hustler"),//Make 50000 from betting Award
    };
    inline const std::vector<Mod_Class::Tattoo> maleTats04 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_008_M", "Sparkey"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_009_M", "Sparks Flying"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_010_M", "Hot Piston"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_011_M", "Ignition"),//

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_010_M", "Dude"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_011_M", "Fooligan Tribal"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_012_M", "Skull Jester"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_013_M", "Budonk-adonk!"),

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_000_M", "Live Fast Mono"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_001_M", "Live Fast Color"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_018_M", "Branched Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_019_M", "Scythed Corpse"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_020_M", "Scythed Corpse & Reaper"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_021_M", "Third Eye"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_022_M", "Pierced Third Eye"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_023_M", "Lip Drip"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_024_M", "Skin Mask"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_025_M", "Webbed Scythe"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_026_M", "Oni Demon"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_027_M", "Bat Wings"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_001_M", "Bright Diamond"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_002_M", "Hustle"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_027_M", "Black Widow"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_044_M", "Clubs"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_043_M", "Diamonds"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_042_M", "Hearts"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_022_M", "Thong's Sword"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_021_M", "Wanted"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_020_M", "UFO"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_019_M", "Teddy Bear"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_018_M", "Stitches"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_017_M", "Space Monkey"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_016_M", "Sleepy"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_015_M", "On/Off"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_014_M", "LS Wings"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_013_M", "LS Star"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_012_M", "Razor Pop"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_011_M", "Lipstick Kiss"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_010_M", "Green Leaf"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_009_M", "Knifed"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_008_M", "Ice Cream"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_007_M", "Two Horns"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_006_M", "Crowned"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_005_M", "Spades"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_004_M", "Bandage"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_003_M", "Assault Rifle"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_002_M", "Animal"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_001_M", "Ace of Spades"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_000_M", "Five Stars"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_012_M", "Thief"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_011_M", "Sinner"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_003_M", "Lock and Load"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_051_M", "Western Stylized"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_038_M", "FTW"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_009_M", "Morbid Arachnid"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_042_M", "Flaming Quad"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_017_M", "Bat Wheel"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_Tat_006_M", "Toxic Spider"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_Tat_004_M", "Scorpion"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_Tat_000_M", "Stunt Skull"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_029", "Beautiful Death"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_025", "Snake Head Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_024", "Snake Head Outline"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_007", "Los Muertos"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_021", "Geo Fox"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_005", "Beautiful Eye"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_M_Neck_003", "$100"),
        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_M_Neck_002", "Script Dollar Sign"),
        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_M_Neck_001", "Bold Dollar Sign"),
        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_M_Neck_000", "Cash is King"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_Head_002", "Shark"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_Neck_001", "Surfs Up"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_Neck_000", "Little Fish"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_Head_001", "Surf LS"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_Head_000", "Pirate Skull"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_000", "Skull")
    };
    inline const std::vector<Mod_Class::Tattoo> maleTats05 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_003_M", "Top Dead Center"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_002_M", "Flaming Driver"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_001_M", "Pegassi Flames"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_000_M", "Mk II Girl"),//

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_033_M", "Fooligan Impotent Rage"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_030_M", "Dude Jester"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_026_M", "Fooligan Clown"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_028_M", "Dude Outline"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_000_M", "The Christmas Spirit"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_001_M", "Festive Reaper"),

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_008_M", "Bigness Chimp"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_009_M", "Up-n-Atomizer Design"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_010_M", "Rocket Launcher Girl"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_028_M", "Laser Eyes Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_029_M", "Classic Vampire"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_049_M", "Demon Drummer"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_006_M", "Skeleton Shot"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_010_M", "Music Is The Remedy"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_011_M", "Serpent Mic"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_019_M", "Weed Knuckles"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_009_M", "Scratch Panther"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_041_M", "Mighty Thog"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_040_M", "Tiger Heart"),

        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_026_M", "Banknote Rose"),
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_019_M", "Can't Win Them All"),
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_014_M", "Vice"),
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_005_M", "Get Lucky"),
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_002_M", "Suits"),

        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_029_M", "Cerberus"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_025_M", "Winged Serpent"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_013_M", "Katana"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_007_M", "Spartan Combat"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_004_M", "Tiger and Mask"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_001_M", "Viking Warrior"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_014_M", "Mermaid's Curse"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_008_M", "Horrors Of The Deep"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_004_M", "Honor"),

        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_003_M", "Toxic Trails"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_027_M", "Serpent Revolver"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_025_M", "Praying Skull"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_016_M", "Blood Money"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_015_M", "Spiked Skull"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_008_M", "Bandolier"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_004_M", "Sidearm"),

        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_008_M", "Scarlett"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_004_M", "Piston Sleeve"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_055_M", "Poison Scorpion"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_053_M", "Muffler Helmet"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_045_M", "Ride Hard Die Fast"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_035_M", "Chain Fist"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_025_M", "Good Luck"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_024_M", "Live to Ride"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_020_M", "Cranial Rose"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_016_M", "Macabre Tree"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_012_M", "Urban Stunter"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_043_M", "Engine Arm"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_039_M", "Kaboom"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_035_M", "Stuntman's End"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_023_M", "Tanked"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_022_M", "Piston Head"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_008_M", "Moonlight Ride"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_002_M", "Big Cat"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_001_M", "8 Eyed Skull"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_022_M", "My Crazy Life"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_018_M", "Skeleton Party"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_006_M", "Love Hustle"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_033_M", "City Sorrow"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_027_M", "Los Santos Life"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_005_M", "No Evil"),//

        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_028_M", "Python Skull"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_018_M", "Divine Goddess"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_016_M", "Egyptian Mural"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_005_M", "Fatal Dagger"),


        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_021_M", "Gabriel"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_020_M", "Archangel and Mary"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_009_M", "Floral Symmetry"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_021", "Time's Up Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_020", "Time's Up Outline"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_012", "8 Ball Skull"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_010", "Electric Snake"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_000", "Skull Rider"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_048", "Peace"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_043", "Triangle White"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_039", "Sleeve"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_037", "Sunrise"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_034", "Stop"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_028", "Thorny Rose"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_027", "Padlock"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_026", "Pizza"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_016", "Lightning Bolt"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_015", "Mustache"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_007", "Bricks"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_003", "Diamond Sparkle"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_M_LeftArm_001", "All-Seeing Eye"),
        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_M_LeftArm_000", "$100 Bill"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_LArm_000", "Tiki Tower"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_LArm_001", "Mermaid L.S."),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_041", "Dope Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_031", "Lady M"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_015", "Zodiac Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_006", "Oriental Mural"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_005", "Serpents"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_015", "Racing Brunette"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_007", "Racing Blonde"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_001", "Burning Heart"),//50 Death Match Award
        //not on list
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_031_M", "Geometric Design")
    };
    inline const std::vector<Mod_Class::Tattoo> maleTats06 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_007_M", "Stick Shift"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_006_M", "Mamba Sleeve"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_005_M", "Hot Rod Creep"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_022_M", "Turbo Hiss"),//

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_032_M", "Fooligan"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_027_M", "Orang-O-Tang Dude"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_029_M", "Orang-O-Tang Gray"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_031_M", "Sailor Fuku Killer"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_002_M", "Skull Bauble"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_003_M", "Bony Snowman"),

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_011_M", "Nothing Mini About It"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_012_M", "Snake Revolver"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_013_M", "Weapon Sleeve"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_030_M", "Centipede"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_031_M", "Fleshy Eye"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_045_M", "Armored Arm"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_046_M", "Demon Smile"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_047_M", "Angel & Devil"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_048_M", "Death Is Certain"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_000_M", "Hood Skeleton"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_005_M", "Peacock"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_007_M", "Ballas 4 Life"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_009_M", "Ascension"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_012_M", "Zombie Rhymes"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_020_M", "Dog Fist"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_032_M", "K.U.L.T.99.1 FM"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_031_M", "Octopus Shades"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_026_M", "Shark Water"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_012_M", "Still Slipping"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_011_M", "Soulwax"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_008_M", "Smiley Glitch"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_007_M", "Skeleton DJ"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_006_M", "Music Locker"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_005_M", "LSUR"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_003_M", "Lighthouse"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_002_M", "Jellyfish Shades"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_001_M", "Tropical Dude"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_000_M", "Headphone Splat"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_034_M", "LS Monogram"),

        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_028_M", "Skull and Aces"),
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_025_M", "Queen of Roses"),
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_018_M", "The Gambler's Life"),
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_004_M", "Lady Luck"),

        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_028_M", "Spartan Mural"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_023_M", "Samurai Tallship"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_018_M", "Muscle Tear"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_017_M", "Feather Sleeve"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_014_M", "Celtic Band"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_012_M", "Tiger Headdress"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_006_M", "Medusa"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_023_M", "Stylized Kraken"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_005_M", "Mutiny"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_001_M", "Crackshot"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_024_M", "Combat Reaper"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_021_M", "Have a Nice Day"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_002_M", "Grenade"),

        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_007_M", "Drive Forever"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_006_M", "Engulfed Block"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_005_M", "Dialed In"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_003_M", "Mechanical Sleeve"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_054_M", "Mum"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_049_M", "These Colors Don't Run"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_047_M", "Snake Bike"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_046_M", "Skull Chain"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_042_M", "Grim Rider"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_033_M", "Eagle Emblem"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_014_M", "Lady Mortality"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_007_M", "Swooping Eagle"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_049_M", "Seductive Mechanic"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_038_M", "One Down Five Up"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_036_M", "Biker Stallion"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_016_M", "Coffin Racer"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_010_M", "Grave Vulture"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_009_M", "Arachnid of Death"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_003_M", "Poison Wrench"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_035_M", "Black Tears"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_028_M", "Loving Los Muertos"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_003_M", "Lady Vamp"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_015_M", "Seductress"),

        Mod_Class::Tattoo("mpluxe2_overlays", "MP_LUXE_TAT_026_M", "Floral Print"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_LUXE_TAT_017_M", "Heavenly Deity"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_LUXE_TAT_010_M", "Intrometric"),

        Mod_Class::Tattoo("mpluxe_overlays", "MP_LUXE_TAT_019_M", "Geisha Bloom"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_LUXE_TAT_013_M", "Mermaid Harpist"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_LUXE_TAT_004_M", "Floral Raven"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_027", "Fuck Luck Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_026", "Fuck Luck Outline"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_023", "You're Next Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_022", "You're Next Outline"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_008", "Death Before Dishonor"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_004", "Snake Shaded"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_003", "Snake Outline"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_045", "Mesh Band"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_044", "Triangle Black"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_036", "Shapes"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_023", "Smiley"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_022", "Pencil"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_020", "Geo Pattern"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_018", "Origami"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_017", "Eye Triangle"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_014", "Spray Can"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_010", "Horseshoe"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_008", "Cube"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_004", "Bone"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_001", "Single Arrow"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_M_RightArm_001", "Green"),
        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_M_RightArm_000", "Dollar Skull"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_RArm_001", "Vespucci Beauty"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_RArm_000", "Tribal Sun"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_047", "Lion"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_038", "Dagger"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_028", "Mermaid"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_027", "Virgin Mary"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_018", "Serpent Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_014", "Flower Mural"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_003", "Dragons and Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_001", "Dragons"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_000", "Brotherhood"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_010", "Ride or Die"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_002", "Grim Reaper Smoking Gun"),
        //Not In List
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_LUXE_TAT_030_M", "Geometric Design")
    };
    inline const std::vector<Mod_Class::Tattoo> maleTats07 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_015_M", "Comedy and Tragedy"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_014_M", "Speed Demon"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_013_M", "Eyeball Shifter"),//

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_038_M", "Fool"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_037_M", "Orang-O-Tang Grenade"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_034_M", "Zombie Head"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_009_M", "Naughty Snow Globe"),

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_002_M", "Cobra Biker"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_014_M", "Minimal SMG"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_015_M", "Minimal Advanced Rifle"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_016_M", "Minimal Sniper Rifle"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_032_M", "Many-eyed Goat"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_053_M", "Mobster Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_054_M", "Wounded Head"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_055_M", "Stabbed Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_056_M", "Tiger Blade"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_022_M", "LS Smoking Cartridges"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_023_M", "Trust"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_029_M", "Soundwaves"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_028_M", "Skull Waters"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_025_M", "Glow Princess"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_024_M", "Pineapple Skull"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_010_M", "Tropical Serpent"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_032_M", "Love Fist"),

        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_027_M", "8-Ball Rose"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_013_M", "One-armed Bandit"),//

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_023_M", "Rose Revolver"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_011_M", "Death Skull"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_007_M", "Stylized Tiger"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_005_M", "Patriot Skull"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_057_M", "Laughing Skull"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_056_M", "Bone Cruiser"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_044_M", "Ride Free"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_037_M", "Scorched Soul"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_036_M", "Engulfed Skull"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_027_M", "Bad Luck"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_015_M", "Ride or Die"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_002_M", "Rose Tribute"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_031_M", "Stunt Jesus"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_028_M", "Quad Goblin"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_021_M", "Golden Cobra"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_013_M", "Dirt Track Hero"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_007_M", "Dagger Devil"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_029_M", "Death Us Do Part"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_020_M", "Presidents"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_007_M", "LS Serpent"),//

        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_011_M", "Cross of Roses"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_LUXE_TAT_000_M", "Serpent of Death"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_002", "Spider Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_001", "Spider Outline"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_040", "Black Anchor"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_019", "Charm"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_009", "Squares"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_Lleg_000", "Tribal Star"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_032", "Faith"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_037", "Grim Reaper"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_035", "Dragon"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_033", "Chinese Dragon"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_026", "Smoking Dagger"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_023", "Hottie"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_021", "Serpent Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_008", "Dragon Mural"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_002", "Melting Skull"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_009", "Dragon and Dagger")
    };
    inline const std::vector<Mod_Class::Tattoo> maleTats08 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_016_M", "Voodoo Skyline"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_017_M", "Sugoi Flames"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_019_M", "Crank Head"),//

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_039_M", "Jack Me"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_035_M", "Erupting Skeleton"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_036_M", "B Donk Now Crank It Later"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_008_M", "Gingerbread Steed"),

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_017_M", "Skull Grenade"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_033_M", "Three-eyed Demon"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_034_M", "Smoldering Reaper"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_050_M", "Gold Gun"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_051_M", "Blue Serpent"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_052_M", "Night Demon"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_003_M", "Bandana Knife"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_021_M", "Graffiti Skull"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_027_M", "Skullphones"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_031_M", "Kifflom"),

        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_020_M", "Cash is King"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_020_M", "Homeward Bound"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_030_M", "Pistol Ace"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_026_M", "Restless Skull"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_006_M", "Combat Skull"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_048_M", "STFU"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_040_M", "American Made"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_028_M", "Dusk Rider"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_022_M", "Western Insignia"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_004_M", "Dragon's Fury"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_047_M", "Brake Knife"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_045_M", "Severed Hand"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_032_M", "Wheelie Mouse"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_025_M", "Speed Freak"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_020_M", "Piston Angel"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_015_M", "Praying Gloves"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_005_M", "Demon Spark Plug"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_030_M", "San Andreas Prayer"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_023_M", "Dance of Hearts"),
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_017_M", "Ink Me"),

        Mod_Class::Tattoo("mpluxe2_overlays", "MP_LUXE_TAT_023_M", "Starmetric"),

        Mod_Class::Tattoo("mpluxe_overlays", "MP_LUXE_TAT_001_M", "Elaborate Los Muertos"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_M_Tat_014", "Floral Dagger"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_042", "Sparkplug"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_M_Tat_038", "Grub"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_M_Rleg_000", "Tribal Tiki Tower"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_043", "Indian Ram"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_042", "Flaming Scorpion"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_040", "Flaming Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_039", "Broken Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_022", "Fiery Dragon"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_017", "Tribal"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_M_007", "The Warrior"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_M_006", "Skull and Sword")
    };

    inline const std::vector<Mod_Class::Tattoo> femaleTats01 = {
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_007_F", "A Little Present For You"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_014_F", "Masked Machete Killer"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_022_F", "Fatal Incursion Outline"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_023_F", "Many-Headed Beast"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_024_F", "Demon Stitches"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_025_F", "Collector"),

        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_004_F", "Rearview"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_012_F", "Tempesta Girl"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_018_F", "Gearhead"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_020_F", "V8 Demon"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_021_F", "Devil in the Back Seat"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_023_F", "Dewbauchee Stylized"),//

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_006_F", "Painted Micro SMG"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_007_F", "Weapon King"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_035_F", "Sniff Sniff"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_036_F", "Charm Pattern"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_037_F", "Witch & Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_038_F", "Pumpkin Bug"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_039_F", "Sinner"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_057_F", "Gray Demon"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_004_F", "Hood Heart"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_008_F", "Los Santos Tag"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_013_F", "Blessed Boombox"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_014_F", "Chamberlain Hills"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_015_F", "Smoking Barrels"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_026_F", "Dollar Guns Crossed"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_021_F", "Skull Surfer"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_020_F", "Speaker Tower"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_019_F", "Record Shot"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_018_F", "Record Head"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_017_F", "Tropical Sorcerer"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_016_F", "Rose Panther"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_015_F", "Paradise Ukulele"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_014_F", "Paradise Nap"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_013_F", "Wild Dancers"),//

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_039_F", "Space Rangers"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_038_F", "Robot Bubblegum"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_036_F", "LS Shield"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_030_F", "Howitzer"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_028_F", "Bananas Gone Bad"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_027_F", "Epsilon"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_024_F", "Mount Chiliad"),//
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_023_F", "Bigfoot"),//

        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_032_F", "Play Your Ace"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_029_F", "The Table"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_021_F", "Show Your Hand"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_017_F", "Roll the Dice"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_015_F", "The Jolly Joker"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_011_F", "Life's a Gamble"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_010_F", "Photo Finish"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_009_F", "Till Death Do Us Part"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_008_F", "Snake Eyes"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_007_F", "777"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_006_F", "Wheel of Suits"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_001_F", "Jackpot"),//

        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_027_F", "Molon Labe"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_024_F", "Dragon Slayer"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_022_F", "Spartan and Horse"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_021_F", "Spartan and Lion"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_016_F", "Odin and Raven"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_015_F", "Samurai Combat"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_011_F", "Weathered Skull"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_010_F", "Spartan Shield"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_009_F", "Norse Rune"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_005_F", "Ghost Dragon"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_002_F", "Kabuto"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_025_F", "Claimed By The Beast"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_024_F", "Pirate Captain"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_022_F", "X Marks The Spot"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_018_F", "Finders Keepers"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_017_F", "Framed Tall Ship"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_016_F", "Skull Compass"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_013_F", "Torn Wings"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_009_F", "Tall Ship Conflict"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_006_F", "Never Surrender"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_003_F", "Give Nothing Back"),

        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_007_F", "Eagle Eyes"),
        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_005_F", "Parachute Belle"),
        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_004_F", "Balloon Pioneer"),
        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_002_F", "Winged Bombshell"),
        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_001_F", "Pilot Skull"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_022_F", "Explosive Heart"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_019_F", "Pistol Wings"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_018_F", "Dual Wield Skull"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_014_F", "Backstabber"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_013_F", "Wolf Insignia"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_009_F", "Butterfly Knife"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_001_F", "Crossed Weapons"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_000_F", "Bullet Proof"),

        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_011_F", "Talk Shit Get Hit"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_010_F", "Take the Wheel"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_009_F", "Serpents of Destruction"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_002_F", "Tuned to Death"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_001_F", "Power Plant"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_000_F", "Block Back"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_043_F", "Ride Forever"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_030_F", "Brothers For Life"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_021_F", "Flaming Reaper"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_017_F", "Clawed Beast"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_011_F", "R.I.P. My Brothers"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_008_F", "Freedom Wheels"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_006_F", "Chopper Freedom"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_048_F", "Racing Doll"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_046_F", "Full Throttle"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_041_F", "Brapp"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_040_F", "Monkey Chopper"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_037_F", "Big Grills"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_034_F", "Feather Road Kill"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_030_F", "Man's Ruin"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_029_F", "Majestic Finish"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_026_F", "Winged Wheel"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_024_F", "Road Kill"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_032_F", "Reign Over"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_031_F", "Dead Pretty"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_008_F", "Love the Game"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_000_F", "SA Assault"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_021_F", "Sad Angel"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_014_F", "Love is Blind"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_010_F", "Bad Angel"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_009_F", "Amazon"),//

        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_029_F", "Geometric Design"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_022_F", "Cloaked Angel"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_LUXE_TAT_024_F", "Feather Mural"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_LUXE_TAT_006_F", "Adorned Wolf"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_015", "Japanese Warrior"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_011", "Roaring Tiger"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_006", "Carp Shaded"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_005", "Carp Outline"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_046", "Triangles"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_041", "Tooth"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_032", "Paper Plane"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_031", "Skateboard"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_030", "Shark Fin"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_025", "Watch Your Step"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_024", "Pyamid"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_012", "Antlers"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_011", "Infinity"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_000", "Crossed Arrows"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_Back_001", "Gold Digger"),
        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_Back_000", "Respect"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Should_000", "Sea Horses"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Back_002", "Shrimp"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Should_001", "Catfish"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Back_000", "Rock Solid"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Back_001", "Hibiscus Flower Duo"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_045", "Skulls and Rose"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_030", "Lucky Celtic Dogs"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_020", "Dragon"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_019", "The Wages of Sin"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_016", "Evil Clown"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_013", "Eagle and Serpent"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_011", "LS Script"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_009", "Skull on the Cross"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_019", "Clown Dual Wield Dollars"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_018", "Clown Dual Wield"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_017", "Clown and Gun"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_016", "Clown"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_014", "Trust No One"),//Car Bomb Award
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_008", "Los Santos Customs"),//Mod a Car Award
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_005", "Angel"),//Win Every Game Mode Award
        //Not In List
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_046", "Zip?"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_006", "Feather Birds"),
        Mod_Class::Tattoo("mpchristmas2018_overlays", "MP_Christmas2018_Tat_000_F", "???")
    };
    inline const std::vector<Mod_Class::Tattoo> femaleTats02 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_024_F", "Futo Smoke"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_025_F", "Benefactor Demon"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_026_F", "Widowmaker"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_027_F", "Engine Heart"),//

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_004_F", "Herbal Bouquet"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_005_F", "Cash Krampus"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_006_F", "All In One Night"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_015_F", "Killer"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_016_F", "Powwer"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_017_F", "Two Headed Beast"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_018_F", "Dudes"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_019_F", "Fooligan Jester"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_020_F", "Vile Smile"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_021_F", "Demon Skull Jester"),

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_040_F", "Monkey"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_041_F", "Dragon"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_042_F", "Snake"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_043_F", "Goat"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_044_F", "Rat"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_045_F", "Rabbit"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_046_F", "Ox"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_047_F", "Pig"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_048_F", "Rooster"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_049_F", "Dog"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_050_F", "Horse"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_051_F", "Tiger"),

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_003_F", "Bullet Mouth"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_004_F", "Smoking Barrel"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_040_F", "Carved Pumpkin"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_041_F", "Branched Werewolf"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_042_F", "Winged Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_058_F", "Shrieking Dragon"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_059_F", "Swords & City"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_016_F", "All From The Same Tree"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_017_F", "King of the Jungle"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_018_F", "Night Owl"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_023_F", "Techno Glitch"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_022_F", "Paradise Sirens"),//

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_035_F", "LS Panic"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_033_F", "LS City"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_026_F", "Dignity"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_025_F", "Davis"),

        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_022_F", "Blood Money"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_003_F", "Royal Flush"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_000_F", "In the Pocket"),//

        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_026_F", "Spartan Skull"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_020_F", "Medusa's Gaze"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_019_F", "Strike Force"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_003_F", "Native Warrior"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_000_F", "Thor - Goblin"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_021_F", "Dead Tales"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_019_F", "Lost At Sea"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_007_F", "No Honor"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_000_F", "Bless The Dead"),

        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_000_F", "Turbulence"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_028_F", "Micro SMG Chain"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_020_F", "Crowned Weapons"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_017_F", "Dog Tags"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_012_F", "Dollar Daggers"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_060_F", "We Are The Mods!"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_059_F", "Faggio"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_058_F", "Reaper Vulture"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_050_F", "Unforgiven"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_041_F", "No Regrets"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_034_F", "Brotherhood of Bikes"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_032_F", "Western Eagle"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_029_F", "Bone Wrench"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_026_F", "American Dream"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_023_F", "Western MC"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_019_F", "Gruesome Talons"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_018_F", "Skeletal Chopper"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_013_F", "Demon Crossbones"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_005_F", "Made In America"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_001_F", "Both Barrels"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_000_F", "Demon Rider"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_044_F", "Ram Skull"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_033_F", "Sugar Skull Trucker"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_027_F", "Punk Road Hog"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_019_F", "Engine Heart"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_018_F", "Vintage Bully"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_011_F", "Wheels of Death"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_019_F", "Death Behind"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_012_F", "Royal Kiss"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_026_F", "Royal Takeover"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_013_F", "Love Gamble"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_002_F", "Holy Mary"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_001_F", "King Fight"),//

        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_027_F", "Cobra Dawn"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_025_F", "Reaper Sway"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_012_F", "Geometric Galaxy"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_002_F", "The Howler"),

        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_015_F", "Smoking Sisters"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_014_F", "Ancient Queen"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_008_F", "Flying Eye"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_007_F", "Eye of the Griffin"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_019", "Royal Dagger Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_018", "Royal Dagger Outline"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_017", "Loose Lips Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_016", "Loose Lips Outline"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_009", "Time To Die"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_047", "Cassette"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_033", "Stag"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_013", "Boombox"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_002", "Chemistry"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_Chest_002", "Love Money"),
        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_Chest_001", "Makin' Money"),
        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_Chest_000", "High Roller"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Chest_001", "Anchor"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Chest_000", "Anchor"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Chest_002", "Los Santos Wreath"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_044", "Stone Cross"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_034", "Flaming Shamrock"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_025", "LS Bold"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_024", "Flaming Cross"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_010", "LS Flames"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_013", "Seven Deadly Sins"),//Kill 1000 Players Award
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_012", "Embellished Scroll"),//Kill 500 Players Award
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_011", "Blank Scroll"),////Kill 100 Players Award?
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_003", "Blackjack")
    };
    inline const std::vector<Mod_Class::Tattoo> femaleTats03 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_028_F", "Sabre Turbo Eyes"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_029_F", "Turbo Dragon"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_030_F", "Fooligan Hellfire"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_031_F", "Hot Rod Demon"),//

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_005_F", "Concealed"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_043_F", "Cursed Saki"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_044_F", "Smouldering Bat & Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_060_F", "Blaine County"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_061_F", "Angry Possum"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_062_F", "Floral Demon"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_024_F", "Beatbox Silhouette"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_025_F", "Davis Flames"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_030_F", "Radio Tape"),//
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_004_F", "Skeleton Breeze"),//

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_037_F", "LadyBug"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_029_F", "Fatal Incursion"),

        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_031_F", "Gambling Royalty"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_024_F", "Cash Mouth"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_016_F", "Rose and Aces"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "mp_vinewood_tat_012_F", "Skull of Suits"),//

        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_008_F", "Spartan Warrior"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_015_F", "Jolly Roger"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_010_F", "See You In Hell"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_002_F", "Dead Lies"),

        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_006_F", "Bombs Away"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_029_F", "Win Some Lose Some"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_010_F", "Cash Money"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_052_F", "Biker Mount"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_039_F", "Gas Guzzler"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_031_F", "Gear Head"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_010_F", "Skull Of Taurus"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_003_F", "Web Rider"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_014_F", "Bat Cat of Spades"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_012_F", "Punk Biker"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_016_F", "Two Face"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_011_F", "Lady Liberty"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_004_F", "Gun Mic"),//

        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_003_F", "Abstract Skull"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_028", "Executioner"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_013", "Lizard"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_035", "Sewn Heart"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_029", "Sad"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_006", "Feather Birds"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_Stom_002", "Money Bag"),
        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_Stom_001", "Santo Capra Logo"),
        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_Stom_000", "Diamond Back"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Stom_000", "Swallow"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Stom_002", "Dolphin"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Stom_001", "Hibiscus Flower"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_RSide_000", "Love Dagger"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_036", "Way of the Gun"),//500 Pistol kills Award
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_029", "Trinity Knot"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_012", "Los Santos Bills"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_004", "Faith"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_004", "Hustler")
    };
    inline const std::vector<Mod_Class::Tattoo> femaleTats04 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_008_F", "Sparkey"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_009_F", "Sparks Flying"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_010_F", "Hot Piston"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_011_F", "Ignition"),//

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_010_F", "Dude"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_011_F", "Fooligan Tribal"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_012_F", "Skull Jester"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_013_F", "Budonk-adonk!"),

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_000_F", "Live Fast Mono"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_001_F", "Live Fast Color"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_018_F", "Branched Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_019_F", "Scythed Corpse"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_020_F", "Scythed Corpse & Reaper"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_021_F", "Third Eye"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_022_F", "Pierced Third Eye"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_023_F", "Lip Drip"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_024_F", "Skin Mask"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_025_F", "Webbed Scythe"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_026_F", "Oni Demon"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_027_F", "Bat Wings"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_001_F", "Bright Diamond"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_002_F", "Hustle"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_027_F", "Black Widow"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_044_F", "Clubs"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_043_F", "Diamonds"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_042_F", "Hearts"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_022_F", "Thong's Sword"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_021_F", "Wanted"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_020_F", "UFO"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_019_F", "Teddy Bear"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_018_F", "Stitches"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_017_F", "Space Monkey"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_016_F", "Sleepy"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_015_F", "On/Off"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_014_F", "LS Wings"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_013_F", "LS Star"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_012_F", "Razor Pop"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_011_F", "Lipstick Kiss"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_010_F", "Green Leaf"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_009_F", "Knifed"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_008_F", "Ice Cream"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_007_F", "Two Horns"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_006_F", "Crowned"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_005_F", "Spades"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_004_F", "Bandage"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_003_F", "Assault Rifle"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_002_F", "Animal"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_001_F", "Ace of Spades"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_000_F", "Five Stars"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_012_F", "Thief"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_011_F", "Sinner"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_003_F", "Lock and Load"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_051_F", "Western Stylized"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_038_F", "FTW"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_009_F", "Morbid Arachnid"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_042_F", "Flaming Quad"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_017_F", "Bat Wheel"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_Tat_006_F", "Toxic Spider"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_Tat_004_F", "Scorpion"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_Tat_000_F", "Stunt Skull"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_029", "Beautiful Death"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_025", "Snake Head Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_024", "Snake Head Outline"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_007", "Los Muertos"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_021", "Geo Fox"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_005", "Beautiful Eye"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_Neck_001", "Money Rose"),
        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_Neck_000", "Val-de-Grace Logo"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Neck_000", "Tribal Butterfly"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_Neck_000", "Little Fish"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_000", "Skull")
    };
    inline const std::vector<Mod_Class::Tattoo> femaleTats05 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_003_F", "Top Dead Center"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_002_F", "Flaming Driver"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_001_F", "Pegassi Flames"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_000_F", "Mk II Girl"),//

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_033_F", "Fooligan Impotent Rage"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_030_F", "Dude Jester"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_026_F", "Fooligan Clown"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_028_F", "Dude Outline"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_000_F", "The Christmas Spirit"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_001_F", "Festive Reaper"),

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_008_F", "Bigness Chimp"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_009_F", "Up-n-Atomizer Design"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_010_F", "Rocket Launcher Girl"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_028_F", "Laser Eyes Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_029_F", "Classic Vampire"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_049_F", "Demon Drummer"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_006_F", "Skeleton Shot"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_010_F", "Music Is The Remedy"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_011_F", "Serpent Mic"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_019_F", "Weed Knuckles"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_009_F", "Scratch Panther"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_041_F", "Mighty Thog"),
        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_040_F", "Tiger Heart"),

        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_026_F", "Banknote Rose"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_019_F", "Can't Win Them All"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_014_F", "Vice"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_005_F", "Get Lucky"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_002_F", "Suits"),//

        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_029_F", "Cerberus"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_025_F", "Winged Serpent"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_013_F", "Katana"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_007_F", "Spartan Combat"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_004_F", "Tiger and Mask"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_001_F", "Viking Warrior"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_014_F", "Mermaid's Curse"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_008_F", "Horrors Of The Deep"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_004_F", "Honor"),

        Mod_Class::Tattoo("mpairraces_overlays", "MP_Airraces_Tattoo_003_F", "Toxic Trails"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_027_F", "Serpent Revolver"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_025_F", "Praying Skull"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_016_F", "Blood Money"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_015_F", "Spiked Skull"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_008_F", "Bandolier"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_004_F", "Sidearm"),

        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_008_F", "Scarlett"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_004_F", "Piston Sleeve"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_055_F", "Poison Scorpion"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_053_F", "Muffler Helmet"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_045_F", "Ride Hard Die Fast"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_035_F", "Chain Fist"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_025_F", "Good Luck"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_024_F", "Live to Ride"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_020_F", "Cranial Rose"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_016_F", "Macabre Tree"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_012_F", "Urban Stunter"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_043_F", "Engine Arm"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_039_F", "Kaboom"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_035_F", "Stuntman's End"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_023_F", "Tanked"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_022_F", "Piston Head"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_008_F", "Moonlight Ride"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_002_F", "Big Cat"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_001_F", "8 Eyed Skull"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_022_F", "My Crazy Life"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_018_F", "Skeleton Party"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_006_F", "Love Hustle"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_033_F", "City Sorrow"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_027_F", "Los Santos Life"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_005_F", "No Evil"),//

        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_028_F", "Python Skull"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_018_F", "Divine Goddess"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_016_F", "Egyptian Mural"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_005_F", "Fatal Dagger"),

        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_021_F", "Gabriel"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_020_F", "Archangel and Mary"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_Luxe_Tat_009_F", "Floral Symmetry"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_021", "Time's Up Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_020", "Time's Up Outline"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_012", "8 Ball Skull"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_010", "Electric Snake"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_000", "Skull Rider"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_048", "Peace"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_043", "Triangle White"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_039", "Sleeve"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_037", "Sunrise"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_034", "Stop"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_028", "Thorny Rose"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_027", "Padlock"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_026", "Pizza"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_016", "Lightning Bolt"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_015", "Mustache"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_007", "Bricks"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_003", "Diamond Sparkle"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_LArm_000", "Greed is Good"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_LArm_001", "Parrot"),
        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_LArm_000", "Tribal Flower"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_041", "Dope Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_031", "Lady M"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_015", "Zodiac Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_006", "Oriental Mural"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_005", "Serpents"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_015", "Racing Brunette"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_007", "Racing Blonde"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_001", "Burning Heart"),//50 Death Match Award
        //not on list
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_031_F", "Geometric Design")
    };
    inline const std::vector<Mod_Class::Tattoo> femaleTats06 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_007_F", "Stick Shift"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_006_F", "Mamba Sleeve"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_005_F", "Hot Rod Creep"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_022_F", "Turbo Hiss"),//

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_032_F", "Fooligan"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_027_F", "Orang-O-Tang Dude"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_029_F", "Orang-O-Tang Gray"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_031_F", "Sailor Fuku Killer"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_002_F", "Skull Bauble"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_003_F", "Bony Snowman"),

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_011_F", "Nothing Mini About It"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_012_F", "Snake Revolver"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_013_F", "Weapon Sleeve"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_030_F", "Centipede"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_031_F", "Fleshy Eye"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_045_F", "Armored Arm"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_046_F", "Demon Smile"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_047_F", "Angel & Devil"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_048_F", "Death Is Certain"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_000_F", "Hood Skeleton"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_005_F", "Peacock"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_007_F", "Ballas 4 Life"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_009_F", "Ascension"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_012_F", "Zombie Rhymes"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_020_F", "Dog Fist"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_032_F", "K.U.L.T.99.1 FM"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_031_F", "Octopus Shades"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_026_F", "Shark Water"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_012_F", "Still Slipping"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_011_F", "Soulwax"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_008_F", "Smiley Glitch"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_007_F", "Skeleton DJ"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_006_F", "Music Locker"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_005_F", "LSUR"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_003_F", "Lighthouse"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_002_F", "Jellyfish Shades"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_001_F", "Tropical Dude"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_000_F", "Headphone Splat"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_034_F", "LS Monogram"),

        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_028_F", "Skull and Aces"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_025_F", "Queen of Roses"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_018_F", "The Gambler's Life"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_004_F", "Lady Luck"),//

        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_028_F", "Spartan Mural"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_023_F", "Samurai Tallship"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_018_F", "Muscle Tear"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_017_F", "Feather Sleeve"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_014_F", "Celtic Band"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_012_F", "Tiger Headdress"),
        Mod_Class::Tattoo("mpchristmas2017_overlays", "MP_Christmas2017_Tattoo_006_F", "Medusa"),

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_023_F", "Stylized Kraken"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_005_F", "Mutiny"),
        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_001_F", "Crackshot"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_024_F", "Combat Reaper"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_021_F", "Have a Nice Day"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_002_F", "Grenade"),

        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_007_F", "Drive Forever"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_006_F", "Engulfed Block"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_005_F", "Dialed In"),
        Mod_Class::Tattoo("mpimportexport_overlays", "MP_MP_ImportExport_Tat_003_F", "Mechanical Sleeve"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_054_F", "Mum"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_049_F", "These Colors Don't Run"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_047_F", "Snake Bike"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_046_F", "Skull Chain"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_042_F", "Grim Rider"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_033_F", "Eagle Emblem"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_014_F", "Lady Mortality"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_007_F", "Swooping Eagle"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_049_F", "Seductive Mechanic"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_038_F", "One Down Five Up"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_036_F", "Biker Stallion"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_016_F", "Coffin Racer"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_010_F", "Grave Vulture"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_009_F", "Arachnid of Death"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_003_F", "Poison Wrench"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_035_F", "Black Tears"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_028_F", "Loving Los Muertos"),
        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_003_F", "Lady Vamp"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_015_F", "Seductress"),//

        Mod_Class::Tattoo("mpluxe2_overlays", "MP_LUXE_TAT_026_F", "Floral Print"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_LUXE_TAT_017_F", "Heavenly Deity"),
        Mod_Class::Tattoo("mpluxe2_overlays", "MP_LUXE_TAT_010_F", "Intrometric"),

        Mod_Class::Tattoo("mpluxe_overlays", "MP_LUXE_TAT_019_F", "Geisha Bloom"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_LUXE_TAT_013_F", "Mermaid Harpist"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_LUXE_TAT_004_F", "Floral Raven"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_027", "Fuck Luck Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_026", "Fuck Luck Outline"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_023", "You're Next Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_022", "You're Next Outline"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_008", "Death Before Dishonor"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_004", "Snake Shaded"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_003", "Snake Outline"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_045", "Mesh Band"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_044", "Triangle Black"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_036", "Shapes"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_023", "Smiley"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_022", "Pencil"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_020", "Geo Pattern"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_018", "Origami"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_017", "Eye Triangle"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_014", "Spray Can"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_010", "Horseshoe"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_008", "Cube"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_004", "Bone"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_001", "Single Arrow"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_RArm_000", "Dollar Sign"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_RArm_001", "Tribal Fish"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_047", "Lion"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_038", "Dagger"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_028", "Mermaid"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_027", "Virgin Mary"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_018", "Serpent Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_014", "Flower Mural"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_003", "Dragons and Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_001", "Dragons"),
        //TatThis.AddMod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_000", "Brotherhood") ,-empty load?

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_010", "Ride or Die"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_002", "Grim Reaper Smoking Gun"),//Clear 5 Gang Atacks in a Day Award
        //Not In List
            Mod_Class::Tattoo("mpluxe2_overlays", "MP_LUXE_TAT_030_F", "Geometric Design")
    };
    inline const std::vector<Mod_Class::Tattoo> femaleTats07 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_015_F", "Comedy and Tragedy"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_014_F", "Speed Demon"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_013_F", "Eyeball Shifter"),//

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_038_F", "Fool"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_037_F", "Orang-O-Tang Grenade"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_034_F", "Zombie Head"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_009_F", "Naughty Snow Globe"),

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_002_F", "Cobra Biker"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_014_F", "Minimal SMG"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_015_F", "Minimal Advanced Rifle"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_016_F", "Minimal Sniper Rifle"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_032_F", "Many-eyed Goat"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_053_F", "Mobster Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_054_F", "Wounded Head"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_055_F", "Stabbed Skull"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_056_F", "Tiger Blade"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_022_F", "LS Smoking Cartridges"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_023_F", "Trust"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_029_F", "Soundwaves"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_028_F", "Skull Waters"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_025_F", "Glow Princess"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_024_F", "Pineapple Skull"),
        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_010_F", "Tropical Serpent"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_032_F", "Love Fist"),

        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_027_F", "8-Ball Rose"),//
        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_013_F", "One-armed Bandit"),//

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_023_F", "Rose Revolver"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_011_F", "Death Skull"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_007_F", "Stylized Tiger"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_005_F", "Patriot Skull"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_057_F", "Laughing Skull"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_056_F", "Bone Cruiser"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_044_F", "Ride Free"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_037_F", "Scorched Soul"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_036_F", "Engulfed Skull"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_027_F", "Bad Luck"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_015_F", "Ride or Die"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_002_F", "Rose Tribute"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_031_F", "Stunt Jesus"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_028_F", "Quad Goblin"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_021_F", "Golden Cobra"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_013_F", "Dirt Track Hero"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_007_F", "Dagger Devil"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_029_F", "Death Us Do Part"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_020_F", "Presidents"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_007_F", "LS Serpent"),//

        Mod_Class::Tattoo("mpluxe2_overlays", "MP_Luxe_Tat_011_F", "Cross of Roses"),
        Mod_Class::Tattoo("mpluxe_overlays", "MP_LUXE_TAT_000_F", "Serpent of Death"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_002", "Spider Color"),
        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_001", "Spider Outline"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_040", "Black Anchor"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_019", "Charm"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_009", "Squares"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_LLeg_000", "Single"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_032", "Faith"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_037", "Grim Reaper"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_035", "Dragon"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_033", "Chinese Dragon"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_026", "Smoking Dagger"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_023", "Hottie"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_021", "Serpent Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_008", "Dragon Mural"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_002", "Melting Skull"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_009", "Dragon and Dagger")
    };
    inline const std::vector<Mod_Class::Tattoo> femaleTats08 = {
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_016_F", "Voodoo Skyline"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_017_F", "Sugoi Flames"),//
        Mod_Class::Tattoo("mp2023_02_overlays", "MP_2023_02_Tat_019_F", "Crank Head"),//

        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_039_F", "Jack Me"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_035_F", "Erupting Skeleton"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_036_F", "B Donk Now Crank It Later"),
        Mod_Class::Tattoo("mpchristmas3_overlays", "MP_Christmas3_Tat_008_F", "Gingerbread Steed"),

        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_017_F", "Skull Grenade"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_033_F", "Three-eyed Demon"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_034_F", "Smoldering Reaper"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_050_F", "Gold Gun"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_051_F", "Blue Serpent"),
        Mod_Class::Tattoo("mpsum2_overlays", "MP_Sum2_Tat_052_F", "Night Demon"),

        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_003_F", "Bandana Knife"),
        Mod_Class::Tattoo("mpsecurity_overlays", "MP_Security_Tat_021_F", "Graffiti Skull"),

        Mod_Class::Tattoo("mpheist4_overlays", "MP_Heist4_Tat_027_F", "Skullphones"),

        Mod_Class::Tattoo("mpheist3_overlays", "mpHeist3_Tat_031_F", "Kifflom"),

        Mod_Class::Tattoo("mpvinewood_overlays", "MP_Vinewood_Tat_020_F", "Cash is King"),//

        Mod_Class::Tattoo("mpsmuggler_overlays", "MP_Smuggler_Tattoo_020_F", "Homeward Bound"),

        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_030_F", "Pistol Ace"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_026_F", "Restless Skull"),
        Mod_Class::Tattoo("mpgunrunning_overlays", "MP_Gunrunning_Tattoo_006_F", "Combat Skull"),

        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_048_F", "STFU"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_040_F", "American Made"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_028_F", "Dusk Rider"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_022_F", "Western Insignia"),
        Mod_Class::Tattoo("mpbiker_overlays", "MP_MP_Biker_Tat_004_F", "Dragon's Fury"),

        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_047_F", "Brake Knife"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_045_F", "Severed Hand"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_032_F", "Wheelie Mouse"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_025_F", "Speed Freak"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_020_F", "Piston Angel"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_015_F", "Praying Gloves"),
        Mod_Class::Tattoo("mpstunt_overlays", "MP_MP_Stunt_tat_005_F", "Demon Spark Plug"),

        Mod_Class::Tattoo("mplowrider2_overlays", "MP_LR_Tat_030_F", "San Andreas Prayer"),

        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_023_F", "Dance of Hearts"),//
        Mod_Class::Tattoo("mplowrider_overlays", "MP_LR_Tat_017_F", "Ink Me"),//

        Mod_Class::Tattoo("mpluxe2_overlays", "MP_LUXE_TAT_023_F", "Starmetric"),

        Mod_Class::Tattoo("mpluxe_overlays", "MP_LUXE_TAT_001_F", "Elaborate Los Muertos"),

        Mod_Class::Tattoo("mpchristmas2_overlays", "MP_Xmas2_F_Tat_014", "Floral Dagger"),

        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_042", "Sparkplug"),
        Mod_Class::Tattoo("mphipster_overlays", "FM_Hip_F_Tat_038", "Grub"),

        Mod_Class::Tattoo("mpbusiness_overlays", "MP_Buis_F_RLeg_000", "Diamond Crown"),

        Mod_Class::Tattoo("mpbeach_overlays", "MP_Bea_F_RLeg_000", "School of Fish"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_043", "Indian Ram"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_042", "Flaming Scorpion"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_040", "Flaming Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_039", "Broken Skull"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_022", "Fiery Dragon"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_017", "Tribal"),
        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_F_007", "The Warrior"),

        Mod_Class::Tattoo("multiplayer_overlays", "FM_Tat_Award_F_006", "Skull and Sword")
    };

    inline const std::vector<DWORD> KeyFind = {
         VK_TAB, //ImGuiKey_Tab;
         VK_LEFT, //ImGuiKey_LeftArrow;
         VK_RIGHT, //ImGuiKey_RightArrow;
         VK_UP, //ImGuiKey_UpArrow;
         VK_DOWN, //ImGuiKey_DownArrow;
         VK_PRIOR, //ImGuiKey_PageUp;
         VK_NEXT, //ImGuiKey_PageDown;
         VK_HOME, //ImGuiKey_Home;
         VK_END, //ImGuiKey_End;
         VK_INSERT, //ImGuiKey_Insert;
         VK_DELETE, //ImGuiKey_Delete;
         VK_BACK, //ImGuiKey_Backspace;
         VK_SPACE, //ImGuiKey_Space;
         VK_RETURN, //ImGuiKey_Enter;
         VK_ESCAPE, //ImGuiKey_Escape;
         VK_OEM_7, //ImGuiKey_Apostrophe;
         VK_OEM_COMMA, //ImGuiKey_Comma;
         VK_OEM_MINUS, //ImGuiKey_Minus;
         VK_OEM_PERIOD, //ImGuiKey_Period;
         VK_OEM_2, //ImGuiKey_Slash;
         VK_OEM_1, //ImGuiKey_Semicolon;
         VK_OEM_PLUS, //ImGuiKey_Equal;
         VK_OEM_4, //ImGuiKey_LeftBracket;
         VK_OEM_5, //ImGuiKey_Backslash;
         VK_OEM_6, //ImGuiKey_RightBracket;
         VK_OEM_3, //ImGuiKey_GraveAccent;
         VK_CAPITAL, //ImGuiKey_CapsLock;
         VK_SCROLL, //ImGuiKey_ScrollLock;
         VK_NUMLOCK, //ImGuiKey_NumLock;
         VK_SNAPSHOT, //ImGuiKey_PrintScreen;
         VK_PAUSE, //ImGuiKey_Pause;
         VK_NUMPAD0, //ImGuiKey_Keypad0;
         VK_NUMPAD1, //ImGuiKey_Keypad1;
         VK_NUMPAD2, //ImGuiKey_Keypad2;
         VK_NUMPAD3, //ImGuiKey_Keypad3;
         VK_NUMPAD4, //ImGuiKey_Keypad4;
         VK_NUMPAD5, //ImGuiKey_Keypad5;
         VK_NUMPAD6, //ImGuiKey_Keypad6;
         VK_NUMPAD7, //ImGuiKey_Keypad7;
         VK_NUMPAD8, //ImGuiKey_Keypad8;
         VK_NUMPAD9, //ImGuiKey_Keypad9;
         VK_DECIMAL, //ImGuiKey_KeypadDecimal;
         VK_DIVIDE, //ImGuiKey_KeypadDivide;
         VK_MULTIPLY, //ImGuiKey_KeypadMultiply;
         VK_SUBTRACT, //ImGuiKey_KeypadSubtract;
         VK_ADD, //ImGuiKey_KeypadAdd;
         VK_LSHIFT, //ImGuiKey_LeftShift;
         VK_LCONTROL, //ImGuiKey_LeftCtrl;
         VK_LMENU, //ImGuiKey_LeftAlt;
         VK_LWIN, //ImGuiKey_LeftSuper;
         VK_RSHIFT, //ImGuiKey_RightShift;
         VK_RCONTROL, //ImGuiKey_RightCtrl;
         VK_RMENU, //ImGuiKey_RightAlt;
         VK_RWIN, //ImGuiKey_RightSuper;
         VK_APPS, //ImGuiKey_Menu;
         '0', //ImGuiKey_0;
         '1', //ImGuiKey_1;
         '2', //ImGuiKey_2;
         '3', //ImGuiKey_3;
         '4', //ImGuiKey_4;
         '5', //ImGuiKey_5;
         '6', //ImGuiKey_6;
         '7', //ImGuiKey_7;
         '8', //ImGuiKey_8;
         '9', //ImGuiKey_9;
         'A', //ImGuiKey_A;
         'B', //ImGuiKey_B;
         'C', //ImGuiKey_C;
         'D', //ImGuiKey_D;
         'E', //ImGuiKey_E;
         'F', //ImGuiKey_F;
         'G', //ImGuiKey_G;
         'H', //ImGuiKey_H;
         'I', //ImGuiKey_I;
         'J', //ImGuiKey_J;
         'K', //ImGuiKey_K;
         'L', //ImGuiKey_L;
         'M', //ImGuiKey_M;
         'N', //ImGuiKey_N;
         'O', //ImGuiKey_O;
         'P', //ImGuiKey_P;
         'Q', //ImGuiKey_Q;
         'R', //ImGuiKey_R;
         'S', //ImGuiKey_S;
         'T', //ImGuiKey_T;
         'U', //ImGuiKey_U;
         'V', //ImGuiKey_V;
         'W', //ImGuiKey_W;
         'X', //ImGuiKey_X;
         'Y', //ImGuiKey_Y;
         'Z', //ImGuiKey_Z;
         VK_F1, //ImGuiKey_F1;
         VK_F2, //ImGuiKey_F2;
         VK_F3, //ImGuiKey_F3;
         VK_F4, //ImGuiKey_F4;
         VK_F5, //ImGuiKey_F5;
         VK_F6, //ImGuiKey_F6;
         VK_F7, //ImGuiKey_F7;
         VK_F8, //ImGuiKey_F8;
         VK_F9, //ImGuiKey_F9;
         VK_F10, //ImGuiKey_F10;
         VK_F11, //ImGuiKey_F11;
         VK_F12, //ImGuiKey_F12;
         VK_F13, //ImGuiKey_F13;
         VK_F14, //ImGuiKey_F14;
         VK_F15, //ImGuiKey_F15;
         VK_F16, //ImGuiKey_F16;
         VK_F17, //ImGuiKey_F17;
         VK_F18, //ImGuiKey_F18;
         VK_F19, //ImGuiKey_F19;
         VK_F20, //ImGuiKey_F20;
         VK_F21, //ImGuiKey_F21;
         VK_F22, //ImGuiKey_F22;
         VK_F23, //ImGuiKey_F23;
         VK_F24, //ImGuiKey_F24;
         VK_BROWSER_BACK, //ImGuiKey_AppBack;
         VK_BROWSER_FORWARD //ImGuiKey_AppForward;
    };
}