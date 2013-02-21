#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <math.h>

bool Debuging = false;

using namespace std;

#define NumberOfTools 10

bool Attack();
bool Build();
bool Burn();
bool Chop();
bool Craft();
bool Dig();
bool Enchant();
bool Go();
bool Hunt();
bool Inventory();
bool Mine();
bool PrintHelp();
bool Stats();
bool Tools();

bool CheckCraftable(unsigned short int Item);
bool Compare(string Input, string Comp);
bool CraftTool(string Item, string Type);

unsigned short int GetCompareNumberRecipes(string Input, string Comp);

string getChoice();

unsigned short int GetInventoryNumber(string Item);

void PrintChoiceError(string Error);
void Wait(float Time);

void PrintCrafting(unsigned short int Detail);

void DestroyPickaxe(unsigned short int Tool);
void DestroyAxe(unsigned short int Tool);
void DestroyShovel(unsigned short int Tool);
void GetMiningXp(unsigned short int Material);
void GetChopingXp(unsigned short int Material);
void GetDigingXp(unsigned short int Material);
void UpdateTotalXp();
void TryCraft(string Item);

unsigned short int GetMiningMaterial(unsigned short int Material);
unsigned short int GetChopingMaterial(unsigned short int Material);
unsigned short int GetDigingMaterial(unsigned short int Material);

bool Nether = false;
bool Portal = false;
bool CraftingTable = Debuging;
bool Furnace = false;

float PlayerXP = 0;
unsigned short int PlayerLevel = 0;

unsigned long int PlayerAttackXP = 0;
unsigned long int PlayerBuildXP = 0;
unsigned long int PlayerChopXP = 0;
unsigned long int PlayerDigXP = 0;
unsigned long int PlayerHuntXP = 0;
unsigned long int PlayerMineXP = 0;

const string AlreadyInNetherMessage = "You are already in the nether!";
const string AlreadyInWorldMessage = "You are already in the world!";
const string GoErrorMessage = "Exspected 'To'!";
const string MissingPortalToNetherMessage = "You can't teleport whitout a portal!";
const string MissingPortalToWorldMessage = "You can't teleport whitout a portal!";
const string PlaceErrorMessage = "The place is not found: ";
const string PortToNetherMessage = "You are teleporting to the nether!";
const string PortToWorldMessage = "You are teleporting to the world!";
const string MainChoiceText = "What do you want to do?";

const string MiningBlocksWorld[10] = {"Cobblestone", "GoldOre", "IronOre", "Coal", "LapisLazuli", "Sandstone", "Diamond", "RedstoneDust", "Emerald", "Obsidian"};
const string ChopingBlocksWorld[9] = {"Wood", "Cactus", "Pumpkin", "YellowFlower", "RedFlower", "RedMushroom", "BrownMushroom", "SugarCanes", "Apple"};
const string DigingBlocksWorld[5] = {"Dirt", "Sand", "Gravel", "ClayBlock", "Flint"};

const unsigned short int MiningChanceWorld[3][10] = { {700, 720, 770, 830, 860, 960, 970, 980, 990, 1000},
                                                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                                      {1, 1, 1, 1, 4, 1, 1, 4, 1, 1}
};
const unsigned short int ChopingChanceWorld[8] = {730, 800, 830, 880, 910, 935, 960, 1000};
const unsigned short int DigingChanceWorld[4] = {800, 880, 960, 1000};

const unsigned short int AppleChance = 125; // 1 / 1000
const unsigned short int FlintChance = 125; // 1 / 1000

const float MiningTimeWorld[10] = {2.00, 3.00, 2.00, 3.00, 3.00, 2.00, 3.00, 5.00, 2.00, 5.00};
const float ChopingTimeWorld[10] = {2.00, 3.00, 2.00, 3.00, 3.00, 2.00, 3.00, 5.00, 2.00, 5.00};
const float DigingTimeWorld[4] = {1.50, 1.50, 1.50, 1.50};

const unsigned short int MiningToolsWorld[10] = {1, 3, 2, 1, 2, 1, 3, 3, 3, 5};
const unsigned short int MiningXpWorld[10] = {0, 20, 10, 5, 10, 0, 25, 20, 25, 10};
const unsigned short int ChopingXpWorld[10] = {0, 20, 10, 5, 10, 0, 25, 20, 25, 10};
const unsigned short int DigingXpWorld[10] = {0, 20, 10, 5, 10, 0, 25, 20, 25, 10};

const string AttackCommand[3] = {"Attack", "attack", "ATTACK"};
const string BuildCommand[3] = {"Build", "build", "BUILD"};
const string BurnCommand[3] = {"Burn", "burn", "BURN"};
const string ChopCommand[3] = {"Chop", "chop", "CHOP"};
const string CoockCommand[3] = {"Coock", "coock", "COOCK"};
const string CraftCommand[3] = {"Craft", "craft", "CRAFT"};
const string DigCommand[3] = {"Dig", "dig", "DIG"};
const string EnchantCommand[3] = {"Enchant", "enchant", "ENCHANT"};
const string ExitCommand[3] = {"Exit", "exit", "EXIT"};
const string GoCommand[3] = {"Go", "go", "GO"};
const string HelpCommand[3] = {"Help", "help", "HELP"};
const string HuntCommand[3] = {"Hunt", "hunt", "HUNT"};
const string InventoryCommand[3] = {"Inventory", "inventory", "INVENTORY"};
const string MineCommand[3] = {"Mine", "mine", "MINE"};
const string NetherCommand[3] = {"Nether", "nether", "NETHER"};
const string StatsCommand[3] = {"Stats", "stats", "STATS"};
const string ToCommand[3] = {"To", "to", "TO"};
const string ToolsCommand[3] = {"Tools", "tools", "TOOLS"};
const string WorldCommand[3] = {"World", "world", "WORLD"};

#define NumberOfCraftable 5
const string Craftable[NumberOfCraftable] = {"WoodenPlank", "CraftingTable", "Torch", "WoodenStick", "Glowstone"};

#define NumberOfRecipes 19
const string Recipes[NumberOfRecipes][10] = {
    {"WoodenPlank", "WoodenPlank", "WoodenPlank", "WoodenPlank", "", "", "", "", "", "CraftingTable"},
    {"Wood", "", "", "", "", "", "", "", "", "WoodenPlank"},
    {"WoodenPlank", "WoodenPlank", "", "", "", "", "", "", "", "WoodenStick"},
    {"Cobblestone", "Cobblestone", "Cobblestone", "Cobblestone", "Cobblestone", "Cobblestone", "Cobblestone", "Cobblestone", "", "Furnace"},
    {"WoodenPlank", "WoodenPlank", "WoodenPlank", "WoodenStick", "WoodenStick", "", "", "", "", "WoodenPickaxe"},
    {"Cobblestone", "Cobblestone", "Cobblestone", "WoodenStick", "WoodenStick", "", "", "", "", "StonePickaxe"},
    {"IronIngot", "IronIngot", "IronIngot", "WoodenStick", "WoodenStick", "", "", "", "", "IronPickaxe"},
    {"GoldIngot", "GoldIngot", "GoldIngot", "WoodenStick", "WoodenStick", "", "", "", "", "GoldenPickaxe"},
    {"Diamond", "Diamond", "Diamond", "WoodenStick", "WoodenStick", "", "", "", "", "DiamondPickaxe"},
    {"WoodenPlank", "WoodenPlank", "WoodenPlank", "WoodenStick", "WoodenStick", "", "", "", "", "WoodenAxe"},
    {"Cobblestone", "Cobblestone", "Cobblestone", "WoodenStick", "WoodenStick", "", "", "", "", "StoneAxe"},
    {"IronIngot", "IronIngot", "IronIngot", "WoodenStick", "WoodenStick", "", "", "", "", "IronAxe"},
    {"GoldIngot", "GoldIngot", "GoldIngot", "WoodenStick", "WoodenStick", "", "", "", "", "GoldenAxe"},
    {"Diamond", "Diamond", "Diamond", "WoodenStick", "WoodenStick", "", "", "", "", "DiamondAxe"},
    {"WoodenPlank", "WoodenStick", "WoodenStick", "", "", "", "", "", "", "WoodenShovel"},
    {"Cobblestone", "WoodenStick", "WoodenStick", "", "", "", "", "StoneShovel"},
    {"IronIngot", "WoodenStick", "WoodenStick", "", "", "", "", "", "", "IronShovel"},
    {"GoldIngot", "WoodenStick", "WoodenStick", "", "", "", "", "", "", "GoldenShovel"},
    {"Diamond", "WoodenStick", "WoodenStick", "", "", "", "", "", "", "DiamondShovel"}
    /*
    {"WoodenPlank", "WoodenPlank", "WoodenStick", "", "", "", "", "", "", "WoodenSword"},
    {"Cobblestone", "Cobblestone", "WoodenStick", "", "", "", "", "StoneSword"},
    {"IronIngot", "IronIngot", "WoodenStick", "", "", "", "", "", "", "IronSword"},
    {"GoldIngot", "GoldIngot", "WoodenStick", "", "", "", "", "", "", "GoldenSword"},
    {"Diamond", "Diamond", "WoodenStick", "", "", "", "", "", "", "DiamondSword"},
    */


};
const unsigned short int RecipesNumber[NumberOfRecipes] = {1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

#define NumberOfItem 60
unsigned long int InventoryNumber[NumberOfItem];
const string InventoryString[3][NumberOfItem] = {
                                    {"WoodenPickaxe", "StonePickaxe", "IronPickaxe", "GoldPickaxe", "DiamondPickaxe", "WoodenAxe", "StoneAxe", "IronAxe", "GoldAxe", "DiamondAxe", "WoodenShovel", "StoneShovel", "IronShovel", "GoldShovel", "DiamondShovel", "Stone", "Cobblestone", "Dirt", "WoodenPlank", "WoodenStick", "Sand", "Gravel", "GoldOre", "GoldIngot", "IronOre", "IronIngot", "Coal", "Wood", "Diamond", "LapisLazuli", "Sandstone", "YellowFlower", "RedstoneDust", "Emerald", "RedFlower", "BrownMushroom", "RedMushroom", "Cactus", "ClayBlock", "Flint", "Apple", "SugerCane", "Pumpkin", "Mycelium", "Obsidian", "Wool", "CraftingTable", "Furnace", "Netherrack", "SoulSand", "GlowstoneBlock", "NetherBrick", "NetherBrickFence", "NetherBrickStairs", "NetherWart"},
                                    {"woodenpickaxe", "stonepickaxe", "ironpickaxe", "goldpickaxe", "diamondpickaxe", "woodenaxe", "stoneaxe", "ironaxe", "goldaxe", "diamondaxe", "woodenshovel", "stoneshovel", "ironshovel", "goldshovel", "diamondshovel", "stone", "cobblestone", "dirt", "woodenplank", "woodenstick", "sand", "gravel", "goldore", "goldingot", "ironore", "ironingot", "coal", "wood", "diamond", "lapislazuli", "sandstone", "yellowflower", "redstonedust", "emerald", "redflower", "brownmushroom", "redmushroom", "cactus", "clayblock", "flint", "apple", "sugercane", "pumpkin", "mycelium", "obsidian", "wool", "craftingtable", "furnace", "netherrack", "soulsand", "glowstoneblock", "netherbrick", "netherbrickfence", "netherbrickstairs", "netherwart"},
                                    {"WoodenPickaxe", "StonePickaxe", "IronPickaxe", "GoldPickaxe", "DiamondPickaxe", "WoodenAxe", "StoneAxe", "IronAxe", "GoldAxe", "DiamondAxe", "WoodenShovel", "StoneShovel", "IronShovel", "GoldShovel", "DiamondShovel", "STONE", "COBBLESTONE", "DIRT", "WOODENPLANK", "WOODENSTICK", "SAND", "GRAVEL", "GOLDORE", "GoldIngot", "IRONORE", "IronIngot", "COAL", "WOOD", "DIAMOND", "LAPISLAZULI", "SANDSTONE", "YELLOWFLOWER", "REDSTONEDUST", "EMERALD", "REDFLOWER", "BROWNMUSHROOM", "REDMUSHROOM", "CACTUS", "CLAYBLOCK", "FLINT", "APPLE", "SUGARCANE", "PUMPKIN", "MYCELIUM", "OBSIDIAN", "WOOL", "CRAFTINGTABLE", "FURNACE", "NETHERRACK", "SOULSAND", "GLOWSTONEBLOCK", "NETHERBRICK", "NETHERBRICKFENCE", "NETHERBRICKSTAIRS", "NETHERWART"}
};

unsigned short int SelectedPickaxe = 0; // The curent selected pickaxe
unsigned short int SelectedAxe = 0; // The curent selected axe
unsigned short int SelectedShovel = 0; // The curent selected shovel

unsigned short int NewTool[5][2] = {
                                    {100, 128}, // % of speed, Durability fo woodenpickaxe
                                    {80, 256}, // % of speed, Durability fo stonepickaxe
                                    {60, 512}, // % of speed, Durability fo ironpickaxe
                                    {50, 1024}, // % of speed, Durability fo goldenpickaxe
                                    {40, 2048} // % of speed, Durability fo diamondpickaxe
};

unsigned short int Pickaxe[5][NumberOfTools] = {
    {5, 2},
    {1024, 256},
    {3, 1},
    {3, 1},
    {3, 1}
}; // Type (Wood, Stone ...), Durability, EfficiencyLevel, FortuneLevel, UnbreakingLevel
unsigned short int Axe[5][NumberOfTools] = {{5},{1024},{3},{3},{3}}; // Type (Wood, Stone ...), Durability, EfficiencyLevel, FortuneLevel, UnbreakingLevel
unsigned short int Shovel[5][NumberOfTools] = {{5},{1024},{3},{3},{3}}; // Type (Wood, Stone ...), Durability, EfficiencyLevel, FortuneLevel, UnbreakingLevel
/*const unsigned short int EnchantmentChance[2][5] = {
                                    {, , }
                                    {, , }
                                    {, , }
}; //Efficiency, Fortune, Unbreaking

const unsigned short int ToolEnchantmentsWeight[3][2] = {10, 5, 2}; //Effciency, Unbreaking, Fortune
*/
unsigned short int Efficiency[4] = {100, 80, 60, 40}; // {100% TimeLevel0, 80% TimeLevel1, ...
unsigned short int Fortune[4][2] = {{0, 0},{350, 0},{300, 450},{500, 750}}; // {{ChanceToGetDoubleLevel0, ChanceToGetTripleLevel0},{ChanceToGetDoubleLevel1, ...
unsigned short int Unbreaking[4] = {8, 4, 2, 1}; // {8 DamageLevel0, 4 DamageLevel1 ...

const string PickaxeString[5] = {"Wooden Pickaxe", "Stone Pickaxe", "Iron Pickaxe", "Golden Pickaxe", "Diamond Pickaxe"};
const string AxeString[5] = {"Wooden Axe", "Stone Axe", "Iron Axe", "Golden Axe", "Diamond Axe"};
const string ShovelString[5] = {"Wooden Shovel", "Stone Shovel", "Iron Shovel", "Golden Shovel", "Diamond Shovel"};

#define NumberOfBurningItem 19
const string Burning[NumberOfBurningItem][2] = {
                                                {"RawPorkchop", "CookedPorkchop"},
                                                {"RawBeef", "Steak"},
                                                {"CookedChicken", "RawChicken"},
                                                {"RawFish", "CookedFish"},
                                                {"Potato", "BakedPotato"},
                                                {"IronOre", "IronIngot"},
                                                {"GoldOre", "GoldIngot"},
                                                {"Sand", "Glass"},
                                                {"Cobblestone", "Stone"},
                                                {"Clay", "Brick"},
                                                {"Netherrack", "NetherBrick"},
                                                {"DiamondOre", "Diamond"},
                                                {"LapisLazuliOre", "LapisLazuli"},
                                                {"RedstoneOre", "RedstoneDust"},
                                                {"CoalOre", "Coal"},
                                                {"EmeraldOre", "Emerald"},
                                                {"NetherQuartzOre", "NetherQuartz"},
                                                {"Wood", "Charcoal"},
                                                {"Cactus", "CactusGreen"}
};
int main(){ // Done
    srand(time(0));
    string Choice;
    while (Choice != ExitCommand[0] && Choice != ExitCommand[1] && Choice != ExitCommand[2]){
        Choice = getChoice();
        if (Choice == ChopCommand[0] || Choice == ChopCommand[1] || Choice == ChopCommand[2]){if (Chop()){break;}}
        else if (Choice == AttackCommand[0] || Choice == AttackCommand[1] || Choice == AttackCommand[2]){if (Attack()){break;}}
        else if (Choice == BuildCommand[0] || Choice == BuildCommand[1] || Choice == BuildCommand[2]){if (Build()){break;}}
        else if (Choice == BurnCommand[0] || Choice == BurnCommand[1] || Choice == BurnCommand[2]){if (Burn()){break;}}
        else if (Choice == CoockCommand[0] || Choice == CoockCommand[1] || Choice == CoockCommand[2]){if (Burn()){break;}}
        else if (Choice == CraftCommand[0] || Choice == CraftCommand[1] || Choice == CraftCommand[2]){if (Craft()){break;}}
        else if (Choice == DigCommand[0] || Choice == DigCommand[1] || Choice == DigCommand[2]){if (Dig()){break;}}
        else if (Choice == EnchantCommand[0] || Choice == EnchantCommand[1] || Choice == EnchantCommand[2]){if (Enchant()){break;}}
        else if (Choice == GoCommand[0] || Choice == GoCommand[1] || Choice == GoCommand[2]){if (Go()){break;}}
        else if (Choice == HelpCommand[0] || Choice == HelpCommand[1] || Choice == HelpCommand[2]){if (PrintHelp()){break;}}
        else if (Choice == HuntCommand[0] || Choice == HuntCommand[1] || Choice == HuntCommand[2]){if (Hunt()){break;}}
        else if (Choice == InventoryCommand[0] || Choice == InventoryCommand[1] || Choice == InventoryCommand[2]){if (Inventory()){break;}}
        else if (Choice == MineCommand[0] || Choice == MineCommand[1] || Choice == MineCommand[2]){if (Mine()){break;}}
        else if (Choice == StatsCommand[0] || Choice == StatsCommand[1] || Choice == StatsCommand[2]){if (Stats()){break;}}
        else if (Choice == ToolsCommand[0] || Choice == ToolsCommand[1] || Choice == ToolsCommand[2]){if (Tools()){break;}}
        else PrintChoiceError(Choice);
    }
    return false;
}
bool Attack(){
    cout << "Attack" << endl;
    return false;
}
bool Break(){
    cout << "Break" << endl;
    return false;
}
bool Build(){
    cout << "Build" << endl;
    return false;
}
bool Burn(){
    cout << "Burn(Coock)" << endl;
    cout << "========================" << endl;
    return false;
}
bool Chop(){ // Done
    cout << "Chop" << endl;
    cout << "========================" << endl;
    if (!Nether){
        unsigned short int Chance = rand() % 1000;
        unsigned short int Material;
        if (Chance < ChopingChanceWorld[0]) Material = 0;
        else if (Chance < ChopingChanceWorld[1]) Material = 1;
        else if (Chance < ChopingChanceWorld[2]) Material = 2;
        else if (Chance < ChopingChanceWorld[3]) Material = 3;
        else if (Chance < ChopingChanceWorld[4]) Material = 4;
        else if (Chance < ChopingChanceWorld[5]) Material = 5;
        else if (Chance < ChopingChanceWorld[6]) Material = 6;
        else if (Chance < ChopingChanceWorld[7]) Material = 7;
        GetChopingXp(Material);
        GetChopingMaterial(Material);
        DestroyAxe(SelectedAxe);
    }
    else{
        cout << "You can't chop in nether!" << endl;
    }
    return false;
}
bool Craft(){ // Done
    cout << "Craft" << endl;
    cout << "=========================" << endl;
    cout << "Write 'Craft Help' for more info!" << endl;
    string Choice;
    cin >> Choice;
    if (Choice == HelpCommand[0] || Choice == HelpCommand[1] || Choice == HelpCommand[2]){
        cout << "Error! Command not found: " << Choice << endl;
        cout << "Write 'Craft Help' for more info!" << endl;
        cout << endl;
    }
    else if (Choice == "ShowCraftable") PrintCrafting(0);
    else if (Choice == "ShowAll") PrintCrafting(1);
    else if (Choice == "ShowNeeded") PrintCrafting(2);
    else if (Choice == "ShowCount") PrintCrafting(3);
    else if (Choice == "ShowRecipes") PrintCrafting(4);

    else{
        TryCraft(Choice);
    }

    return false;
}
bool Dig(){ // Done - Missing Nether
    cout << "Dig" << endl;
    cout << "========================" << endl;
    if (!Nether){
        unsigned short int Chance = rand() % 1000;
        unsigned short int Material;
        if (Chance < DigingChanceWorld[0]) Material = 0;
        else if (Chance < DigingChanceWorld[1]) Material = 1;
        else if (Chance < DigingChanceWorld[2]) Material = 2;
        else if (Chance < DigingChanceWorld[3]) Material = 3;
        GetDigingXp(Material);
        GetDigingMaterial(Material);
        DestroyShovel(SelectedShovel);
    }
    else{

    }
    return false;
}
bool Enchant(){
    /*if (EnchantingTable == true && Bookshelvs == true) {
        cout << "Enchant" << endl;
        cout << "========================" << endl;
        cout << "Select what tool you want to enchant: ";

        unsigned short int Chance = rand() % 1000;

        string ToolSelected;
        short int LevelSelected;

        cin >> ToolSelected;

        if (ToolSelected == "Pickaxe" || ToolSelected == "pickaxe" || ToolSelected == "PICKAXE") {
            cout << "Pickaxe selected"; << endl;
            cout << "Type in what level enchantment you want to put on your pickaxe: ";

            cin >> LevelSelected;

            if (LevelSelected == PlayerLevel) {
                if (Chance < [0]) Pickaxe[5][PickaxeSelected] = 0;
                else if (Chance < [1]) Material = 1;
                else if (Chance < [2]) Material = 2;
                else if (Chance < [3]) Material = 3;
                else if (Chance < [4]) Material = 4;
                else if (Chance < [5]) Material = 5;
                else if (Chance < [6]) Material = 6;
                else if (Chance < [7]) Material = 7;
            }
            else cout << "You do not have enough levels" << endl;
        }
    }
    else cout << "You need an Enchantment Table to be able to enchant!" << endl; return false;
    */
    return false;
}
bool Go(){ // Done
    string Choice;
    cin >> Choice;
    if (Choice == ToCommand[0] || Choice == ToCommand[1] || Choice == ToCommand[2]){
        cin >> Choice;
        if (Choice == NetherCommand[0] || Choice == NetherCommand[1] || Choice == NetherCommand[2]){
            if (!Nether){
                if (Portal){
                    Nether = true;
                    cout << PortToNetherMessage << endl;
                }
                else cout << MissingPortalToNetherMessage << endl;
            }
            else cout << AlreadyInNetherMessage << endl;
        }
        else if (Choice == WorldCommand[0] || Choice == WorldCommand[1] || Choice == WorldCommand[2]){
            if (Nether){
                if (Portal){
                    Nether = false;
                    cout << PortToWorldMessage << endl;
                }
                else cout << MissingPortalToWorldMessage << endl;
            }
            else cout << AlreadyInWorldMessage << endl;
        }
        else cout << PlaceErrorMessage << Choice << endl;
    }
    else cout << GoErrorMessage << endl;
    return false;
}
bool Hunt(){
    cout << "Hunt" << endl;
    return false;
}
bool Inventory(){ // Done
    cout << "Inventory" << endl;
    cout << "=========================" << endl;
    for (int a = 0; a < NumberOfItem; a++){
        if (InventoryNumber[a]){
            cout << InventoryString[0][a] << ": " << InventoryNumber[a] << endl;
        }
    }
    return false;
}
bool Mine(){ // Done - Missing Nether
    cout << "Mine" << endl;
    cout << "========================" << endl;
    unsigned short int Chance = rand() % 1000;
    if (!Nether){
        if (Pickaxe[0][SelectedPickaxe]){
            unsigned short int Material;
            if (Chance < MiningChanceWorld[0][0]){if (MiningToolsWorld[0] <= Pickaxe[0][SelectedPickaxe])      {GetMiningXp(0); Material = GetMiningMaterial(0); DestroyPickaxe(SelectedPickaxe);} else {cout << "You can't mine " << MiningBlocksWorld[0] << " whith a " << PickaxeString[Pickaxe[0][SelectedPickaxe] - 1] << endl;}}
            else if (Chance < MiningChanceWorld[0][1]){if (MiningToolsWorld[1] <= Pickaxe[0][SelectedPickaxe]) {GetMiningXp(1); Material = GetMiningMaterial(1); DestroyPickaxe(SelectedPickaxe);} else {cout << "You can't mine " << MiningBlocksWorld[1] << " whith a " << PickaxeString[Pickaxe[0][SelectedPickaxe] - 1] << endl;}}
            else if (Chance < MiningChanceWorld[0][2]){if (MiningToolsWorld[2] <= Pickaxe[0][SelectedPickaxe]) {GetMiningXp(2); Material = GetMiningMaterial(2); DestroyPickaxe(SelectedPickaxe);} else {cout << "You can't mine " << MiningBlocksWorld[2] << " whith a " << PickaxeString[Pickaxe[0][SelectedPickaxe] - 1] << endl;}}
            else if (Chance < MiningChanceWorld[0][3]){if (MiningToolsWorld[3] <= Pickaxe[0][SelectedPickaxe]) {GetMiningXp(3); Material = GetMiningMaterial(3); DestroyPickaxe(SelectedPickaxe);} else {cout << "You can't mine " << MiningBlocksWorld[3] << " whith a " << PickaxeString[Pickaxe[0][SelectedPickaxe] - 1] << endl;}}
            else if (Chance < MiningChanceWorld[0][4]){if (MiningToolsWorld[4] <= Pickaxe[0][SelectedPickaxe]) {GetMiningXp(4); Material = GetMiningMaterial(4); DestroyPickaxe(SelectedPickaxe);} else {cout << "You can't mine " << MiningBlocksWorld[4] << " whith a " << PickaxeString[Pickaxe[0][SelectedPickaxe] - 1] << endl;}}
            else if (Chance < MiningChanceWorld[0][5]){if (MiningToolsWorld[5] <= Pickaxe[0][SelectedPickaxe]) {GetMiningXp(5); Material = GetMiningMaterial(5); DestroyPickaxe(SelectedPickaxe);} else {cout << "You can't mine " << MiningBlocksWorld[5] << " whith a " << PickaxeString[Pickaxe[0][SelectedPickaxe] - 1] << endl;}}
            else if (Chance < MiningChanceWorld[0][6]){if (MiningToolsWorld[6] <= Pickaxe[0][SelectedPickaxe]) {GetMiningXp(6); Material = GetMiningMaterial(6); DestroyPickaxe(SelectedPickaxe);} else {cout << "You can't mine " << MiningBlocksWorld[6] << " whith a " << PickaxeString[Pickaxe[0][SelectedPickaxe] - 1] << endl;}}
            else if (Chance < MiningChanceWorld[0][7]){if (MiningToolsWorld[7] <= Pickaxe[0][SelectedPickaxe]) {GetMiningXp(7); Material = GetMiningMaterial(7); DestroyPickaxe(SelectedPickaxe);} else {cout << "You can't mine " << MiningBlocksWorld[7] << " whith a " << PickaxeString[Pickaxe[0][SelectedPickaxe] - 1] << endl;}}
            else if (Chance < MiningChanceWorld[0][8]){if (MiningToolsWorld[8] <= Pickaxe[0][SelectedPickaxe]) {GetMiningXp(8); Material = GetMiningMaterial(8); DestroyPickaxe(SelectedPickaxe);} else {cout << "You can't mine " << MiningBlocksWorld[8] << " whith a " << PickaxeString[Pickaxe[0][SelectedPickaxe] - 1] << endl;}}
            else if (Chance < MiningChanceWorld[0][9]){if (MiningToolsWorld[9] <= Pickaxe[0][SelectedPickaxe]) {GetMiningXp(9); Material = GetMiningMaterial(9); DestroyPickaxe(SelectedPickaxe);} else {cout << "You can't mine " << MiningBlocksWorld[9] << " whith a " << PickaxeString[Pickaxe[0][SelectedPickaxe] - 1] << endl;}}
        }
        else cout << "You have no Pickaxe selected!" << endl;
    }
    else{

    }
    return false;
}
bool PrintHelp(){ // Done
    string Help = "";
    Help += "Help\n";
    Help += "=========================\n";
    Help += "Attack\n";
    Help += "Build\n";
    Help += "Burn\n";
    Help += "Chop\n";
    Help += "Coock\n";
    Help += "Craft\n";
    Help += "Enchant\n";
    Help += "Go to Nether\n";
    Help += "Go to World\n";
    Help += "Help\n";
    Help += "Hunt\n";
    Help += "Inventory\n";
    Help += "Mine\n";
    cout << Help << endl;
}
bool Stats(){ // Done
    cout << "Stats" << endl;
    cout << "=========================" << endl;
    cout << "Attack XP:    " << PlayerAttackXP << endl;
    cout << "Building XP:  " << PlayerBuildXP << endl;
    cout << "Choping XP:   " << PlayerChopXP << endl;
    cout << "Diging XP:    " << PlayerDigXP << endl;
    cout << "Hunting XP:   " << PlayerHuntXP << endl;
    cout << "Mining XP:    " << PlayerMineXP << endl;
    cout << endl;
    cout << "Total Xp:     " << PlayerXP << endl;
    cout << "Total level:  " << PlayerLevel << endl;
    cout << endl;
    return false;
}
bool Tools(){ // Done
    cout << "Stats" << endl;
    cout << "=========================" << endl;
    for (unsigned short int a = 0; a < 5; a++) if (Pickaxe[0][a]){
        cout << "Pickaxe slot " << a << ": " << InventoryString[0][Pickaxe[0][a] - 1] << ", Durability = " << Pickaxe[1][a] << ", Efficiency Level = " << Pickaxe[2][a] << ", Fortune Level = " << Pickaxe[3][a] << ", Unbreaking Level = " << Pickaxe[4][a] << endl;
    }
    for (unsigned short int a = 0; a < 5; a++) if (Axe[0][a]){
        cout << "Axe slot " << a << ": " << InventoryString[0][Axe[0][a] + 4] << ", Durability = " << Axe[1][a] << ", Efficiency Level = " << Axe[2][a] << ", Fortune Level = " << Axe[3][a] << ", Unbreaking Level = " << Axe[4][a] << endl;
    }
    for (unsigned short int a = 0; a < 5; a++) if (Shovel[0][a]){
        cout << "Shovel slot " << a << ": " << InventoryString[0][Shovel[0][a] + 9] << ", Durability = " << Shovel[1][a] << ", Efficiency Level = " << Shovel[2][a] << ", Fortune Level = " << Pickaxe[3][a] << ", Unbreaking Level = " << Pickaxe[4][a] << endl;
    }
}
string getChoice(){ // Done
    cout << MainChoiceText << endl;
    string choice;
    cin >> choice;
    cout << endl;
    return choice;
}
void PrintChoiceError(string Error){ // Done
    cout << "Error! Command not found: " << Error << endl;
    cout << "Write 'Help' for more info!" << endl;
    cout << endl;
}
void Wait(float Time){ // Done
    if (!Debuging){
        float secs = Time;
        clock_t delay = secs * CLOCKS_PER_SEC;
        clock_t start = clock();
        while (clock() - start < delay);
    }
}
unsigned short int GetInventoryNumber(string Item){ // Done
    for (unsigned short int a = 0; true; a++){
        if (Item == InventoryString[0][a]){
            return a;
            break;
        }
    }
}
unsigned short int GetMiningMaterial(unsigned short int Material){ // Done
    unsigned short int NumberOfMaterials = (rand() % int(MiningChanceWorld[2][Material])) + MiningChanceWorld[1][Material];

    if (Pickaxe[3][SelectedPickaxe]){
        unsigned short int Chance = rand() % 1000;

        if (Chance < Fortune[Pickaxe[3][SelectedPickaxe]][0]) NumberOfMaterials *= 2;
        else if (Chance < Fortune[Pickaxe[3][SelectedPickaxe]][1]) NumberOfMaterials *= 3;
    }
    Wait(MiningTimeWorld[Material] * (NewTool[Pickaxe[0][SelectedPickaxe] - 1][0] / float(Efficiency[3 - Pickaxe[4][SelectedPickaxe]])));
    cout << "You got " << NumberOfMaterials << " " << MiningBlocksWorld[Material] << endl;

    InventoryNumber[GetInventoryNumber(MiningBlocksWorld[Material])] += NumberOfMaterials;
    cout << "You now have: " << InventoryNumber[GetInventoryNumber(MiningBlocksWorld[Material])] << " " << MiningBlocksWorld[Material] << endl;
    cout << endl;

    return Material;
}
unsigned short int GetChopingMaterial(unsigned short int Material){ // Done
    unsigned short int NumberOfMaterials = 1;
    if (Axe[3][SelectedAxe]){
        unsigned short int Chance = rand() % 1000;
        if (Chance < Fortune[Axe[3][SelectedAxe]][0]) NumberOfMaterials *= 2;
        else if (Chance < Fortune[Axe[3][SelectedAxe]][1]) NumberOfMaterials *= 3;
    }
    Wait(ChopingTimeWorld[Material] * (NewTool[Axe[0][SelectedAxe] - 1][0] / float(Efficiency[3 - Axe[4][SelectedAxe]])));
    if (Material == 0){
        unsigned short int Apple = rand() % 1000;
        if (Apple < AppleChance){
            InventoryNumber[GetInventoryNumber(ChopingBlocksWorld[8])] += 1;
            cout << "You got 1 Apple!"  << endl;
            cout << "You now have: " << InventoryNumber[GetInventoryNumber(ChopingBlocksWorld[8])] << " Apples!" << endl;
        }
    }
    cout << "You got " << NumberOfMaterials << " " << ChopingBlocksWorld[Material] << "!" << endl;

    InventoryNumber[GetInventoryNumber(ChopingBlocksWorld[Material])] += NumberOfMaterials;
    cout << "You now have: " << InventoryNumber[GetInventoryNumber(ChopingBlocksWorld[Material])] << " " << ChopingBlocksWorld[Material] << "!" << endl;
    cout << endl;

    return Material;
}
unsigned short int GetDigingMaterial(unsigned short int Material){ // Done
    if (Material == 2){
        unsigned short int Flint = rand() % 1000;
        if (Flint < FlintChance) Material = 4;
    }

    unsigned short int NumberOfMaterials = 1;
    if (Shovel[3][SelectedShovel]){
        unsigned short int Chance = rand() % 1000;
        if (Chance < Fortune[Shovel[3][SelectedShovel]][0]) NumberOfMaterials *= 2;
        else if (Chance < Fortune[Shovel[3][SelectedShovel]][1]) NumberOfMaterials *= 3;
    }
    Wait(DigingTimeWorld[Material] * (NewTool[Shovel[0][SelectedShovel] - 1][0] / float(Efficiency[3 - Shovel[4][SelectedShovel]])));
    cout << "You got " << NumberOfMaterials << " " << DigingBlocksWorld[Material] << endl;

    InventoryNumber[GetInventoryNumber(DigingBlocksWorld[Material])] += NumberOfMaterials;
    cout << "You now have: " << InventoryNumber[GetInventoryNumber(DigingBlocksWorld[Material])] << " " << DigingBlocksWorld[Material] << endl;
    cout << endl;

    return Material;
}
void DestroyPickaxe(unsigned short int Item){ // Done
    Pickaxe[1][Item] -= Unbreaking[Pickaxe[4][SelectedPickaxe]];
    if (Pickaxe[1][Item] <= 0){
        for (int a = 0; a < 4; a++) Pickaxe[a][Item] = 0;
        cout << "Your Pickaxe broke!" << endl;
    }
}
void DestroyAxe(unsigned short int Item){ // Done
    Axe[1][Item] -= Unbreaking[Axe[4][SelectedAxe]];
    if (Axe[1][Item] <= 0){
        for (int a = 0; a < 4; a++) Axe[a][Item] = 0;
        cout << "Your Axe broke!" << endl;
    }
}
void DestroyShovel(unsigned short int Item){ // Done
    Shovel[1][Item] -= Unbreaking[Shovel[4][SelectedShovel]];
    if (Shovel[Item] <= 0){
        for (int a = 0; a < 4; a++) Shovel[a][Item] = 0;
        cout << "Your Shovel broke!" << endl;
    }
}
void GetMiningXp(unsigned short int Material){ // Done
    PlayerMineXP += MiningXpWorld[Material];
    UpdateTotalXp();
}
void GetChopingXp(unsigned short int Material){ // Done
    PlayerChopXP += ChopingXpWorld[Material];
    UpdateTotalXp();
}
void GetDigingXp(unsigned short int Material){ // Done
    PlayerDigXP += DigingXpWorld[Material];
    UpdateTotalXp();
}
void UpdateTotalXp(){ // Done
    PlayerXP = PlayerAttackXP + PlayerBuildXP + PlayerChopXP + PlayerDigXP + PlayerHuntXP + PlayerMineXP;
    PlayerLevel = pow((-20.00 + PlayerXP), 0.40);
}
bool CheckCraftable(unsigned short int Item){ // Done
    unsigned long int InventoryCraftableCheck[NumberOfItem];
    for (unsigned short int a = 0; a < NumberOfItem; a++) InventoryCraftableCheck[a] = InventoryNumber[a];
    unsigned short int Trues = 0;
    for (unsigned short int a = 0; a < 9; a++){
        if (Recipes[Item][a] == "" || InventoryCraftableCheck[GetInventoryNumber(Recipes[Item][a])]){
            InventoryCraftableCheck[GetInventoryNumber(Recipes[Item][a])]--;
            Trues++;
        }
    }
    if (Trues == 9) return true;
    else return false;
}
void PrintCrafting(unsigned short int Detail){ // Done
    if (!Detail){
        cout << "Craftable Items:" << endl;
        for (unsigned short int a = 0; a < NumberOfRecipes; a++) if (CheckCraftable(a)) cout << Recipes[a][9] << endl;
        cout << endl;
    }
    else if (Detail == 1){
        cout << "Craftable?:" << endl;
        for (unsigned short int a = 0; a < NumberOfRecipes; a++){
            if (CheckCraftable(a)) cout << Recipes[a][9] << ": True" << endl;
            else cout << Recipes[a][9] << ": False" << endl;
        }
        cout << endl;
    }
    else if (Detail == 2) for (unsigned short int a = 0; a < NumberOfRecipes; a++){
        if (!CheckCraftable(a)){
            unsigned long int InventoryCraftableCheck[NumberOfItem];
            for (unsigned short int b = 0; b < NumberOfItem; b++) InventoryCraftableCheck[b] = InventoryNumber[b];
            cout << "Needed for crafting " << Recipes[a][9] << ": ";
            for (unsigned short int b = 0; b < 9; b++){
                if (Recipes[a][b] == "" || InventoryCraftableCheck[GetInventoryNumber(Recipes[a][b])]) InventoryCraftableCheck[GetInventoryNumber(Recipes[a][b])]--;
                else{
                    cout << Recipes[a][b] << " ";
                }
            }
            cout << endl;
        }
        else cout << Recipes[a][9] << " is craftable." << endl;
    }
    else if (Detail == 3) for (unsigned short int a = 0; a < NumberOfRecipes; a++){
        if (CheckCraftable(a)){
            unsigned long int InventoryCraftableCheck[NumberOfItem];
            for (unsigned short int b = 0; b < NumberOfItem; b++) InventoryCraftableCheck[b] = InventoryNumber[b];
            unsigned short int count = 0;
            for (unsigned short int b = 0; true; b++){
                unsigned short int Trues = 0;
                for (unsigned short int c = 0; c < 9; c++){
                    if (Recipes[a][c] == "" || InventoryCraftableCheck[GetInventoryNumber(Recipes[a][c])]){
                        if (Recipes[a][c] != "") InventoryCraftableCheck[GetInventoryNumber(Recipes[a][c])]--;
                        Trues++;
                    }
                }
                count = b * RecipesNumber[a];
                if (Trues < 9) break;
            }
            cout << count << " x " << Recipes[a][9] << endl;
        }
        else cout << "Can't craft " << Recipes[a][9] << endl;
    }
    else if (Detail == 4){
        cout << "Crafting recipes:" << endl;
        for (unsigned short int a = 0; a < NumberOfRecipes; a++){
            cout << RecipesNumber[a] << " x " << Recipes[a][9] << ":";
            for (unsigned short int b = 0; b < 9; b++) if (Recipes[a][b] != "") cout << " " << Recipes[a][b];
            cout << endl;
        }
        cout << endl;
    }
}
void TryCraft(string Item){ // Done - Missing (Fishingrod, Sword, Bow, Shoes, Pants, Chest, Helm, FlintN'Steel)
    bool Able = false;
    unsigned short int CompareNumber;

    for (int a = 0; a < NumberOfRecipes; a++){
        bool Compareable = Compare(Item, Recipes[a][9]);
        if (Compareable){
            CompareNumber = GetCompareNumberRecipes(Item, Recipes[a][9]);
            Able = true;
            break;
        }
    }

    if (Able){
        bool Allow = false;
        if (!CraftingTable){
            for (unsigned short int a = 0; a < NumberOfCraftable; a++){
                if (Craftable[a] == Recipes[CompareNumber][9]) Allow = true;
            }
        }
        if (Allow || CraftingTable){
            if (CheckCraftable(CompareNumber)){
                for (unsigned short int a = 0; a < 9; a++) if (Recipes[CompareNumber][a] != ""){
                    InventoryNumber[GetInventoryNumber(Recipes[CompareNumber][a])]--;
                }
                if (CraftTool(Recipes[CompareNumber][9], "Pickaxe")){
                    unsigned short int Slot;
                    for (unsigned short int a = 0; a < NumberOfTools; a++){
                        if (!Pickaxe[0][a]){
                            Slot = a;
                            break;
                        }
                        else if (a == 9){
                            cout << "No empty Pickaxeslots!" << endl;
                            Slot = 1000;
                        }
                    }
                    if (Slot != 1000){
                        Pickaxe[0][Slot] = GetInventoryNumber(Recipes[CompareNumber][9]) + 1;
                        Pickaxe[1][Slot] = NewTool[GetInventoryNumber(Recipes[CompareNumber][9])][1];
                        cout << "1 x " << Recipes[CompareNumber][9] << " crafted!" << endl;
                        cout << endl;
                    }
                }
                else if (CraftTool(Recipes[CompareNumber][9], "Axe")){
                    unsigned short int Slot;
                    for (unsigned short int a = 0; a < NumberOfTools; a++){
                        if (!Axe[0][a]){
                            Slot = a;
                            break;
                        }
                        else if (a == 9){
                            cout << "No empty Axeslots!" << endl;
                            Slot = 1000;
                        }
                    }
                    if (Slot != 1000){
                        Axe[0][Slot] = GetInventoryNumber(Recipes[CompareNumber][9]) - 4;
                        Axe[1][Slot] = NewTool[GetInventoryNumber(Recipes[CompareNumber][9]) - 5][1];
                        cout << "1 x " << Recipes[CompareNumber][9] << " crafted!" << endl;
                        cout << endl;
                    }

                }
                else if (CraftTool(Recipes[CompareNumber][9], "Shovel")){
                    unsigned short int Slot;
                    for (unsigned short int a = 0; a < NumberOfTools; a++){
                        if (!Shovel[0][a]){
                            Slot = a;
                            break;
                        }
                        else if (a == 9){
                            cout << "No empty Shovelslots!" << endl;
                            Slot = 1000;
                        }
                    }
                    if (Slot != 1000){
                        Shovel[0][Slot] = GetInventoryNumber(Recipes[CompareNumber][9]) - 9;
                        Shovel[1][Slot] = NewTool[GetInventoryNumber(Recipes[CompareNumber][9]) - 10][1];
                        cout << "1 x " << Recipes[CompareNumber][9] << " crafted!" << endl;
                        cout << endl;
                    }
                }
                else{
                    InventoryNumber[GetInventoryNumber(Recipes[CompareNumber][9])] += RecipesNumber[CompareNumber];
                    if (Recipes[CompareNumber][9] == "CraftingTable") CraftingTable = true;
                    else if (Recipes[CompareNumber][9] == "Furnace") Furnace = true;
                    cout << RecipesNumber[CompareNumber] << " x " << Recipes[CompareNumber][9] << " crafted!" << endl;
                    cout << endl;
                }
            }
            else cout << "Need resorces for crafting: " << Recipes[CompareNumber][9] << endl;
        }
        else{
            cout << "Can't craft " << Recipes[CompareNumber][9] << " whithout a CaftingTable!" << endl;
        }
    }
    else{
        cout << "Error! Command not found: " << Item << endl;
        cout << "Write 'Craft Help' for more info!" << endl;
        cout << endl;
    }
}
bool CraftTool(string Item, string Type){ // Done
    bool Bool = false;
    if (Type == "Pickaxe"){
        for (unsigned short int a = 0; a < 5; a++){
            if (Item == InventoryString[0][a]){
                Bool = true;
                break;
            }
        }
    }
    else if (Type == "Axe"){
        for (unsigned short int a = 5; a < 10; a++){
            if (Item == InventoryString[0][a]){
                Bool = true;
                break;
            }
        }
    }
    if (Type == "Shovel"){
        for (unsigned short int a = 10; a < 15; a++){
            if (Item == InventoryString[0][a]){
                Bool = true;
                break;
            }
        }
    }
    return Bool;
}
unsigned short int GetCompareNumberRecipes(string Input, string Comp){ // Done
    for (unsigned short int a = 0; a < NumberOfItem; a++){
        for (unsigned short int b = 0; b < 3; b++){
            if (Input == InventoryString[b][a]){
                if (Comp == InventoryString[0][a]){
                    for (unsigned short int c = 0; c < NumberOfRecipes; c++){
                        if (Recipes[c][9] == InventoryString[0][a]){
                            return c;
                        }
                    }
                    break;
                    break;
                }
            }
        }
    }
}
bool Compare(string Input, string Comp){ // Done
    bool Bool = false;
    for (unsigned short int a = 0; a < NumberOfItem; a++){
        for (unsigned short int b = 0; b < 3; b++){
            if (Input == InventoryString[b][a]){
                if (Comp == InventoryString[0][a]){
                    Bool = true;
                    break;
                    break;
                }
            }
        }
    }
    return Bool;
}
