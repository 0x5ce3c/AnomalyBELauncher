#include "main.h"
#include "ImFuncs.h"

void UpdateSystemInfo()
{
	sysi->SetUpdateInterval(2000);
	sysi->UpdateInfo();
}

void MyGui::renderImguiMenu(bool* p_open)
{
	funcs_enabler();			

	const time_t timer = time(NULL);
	pMenu->AddMenuText(ImFuncs::animateString(ctime(&timer), 20).c_str(), false, ImColorOrange, true);

	//auto thw = ThreadWrapper::create();
	//thw->beginThread(UpdateSystemInfo);


	//sysinfotoconsole();							
	//ImGui::TextWithColors(u8"%s", ImFuncs::animateString(sysi->GetCPUInfo().c_str(), 5).c_str());
	//sysi->GetDiskInfo();

	//ImGui::TextWithColors(u8"%s", ImFuncs::animateString(sysi->GetInternetStatus().c_str(), 15).c_str());		
		//ImGui::Separator();
		sn->con.Draw(u8"console");
	
}

