#pragma once
#pragma warning(disable: 4099)
#pragma comment(lib, "pluginsdk.lib")
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

#include <pch.h>
#include <json.hpp>
#include <fpstimer.hpp>
#include <resource.hpp>
#include <imgui/imgui_rotate.h>
#include "bakkesmod/wrappers/GuiManagerWrapper.h"

#include <map>
#include <vector>
#include <fstream>
#include <windows.h>
#include <functional>
#include <utils/parser.h>

#include "Utils.h"
#include "Languages.h"
#include "Resources/Resource.h"

#define  M_PI	3.14159265358979323846

using json = nlohmann::json;

namespace fs = std::filesystem;

enum ToggleFlags {
	ToggleFlags_Toggle,
	ToggleFlags_Show,
	ToggleFlags_Hide
};

enum RefreshFlags {
	RefreshFlags_Off,
	RefreshFlags_Refresh,
	RefreshFlags_RefreshAndImages
};

enum RecoveryFlags {
	RecoveryFlags_Off,
	RecoveryFlags_Files,
	RecoveryFlags_Welcome,
	RecoveryFlags_Process,
	RecoveryFlags_Finish
};

struct Color {
	bool enable = false;
	ImColor color = ImGui::GetColorU32({ 255.f, 255.f, 255.f, 1.f });
};

struct Element {
	std::string name = "Unknown";
	std::string type;
	std::string font;
	std::string value;
	std::vector<ImVec2> positions;
	ImVec2 size;
	Color color;
	Color fill;
	Color stroke;
	float scale = 1.f;
	bool rotate_enable = false;
	float rotate = 0.f;
};

struct Options {
	int x;
	int y;
	int width;
	int height;
	float scale;
	float opacity;
};

struct Stats {
	int games = 0;
	float myMMR = 100.f;
	float MMRChange = 0.f;
	float MMRCumulChange = 0.f;
	int win = 0;
	int loss = 0;
	int streak = 0;
	int demo = 0;
	int demoCumul = 0;
	int death = 0;
	int deathCumul = 0;

	/// Shots
	int Center = 0;
	int Clear = 0;
	int FirstTouch = 0;
	int ShotOnGoal = 0;
	int AerialHit = 0;
	int BicycleHit = 0;
	int TeamClear = 0;
	int TeamShotOnGoal = 0;
	int TeamBicycleHit = 0;
	int TotalClear = 0;
	int TotalShotOnGoal = 0;
	int TotalBicycleHit = 0;

	int CenterCumul = 0;
	int ClearCumul = 0;
	int FirstTouchCumul = 0;
	int ShotOnGoalCumul = 0;
	int AerialHitCumul = 0;
	int BicycleHitCumul = 0;
	int TeamClearCumul = 0;
	int TeamShotOnGoalCumul = 0;
	int TeamBicycleHitCumul = 0;
	int TotalClearCumul = 0;
	int TotalShotOnGoalCumul = 0;
	int TotalBicycleHitCumul = 0;

	/// Miscs
	int HatTrick = 0;
	int LowFive = 0;
	int HighFive = 0;
	int MVP = 0;
	int TeamHatTrick = 0;
	int TeamLowFive = 0;
	int TeamHighFive = 0;
	int TeamMVP = 0;
	int TotalHatTrick = 0;
	int TotalLowFive = 0;
	int TotalHighFive = 0;
	int TotalMVP = 0;

	int HatTrickCumul = 0;
	int LowFiveCumul = 0;
	int HighFiveCumul = 0;
	int MVPCumul = 0;
	int TeamHatTrickCumul = 0;
	int TeamLowFiveCumul = 0;
	int TeamHighFiveCumul = 0;
	int TeamMVPCumul = 0;
	int TotalHatTrickCumul = 0;
	int TotalLowFiveCumul = 0;
	int TotalHighFiveCumul = 0;
	int TotalMVPCumul = 0;

	/// Assists
	int Assist = 0;
	int Playmaker = 0; // 3 assists in a game
	int TeamAssist = 0;
	int TeamPlaymaker = 0;
	int TotalAssist = 0;
	int TotalPlaymaker = 0;

	int AssistCumul = 0;
	int PlaymakerCumul = 0;
	int TeamAssistCumul = 0;
	int TeamPlaymakerCumul = 0;
	int TotalAssistCumul = 0;
	int TotalPlaymakerCumul = 0;

	/// Goals
	int Goal = 0;
	int OwnGoal = 0;
	int AerialGoal = 0;
	int BackwardsGoal = 0;
	int BicycleGoal = 0;
	int LongGoal = 0;
	int TurtleGoal = 0;
	int OvertimeGoal = 0;
	int HoopsSwishGoal = 0;
	int PoolShot = 0;
	int TeamGoal = 0;
	int TeamAerialGoal = 0;
	int TeamBackwardsGoal = 0;
	int TeamBicycleGoal = 0;
	int TeamLongGoal = 0;
	int TeamTurtleGoal = 0;
	int TeamOvertimeGoal = 0;
	int TeamHoopsSwishGoal = 0;
	int TeamPoolShot = 0;
	int TotalGoal = 0;
	int TotalAerialGoal = 0;
	int TotalBackwardsGoal = 0;
	int TotalBicycleGoal = 0;
	int TotalLongGoal = 0;
	int TotalTurtleGoal = 0;
	int TotalOvertimeGoal = 0;
	int TotalHoopsSwishGoal = 0;
	int TotalPoolShot = 0;

	int GoalCumul = 0;
	int OwnGoalCumul = 0;
	int AerialGoalCumul = 0;
	int BackwardsGoalCumul = 0;
	int BicycleGoalCumul = 0;
	int LongGoalCumul = 0;
	int TurtleGoalCumul = 0;
	int OvertimeGoalCumul = 0;
	int HoopsSwishGoalCumul = 0;
	int PoolShotCumul = 0;
	int TeamGoalCumul = 0;
	int TeamAerialGoalCumul = 0;
	int TeamBackwardsGoalCumul = 0;
	int TeamBicycleGoalCumul = 0;
	int TeamLongGoalCumul = 0;
	int TeamTurtleGoalCumul = 0;
	int TeamOvertimeGoalCumul = 0;
	int TeamHoopsSwishGoalCumul = 0;
	int TeamPoolShotCumul = 0;
	int TotalGoalCumul = 0;
	int TotalAerialGoalCumul = 0;
	int TotalBackwardsGoalCumul = 0;
	int TotalBicycleGoalCumul = 0;
	int TotalLongGoalCumul = 0;
	int TotalTurtleGoalCumul = 0;
	int TotalOvertimeGoalCumul = 0;
	int TotalHoopsSwishGoalCumul = 0;
	int TotalPoolShotCumul = 0;

	/// Saves
	int Save = 0;
	int EpicSave = 0;
	int Savior = 0; // 3 saves in a game
	int TeamSave = 0;
	int TeamEpicSave = 0;
	int TeamSavior = 0;
	int TotalSave = 0;
	int TotalEpicSave = 0;
	int TotalSavior = 0;

	int SaveCumul = 0;
	int EpicSaveCumul = 0;
	int SaviorCumul = 0;
	int TeamSaveCumul = 0;
	int TeamEpicSaveCumul = 0;
	int TeamSaviorCumul = 0;
	int TotalSaveCumul = 0;
	int TotalEpicSaveCumul = 0;
	int TotalSaviorCumul = 0;

	/// Dropshot
	int BreakoutDamage = 0;
	int BreakoutDamageLarge = 0;
	int TeamBreakoutDamage = 0;
	int TeamBreakoutDamageLarge = 0;
	int TotalBreakoutDamage = 0;
	int TotalBreakoutDamageLarge = 0;

	int BreakoutDamageCumul = 0;
	int BreakoutDamageLargeCumul = 0;
	int TeamBreakoutDamageCumul = 0;
	int TeamBreakoutDamageLargeCumul = 0;
	int TotalBreakoutDamageCumul = 0;
	int TotalBreakoutDamageLargeCumul = 0;

	/// Knockout
	int Knockout = 0;
	int KnockoutDeath = 0;
	int KnockoutThrown = 0;
	int KnockoutGrabbed = 0;
	int KnockoutDoubleKO = 0;
	int KnockoutHeavyHit = 0;
	int KnockoutHitTaken = 0;
	int KnockoutLightHit = 0;
	int KnockoutBlockTaken = 0;
	int KnockoutHeavyBlock = 0;
	int KnockoutTeam = 0;
	int KnockoutTeamDeath = 0;
	int KnockoutTeamDoubleKO = 0;
	int KnockoutTeamHeavyHit = 0;
	int KnockoutTeamHeavyBlock = 0;
	int KnockoutTotal = 0;
	int KnockoutTotalDeath = 0;
	int KnockoutTotalDoubleKO = 0;
	int KnockoutTotalHeavyHit = 0;
	int KnockoutTotalHeavyBlock = 0;

	int KnockoutMatch = 0;
	int KnockoutDeathMatch = 0;
	int KnockoutThrownMatch = 0;
	int KnockoutGrabbedMatch = 0;
	int KnockoutDoubleKOMatch = 0;
	int KnockoutHeavyHitMatch = 0;
	int KnockoutHitTakenMatch = 0;
	int KnockoutLightHitMatch = 0;
	int KnockoutBlockTakenMatch = 0;
	int KnockoutHeavyBlockMatch = 0;
	int KnockoutTeamMatch = 0;
	int KnockoutTeamDeathMatch = 0;
	int KnockoutTeamDoubleKOMatch = 0;
	int KnockoutTeamHeavyHitMatch = 0;
	int KnockoutTeamHeavyBlockMatch = 0;
	int KnockoutTotalMatch = 0;
	int KnockoutTotalDeathMatch = 0;
	int KnockoutTotalDoubleKOMatch = 0;
	int KnockoutTotalHeavyHitMatch = 0;
	int KnockoutTotalHeavyBlockMatch = 0;

	int KnockoutCumul = 0;
	int KnockoutDeathCumul = 0;
	int KnockoutThrownCumul = 0;
	int KnockoutGrabbedCumul = 0;
	int KnockoutDoubleKOCumul = 0;
	int KnockoutHeavyHitCumul = 0;
	int KnockoutHitTakenCumul = 0;
	int KnockoutLightHitCumul = 0;
	int KnockoutBlockTakenCumul = 0;
	int KnockoutHeavyBlockCumul = 0;
	int KnockoutTeamCumul = 0;
	int KnockoutTeamDeathCumul = 0;
	int KnockoutTeamDoubleKOCumul = 0;
	int KnockoutTeamHeavyHitCumul = 0;
	int KnockoutTeamHeavyBlockCumul = 0;
	int KnockoutTotalDeathCumul = 0;
	int KnockoutTotalDoubleKOCumul = 0;
	int KnockoutTotalHeavyHitCumul = 0;
	int KnockoutTotalCumul = 0;
	int KnockoutTotalHeavyBlockCumul = 0;

	bool isInit = false;
};

struct ThemeFont {
	int size = 0;
	std::string name = "";
	bool isDefault = false;
};

struct Theme {
	std::string name = "Unknown";
	std::string author = "Unknown";
	std::string version = "v1.0.0";
	std::string date = "";
	std::vector<ThemeFont> fonts = {};
	std::vector<Element> elements;
};

struct StatTickerParams {
	uintptr_t Receiver; // person who got a stat
	uintptr_t Victim; // person who is victim of a stat (only exists for demos afaik)
	uintptr_t StatEvent;
};

struct StatEventParams {
	uintptr_t PRI; // always primary player
	uintptr_t StatEvent; // wrapper for the stat event
};

struct Vector2D {
	float x = 0;
	float y = 0;
	float width = 0;
	float height = 0;
};


class RocketStats : public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginWindow
{
private:
	int rs_recovery = RecoveryFlags_Off;
	float rs_launch = 0.f;
	float rs_llaunch = 0.f;
	bool rs_logo_mouv = false;
	float rs_buttons_x = 0.f;
	float rs_logo_rotate = 0.f;
	float rs_screen_scale[2] = { 1.f, 1.f };
	std::vector<std::string> rs_lang;
	std::shared_ptr<ImageWrapper> rs_logo;
	std::shared_ptr<ImageWrapper> rs_title;
	std::shared_ptr<ImageWrapper> rs_welcome;
	ImDrawList* rs_drawlist = IM_NEW(ImDrawList(NULL));

	// Time
	tm local_time;
	time_t current_time;
	FPSTimer timer_30fps = FPSTimer(30, true);

	// Themes
	ImVec2 theme_size = { 0.f, 0.f };
	ImVec2 display_size = { 0.f, 0.f };
	unsigned char theme_style = 0;
	unsigned char theme_refresh = 2;

	json theme_config = json::object();
	json themes_values = json::object();
	Theme theme_render;
	std::string theme_prev = "";
	std::string theme_hide_value = "##";
	std::vector<Theme> themes;
	std::vector<std::string> modes;
	std::map<std::string, std::string> theme_vars;
	std::map<std::string, std::shared_ptr<ImageWrapper>> theme_images;

	// Overlay
	bool overlay_move = false;
	ImVec2 overlay_cursor;
	ImVec2 overlay_origin;

	//std::unique_ptr<MMRNotifierToken> notifierToken;

	// Game states
	int menu_stack = 0;
	bool is_in_game = false;
	bool is_in_menu = false;
	bool is_in_freeplay = false;
	bool is_in_scoreboard = false;
	bool is_online_game = false;
	bool is_offline_game = false;
	bool is_boosting = false;
	bool is_game_ended = false;
	bool is_game_started = false;

	// All stats
	Stats always;
	Stats session;
	std::map<int, Stats> stats;
	std::map<int, Stats> always_gm;

	// Current stats
	int my_team_num = -1;

	typedef struct s_current {
		int tier = 0;
		int playlist = 0;
		bool ranked = false;
		std::string rank = "norank";
		std::string division = "nodiv";
		std::string preview_rank = "norank";
		std::string preview_division = "nodiv";
		int rank_number = 0;
		int division_number = 0;
		int preview_rank_number = 0;
		int preview_division_number = 0;

		Stats stats = {};
	} t_current;

	t_current current;
	std::string last_rank = "norank";
	std::string last_division = "nodiv";

	// Rank & Division
	int rank_nb = 23;
	std::shared_ptr<ImageWrapper> casual;
	std::vector<std::string> roman_numbers = { "", "I", "II", "III", "IV", "V" };

	typedef struct s_ranks {
		std::string name;
		std::shared_ptr<ImageWrapper> image;
	} t_ranks;

	t_ranks rank[23] = {
		{"Unranked", nullptr},
		{"Bronze_I", nullptr},
		{"Bronze_II", nullptr},
		{"Bronze_III", nullptr},
		{"Silver_I", nullptr},
		{"Silver_II", nullptr},
		{"Silver_III", nullptr},
		{"Gold_I", nullptr},
		{"Gold_II", nullptr},
		{"Gold_III", nullptr},
		{"Platinum_I", nullptr},
		{"Platinum_II", nullptr},
		{"Platinum_III", nullptr},
		{"Diamond_I", nullptr},
		{"Diamond_II", nullptr},
		{"Diamond_III", nullptr},
		{"Champion_I", nullptr},
		{"Champion_II", nullptr},
		{"Champion_III", nullptr},
		{"Grand_Champion_I", nullptr},
		{"Grand_Champion_II", nullptr},
		{"Grand_Champion_III", nullptr},
		{"Supersonic_Legend", nullptr},
	};

	const std::map<int, std::string> playlist_name = {
		{1, "Duel"},
		{2, "Doubles"},
		{3, "Standard"},
		{4, "Chaos"},

		{6, "Private Match"},
		{7, "Season"},
		{8, "Offline Splitscreen"},
		{9, "Training"},

		{10, "Ranked Duel"},
		{11, "Ranked Doubles"},
		{12, "Ranked Solo Standard"},
		{13, "Ranked Standard"},

		{15, "Casual SnowDay"},
		{16, "Experimental"},
		{17, "Casual Hoops"},
		{18, "Casual Rumble"},

		{19, "Workshop"},
		{20, "UGCTrainingEditor"},
		{21, "UGCTraining"},
		{22, "Custom Tournament"},
		{23, "Casual Dropshot"},
		{24, "Local"},
		{26, "FaceIt"},

		{27, "Ranked Hoops"},
		{28, "Ranked Rumble"},
		{29, "Ranked Dropshot"},
		{30, "Ranked SnowDay"},

		{31, "Ghost Hunt"},
		{32, "Beachball"},
		{33, "Spike Rush"},
		{34, "Season Tournament"},
		{35, "Rocket Labs"},
		{37, "Dropshot Rumble"},
		{38, "Heatseeker"},
		{41, "Boomer Ball"},
		{43, "Heatseeker Doubles"},
		{44, "Winter Breakaway"},
		{46, "Gridiron"},
		{47, "Super Cube"},
		{48, "Tactical Rumble"},
		{49, "Spring Loaded"},
		{54, "Knockout"}
	};

	// PluginWindow
	int windows_count = -1;
	bool mouse_state = false;
	bool escape_state = false;
	bool plugin_open = false;
	bool settings_open = false;
	std::string menu_name = "rocketstats";
	std::string menu_title = "RocketStats";
	std::string menu_version = "";

	void RenderIcon();
	void RenderOverlay();
	void RenderSettings();

	virtual void Render() override;
	virtual std::string GetMenuName() override;
	virtual std::string GetMenuTitle() override;
	virtual void SetImGuiContext(uintptr_t ctx) override;
	virtual bool ShouldBlockInput() override;
	virtual bool IsActiveOverlay() override;
	virtual void OnOpen() override;
	virtual void OnClose() override;

public:
	int rs_mode = 0;
	int rs_theme = 0;

	bool rs_disp_obs = false;
	bool rs_disp_overlay = true;
	bool rs_enable_inmenu = true;
	bool rs_enable_ingame = true;
	bool rs_enable_inscoreboard = true;
	bool rs_enable_float = false;
	bool rs_preview_rank = false;
	bool rs_roman_numbers = true;

	bool rs_replace_mmr = false;
	bool rs_replace_mmr_cc = false;
	bool rs_replace_mmrc = false;
	bool rs_replace_mmrc_cc = false;
	bool rs_replace_mmrcc = false;
	bool rs_replace_mmrcc_c = false;

	bool rs_in_file = true;
	bool rs_select_all_file = true;
	bool rs_file_games = true;
	bool rs_file_gm = true;
	bool rs_file_rank = true;
	bool rs_file_div = true;
	bool rs_file_mmr = true;
	bool rs_file_mmrc = true;
	bool rs_file_mmrcc = true;
	bool rs_file_win = true;
	bool rs_file_loss = true;
	bool rs_file_streak = true;
	bool rs_file_winratio = true;
	bool rs_file_winpercentage = true;
	bool rs_file_demo = true;
	bool rs_file_demom = true;
	bool rs_file_democ = true;
	bool rs_file_death = true;
	bool rs_file_deathm = true;
	bool rs_file_deathc = true;
	bool rs_file_shots = true;
	bool rs_file_miscs = true;
	bool rs_file_assists = true;
	bool rs_file_goals = true;
	bool rs_file_saves = true;
	bool rs_file_dropshot = true;
	bool rs_file_knockout = true;
	bool rs_file_boost = true;

	bool rs_select_all_hide = true;
	bool rs_hide_games = false;
	bool rs_hide_gm = false;
	bool rs_hide_rank = false;
	bool rs_hide_div = false;
	bool rs_hide_mmr = false;
	bool rs_hide_mmrc = false;
	bool rs_hide_mmrcc = false;
	bool rs_hide_win = false;
	bool rs_hide_loss = false;
	bool rs_hide_streak = false;
	bool rs_hide_winratio = false;
	bool rs_hide_winpercentage = false;
	bool rs_hide_demo = false;
	bool rs_hide_demom = false;
	bool rs_hide_democ = false;
	bool rs_hide_death = false;
	bool rs_hide_deathm = false;
	bool rs_hide_deathc = false;
	bool rs_hide_shots = false;
	bool rs_hide_miscs = false;
	bool rs_hide_assists = false;
	bool rs_hide_goals = false;
	bool rs_hide_saves = false;
	bool rs_hide_dropshot = false;
	bool rs_hide_knockout = false;

	float rs_x = 0.7f;
	float rs_y = 0.575f;
	float rs_scale = 1.f;
	bool rs_rotate_enabled = false;
	float rs_rotate = 0.f;
	float rs_crotate = 0.f;
	float rs_opacity = 1.f;

	bool rs_x_edit = false;
	bool rs_y_edit = false;
	bool rs_scale_edit = false;
	bool rs_rotate_edit = false;
	bool rs_opacity_edit = false;

	// Utils
	Stats GetStats();
	std::string GetRank(int tierID);
	std::string GetRankName(int tierID, int& number);
	std::string GetPlaylistName(int playlistID);
	std::string GetRoman(int number);
	std::string AddRoman(std::string str, int number);
	void LogImageLoadStatus(bool status, std::string imageName);
	std::shared_ptr<ImageWrapper> LoadImg(const std::string& _filename);
	std::shared_ptr<ImageWrapper> LoadImg(fs::path& _path);
	void LoadImgs();
	bool GetCVar(const char* name, int& value);
	bool GetCVar(const char* name, bool& value);
	bool GetCVar(const char* name, float& value);
	bool SetCVar(const char* name, int& value, bool save = false);
	bool SetCVar(const char* name, bool& value, bool save = false);
	bool SetCVar(const char* name, float& value, bool save = false);
	void CloseWelcome();
	bool RecoveryOldVars();

	// PluginLoadRoutines
	virtual void onLoad();
	virtual void onUnload();
	void onInit();
	void SetCustomProtocol();
	void ShowPlugin(std::string eventName);
	void UpdateUIScale(std::string eventName);
	void TogglePlugin(std::string eventName, ToggleFlags mode = ToggleFlags_Toggle);
	void ToggleSettings(std::string eventName, ToggleFlags mode = ToggleFlags_Toggle);

	// GameManagement
	void GameStart(std::string eventName);
	void GameEnd(std::string eventName);
	void GameDestroyed(std::string eventName);
	int GetGameTime();
	TeamWrapper GetTeam(bool opposing);
	ImColor GetTeamColor(TeamWrapper team);

	// StatsManagement
	bool isPrimaryPlayer(PriWrapper pri);
	void onStatEvent(ServerWrapper caller, void* args);
	void onStatTickerMessage(ServerWrapper caller, void* args);
	void onGoalScore(std::string eventName);
	void InitRank();
	void MajRank(bool isRanked, float _currentMMR, SkillRank playerRank);
	void UpdateMMR(UniqueIDWrapper id);
	void InitStats();
	void SessionStats();
	void ResetStats();
	void ResetBasicStats();

	// BoostManagement
	void OnBoostStart(std::string eventName);
	void OnBoostEnd(std::string eventName);
	int GetBoostAmount();
	//void StopBoost();

	// OverlayManagement
	void LoadThemes();
	bool ChangeTheme(int idx);
	void SetTheme(std::string name);
	void SetRefresh(unsigned char value);
	void RefreshFiles(std::string old, CVarWrapper now);
	void RefreshTheme(std::string old, CVarWrapper now);
	void RefreshVars();
	Element CalculateElement(json& element, Options& options, bool& check);
	void RenderElement(ImDrawList* drawlist, Element& element);

	// LangManagement
	void ChangeLang(int id = IDB_LANG_INT);
	std::string GetLang(LangStringId id);

	// FileManagement
	std::string GetPath(std::string _path = "", bool root = false);
	bool ExistsPath(std::string _filename, bool root = false);
	bool RemoveFile(std::string _filename, bool root = false);
	std::string ReadFile(std::string _filename, bool root = false);
	json ReadJSON(std::string _filename, bool root = false);
	void WriteInFile(std::string _fileName, std::string _value, bool root = false);
	bool WriteResInFile(std::string _filename, int id, const char* type, bool root = false);
	void MigrateFolder();
	void MigrateRemove();
	void UpdateFiles(bool force = false);
	void ResetFiles();
	bool ReadConfig();
	void WriteConfig();

	// VarManagement
	/// Base
	std::string VarGames(bool write = false, bool force = false, bool default_value = false);
	std::string VarGameMode(bool write = false, bool force = false, bool default_value = false);
	std::string VarRank(bool write = false, bool force = false, bool default_value = false, int* number = nullptr);
	std::string SubVarRankName(std::string value, int number, bool default_value = false);
	std::string SubVarRankNumber(std::string value, int number, bool default_value = false);
	std::string VarDiv(bool write = false, bool force = false, bool default_value = false, int* number = nullptr);
	std::string SubVarDivName(std::string value, int number, bool default_value = false);
	std::string SubVarDivNumber(std::string value, int number, bool default_value = false);
	std::string VarMMR(bool write = false, bool force = false, bool default_value = false);
	std::string VarMMRChange(bool write = false, bool force = false, bool default_value = false);
	std::string VarMMRCumulChange(bool write = false, bool force = false, bool default_value = false);
	std::string VarWin(bool write = false, bool force = false, bool default_value = false);
	std::string VarLoss(bool write = false, bool force = false, bool default_value = false);
	std::string VarStreak(bool write = false, bool force = false, bool default_value = false);
	std::string VarWinRatio(bool write = false, bool force = false, bool default_value = false);
	std::string VarWinPercentage(bool write = false, bool force = false, bool default_value = false);
	std::string VarDemolitions(bool write = false, bool force = false, bool default_value = false);
	std::string VarDemolitionsMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarDemolitionsCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarDeath(bool write = false, bool force = false, bool default_value = false);
	std::string VarDeathMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarDeathCumul(bool write = false, bool force = false, bool default_value = false);

	/// Shots
	void AllShots(bool force = false, bool default_value = false);
	void AllShotsCenter(bool force = false, bool default_value = false);
	void AllShotsClear(bool force = false, bool default_value = false);
	void AllShotsFirstTouch(bool force = false, bool default_value = false);
	void AllShotsShotOnGoal(bool force = false, bool default_value = false);
	void AllShotsAerialHit(bool force = false, bool default_value = false);
	void AllShotsBicycleHit(bool force = false, bool default_value = false);

	std::string VarShotsCenter(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsClear(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsFirstTouch(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsShotOnGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsAerialHit(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsBicycleHit(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsTeamShotOnGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsTeamBicycleHit(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsTotalShotOnGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsTotalBicycleHit(bool write = false, bool force = false, bool default_value = false);

	std::string VarShotsCenterMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsClearMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsFirstTouchMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsShotOnGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsAerialHitMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsBicycleHitMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsTeamShotOnGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsTeamBicycleHitMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsTotalShotOnGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsTotalBicycleHitMatch(bool write = false, bool force = false, bool default_value = false);

	std::string VarShotsCenterCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsClearCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsFirstTouchCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsShotOnGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsAerialHitCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsBicycleHitCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsTeamShotOnGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsTeamBicycleHitCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsTotalShotOnGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarShotsTotalBicycleHitCumul(bool write = false, bool force = false, bool default_value = false);

	/// Miscs
	void AllMiscs(bool force = false, bool default_value = false);
	void AllMiscsHatTrick(bool force = false, bool default_value = false);
	void AllMiscsLowFive(bool force = false, bool default_value = false);
	void AllMiscsHighFive(bool force = false, bool default_value = false);
	void AllMiscsMVP(bool force = false, bool default_value = false);

	std::string VarMiscsHatTrick(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsLowFive(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsHighFive(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsMVP(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTeamHatTrick(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTeamLowFive(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTeamHighFive(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTeamMVP(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTotalHatTrick(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTotalLowFive(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTotalHighFive(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTotalMVP(bool write = false, bool force = false, bool default_value = false);

	std::string VarMiscsHatTrickMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsLowFiveMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsHighFiveMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsMVPMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTeamHatTrickMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTeamLowFiveMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTeamHighFiveMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTeamMVPMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTotalHatTrickMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTotalLowFiveMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTotalHighFiveMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTotalMVPMatch(bool write = false, bool force = false, bool default_value = false);

	std::string VarMiscsHatTrickCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsLowFiveCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsHighFiveCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsMVPCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTeamHatTrickCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTeamLowFiveCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTeamHighFiveCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTeamMVPCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTotalHatTrickCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTotalLowFiveCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTotalHighFiveCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarMiscsTotalMVPCumul(bool write = false, bool force = false, bool default_value = false);

	/// Assists
	void AllAssists(bool force = false, bool default_value = false);
	void AllAssistsAssist(bool force = false, bool default_value = false);
	void AllAssistsPlaymaker(bool force = false, bool default_value = false);

	std::string VarAssistsAssist(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsPlaymaker(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsTeamAssist(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsTeamPlaymaker(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsTotalAssist(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsTotalPlaymaker(bool write = false, bool force = false, bool default_value = false);

	std::string VarAssistsAssistMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsPlaymakerMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsTeamAssistMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsTeamPlaymakerMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsTotalAssistMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsTotalPlaymakerMatch(bool write = false, bool force = false, bool default_value = false);

	std::string VarAssistsAssistCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsPlaymakerCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsTeamAssistCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsTeamPlaymakerCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsTotalAssistCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarAssistsTotalPlaymakerCumul(bool write = false, bool force = false, bool default_value = false);

	/// Goals
	void AllGoals(bool force = false, bool default_value = false);
	void AllGoalsGoal(bool force = false, bool default_value = false);
	void AllGoalsOwnGoal(bool force = false, bool default_value = false);
	void AllGoalsAerialGoal(bool force = false, bool default_value = false);
	void AllGoalsBackwardsGoal(bool force = false, bool default_value = false);
	void AllGoalsBicycleGoal(bool force = false, bool default_value = false);
	void AllGoalsLongGoal(bool force = false, bool default_value = false);
	void AllGoalsTurtleGoal(bool force = false, bool default_value = false);
	void AllGoalsOvertimeGoal(bool force = false, bool default_value = false);
	void AllGoalsHoopsSwishGoal(bool force = false, bool default_value = false);
	void AllGoalsPoolShot(bool force = false, bool default_value = false);

	std::string VarGoalsGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsOwnGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsAerialGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsBackwardsGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsBicycleGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsLongGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTurtleGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsOvertimeGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsHoopsSwishGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsPoolShot(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamAerialGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamBackwardsGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamBicycleGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamLongGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamTurtleGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamOvertimeGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamHoopsSwishGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamPoolShot(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalAerialGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalBackwardsGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalBicycleGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalLongGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalTurtleGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalOvertimeGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalHoopsSwishGoal(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalPoolShot(bool write = false, bool force = false, bool default_value = false);

	std::string VarGoalsGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsOwnGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsAerialGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsBackwardsGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsBicycleGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsLongGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTurtleGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsOvertimeGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsHoopsSwishGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsPoolShotMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamAerialGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamBackwardsGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamBicycleGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamLongGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamTurtleGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamOvertimeGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamHoopsSwishGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamPoolShotMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalAerialGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalBackwardsGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalBicycleGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalLongGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalTurtleGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalOvertimeGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalHoopsSwishGoalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalPoolShotMatch(bool write = false, bool force = false, bool default_value = false);

	std::string VarGoalsGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsOwnGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsAerialGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsBackwardsGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsBicycleGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsLongGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTurtleGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsOvertimeGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsHoopsSwishGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsPoolShotCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamAerialGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamBackwardsGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamBicycleGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamLongGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamTurtleGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamOvertimeGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamHoopsSwishGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTeamPoolShotCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalAerialGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalBackwardsGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalBicycleGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalLongGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalTurtleGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalOvertimeGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalHoopsSwishGoalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarGoalsTotalPoolShotCumul(bool write = false, bool force = false, bool default_value = false);

	/// Saves
	void AllSaves(bool force = false, bool default_value = false);
	void AllSavesSave(bool force = false, bool default_value = false);
	void AllSavesEpicSave(bool force = false, bool default_value = false);
	void AllSavesSavior(bool force = false, bool default_value = false);

	std::string VarSavesSave(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesEpicSave(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesSavior(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTeamSave(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTeamEpicSave(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTeamSavior(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTotalSave(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTotalEpicSave(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTotalSavior(bool write = false, bool force = false, bool default_value = false);

	std::string VarSavesSaveMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesEpicSaveMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesSaviorMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTeamSaveMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTeamEpicSaveMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTeamSaviorMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTotalSaveMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTotalEpicSaveMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTotalSaviorMatch(bool write = false, bool force = false, bool default_value = false);

	std::string VarSavesSaveCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesEpicSaveCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesSaviorCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTeamSaveCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTeamEpicSaveCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTeamSaviorCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTotalSaveCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTotalEpicSaveCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarSavesTotalSaviorCumul(bool write = false, bool force = false, bool default_value = false);

	/// Dropshot
	void AllDropshot(bool force = false, bool default_value = false);
	void AllDropshotBreakoutDamage(bool force = false, bool default_value = false);
	void AllDropshotBreakoutDamageLarge(bool force = false, bool default_value = false);

	std::string VarDropshotBreakoutDamage(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotBreakoutDamageLarge(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotTeamBreakoutDamage(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotTeamBreakoutDamageLarge(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotTotalBreakoutDamage(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotTotalBreakoutDamageLarge(bool write = false, bool force = false, bool default_value = false);

	std::string VarDropshotBreakoutDamageMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotBreakoutDamageLargeMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotTeamBreakoutDamageMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotTeamBreakoutDamageLargeMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotTotalBreakoutDamageMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotTotalBreakoutDamageLargeMatch(bool write = false, bool force = false, bool default_value = false);

	std::string VarDropshotBreakoutDamageCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotBreakoutDamageLargeCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotTeamBreakoutDamageCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotTeamBreakoutDamageLargeCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotTotalBreakoutDamageCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarDropshotTotalBreakoutDamageLargeCumul(bool write = false, bool force = false, bool default_value = false);

	/// Knockout
	void AllKnockout(bool force = false, bool default_value = false);
	void AllKnockoutBase(bool force = false, bool default_value = false);
	void AllKnockoutDeath(bool force = false, bool default_value = false);
	void AllKnockoutThrown(bool force = false, bool default_value = false);
	void AllKnockoutGrabbed(bool force = false, bool default_value = false);
	void AllKnockoutDoubleKO(bool force = false, bool default_value = false);
	void AllKnockoutHeavyHit(bool force = false, bool default_value = false);
	void AllKnockoutHitTaken(bool force = false, bool default_value = false);
	void AllKnockoutLightHit(bool force = false, bool default_value = false);
	void AllKnockoutBlockTaken(bool force = false, bool default_value = false);
	void AllKnockoutHeavyBlock(bool force = false, bool default_value = false);

	std::string VarKnockout(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutDeath(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutThrown(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutGrabbed(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutDoubleKO(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutHeavyHit(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutHitTaken(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutLightHit(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutBlockTaken(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutHeavyBlock(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeam(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamDeath(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamDoubleKO(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamHeavyHit(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamHeavyBlock(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotal(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalDeath(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalDoubleKO(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalHeavyHit(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalHeavyBlock(bool write = false, bool force = false, bool default_value = false);

	std::string VarKnockoutMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutDeathMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutThrownMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutGrabbedMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutDoubleKOMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutHeavyHitMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutHitTakenMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutLightHitMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutBlockTakenMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutHeavyBlockMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamDeathMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamDoubleKOMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamHeavyHitMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamHeavyBlockMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalDeathMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalDoubleKOMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalHeavyHitMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalHeavyBlockMatch(bool write = false, bool force = false, bool default_value = false);

	std::string VarKnockoutCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutDeathCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutThrownCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutGrabbedCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutDoubleKOCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutHeavyHitCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutHitTakenCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutLightHitCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutBlockTakenCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutHeavyBlockCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamDeathCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamDoubleKOCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamHeavyHitCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTeamHeavyBlockCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalDeathCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalDoubleKOCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalHeavyHitCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarKnockoutTotalHeavyBlockCumul(bool write = false, bool force = false, bool default_value = false);

	/// Other
	std::string VarBoost(bool write = false, bool force = false, bool default_value = false, bool enabled = false);
};
