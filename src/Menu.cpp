#include "main.h"
#include "ImFuncs.h"

void UpdateSystemInfo()
{
	sysi->SetUpdateInterval(2000);
	sysi->UpdateInfo();
}

struct Account {
	std::string username;
	std::string password;

	void serialize(std::ofstream& out) const {
		size_t username_length = username.size();
		size_t password_length = password.size();
		out.write(reinterpret_cast<const char*>(&username_length), sizeof(username_length));
		out.write(username.c_str(), username_length);
		out.write(reinterpret_cast<const char*>(&password_length), sizeof(password_length));
		out.write(password.c_str(), password_length);
	}

	void deserialize(std::ifstream& in) {
		size_t username_length;
		size_t password_length;
		in.read(reinterpret_cast<char*>(&username_length), sizeof(username_length));
		username.resize(username_length);
		in.read(&username[0], username_length);
		in.read(reinterpret_cast<char*>(&password_length), sizeof(password_length));
		password.resize(password_length);
		in.read(&password[0], password_length);
	}
};

class AccountManager {
private:
	std::vector<Account> accounts;
	const std::string filename = "accounts.bin";
	std::string loggedInUser;

public:
	void registerAccount(const std::string& username, const std::string& password) {
		Account newAccount{ username, password };
		accounts.push_back(newAccount);
		saveAccounts();
	}

	void saveAccounts() {
		std::ofstream out(filename, std::ios::binary);
		for (const auto& account : accounts) {
			account.serialize(out);
		}
	}

	void loadAccounts() {
		std::ifstream in(filename, std::ios::binary);
		while (in.peek() != EOF) {
			Account account;
			account.deserialize(in);
			accounts.push_back(account);
		}
	}

	bool authenticate(const std::string& username, const std::string& password) {
		for (const auto& account : accounts) {
			if (account.username == username && account.password == password) {
				loggedInUser = username;
				return true;
			}
		}
		return false;
	}

	void logout() {
		loggedInUser.clear();
	}

	bool isLoggedIn() const {
		return !loggedInUser.empty();
	}

	std::string getLoggedInUser() const {
		return loggedInUser;
	}

	int GetCountAccounts() const {		
		return accounts.size();
	}
};

AccountManager am;
static bool MenuSysSecure = false;
void AuthMenu()
{
	am.loadAccounts();
	static bool MenuCreateUser = false;
	static bool MenuAuthUser = false;
	
	ImGuiWindowFlags window_flags_about = 0;
	window_flags_about |= ImGuiWindowFlags_NoResize;
	window_flags_about |= ImGuiWindowFlags_NoCollapse;
	window_flags_about |= ImGuiWindowFlags_NoMove;
	
	if (am.isLoggedIn() == false)
	{
		MenuSysSecure = true;
	}
	if (MenuSysSecure == true)
	{
		ImGui::OpenPopup(u8"Система безопасности SkyNet");
	}
		ImGui::SetNextWindowSize(ImVec2(ImGui::GetWindowSize().x - 6, ImGui::GetWindowSize().y - 6));
		if (ImGui::BeginPopupModal(u8"Система безопасности SkyNet", 0, window_flags_about))
		{
			static char username[128] = "";
			static char password[128] = "";
			
				if (am.GetCountAccounts() == 0)
				{
					ImGui::TextWithColors(u8"{FF0000}Добро пожаловать в SkyNet! Пожалуйста, создайте аккаунт!");
				}
				else if (am.GetCountAccounts() > 0)
				{
					ImGui::TextWithColors(u8"{FFFF00}Добро пожаловать в SkyNet! Пожалуйства, авторизуйтесь!");
				}

				ImGui::SetCursorPos(ImVec2(gui::size.x / 2 - 100, gui::size.y / 2 - 80));
				ImGui::PushItemWidth(200); //NOTE: (Push/Pop)ItemWidth is optional
				
				ImGui::InputText("#login", username, IM_ARRAYSIZE(username));
				ImGui::PopItemWidth();

				ImGui::SetCursorPos(ImVec2(gui::size.x / 2 - 100, gui::size.y / 2 - 40));
				ImGui::PushItemWidth(200); //NOTE: (Push/Pop)ItemWidth is optional
				
				ImGui::InputText("#pswd", password, IM_ARRAYSIZE(password));
				ImGui::PopItemWidth();

				ImGui::NewLine();

				if (am.GetCountAccounts() == 0)
				{
					if (pMenu->AddStaticButton(u8"Создать", gui::size.x / 2))
					{
						am.registerAccount(username, password);
						//ImGui::CloseCurrentPopup();
					}
				}
				else if (am.GetCountAccounts() > 0)
				{
					if (pMenu->AddStaticButton(u8"Войти", gui::size.x / 2))
					{
						if (am.authenticate(username, password))
						{
							MenuSysSecure = false;
							ImGui::CloseCurrentPopup();
						}
					}
				}
				

			

			ImGui::SetCursorPos(ImVec2(gui::size.x / 2, gui::size.y / 2));

			if (pMenu->AddStaticButton(u8"Выход"))
			{
				ExitProcess(0);
			}
			ImGui::EndPopup();
		}
				
}

void MyGui::renderImguiMenu(bool* p_open)
{
	funcs_enabler();	
	
	AuthMenu();

	const time_t timer = time(NULL);
	pMenu->AddMenuText(ImFuncs::animateString(ctime(&timer), 20).c_str(), false, ImColorOrange, true);

	auto thw = ThreadWrapper::create();
	thw->beginThread(UpdateSystemInfo);

	if(am.isLoggedIn() == true)
	{
		ImGui::TextWithColors(u8"Вы авторизованы как: %s", am.getLoggedInUser().c_str());
		ImGui::SameLine();
		if (pMenu->AddStaticButton(u8"Выйти"))
		{
			am.logout();
			MenuSysSecure = true;
		};		

	//sysinfotoconsole();						
	
	//ImGui::TextWithColors(u8"%s", ImFuncs::animateString(sysi->GetCPUInfo().c_str(), 5).c_str());

	//sysi->GetDiskInfo();

	ImGui::TextWithColors(u8"%s", ImFuncs::animateString(sysi->GetInternetStatus().c_str(), 15).c_str());		
		ImGui::Separator();
		sn->con.Draw(u8"console");
	}	
	
}

