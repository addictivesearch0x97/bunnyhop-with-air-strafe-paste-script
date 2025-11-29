#include <algorithm>

void AddLineGlow(ImVec2 start,ImVec2 end,ImColor col,float size, int gsize) {
	ImGui::GetBackgroundDrawList()->AddLine(start,end,col,size);
	for(int i = 0; i < gsize; i++) {
		ImGui::GetBackgroundDrawList()->AddLine(start,end,ImColor(col.Value.x,col.Value.y,col.Value.z,col.Value.w * (1.0f / (float)gsize) * (((float)(gsize - i))/(float)gsize)),size + i);
        }
    }
	void XinkyDrawLineGlow(ImVec2 start,ImVec2 end,ImColor col,float size, int gsize) {
        ImGui::GetBackgroundDrawList()->AddLine(start,end,col,size);
        for(int i = 0; i < gsize; i++) {
            ImGui::GetBackgroundDrawList()->AddLine(start,end,ImColor(col.Value.x,col.Value.y,col.Value.z,col.Value.w * (1.0f / (float)gsize) * (((float)(gsize - i))/(float)gsize)),size + i);
        }
    }
	
Vector3 calculate(Vector3 position) {
  auto mainCamera = Camera$$main();
  if (mainCamera) {
   Vector3 vectorFromCamera = position - Transform$$position[Component$$transform[mainCamera]()]();
   float cameraNormDot = Vector3::Dot(Transform$$forward[Component$$transform[mainCamera]](), vectorFromCamera);
   return cameraNormDot <= 0 ? Transform$$position[Component$$transform[mainCamera]()]() + (vectorFromCamera - (Transform$$forward[Component$$transform[mainCamera]]() * cameraNormDot * 1.01)) : position;
  }
 }
 

ImVec2 w2s_i(Vector3 position, bool fixPosition = false) {
  auto mainCamera = Camera$$main();
  if (mainCamera) {
   Vector3 point = Camera$$World2ScreenPoint[mainCamera](fixPosition ? calculate(position) : position);
   return {point.x, ImGui::GetIO().DisplaySize.y - point.y};
  }
 }
 
 ImVec2 w2s_c(Vector3 position, bool check, bool fixPosition = false) {
     auto mainCamera = Camera$$main();
  if (mainCamera) {
   Vector3 point = Camera$$World2ScreenPoint[mainCamera](fixPosition ? calculate(position) : position);
      check = point.z > 0.1f;
      return {point.x, ImGui::GetIO().DisplaySize.y - point.y};
  }
 }

ImVec2 world2screen_i(Vector3 position) {
    auto camera = Camera$$main();   
    if (!camera)
		return {0,0};
		
    Vector3 Camera$$W2SPoint_P = Camera$$W2SPoint(camera, position);  
    return {Camera$$W2SPoint_P.x, glHeight - Camera$$W2SPoint_P.y};
}
void DrawRectFilledGlow(ImVec2 start,ImVec2 end,ImColor col1, ImColor col2, ImColor col3, ImColor col4, int gsize) {
    ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(start,end,col1, col2, col3, col4);
    for(int i = 0; i < gsize; i++) {
        ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(start, end, ImColor(col1.Value.x,col1.Value.y,col1.Value.z,col1.Value.w * (1.0f / (float)gsize) * (((float)(gsize - i))/(float)gsize)), ImColor(col2.Value.x,col2.Value.y,col2.Value.z,col2.Value.w * (1.0f / (float)gsize) * (((float)(gsize - i))/(float)gsize)), ImColor(col3.Value.x,col3.Value.y,col3.Value.z,col3.Value.w * (1.0f / (float)gsize) * (((float)(gsize - i))/(float)gsize)), ImColor(col4.Value.x,col4.Value.y,col4.Value.z,col4.Value.w * (1.0f / (float)gsize) * (((float)(gsize - i))/(float)gsize)));
    }
}


ImVec2 world2screen_c(Vector3 position, bool &checker) {
    auto camera = Camera$$main();   
    if (!camera)
		return {0,0};
		
    Vector3 Camera$$W2SPoint_P = Camera$$W2SPoint(camera, position);
    checker = Camera$$W2SPoint_P.z <= 0;
    return ImVec2(Camera$$W2SPoint_P.x, glHeight - Camera$$W2SPoint_P.y);
}
Vector3 enemyLocation(void *instance) {
	return Transform$$position[instance]();
}

std::map<string, std::string> weaponIdToFont = {{"M4A4", "Q"}};

int get_weaponid(void *instance) {
    auto currentWeapon = *(void **)((uintptr_t)instance + 0x48);
    if (currentWeapon) {
        auto weaponId = *(int *)((uintptr_t)currentWeapon + 0x8);
        }
    }
	

void line_glow(ImVec2 start, ImVec2 end, ImColor color, float thickness, int glowSize) {
		ImGui::GetBackgroundDrawList()->AddLine(start, end, color, thickness);
		for (int i = 0; i < glowSize; i++) {
			ImGui::GetBackgroundDrawList()->AddLine(start, end, ImColor(color.Value.x, color.Value.y, color.Value.z, color.Value.w * (1.0f / (float)glowSize) * (((float)(glowSize - i)) / (float)glowSize)), thickness + i);
		}
	}

void add_text(ImVec2 position, ImColor color, const char *text, int size, string type = "") {
		float stroke = 0.95;
		
		if (type == OBFUSCATE_BNM("shadow")) {
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x + stroke), (int)(position.y + stroke)), ImColor(0, 0, 0), text);
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x), (int)(position.y)), ImColor(0, 0, 0, 255), text);
		}
		
		if (type == OBFUSCATE_BNM("outline")) {
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x - stroke), (int)(position.y + stroke)), ImColor(0, 0, 0), text);
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x - stroke), (int)(position.y - stroke)), ImColor(0, 0, 0), text);
   	 		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x + stroke), (int)(position.y + stroke)), ImColor(0, 0, 0), text);
    		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x + stroke), (int)(position.y - stroke)), ImColor(0, 0, 0), text);
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x), (int)(position.y + stroke)), ImColor(0, 0, 0), text);
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x), (int)(position.y - stroke)), ImColor(0, 0, 0), text);
   	 		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x + stroke), (int)(position.y)), ImColor(0, 0, 0), text);
    		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x + stroke), (int)(position.y)), ImColor(0, 0, 0), text);
		}
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)position.x, (int)position.y), color, text);
	}
		
inline float lerp(float a, float b, float f) {
    return clamp<float>(a + f * (b - a),a > b ? b : a,a > b ? a : b);
}

inline void arc_line(float x, float y, float radius, float min_angle, float max_angle, ImColor col, float thickness) {
    ImGui::GetBackgroundDrawList()->PathArcTo(ImVec2 (x, y), radius, Deg2Rad * min_angle, Deg2Rad * max_angle, 32);
    ImGui::GetBackgroundDrawList()->PathStroke(col, false, thickness);
}

inline void arc(float x, float y, float radius, float min_angle, float max_angle, ImColor col, float thickness) {
    ImGui::GetBackgroundDrawList()->PathArcTo(ImVec2 (x, y), radius, Deg2Rad * min_angle, Deg2Rad * max_angle, 32);
    ImGui::GetBackgroundDrawList()->PathStroke(col, false, thickness);
}

void arc_triangle(float x, float y, float radius, float min_angle, float max_angle, ImColor col, float thickness) {
    float half_angle = (max_angle - min_angle) / 2.0f;
    float center_angle = min_angle + half_angle;

    ImVec2 center(x + cos(Deg2Rad * center_angle) * radius, y + sin(Deg2Rad * center_angle) * radius);
    float triangle_side = sin(Deg2Rad * half_angle) * radius * 2.0f;

    ImVec2 p1(center.x + cos(Deg2Rad * (min_angle + half_angle - 90.0f)) * triangle_side / 2.0f,
              center.y + sin(Deg2Rad * (min_angle + half_angle - 90.0f)) * triangle_side / 2.0f);
    ImVec2 p2(center.x + cos(Deg2Rad * (min_angle + half_angle)) * triangle_side / 2.0f,
              center.y + sin(Deg2Rad * (min_angle + half_angle)) * triangle_side / 2.0f);
    ImVec2 p3(center.x + cos(Deg2Rad * (min_angle + half_angle + 90.0f)) * triangle_side / 2.0f,
              center.y + sin(Deg2Rad * (min_angle + half_angle + 90.0f)) * triangle_side / 2.0f);

    ImGui::GetBackgroundDrawList()->AddTriangleFilled(p1, p2, p3, col);
    ImGui::GetBackgroundDrawList()->AddTriangle(p1, p2, p3, ImColor(0,0,0,255), thickness);
}

void DrawLineGlow(ImVec2 start,ImVec2 end,ImColor col,float size, int gsize) {
    ImGui::GetBackgroundDrawList()->AddLine(start,end,col,size);
    for(int i = 0; i < gsize; i++) {
        ImGui::GetBackgroundDrawList()->AddLine(start,end,ImColor(col.Value.x,col.Value.y,col.Value.z,col.Value.w * (1.0f / (float)gsize) * (((float)(gsize - i))/(float)gsize)),size + i);
    }
}

void DrawRectGlow(ImVec2 start, ImVec2 end, ImVec4 col,int gsize) {
    for (int i = 0; i < gsize; i++) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(start.x - i, start.y - i), ImVec2(end.x + i, end.y + i), ImGui::GetColorU32(ImVec4(col.x, col.y, col.z, col.w * (1.0f / (float)gsize) * (((float)(gsize - i)) / (float)gsize))));
    }
    ImGui::GetBackgroundDrawList()->AddRectFilled(start, end, ImGui::GetColorU32(col));
}

void TextOutline(ImColor color, const char *text, ImVec2 position, float size, float width) {
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2(position.x, position.y + width), ImColor(0, 0, 0, 255), text);
    ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2(position.x + width, position.y), ImColor(0, 0, 0, 255), text);
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, position, color, text);
	}
	
/*void TextOutline1(ImColor color, const char *text, ImVec2 position, float size, float width) {
	float stroke = 1.0;
    //ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2(position.x, position.y - width), ImColor(0, 0, 0, 255), text);
    ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x - stroke), (int)(position.y + stroke)), ImColor(0, 0, 0), text);
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x - stroke), (int)(position.y - stroke)), ImColor(0, 0, 0), text);
   	 		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x + stroke), (int)(position.y + stroke)), ImColor(0, 0, 0), text);
    		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x + stroke), (int)(position.y - stroke)), ImColor(0, 0, 0), text);
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x), (int)(position.y + stroke)), ImColor(0, 0, 0), text);
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x), (int)(position.y - stroke)), ImColor(0, 0, 0), text);
   	 		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x + stroke), (int)(position.y)), ImColor(0, 0, 0), text);
    		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((int)(position.x + stroke), (int)(position.y)), ImColor(0, 0, 0), text);
    ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, position, color, text);
    }*/
	
void TextOutline1(ImColor color, const char *text, ImVec2 position, float size, float width)
{
    ImDrawList* dl   = ImGui::GetBackgroundDrawList();
    ImFont*     font = ImGui::GetFont();

    const float r = 1.0f;                       // всегда 1 пиксель
    ImColor outline_col = ImColor(0, 0, 0, 255);

    // 8 направлений вокруг текста
    static const ImVec2 offsets[8] =
    {
        ImVec2(-r, -r),
        ImVec2( 0, -r),
        ImVec2( r, -r),
        ImVec2(-r,  0),
        ImVec2( r,  0),
        ImVec2(-r,  r),
        ImVec2( 0,  r),
        ImVec2( r,  r)
    };

    for (ImVec2 o : offsets)
        dl->AddText(font, size, ImVec2(position.x + o.x, position.y + o.y),
                    outline_col, text);

    // основной текст
    dl->AddText(font, size, position, color, text);
}

void DrawCircleGlow(ImVec2 center, float radius, ImColor col, int segments, int size, int gsize) {
    ImGui::GetBackgroundDrawList()->AddCircle(center, radius, col, segments, size);
    for(int i = 0; i < gsize; i++) {
        ImGui::GetBackgroundDrawList()->AddCircle(center,radius, ImColor(col.Value.x,col.Value.y,col.Value.z,col.Value.w * (1.0f / (float)gsize) * (((float)(gsize - i))/(float)gsize)), segments, size + i);
    }
}

void circle_glow(ImVec2 position, float radius, ImColor color, int segments, int thickness, int glowSize) {
		ImGui::GetBackgroundDrawList()->AddCircle(position, radius, color, segments, glowSize);
    	for (int i = 0; i < glowSize; i++) {
        	ImGui::GetBackgroundDrawList()->AddCircle(position, radius, ImColor(color.Value.x, color.Value.y, color.Value.z, color.Value.w * (1.0f / (float)glowSize) * (((float)(glowSize - i)) / (float)glowSize)), segments, thickness + i);
   	 	}
	}
	
	
float BOG_TO_GRD(float BOG) {
 return (180 / M_PI) * BOG;
}

float GRD_TO_BOG(float GRD) {
 return (M_PI / 180) * GRD;
}
static int xinky = 0;
int rm = 255;
int gm = 0;
int bm = 0;
int mm = 0;
void DrawSwastonCrosshair(int size, int Drehungswinkell) {
    auto isFrames = ImGui::GetFrameCount();

    static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;
    xinky++;
    if (xinky >= 0)
        xinky = 0;
    ImVec4 isRGB = ImVec4(isRed, isGreen, isBlue, 1.0f);
    auto MiddleX = glWidth / 2;
    auto MiddleY = glHeight / 2;
    int a = (int) (glHeight / 2 / (61 - size));
    float gamma = atan(a / a);

    int i = 0;
    while (i < 4) {
        std::vector<int> p;
        p.push_back(a * sin(GRD_TO_BOG(xinky + (i * 90))));
        p.push_back(a * cos(GRD_TO_BOG(xinky + (i * 90))));
        p.push_back(
                (a / cos(gamma)) * sin(GRD_TO_BOG(xinky + (i * 90) + BOG_TO_GRD(gamma))));
        p.push_back(
                (a / cos(gamma)) * cos(GRD_TO_BOG(xinky + (i * 90) + BOG_TO_GRD(gamma))));

        ImGui::GetBackgroundDrawList()->AddLine({MiddleX, MiddleY},
                                                {MiddleX + p[0], MiddleY - p[1]},
                                                GetColorU32(*(ImVec4 *)swcol));
        ImGui::GetBackgroundDrawList()->AddLine({MiddleX + p[0], MiddleY - p[1]},
                                                {MiddleX + p[2], MiddleY - p[3]},
                                                GetColorU32(*(ImVec4 *)swcol));

        i++;
    }
}


void MovementHistory() {
	/*if (!PlayerTracerEnable)
		return;
        
    static vector<Vector3> tracer_data;
	tracer_data.push_back(myposition);
	if (tracer_data.size() > 100) {
		tracer_data.erase(tracer_data.begin());
	}
		
	for (int i = 0; i != tracer_data.size(); i++) {
		if (i < 3 || tracer_data[i] == tracer_data[i - 1])
			continue;
							
		auto position_tracer1 = Camera$$World2ScreenPoint[Camera$$main()](tracer_data[i]);
		auto position_tracer2 = Camera$$World2ScreenPoint[Camera$$main()](tracer_data[i - 1]);
		position_tracer1.y = glHeight - position_tracer1.y;
		position_tracer2.y = glHeight - position_tracer2.y;
		if (position_tracer1.z <= 0 || position_tracer2.z <= 0)
			continue;
			
		if (PlayerTracerDefualt) {
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(position_tracer1.x, position_tracer1.y), ImVec2(position_tracer2.x, position_tracer2.y), ImGui::GetColorU32(*(ImVec4 *)PlayerTracerColor));
			}
			
		if (PlayerTracerGlow) {
			AddLineGlow(ImVec2(position_tracer1.x, position_tracer1.y), ImVec2(position_tracer2.x, position_tracer2.y), ImGui::GetColorU32(*(ImVec4 *)PlayerTracerColor), 2.5f, 35);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(position_tracer1.x, position_tracer1.y), ImVec2(position_tracer2.x, position_tracer2.y), ImGui::GetColorU32(*(ImVec4 *)PlayerTracerColor));
		}
			
		if (PlayerTracerRainbow) {
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(position_tracer1.x, position_tracer1.y), ImVec2(position_tracer2.x, position_tracer2.y), ImColor::HSV((float) i / 100, 1.f, 1.f));
			}
			
		if (PlayerTracerRainbowGlow) {
			AddLineGlow(ImVec2(position_tracer1.x, position_tracer1.y), ImVec2(position_tracer2.x, position_tracer2.y), ImColor::HSV((float) i / 100, 1.f, 1.f), 2.5f, 35);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(position_tracer1.x, position_tracer1.y), ImVec2(position_tracer2.x, position_tracer2.y), ImColor::HSV((float) i / 100, 1.f, 1.f));
		}
	}
}*/
if (!PlayerTracerEnable)
		return;
	static vector<Vector3> movementHistory;
		
		movementHistory.push_back(myposition);
		if (movementHistory.size() > 450)
		{
			movementHistory.erase(movementHistory.begin());
		}
		
		for (int i = 0; i != movementHistory.size(); i++)
		{
			if (i < 3 || movementHistory[i] == movementHistory[i-1])
				continue;
				
			auto position_tracer1 = Camera$$World2ScreenPoint[Camera$$main()](movementHistory[i]);
			auto position_tracer2 = Camera$$World2ScreenPoint[Camera$$main()](movementHistory[i - 1]);
			position_tracer1.y = glHeight - position_tracer1.y;
			position_tracer2.y = glHeight - position_tracer2.y;
			if (position_tracer1.z <= 0 || position_tracer2.z <= 0)
				continue;
		if (PlayerTracerDefualt) {
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(position_tracer1.x, position_tracer1.y), ImVec2(position_tracer2.x, position_tracer2.y), ImGui::GetColorU32(*(ImVec4 *)PlayerTracerColor));
			}
		}
	}
	
	
#define IMGUI_DEFINE_MATH_OPERATORS
#include <math.h>
#include <cmath>
void RenderESP() {
	
	
	
	
	if (!EspEnable)
		return;
	
	auto mainCamera = Camera$$main();
    if (!mainCamera)
        return;

    if(SilentAimFov) {
    if (drawAimFov) {
		//ImColor(SilentAimFovColor[0], SilentAimFovColor[1], SilentAimFovColor[2]);
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(glWidth / 2, glHeight / 2), SilentAimFovRadius, ImColor(SilentAimFovColor[0], SilentAimFovColor[1], SilentAimFovColor[2]), segments, 3.0f);
		if(fillAimFov) {
			ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(glWidth / 2, glHeight / 2), SilentAimFovRadius,  ImGui::ColorConvertFloat4ToU32(ImVec4(SilentAimFovColor[0], SilentAimFovColor[1], SilentAimFovColor[2], float(fillFovAlpha) / 255.f)), segments);
		}
		if(aimFovOutline) {
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(glWidth / 2, glHeight / 2), SilentAimFovRadius , ImColor(0,0,0), segments, 6.0f);
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(glWidth / 2, glHeight / 2), SilentAimFovRadius, ImColor(SilentAimFovColor[0], SilentAimFovColor[1], SilentAimFovColor[2]), segments, 3.0f);
    }
		if(aimFovGlow) {
			DrawCircleGlow(ImVec2(glWidth / 2, glHeight / 2), SilentAimFovRadius, ImColor(SilentAimFovColor[0], SilentAimFovColor[1], SilentAimFovColor[2]), segments, 3.0f, 5);
		}
}
}
	
	
	
	Camera$$clearFlags[Camera$$main()].set(SkyBox ? 2 : 1);
	
	if (SkyBox) {
		Camera$$backgroundColor[Camera$$main()] = Color(SkyBoxColor[0], SkyBoxColor[1], SkyBoxColor[2], SkyBoxColor[3]);
	}
	


    auto cameraTransform = Component$$transform[mainCamera]();
    if (!cameraTransform)
        return;

    auto players = PLH$$player();
    if (!players)
        return;

    for (void *localPlayer : players->toCPPlist()) {
        if (!localPlayer)
            continue;

        auto isLocal = *(bool *)((addr_t)localPlayer + 0x10);
        if (!isLocal)
            continue;

        auto localPlayerTeam = *(int *)((addr_t)localPlayer + 0x1C);

        auto myPlayerPO = *(void **)((addr_t)localPlayer + 0x14);
        if (!myPlayerPO)
            continue;

        auto myTransform = *(monoArray<void *> **)((addr_t)myPlayerPO + 0x7C);
        if (!myTransform)
            continue;
			
		for (void *player : players->toCPPlist()) {
            if (!player || localPlayer == player)
                continue;
						
			//monoArray<void **> *hits = *(monoArray<void **> **)((uint64_t)myPlayerPO + 0x80);

			//bool raycastCheck = Physics$$Raycast;

            auto team = *(int *)((addr_t)player + 0x1C);
            auto health = *(int *)((addr_t)player + 0x34);
			auto armor = *(int *)((addr_t)player + 0x38);


// Рисуем заполненный прямоугольник с использованием ImGui
//ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(rectLeft, rectTop), ImVec2(rectRight, rectBottom), ImColor(255, 255, 255));
			
			
           	if (health <= 0 || (!SingleMode && localPlayerTeam == team))
                continue;
				
            auto playerPO = *(void **)((addr_t)player + 0x14);
            if (!playerPO)
                continue;

            auto transform = *(monoArray<void *> **)((addr_t)playerPO + 0x7C);
            if (!transform)
                continue;
			auto playerTR = *(monoArray<void *> **)((addr_t)playerPO + 0x7C);
                if (!playerTR)
                    continue;
					
			auto enemyPlayerTRHB = *(monoArray<void *> **)((addr_t)playerPO + offsets::PlayerObject$$trhb);
                if (!enemyPlayerTRHB)
                   	 continue;
				
			 auto localPlayerPO = *(void **)((addr_t)localPlayer + offsets::PlayerData$$po);
			if (!localPlayerPO)
				continue;
				
			auto localPlayerTRHB = *(monoArray<void* > **)((addr_t)localPlayerPO + offsets::PlayerObject$$trhb);
			if (!localPlayerTRHB)
				continue;
			
			auto playerPosition = Transform$$position[playerTR]();
			
			auto camera_transform = Component$$transform[Camera$$main()]();
			auto camera_position = Transform$$position[camera_transform]();
			ImVec4 BOX_GRAD = ImVec4(EspBoxGradientColor[0], EspBoxGradientColor[1], EspBoxGradientColor[2], EspBoxGradientColor[3]);
			ImVec4 BOX_GRA1 = ImVec4(255, 255, 255, 0);
			//bool raycast = Physics$$Raycast;
			//auto world_position = Transform$$position[transform]();
			auto world_position = Transform$$position[transform]();
			auto screen_position = Camera$$World2ScreenPoint[Camera$$main()](world_position);
			//auto w2sC = world2screen_c(world_position + Vector3(0, 90.0, 0), checker);
			screen_position.y = glHeight - screen_position.y;
			/*monoArray<void **> *Myp3NK = *(monoArray<void **> **)((addr_t)playerPO + 0x80);
			auto hits = Myp3NK->toCPPlist();
			auto hits->toCPPlist() = *(monoArray<void **> **)((addr_t)playerPO + 0x80);
			*/
			auto pos = Transform$$position[playerTR]();
			auto checker = false;
			auto w2sC = world2screen_c(pos + Vector3(0, 0.9, 0), checker);
			
			Vector3 viewpos = Transform$$position[Component$$transform[Camera$$main()]()]();


                        auto distanceOof = Vector3::Distance(viewpos, pos);

						
				if (OutOfFov) {
					if ((w2sC.x < 0 || w2sC.x > glWidth) || (w2sC.y < 0 || w2sC.y > glHeight)) {
						constexpr int maxpixels = 200;
						int pixels = maxpixels;
						
						if (w2sC.x < 0)
							pixels = std::clamp((int) -w2sC.x, 0, maxpixels);
                                    
						if (w2sC.y < 0)
							pixels = std::clamp((int) -w2sC.y, 0, maxpixels);
							
						if (w2sC.x > glWidth)
							pixels = std::clamp((int) w2sC.x - glWidth, 0, maxpixels);
                                    
						if (w2sC.y > glHeight)
							pixels = std::clamp((int) w2sC.y - glHeight, 0, maxpixels);
							
						float opacity = (float) pixels / (float) maxpixels;
						
						float size = OutOfFovSize;
						
						Vector3 viewdir = Transform$$forward[Component$$transform[Camera$$main()]()]();
                        Vector3 targetdir = (pos - viewpos).normalized();

                       float viewangle = atan2(viewdir.z, viewdir.x) * Rad2Deg;
                          float targetangle =
                                        atan2(targetdir.z, targetdir.x) * Rad2Deg;

                                if (viewangle < 0) viewangle += 360;
                                if (targetangle < 0) targetangle += 360;

                                float angle = targetangle - viewangle;


                                while (angle < 0) angle += 360;
                                while (angle > 360) angle -= 360;

                                angle = 360 - angle;
                                angle -= 90;
								if(OutOfFovArc) {
								arc(glWidth / 2, glHeight / 2, 226 + distanceOof * 2,
                                    angle - size,
                                    angle + size,
                                    ImColor(1.f, 1.f, 1.f, 1.f * opacity), 4.f);
								}
							if(OutOfFovTrinagle) {
								arc_triangle(glWidth / 2, glHeight / 2, 226 + distanceOof * 2,
                                    angle - size,
                                    angle + size,
                                    ImColor(1.f, 1.f, 1.f, 1.f * opacity), 4.f);
							}
						}
					}
								
								
			monoArray<void **> *enemySkelet = *(monoArray<void **> **)((addr_t)playerPO + 0x80);
			monoArray<void **> *localSkelet = *(monoArray<void **> **)((addr_t)localPlayerPO + 0x80);
			auto hitsenemy = enemySkelet->toCPPlist();
			auto hitslocal = localSkelet->toCPPlist();
			//auto w2sC = Camera$$World2ScreenPoint[mainCamera](Vector3(Transform$$position[playerTR]() + Vector3(0, 1.9f, 0)));
			//auto outoffov = world2screen_c(world_position + Vector3(0, 90.0, 0), checker);
			auto w2sTop = world2screen_i(world_position + Vector3(0, 1.9f, 0));
			auto w2sBottom = world2screen_i(world_position + Vector3(0, 0, 0));
        	auto pmtXtop = w2sTop.x;
			auto position_outoffov = world2screen_c(world_position + Vector3(0, 90.0, 0), checker);
       	 	auto pmtXbottom = w2sBottom.x;
        	if (w2sTop.x > w2sBottom.x) {
				pmtXtop = w2sBottom.x;
            	pmtXbottom = w2sTop.x;
        	}
			
			if (screen_position.z <= 0)
				continue;
		
			
			bool raycastCheck = Physics$$Raycast;
			auto distanc = Vector3::Distance(viewpos, pos);
			if (screen_position.z <= 0)
				continue;
			RaycastHit hitInfo;
			
			//Vector3 gpp = Transform$$position[transform]();
			string playername = (*(monoString **)((addr_t)player + 0xC))->str();
			string distance = (to_string((int)screen_position.z) + "FT").c_str();
			auto playerDistance = Vector3::Distance(Transform$$position[Component$$transform[mainCamera]()](), playerPosition);
			string money = string(to_string(*(int*)((uintptr_t)player + 0x48))).c_str();
			money += string("$");
			auto hp = (float) health;
			auto arm = (float) armor;
			
			string hpstring = to_string(health);
			string armstring = to_string(armor);
			
			auto visibleCheck = Physics$$Linecast$$HitInfo(camera_position, camera_position - playerPosition, &hitInfo);
			ImColor autoColor;
			
			if (health == 100) {
                autoColor = ImColor(0, 255, 0);
            } else if (health > 75) {
                autoColor = ImColor(35, 196, 0);
            } else if (health > 50) {
                autoColor = ImColor(196, 187, 2);
            } else if (health > 30) {
                autoColor = ImColor(196, 119, 6);
            } else if (health > 20) {
                autoColor = ImColor(196, 9, 1);
            } else if (health > 10) {
                autoColor = ImColor(196, 9, 1);
			    }
			
				/*int* armor = reinterpret_cast<int*>(reinterpret_cast<addr_t>(player) + 0x38);

// Рассчитываем координаты прямоугольника для рисования
float rectLeft = pmtXtop - std::abs((w2sTop.y - w2sBottom.y) / 4);
float rectRight = pmtXbottom.x - std::abs((w2sTop.y - w2sBottom.y) / 4) + std::abs((w2sTop.y - w2sBottom.y) / 2 * (*armor / 100.f));
float rectTop = w2sBottom.y + 4;
float rectBottom = w2sBottom.y + 7;

auto arm = (float) armor;
string armorstring = to_string(armor);*/
			//auto visibleCheck = Physics$$Linecast$$HitInfo(camera_position, camera_position - pos, &hitInfo);
			if (EspEnable){
				
	
						
					if (hitHistory && !hitData.empty()) {
				for (auto i = 0; i < hitData.size(); i++) {
					hitTime[i]++;
					if (hitTime[i] > 250)
						continue;
						
					if (hitData[i].animation < 1)
						hitData.erase(hitData.begin() + i);
						
					if (hitData[i].animation > 0) 
						hitData[i].animation -= 0.50;
               					
					auto hitPosition = w2s_i(hitData[i].hit, true);
               		auto cameraPosition = w2s_c(hitData[i].camera, false, true);
					auto getDamage = hitData[i].damage;
                	auto animation = hitData[i].animation;
					
					if (getDamage > 0) {
						if (hitMarkerEnable) {
							if(hitMarker) {
							/*//outline start
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x - 3, hitPosition.y - 3), ImVec2(hitPosition.x - 8, hitPosition.y - 8), ImColor(hitmarout.x, hitmarout.y, hitmarout.z, (float) animation / 255), 5.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x - 3, hitPosition.y + 3), ImVec2(hitPosition.x - 8, hitPosition.y + 8), ImColor(hitmarout.x, hitmarout.y, hitmarout.z, (float) animation / 255), 5.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x + 3, hitPosition.y - 3), ImVec2(hitPosition.x + 8, hitPosition.y - 8), ImColor(hitmarout.x, hitmarout.y, hitmarout.z, (float) animation / 255), 5.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x + 3, hitPosition.y + 3), ImVec2(hitPosition.x + 8, hitPosition.y + 8), ImColor(hitmarout.x, hitmarout.y, hitmarout.z, (float) animation / 255), 5.0f);
							//outline end*/
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x - 3, hitPosition.y - 3), ImVec2(hitPosition.x - 8, hitPosition.y - 8), ImColor(hitMarkCol[0],hitMarkCol[1], hitMarkCol[2], (float) animation / 255), 2.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x - 3, hitPosition.y + 3), ImVec2(hitPosition.x - 8, hitPosition.y + 8), ImColor(hitMarkCol[0],hitMarkCol[1], hitMarkCol[2], (float) animation / 255), 2.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x + 3, hitPosition.y - 3), ImVec2(hitPosition.x + 8, hitPosition.y - 8), ImColor(hitMarkCol[0],hitMarkCol[1], hitMarkCol[2], (float) animation / 255), 2.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x + 3, hitPosition.y + 3), ImVec2(hitPosition.x + 8, hitPosition.y + 8), ImColor(hitMarkCol[0],hitMarkCol[1], hitMarkCol[2], (float) animation / 255), 2.0f);
						}
							if (hitMarkerGlow) {
								line_glow(ImVec2(hitPosition.x - 3, hitPosition.y - 3), ImVec2(hitPosition.x - 8, hitPosition.y - 8), ImColor(hitMarkCol[0],hitMarkCol[1], hitMarkCol[2], (float) animation / 255), 1.5f, 25.0f);
								line_glow(ImVec2(hitPosition.x - 3, hitPosition.y + 3), ImVec2(hitPosition.x - 8, hitPosition.y + 8), ImColor(hitMarkCol[0],hitMarkCol[1], hitMarkCol[2], (float) animation / 255), 1.5f, 25.0f);
								line_glow(ImVec2(hitPosition.x + 3, hitPosition.y - 3), ImVec2(hitPosition.x + 8, hitPosition.y - 8), ImColor(hitMarkCol[0],hitMarkCol[1], hitMarkCol[2], (float) animation / 255), 1.5f, 25.0f);
								line_glow(ImVec2(hitPosition.x + 3, hitPosition.y + 3), ImVec2(hitPosition.x + 8, hitPosition.y + 8), ImColor(hitMarkCol[0],hitMarkCol[1], hitMarkCol[2], (float) animation / 255), 1.5f, 25.0f);
							}
							if(hitMarkerOutline) {
							//outline start
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x - 3, hitPosition.y - 3), ImVec2(hitPosition.x - 8, hitPosition.y - 8), ImColor(hitmarout.x, hitmarout.y, hitmarout.z, (float) animation / 255), 5.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x - 3, hitPosition.y + 3), ImVec2(hitPosition.x - 8, hitPosition.y + 8), ImColor(hitmarout.x, hitmarout.y, hitmarout.z, (float) animation / 255), 5.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x + 3, hitPosition.y - 3), ImVec2(hitPosition.x + 8, hitPosition.y - 8), ImColor(hitmarout.x, hitmarout.y, hitmarout.z, (float) animation / 255), 5.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x + 3, hitPosition.y + 3), ImVec2(hitPosition.x + 8, hitPosition.y + 8), ImColor(hitmarout.x, hitmarout.y, hitmarout.z, (float) animation / 255), 5.0f);
							//outline end
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x - 3, hitPosition.y - 3), ImVec2(hitPosition.x - 8, hitPosition.y - 8), ImColor(hitMarkCol[0],hitMarkCol[1], hitMarkCol[2], (float) animation / 255), 2.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x - 3, hitPosition.y + 3), ImVec2(hitPosition.x - 8, hitPosition.y + 8), ImColor(hitMarkCol[0],hitMarkCol[1], hitMarkCol[2], (float) animation / 255), 2.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x + 3, hitPosition.y - 3), ImVec2(hitPosition.x + 8, hitPosition.y - 8), ImColor(hitMarkCol[0],hitMarkCol[1], hitMarkCol[2], (float) animation / 255), 2.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitPosition.x + 3, hitPosition.y + 3), ImVec2(hitPosition.x + 8, hitPosition.y + 8), ImColor(hitMarkCol[0],hitMarkCol[1], hitMarkCol[2], (float) animation / 255), 2.0f);
							}
						}
						if (showDamage) {
							auto playerDamage = "-" + std::to_string(static_cast<int>(getDamage)); 
							add_text(ImVec2(hitPosition.x - ImGui::CalcTextSize(playerDamage.c_str()).x / 2, hitPosition.y - 20 - (255 - animation) / 10), ImColor(showDmgCol[0], showDmgCol[1], showDmgCol[2], (float) animation / 255), playerDamage.c_str(), 18, "shadow");
               			}
						if (bulletTracerEnable) {
							
						if (bulletTracer) {
                	 	  	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(cameraPosition.x, cameraPosition.y), ImVec2(hitPosition.x, hitPosition.y), ImColor(bullTracCol[0], bullTracCol[1], bullTracCol[2], (float) animation / 255), 2.0f);
						}
							if (bulletTracerGlow) {
                   	 			line_glow(ImVec2(cameraPosition.x, cameraPosition.y), ImVec2(hitPosition.x, hitPosition.y), ImColor(bullTracCol[0], bullTracCol[1], bullTracCol[2], (float) animation / 255), 2.0f, 25);
						}
						if (bulletTracerOutline) {
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(cameraPosition.x, cameraPosition.y), ImVec2(hitPosition.x, hitPosition.y), ImColor(bullTracColO[0], bullTracColO[1], bullTracColO[2], (float) animation / 255), 5.0f);
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(cameraPosition.x, cameraPosition.y), ImVec2(hitPosition.x, hitPosition.y), ImColor(bullTracCol[0], bullTracCol[1], bullTracCol[2], (float) animation / 255), 2.0f);
						}
					}
						/*if (hitLog) {
							PushFont(pixel);
							auto enemyName = (*(monoString **)((addr_t)getEnemyPlayer + offsets::PlayerData$$playername))->str();
							if (getDamage > 0) {
								std::ostringstream log;
								std::string bodyhit;
								log << "HIT " << enemyName << " FOR " << getDamage << " DAMAGE";
								std::string hitLog = log.str();
                                
                                ImGui::GetBackgroundDrawList()->AddText(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - ImGui::CalcTextSize(hitLog.c_str()).x / 2, (ImGui::GetIO().DisplaySize.y / 2 + 170 + i * 20)), ImColor(ImVec4(1.0f, 1.0f, 1.0f, (float) animation / 255)), hitLog.c_str());
							}
							PopFont();
						}*/
					}
				}
			}
						
						
						/*if (OutOfFovArc) {
							arc_line(glWidth / 2, glHeight / 2, 170 + distanc * 2, angle - size, angle + size, ImGui::GetColorU32(*(ImVec4 *)OutOfFovColor), 4.f);
							arc_line(glWidth / 2, glHeight / 2, 163 + distanc * 2, angle - size, angle + size, ImColor(255, 10, 10) , 2.5f);
						}
						if (OutOfFovTrinagle) {
							arc_triangle(glWidth / 2, glHeight / 2, 170 + distanc * 2, angle - size, angle + size, ImGui::GetColorU32(*(ImVec4 *)OutOfFovColor), 4.f);
						}
					}
				}
//Out of screen for bpm*/
				
				if (espMyState) {
				string localState;
				auto inAir = *(bool *)((addr_t)localPlayer + offsets::PlayerData$$inAir);
				auto inDuck = *(bool *)((addr_t)localPlayer + offsets::PlayerData$$inDuck);
				if (inAir) {
					localState += "AIR";
					ImGui::GetBackgroundDrawList()->AddText(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - ImGui::CalcTextSize(localState.c_str()).x / 2, (ImGui::GetIO().DisplaySize.y / 2 + 200)), ImColor(255, 255, 255), localState.c_str());
				} else if (inDuck) {
					localState += "DUCK";
					ImGui::GetBackgroundDrawList()->AddText(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - ImGui::CalcTextSize(localState.c_str()).x / 2, (ImGui::GetIO().DisplaySize.y / 2 + 200)), ImColor(255, 255, 255), localState.c_str());
				} else {
					localState += "STAND";
					ImGui::GetBackgroundDrawList()->AddText(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - ImGui::CalcTextSize(localState.c_str()).x / 2, (ImGui::GetIO().DisplaySize.y / 2 + 200)), ImColor(255, 255, 255), localState.c_str());
				}
			}
				
			if (jumpHistory) {
                for (auto i = 0; i < jumpData.size(); i++) {
                    if (jumpData[i].animation > 0)
                        jumpData[i].animation = jumpData[i].animation - 1;
                        
                    auto position = method::Camera$$World2ScreenPoint[property::Camera$$main](jumpData[i].position);
                    auto animation = jumpData[i].animation;
                }
            }
			
			static float deltaTime;
				deltaTime += ImGui::GetIO().DeltaTime;
            	if (deltaTime >= 1.5) {
					footsteps_data.push_back({GetColorU32(*(ImVec4 *)footStepsColor), property::Transform$$position[playerTR]()});
					deltaTime = 0;
          	  	}
			
        		if (footsteps_data.size() > 15)
					footsteps_data.pop_front();
					
				if (footSteps && !footsteps_data.empty()) {
						for (auto i = 0; i < footsteps_data.size(); i++) {
							if (footsteps_data[i].animation > 0)
								footsteps_data[i].animation -= 1.5;
					  
							if (footsteps_data[i].radius > 0)
								footsteps_data[i].radius += 0.005;
						
                			float step = 2 * M_PI / 22;
               				float h = footsteps_data[i].position.x;
              	  			float k = footsteps_data[i].position.z;
                			float r = footsteps_data[i].radius;
                			int e = 0;
                			for (float theta = 0; theta < 2 * M_PI; theta += step) {
                   				float x = h + r * cos(theta);
                   	  			float y = k - r * sin(theta);
								e = e + 1;
								if (e > 1) {
                         			float xz = h + r * cos(theta - step);
                        			float yz = k - r * sin(theta - step);
                        			auto pos1 = method::Camera$$World2ScreenPoint[property::Camera$$main()](Vector3(x, footsteps_data[i].position.y + 0, y));
									auto pos2 = method::Camera$$World2ScreenPoint[property::Camera$$main()](Vector3(xz, footsteps_data[i].position.y + 0, yz));
									pos1.y = ImGui::GetIO().DisplaySize.y - pos1.y;
									pos2.y = ImGui::GetIO().DisplaySize.y - pos2.y;
                        			if (pos1.z < 1.0 || pos2.z < 1.0)
										continue;
										
  	                      			if(footStepsOutline) {
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImColor(footsteps_data[i].color.Value.x, footsteps_data[i].color.Value.y, footsteps_data[i].color.Value.z, (float) footsteps_data[i].animation / 255), 0.5);
									}
									
									if(footStepsOutline) {
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImColor(footsteps_data[i].color.Value.x, footsteps_data[i].color.Value.y, footsteps_data[i].color.Value.z, (float) footsteps_data[i].animation / 255), 2);
										ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImColor(footsteps_data[i].color.Value.x, footsteps_data[i].color.Value.y, footsteps_data[i].color.Value.z, (float) footsteps_data[i].animation / 255), 0.5);
									}
									
									if (footStepsGlow) {
										line_glow(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImColor(footsteps_data[i].color.Value.x, footsteps_data[i].color.Value.y, footsteps_data[i].color.Value.z, (float) footsteps_data[i].animation / 255), 0.5, 12);
								}
							}
						}
					}
				}
			
			if(tracer) {
				movementHistory.push_back(localPosition);
				if (movementHistory.size() > 400)
					movementHistory.erase(movementHistory.begin());
			
				for (int i = 0; i != movementHistory.size(); i++) {
					if (i < 3 || movementHistory[i] == movementHistory[i - 1])
						continue;
						
					auto pos1 = method::Camera$$World2ScreenPoint[property::Camera$$main()](movementHistory[i]);
					auto pos2 = method::Camera$$World2ScreenPoint[property::Camera$$main()](movementHistory[i - 1]);
					pos1.y = ImGui::GetIO().DisplaySize.y - pos1.y;
					pos2.y = ImGui::GetIO().DisplaySize.y - pos2.y;
					if (pos1.z <= 0 || pos2.z <= 0)
						continue;
					
					if(tracerDefault) {
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImGui::GetColorU32(*(ImVec4 *)tracerColor), 3);
					}
						
					if(tracerGlow) {
						line_glow(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImGui::GetColorU32(*(ImVec4 *)tracerColor), 3.0f, 20);
					}
					
					if (tracerOutline)
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImColor(0, 0, 0), 3);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImGui::GetColorU32(*(ImVec4 *)tracerColor), 3);
				}
			}	
				
				
				/*if (OutOfFov) {
				if(raycastCheck){
					if ((position_outoffov.x < 0 || position_outoffov.x > glWidth) || (position_outoffov.y < 0 || position_outoffov.y > glHeight) || !checker) {
						constexpr int maxpixels = 200;
						int pixels = maxpixels;

                        if (checker) {
							if (position_outoffov.x < 0)
								pixels = std::clamp((int) - position_outoffov.x, 0, maxpixels);
								
                            if (position_outoffov.y < 0)
								pixels = std::clamp((int) - position_outoffov.y, 0, maxpixels);
								
                            if (position_outoffov.x > glWidth)
								pixels = std::clamp((int) position_outoffov.x - glWidth, 0, maxpixels);
								
                            if (position_outoffov.y > glHeight)
								pixels = std::clamp((int) position_outoffov.y - glHeight, 0, maxpixels);
                        }
						
						float opacity = (float) pixels / (float) maxpixels;
                        float size = OutOfFovSize;
                        Vector3 viewdir = Camera$$World2ScreenPoint[Camera$$main()]();
                        Vector3 targetdir = viewpos.normalized();
                        float viewangle = atan2(viewdir.z, viewdir.x) * Rad2Deg;
                        float targetangle = atan2(targetdir.z, targetdir.x) * Rad2Deg;
						
						if (viewangle < 0)
							viewangle += 360;
							
                        if (targetangle < 0)
							targetangle += 360;

                        float angle = targetangle - viewangle;
						while (angle < 0) angle += 360;
                        while (angle > 360) angle -= 360;
						angle = 360 - angle;
                        angle -= 90;
						if (OutOfFovArc) {
							arc_line(glWidth / 2, glHeight / 2, 170 + distanc * 2, angle - size, angle + size, ImGui::GetColorU32(*(ImVec4 *)OutOfFovColor), 4.f);
							arc_line(glWidth / 2, glHeight / 2, 163 + distanc * 2, angle - size, angle + size, ImColor(255, 10, 10) , 2.5f);
						}
						if (OutOfFovTrinagle) {
							arc_triangle(glWidth / 2, glHeight / 2, 170 + distanc * 2, angle - size, angle + size, ImGui::GetColorU32(*(ImVec4 *)OutOfFovColor), 4.f);
						}}}}*/
				
				if(EspBoxEnable) {
					if(BoxFilled){
						ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(pmtXtop - abs((w2sTop.y - w2sBottom.y) / 4), w2sTop.y + 0.15), ImVec2(pmtXbottom + abs((w2sTop.y - w2sBottom.y) / 3), w2sBottom.y + 0.7), ImGui::ColorConvertFloat4ToU32(ImVec4(BoxFilledColor[0],BoxFilledColor[1],BoxFilledColor[2], float(BoxFilledAlpha)/255.f)), EspBoxRounding, 0);
					}
/*if (EspBox) {
    // Calculate rectangle bounds once
    float offset = abs((w2sTop.y - w2sBottom.y) / 4);
    ImVec2 topLeft(pmtXtop - offset, w2sTop.y + 0.15f);
    ImVec2 bottomRight(pmtXbottom + offset * 4 / 3, w2sBottom.y + 0.7f);
    
    auto drawList = ImGui::GetBackgroundDrawList();
    ImU32 boxColor = ImGui::GetColorU32(*(ImVec4 *)EspBoxColor);

    // Draw outline if enabled
    if (boxOutline) {
        drawList->AddRect(topLeft, bottomRight, ImColor(0, 0, 0, 255), EspBoxRounding, 0, 5.0f);
    }
    
    // Draw main rectangle
    drawList->AddRect(topLeft, bottomRight, boxColor, EspBoxRounding, 0, 2.0f);
}*/

if (EspBox) {
    auto dl = ImGui::GetBackgroundDrawList();
    float off = fabsf(w2sTop.y - w2sBottom.y) * 0.25f;
    ImRect r(floorf(pmtXtop - off), floorf(w2sTop.y + 0.15f), floorf(pmtXbottom + off * 1.333f), floorf(w2sBottom.y + 0.7f));

    int backup_flags = dl->Flags;
    dl->Flags &= ~ImDrawListFlags_AntiAliasedLines;

    if (boxOutline) {
        dl->AddRect({ r.Min.x - 1, r.Min.y - 1 }, { r.Max.x + 1, r.Max.y + 1 }, ImColor(0, 0, 0), EspBoxRounding);
        dl->AddRect({ r.Min.x + 1, r.Min.y + 1 }, { r.Max.x - 1, r.Max.y - 1 }, ImColor(0, 0, 0), EspBoxRounding);
    }

    dl->AddRect(r.Min, r.Max, ImGui::GetColorU32(*(ImVec4*)EspBoxColor), EspBoxRounding);
    dl->Flags = backup_flags;
}



if (boxCorner) {
    auto dl = ImGui::GetBackgroundDrawList();
    float off = fabsf(w2sTop.y - w2sBottom.y) * 0.25f;
    // Границы бокса
    ImRect r(floorf(pmtXtop - off), floorf(w2sTop.y + 0.15f), floorf(pmtXbottom + off * 1.333f), floorf(w2sBottom.y + 0.7f));

    int bk = dl->Flags;
    dl->Flags &= ~ImDrawListFlags_AntiAliasedLines; // Без сглаживания

    ImU32 col = ImGui::GetColorU32(*(ImVec4*)EspBoxColor);
    ImU32 black = 0xFF000000; // Черный цвет (AABBGGRR)
    float len = 6.0f;

    // Лямбда рисует один угол (сразу две палки), соблюдая порядок слоев
    auto Corner = [&](float x, float y, float dx, float dy) {
        // Вычисляем координаты для Горизонтальной (H) и Вертикальной (V) палок
        // dx/dy - направление (-1 или 1). Толщина 1px направлена внутрь.
        
        // Размеры усиков с учетом знака
        float w = (dx > 0) ? len : -len;
        float h = (dy > 0) ? len : -len;
        
        // Координаты концов H-палки
        float hx1 = x, hx2 = x + w;
        float hy1 = y, hy2 = y + (dy > 0 ? 1.0f : -1.0f);
        
        // Координаты концов V-палки
        float vx1 = x, vx2 = x + (dx > 0 ? 1.0f : -1.0f);
        float vy1 = y, vy2 = y + h;

        // Нормализуем координаты (чтобы Min был < Max для AddRectFilled)
        auto Fix = [](float& a, float& b) { if (a > b) std::swap(a, b); };
        Fix(hx1, hx2); Fix(hy1, hy2);
        Fix(vx1, vx2); Fix(vy1, vy2);

        // СЛОЙ 1: Черная обводка (рисуем для обеих палок СРАЗУ)
        // Расширяем на 1 пиксель во все стороны (-1, +1)
        if (boxOutline) {
            dl->AddRectFilled({ hx1 - 1, hy1 - 1 }, { hx2 + 1, hy2 + 1 }, black);
            dl->AddRectFilled({ vx1 - 1, vy1 - 1 }, { vx2 + 1, vy2 + 1 }, black);
        }

        // СЛОЙ 2: Цветная заливка (рисуем поверх черного)
        dl->AddRectFilled({ hx1, hy1 }, { hx2, hy2 }, col);
        dl->AddRectFilled({ vx1, vy1 }, { vx2, vy2 }, col);
    };

    // Рисуем 4 угла
    Corner(r.Min.x, r.Min.y, 1.f, 1.f);   // Top-Left
    Corner(r.Max.x, r.Min.y, -1.f, 1.f);  // Top-Right
    Corner(r.Min.x, r.Max.y, 1.f, -1.f);  // Bottom-Left
    Corner(r.Max.x, r.Max.y, -1.f, -1.f); // Bottom-Right

    dl->Flags = bk;
}


}
					
					
					
				
if (EspBoxGradient) {
    // Calculate rectangle bounds to match EspBox
    float offset = abs((w2sTop.y - w2sBottom.y) / 4);
    ImVec2 topLeft(pmtXtop - offset, w2sTop.y + 0.15f);
    ImVec2 bottomRight(pmtXbottom + offset * 4 / 3, w2sBottom.y + 0.7f);

    auto drawList = ImGui::GetBackgroundDrawList();
	
    // Draw gradient-filled rectangle
    drawList->AddRectFilledMultiColor(
        topLeft,
        bottomRight,
        ImGui::GetColorU32(*(ImVec4 *)EspBoxGradientColor),
        ImGui::GetColorU32(*(ImVec4 *)EspBoxGradientColor),
        ImGui::GetColorU32(*(ImVec4 *)EspBoxGradientColor1),
        ImGui::GetColorU32(*(ImVec4 *)EspBoxGradientColor1)
    );
}

					float armorSize = 3.1;
if (EspHealthEn) {
						

// Общая лямбда (вставь перед if-ами или используй как копипасту)
auto DrawPixelBar = [&](ImDrawList* dl, ImRect r, ImU32 col, float pct, bool horiz) {
    // Черная рамка (1px снаружи) + Фон
    dl->AddRectFilled({ r.Min.x - 1, r.Min.y - 1 }, { r.Max.x + 1, r.Max.y + 1 }, 0xFF000000);
    dl->AddRectFilled(r.Min, r.Max, ImColor(0, 0, 0, 100));
    
    if (pct <= 0.0f) return;
    if (horiz) {
        float w = floorf((r.Max.x - r.Min.x) * pct);
        if (w > 0) dl->AddRectFilled(r.Min, { r.Min.x + w, r.Max.y }, col);
    } else {
        float h = floorf((r.Max.y - r.Min.y) * pct);
        if (h > 0) dl->AddRectFilled({ r.Min.x, r.Max.y - h }, r.Max, col);
    }
};

float gap = 3.0f; // Твой оффсет отступа

if (EspHealth) {
    auto dl = ImGui::GetBackgroundDrawList();
    float off = fabsf(w2sTop.y - w2sBottom.y) * 0.25f;
    float boxLeft = floorf(pmtXtop - off);
    // X: (БоксСлева - отступ - 2pxширина) до (БоксСлева - отступ)
    ImRect r(boxLeft - gap - 2.0f, floorf(w2sTop.y + 0.15f), boxLeft - gap, floorf(w2sBottom.y + 0.7f));

    int bk = dl->Flags; dl->Flags &= ~(ImDrawListFlags_AntiAliasedLines | ImDrawListFlags_AntiAliasedFill);
    DrawPixelBar(dl, r, ImGui::GetColorU32(*(ImVec4*)EspHealthColor), health / 100.f, false);
    dl->Flags = bk;
}

if (EspHealthAuto) {
    auto dl = ImGui::GetBackgroundDrawList();
    float off = fabsf(w2sTop.y - w2sBottom.y) * 0.25f;
    float boxLeft = floorf(pmtXtop - off);
    ImRect r(boxLeft - gap - 2.0f, floorf(w2sTop.y + 0.15f), boxLeft - gap, floorf(w2sBottom.y + 0.7f));

    int bk = dl->Flags; dl->Flags &= ~(ImDrawListFlags_AntiAliasedLines | ImDrawListFlags_AntiAliasedFill);
    DrawPixelBar(dl, r, autoColor, health / 100.f, false);
    dl->Flags = bk;
}

if (EspHealthGlow) {
    auto dl = ImGui::GetBackgroundDrawList();
    float off = fabsf(w2sTop.y - w2sBottom.y) * 0.25f;
    float boxLeft = floorf(pmtXtop - off);
    ImRect r(boxLeft - gap - 2.0f, floorf(w2sTop.y + 0.15f), boxLeft - gap, floorf(w2sBottom.y + 0.7f));

    int bk = dl->Flags; dl->Flags &= ~(ImDrawListFlags_AntiAliasedLines | ImDrawListFlags_AntiAliasedFill);
    
    // Рисуем базу
    DrawPixelBar(dl, r, ImGui::GetColorU32(*(ImVec4*)EspHealthColor), health / 100.f, false);

    // Рисуем Glow поверх (полупрозрачные рамки)
    if (health > 0) {
        float h = floorf((r.Max.y - r.Min.y) * (health / 100.f));
        float top = r.Max.y - h;
        ImVec4 c = *(ImVec4*)EspHealthColor;
        dl->AddRect({ r.Min.x - 1, top - 1 }, { r.Max.x + 1, r.Max.y + 1 }, ImGui::GetColorU32({c.x, c.y, c.z, 0.4f}));
        dl->AddRect({ r.Min.x - 2, top - 2 }, { r.Max.x + 2, r.Max.y + 2 }, ImGui::GetColorU32({c.x, c.y, c.z, 0.2f}));
    }
    dl->Flags = bk;
}

if (EspHealthGradient) {
    auto dl = ImGui::GetBackgroundDrawList();
    float off = fabsf(w2sTop.y - w2sBottom.y) * 0.25f;
    float boxLeft = floorf(pmtXtop - off);
    ImRect r(boxLeft - gap - 2.0f, floorf(w2sTop.y + 0.15f), boxLeft - gap, floorf(w2sBottom.y + 0.7f));

    int bk = dl->Flags; dl->Flags &= ~(ImDrawListFlags_AntiAliasedLines | ImDrawListFlags_AntiAliasedFill);
    
    // Ручная отрисовка базы (так как градиент)
    dl->AddRectFilled({ r.Min.x - 1, r.Min.y - 1 }, { r.Max.x + 1, r.Max.y + 1 }, 0xFF000000);
    dl->AddRectFilled(r.Min, r.Max, ImColor(0, 0, 0, 100));
    
    if (health > 0) {
        float h = floorf((r.Max.y - r.Min.y) * (health / 100.f));
        dl->AddRectFilledMultiColor({ r.Min.x, r.Max.y - h }, r.Max, 
            ImGui::GetColorU32(*(ImVec4*)EspHealthGradientColor), ImGui::GetColorU32(*(ImVec4*)EspHealthGradientColor),
            ImGui::GetColorU32(*(ImVec4*)EspHealthGradientColor1), ImGui::GetColorU32(*(ImVec4*)EspHealthGradientColor1));
    }
    dl->Flags = bk;
}
					if (EspHealthText) {
					ImGui::PushFont(espfont);
					if (health <= 99) {
					TextOutline1(ImGui::GetColorU32(*(ImVec4 *)EspHealthTextColor), hpstring.c_str(), ImVec2(pmtXtop - abs((w2sTop.y - w2sBottom.y) / 3.85) - EspHealthStroke / 2 - 6 - 2 - ImGui::CalcTextSize(std::to_string(health).c_str()).x / 2, lerp(w2sBottom.y, w2sTop.y, hp / 100.0f) - ImGui::CalcTextSize(std::to_string(health).c_str()).y / 2), 20, 0.9f);
					}
					ImGui::PopFont();
					}
					if(EspArmorEn){
						armorSize = 3.1;
						} else {
						armorSize = 4.0;
						}
					if(selected_armorbn[0]) {

if (EspArmor) {
    auto dl = ImGui::GetBackgroundDrawList();
    float off = fabsf(w2sTop.y - w2sBottom.y) * 0.25f;
    
    // Координаты: Снизу бокса + gap. Высота 2px.
    float y1 = floorf(w2sBottom.y + 0.7f + gap);
    float y2 = y1 + 2.0f;
    ImRect r(floorf(pmtXtop - off), y1, floorf(pmtXbottom + off * 1.333f), y2);

    int bk = dl->Flags; 
    dl->Flags &= ~(ImDrawListFlags_AntiAliasedLines | ImDrawListFlags_AntiAliasedFill);

    // 1. Рисуем фон (Черная рамка + темная подложка)
    dl->AddRectFilled({ r.Min.x - 1, r.Min.y - 1 }, { r.Max.x + 1, r.Max.y + 1 }, 0xFF000000); // Outline
    dl->AddRectFilled(r.Min, r.Max, ImColor(0, 0, 0, 100)); // Background

    // 2. Твоя логика проверки
    float drawArmor = armor;
    if (drawArmor == 0) drawArmor = 100; 
    else if (drawArmor == 100) drawArmor = 0;

    // 3. Рисуем заливку
    if (drawArmor > 0) {
        float width = r.Max.x - r.Min.x;
        float fillWidth = floorf(width * (drawArmor / 100.0f));
        
        // Проверка, чтобы не рисовать нулевую ширину
        if (fillWidth >= 1.0f) {
            dl->AddRectFilled(
                r.Min, 
                { r.Min.x + fillWidth, r.Max.y }, 
                ImGui::GetColorU32(*(ImVec4*)armCol)
            );
        }
    }

    dl->Flags = bk;
}

if (EspArmorGradient) {
    auto dl = ImGui::GetBackgroundDrawList();
    float off = fabsf(w2sTop.y - w2sBottom.y) * 0.25f;
    
    float y1 = floorf(w2sBottom.y + 0.7f + gap);
    float y2 = y1 + 2.0f;
    ImRect r(floorf(pmtXtop - off), y1, floorf(pmtXbottom + off * 1.333f), y2);

    int bk = dl->Flags; 
    dl->Flags &= ~(ImDrawListFlags_AntiAliasedLines | ImDrawListFlags_AntiAliasedFill);

    dl->AddRectFilled({ r.Min.x - 1, r.Min.y - 1 }, { r.Max.x + 1, r.Max.y + 1 }, 0xFF000000);
    dl->AddRectFilled(r.Min, r.Max, ImColor(0, 0, 0, 100));

    float drawArmor = armor;
    if (drawArmor == 0) drawArmor = 100; 
    else if (drawArmor == 100) drawArmor = 0;

    if (drawArmor > 0) {
        float width = r.Max.x - r.Min.x;
        float fillWidth = floorf(width * (drawArmor / 100.0f));

        if (fillWidth >= 1.0f) {
            dl->AddRectFilledMultiColor(
                r.Min, 
                { r.Min.x + fillWidth, r.Max.y },
                ImGui::GetColorU32(*(ImVec4*)armCol2),
                ImGui::GetColorU32(*(ImVec4*)armCol1),
                ImGui::GetColorU32(*(ImVec4*)armCol1),
                ImGui::GetColorU32(*(ImVec4*)armCol2)
            );
        }
    }
    dl->Flags = bk;
}

if (EspArmorGlow) {
    auto dl = ImGui::GetBackgroundDrawList();
    float off = fabsf(w2sTop.y - w2sBottom.y) * 0.25f;
    
    float y1 = floorf(w2sBottom.y + 0.7f + gap);
    float y2 = y1 + 2.0f;
    ImRect r(floorf(pmtXtop - off), y1, floorf(pmtXbottom + off * 1.333f), y2);

    int bk = dl->Flags; 
    dl->Flags &= ~(ImDrawListFlags_AntiAliasedLines | ImDrawListFlags_AntiAliasedFill);

    dl->AddRectFilled({ r.Min.x - 1, r.Min.y - 1 }, { r.Max.x + 1, r.Max.y + 1 }, 0xFF000000);
    dl->AddRectFilled(r.Min, r.Max, ImColor(0, 0, 0, 100));

    float drawArmor = armor;
    if (drawArmor == 0) drawArmor = 100; 
    else if (drawArmor == 100) drawArmor = 0;

    if (drawArmor > 0) {
        float width = r.Max.x - r.Min.x;
        float fillWidth = floorf(width * (drawArmor / 100.0f));
        float rightX = r.Min.x + fillWidth;

        if (fillWidth >= 1.0f) {
            dl->AddRectFilled(r.Min, { rightX, r.Max.y }, ImGui::GetColorU32(*(ImVec4*)armCol));
            
            // Glow (пиксельный стиль)
            ImVec4 c = *(ImVec4*)armCol;
            dl->AddRect({ r.Min.x - 1, r.Min.y - 1 }, { rightX + 1, r.Max.y + 1 }, ImGui::GetColorU32({c.x, c.y, c.z, 0.4f}));
            dl->AddRect({ r.Min.x - 2, r.Min.y - 2 }, { rightX + 2, r.Max.y + 2 }, ImGui::GetColorU32({c.x, c.y, c.z, 0.2f}));
        }
    }
    dl->Flags = bk;
}
					if(selected_armorbn[1]) {
					if (ArmorNumber) {
					ImGui::PushFont(espfont);
					if (armor <= 99) {
					//ImGui::GetBackgroundDrawList()->AddText(pixel, 20, ImVec2(lerp(pmtXtop - std::abs((w2sTop.y - w2sBottom.y) / 4), pmtXbottom + abs((w2sTop.y - w2sBottom.y) / 4), armor / 100.0f), (w2sBottom.y + 4) - ImGui::CalcTextSize(std::to_string(armor).c_str()).y / 2), armstring.c_str(), 0.9f);
					add_text(ImVec2(lerp(pmtXtop - std::abs((w2sTop.y - w2sBottom.y) / 4.2), pmtXbottom + abs((w2sTop.y - w2sBottom.y) / 4), armor / 100.0f), (w2sBottom.y + 5) - ImGui::CalcTextSize(std::to_string(armor).c_str()).y / 2), ImGui::GetColorU32(*(ImVec4*)EspHealthTextColor), armstring.c_str(),  20, "outline");
					}
					ImGui::PopFont();
					}
					}
					}
			      }

				  
				if (EspCircle) {
					float step = 2 * M_PI / 22;
                	float h = enemyLocation(transform).x;
                	float k = enemyLocation(transform).z;
                	float r = 0.5f;
                	int e = 0;
				
                	for (float theta = 0; theta < 2 * M_PI; theta += step) {
						float x = h + r * cos(theta);
						float y = k - r * sin(theta);
                    	e = e + 1;
                    	if (e > 1) {
                    		float xz = h + r * cos(theta - step);
                       		float yz = k - r * sin(theta - step);
                        	Vector3 pos1 = Camera$$World2ScreenPoint[Camera$$main](Vector3(x, enemyLocation(transform).y + 0, y));
                        	Vector3 pos2 = Camera$$World2ScreenPoint[Camera$$main](Vector3(xz, enemyLocation(transform).y + 0, yz));
							pos1.y = glHeight - pos1.y;
							pos2.y = glHeight - pos2.y;
							
							if (pos1.z <= 0 || pos2.z <= 0)
								continue;
								
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImGui::GetColorU32(*(ImVec4 *)EspCircleColor), 1.5f);
							///*GetBackgroundDrawList()->*/AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), ImGui::GetColorU32(*(ImVec4 *)EspCircleColor), 2.5f);
						}
					}
				}
			
if (EspName) {
    ImGui::PushFont(verdana);
    
    // Calculate box center using the same bounds as the ESP box
    float offset = abs((w2sTop.y - w2sBottom.y) / 4);
    float boxTopLeftX = pmtXtop - offset;
    float boxBottomRightX = pmtXbottom + offset * 4 / 3;
    float boxCenterX = boxTopLeftX + (boxBottomRightX - boxTopLeftX) / 2;
    
    // Calculate text size
    float fontSize = ImGui::GetFontSize(); // Use current font size
    ImVec2 textSize = ImGui::CalcTextSize(playername.c_str());
    
    // Position text centered above the box
    float textX = boxCenterX - (textSize.x / 2);
    float textY = w2sTop.y - textSize.y - 5.0f; // Adjust vertical offset (5.0f for padding above box)
    
    // Render text with shadow
    ImGui::GetBackgroundDrawList()->AddText(
        ImGui::GetFont(),
        fontSize,
        ImVec2(textX + 1.1f, textY + 1.1f), // Shadow offset (1.0f for subtle shadow)
        ImColor(0, 0, 0, 160), // Black shadow
        playername.c_str()
    );
    ImGui::GetBackgroundDrawList()->AddText(
        ImGui::GetFont(),
        fontSize,
        ImVec2(textX, textY), // Main text position
        ImGui::GetColorU32(*(ImVec4 *)EspNameColor), // Main text color
        playername.c_str()
    );
    
    ImGui::PopFont();
}
			if(espWeapon) {
				auto currentWeapon = *(void **)((addr_t)player + 0xEC);
				if (currentWeapon) {
					auto weaponItem = *(void **)((addr_t)currentWeapon + 0xC);
                	if (weaponItem) {
                    	auto weaponName = *(monoString **)((addr_t)weaponItem + 0x10);
						if(selected_weapon[0]) {
						if (EspWeapon && weaponName) {
							ImGui::PushFont(espfont);
							auto weapon = weaponName->str();
// Calculate text size and width
ImVec2 textSize = ImGui::CalcTextSize(weapon.c_str());
float fontSize = ImGui::GetFontSize();
float scaleFactor = fontSize + esphptextsize;
float textWidth = (textSize.x / fontSize) * scaleFactor;
float textHeight = (textSize.y / fontSize) * scaleFactor;

// Calculate box bounds for precise centering
float offset = abs((w2sTop.y - w2sBottom.y) / 4);
ImVec2 topLeft(floor(pmtXtop - offset) + 0.5f, w2sTop.y + 0.15f);
ImVec2 bottomRight(floor(pmtXbottom + offset * 4 / 3) + 0.5f, w2sBottom.y + 0.7f);
float boxWidth = bottomRight.x - topLeft.x;
float boxCenterX = floor(topLeft.x + (boxWidth / 2.0f)) + 0.5f;

// Calculate centered x position with pixel-perfect alignment
float posX = floor(boxCenterX - (textWidth / 2.0f)) + 0.5f;
// Calculate y position with pixel-perfect alignment
// Changed 27.0f to 14.0f to move UP to the dot
float posY = floor(w2sBottom.y - textHeight + 16.0f) + 0.5f;

TextOutline1(ImGui::GetColorU32(*(ImVec4 *)EspWeaponColor), weapon.c_str(), ImVec2(posX, posY), 10, 160);
ImGui::PopFont();

						}
					}
							if(selected_weapon[1]) {
							if (EspWeaponIcon && weaponName) {
								ImGui::PushFont(weaponicon);
								string deaster;
								if (weaponName->str() == "AK47") {
									deaster = "S";
								}
								if (weaponName->str() == "SSCOUT") {
									deaster = "X";
								}
								if (weaponName->str() == "AWP") {
									deaster = "Y";
								}
								if (weaponName->str() == "DEAGLE") {
									deaster = "G";
								}
								if (weaponName->str() == "KNIFE PP") {
									deaster = "b";
								}
								if (weaponName->str() == "KNIFE BO") {
									deaster = "b";
								}
								if (weaponName->str() == "FAMAS") {
									deaster = "R";
								}
								if(weaponName->str() == "AUG") {
									deaster = "W";
								}
								if (weaponName->str() == "M4A4") {
									deaster = "T";
								}
								if (weaponName->str() == "SIG556") {
									deaster = "W";
								}
								if (weaponName->str() == "P90") {
									deaster = "P";
								}
								if (weaponName->str() == "MP7") {
									deaster = "O";
								}
								if (weaponName->str() == "MAC10") {
									deaster = "L";
								}
								if (weaponName->str() == "MP9") {
									deaster = "O";
								}
								if (weaponName->str() == "UMP") {
									deaster = "M";
								}
								if (weaponName->str() == "FIVESEVEN") {
									deaster = "F";
								}
								if (weaponName->str() == "TEC9") {
									deaster = "E";
								}
								if (weaponName->str() == "GLOCK18") {
									deaster = "A";
								}
								if (weaponName->str() == "NOVA") {
									deaster = "I";
								}
								if (weaponName->str() == "REMING870") {
									deaster = "H";
								}
								if (weaponName->str() == "XM1014") {
									deaster = "I";
								}
								if (weaponName->str() == "VINTOREZ") {
									deaster = "Y";
								}
								if (weaponName->str() == "HEGRENADE") {
									deaster = "p";
								}
								if (weaponName->str() == "FLASHGRENADE") {
									deaster = "n";
								}
								if (weaponName->str() == "SMOKEGRENADE") {
									deaster = "o";
								}
ImVec2 textSize = ImGui::CalcTextSize(deaster.c_str());
float fontSize = ImGui::GetFontSize();
float scaleFactor = fontSize + esphptextsize;
float textWidth = (textSize.x / fontSize) * scaleFactor;
float textHeight = (textSize.y / fontSize) * scaleFactor;

// Calculate box bounds for precise centering
float offset = abs((w2sTop.y - w2sBottom.y) / 4);
ImVec2 topLeft(pmtXtop - offset, w2sTop.y + 0.15f);
ImVec2 bottomRight(pmtXbottom + offset * 4 / 3, w2sBottom.y + 0.7f);
float boxWidth = bottomRight.x - topLeft.x;
float boxCenterX = topLeft.x + (boxWidth / 2.0f);

// Calculate centered x position with subpixel adjustment
float posX = floor(boxCenterX - (textWidth / 2.0f)) + 0.5f;
// Calculate y position with subpixel adjustment, moved slightly higher
// Changed 43.0f to 25.0f to follow the weapon text tightly
float posY = floor(w2sBottom.y - textHeight + 33.0f) + 0.5f;

TextOutline1(ImGui::GetColorU32(*(ImVec4 *)EspWeaponColor), deaster.c_str(), ImVec2(posX, posY), 20, 160);
ImGui::PopFont();
							}		
						}	
					}
				}
			}
		}
			
				if (EspLineEnable) {
					if(EspLineUp){
						ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2((pmtXtop + (pmtXbottom - pmtXtop) / 2) - 0.5f, w2sBottom.y), ImVec2((pmtXtop + (pmtXbottom - pmtXtop) / 2) + 1, w2sBottom.y), ImVec2(glWidth / 2, 0), ImGui::GetColorU32(*(ImVec4 *)EspLineColor));
				}
					if(EspLineCenter){
						ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2((pmtXtop + (pmtXbottom - pmtXtop) / 2) - 0.5f, w2sBottom.y), ImVec2((pmtXtop + (pmtXbottom - pmtXtop) / 2) + 1, w2sBottom.y), ImVec2(glWidth / 2, glHeight / 2), ImGui::GetColorU32(*(ImVec4 *)EspLineColor));
					}
					if (EspLineDown) {
						ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2((pmtXtop + (pmtXbottom - pmtXtop) / 2) - 0.5f, w2sBottom.y), ImVec2((pmtXtop + (pmtXbottom - pmtXtop) / 2) + 1, w2sBottom.y), ImVec2(glWidth / 2, glHeight + 50), ImGui::GetColorU32(*(ImVec4 *)EspLineColor));
					}
				}
					
ImGui::PushFont(espfont);

// X
float right_offset = fabsf(w2sTop.y - w2sBottom.y) / 3.0f;
float right_x = floorf(pmtXbottom + right_offset + 3.5f) + 0.5f;

// Шаг строки
float step = 8.0f;

// Y Флагов
float flag_y = floorf(w2sTop.y - 2.0f) + 0.5f;

// Y Списка
float list_y = floorf(w2sTop.y + 6.0f) + 0.5f;

// ---- СМЕЩЕНИЕ ВСЕГО ТЕКСТА НА 1px ВЛЕВО И ВВЕРХ ----
right_x -= 1.0f;
flag_y -= 1.0f;
list_y -= 1.0f;
// -----------------------------------------------------

if (EspArmorIndicator) {
    const char* txt = "HK";
    ImVec4* col = (ImVec4*)stateHkColor;
    
    bool air  = *(bool*)((addr_t)player + offsets::PlayerData$$inAir);
    bool duck = *(bool*)((addr_t)player + offsets::PlayerData$$inDuck);

    if (air)  { txt = "AR"; col = (ImVec4*)stateArColor; }
    else if (duck) { txt = "DK"; col = (ImVec4*)stateDkColor; }

    TextOutline1(ImGui::GetColorU32(*col), txt,
                 ImVec2(right_x, flag_y), 10, 1.0f);
}

if (EspDistance) {
    TextOutline1(ImGui::GetColorU32(*(ImVec4*)EspDistanceColor),
                 distance.c_str(),
                 ImVec2(right_x, list_y), 10, 1.0f);
    list_y += step;
}

if (EspMoney) {
    TextOutline1(ImGui::GetColorU32(*(ImVec4*)EspMoneyColor),
                 money.c_str(),
                 ImVec2(right_x, list_y), 10, 1.0f);
}

ImGui::PopFont();
				
if (EspSkeleton)
{
	if(enemyPlayerTRHB->getPointer()) {
    for (int i1 = 0; i1 != hitsenemy.size(); i1++)
    {
        for (int i2 = 0; i2 != hitsenemy.size(); i2++)
        {
            if ((i1 == 6 && i2 == 5) || (i1 == 5 && i2 == 4) || (i1 == 4 && i2 == 3) || (i1 == 3 && i2 == 10) || (i1 == 10 && i2 == 11) || (i1 == 11 && i2 == 12) || (i1 == 3 && i2 == 2) || (i1 == 2 && i2 == 1) || (i1 == 1 && i2 == 7) || (i1 == 7 && i2 == 8) || (i1 == 1 && i2 == 13) || (i1 == 13 && i2 == 14))
            {
                if (!hitsenemy[i1] || !hitsenemy[i2])
                continue;
                
                Vector3 pos = Camera$$World2ScreenPoint[mainCamera](Transform$$position[hitsenemy[i1]]());
                Vector3 pos2 = Camera$$World2ScreenPoint[mainCamera](Transform$$position[hitsenemy[i2]]());
				Vector3 hppos = Camera$$World2ScreenPoint[mainCamera](Transform$$position[hitsenemy[3]]());
                pos.y = glHeight - pos.y;
                pos2.y = glHeight - pos2.y;
				hppos.y = glHeight - hppos.y;
                if (pos.z <= 0 || pos2.z <= 0)
                continue;
                
                ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos2.x, pos2.y), GetColorU32(*(ImVec4 *)EspSkeletonColor), 3);
				if(skeletonOutline) {
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos2.x, pos2.y), ImColor(0, 0, 0), 5);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos2.x, pos2.y), GetColorU32(*(ImVec4 *)EspSkeletonColor), 3);
				}
            	if (EspSkeletonHead) {
                ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(hppos.x, hppos.y - 250 / hppos.z), 250 / hppos.z, GetColorU32(*(ImVec4 *)EspSkeletonColor), 0, 3);
				if(skeletonOutline) {
					ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(hppos.x, hppos.y - 250 / hppos.z), 250 / hppos.z, ImColor(0, 0, 0), 0, 5);
					ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(hppos.x, hppos.y - 250 / hppos.z), 250 / hppos.z, GetColorU32(*(ImVec4 *)EspSkeletonColor), 0, 3);
				}
            }
        }
    }
}
}
}
					if (espMySkeleton) {
						if(localPlayerTRHB->getPointer()) {
							for (int i1 = 0; i1 != hitslocal.size(); i1++)
    {
        for (int i2 = 0; i2 != hitslocal.size(); i2++)
        {
            if ((i1 == 6 && i2 == 5) || (i1 == 5 && i2 == 4) || (i1 == 4 && i2 == 3) || (i1 == 3 && i2 == 10) || (i1 == 10 && i2 == 11) || (i1 == 11 && i2 == 12) || (i1 == 3 && i2 == 2) || (i1 == 2 && i2 == 1) || (i1 == 1 && i2 == 7) || (i1 == 7 && i2 == 8) || (i1 == 1 && i2 == 13) || (i1 == 13 && i2 == 14))
            {
                if (!hitslocal[i1] || !hitslocal[i2])
                continue;
                
                Vector3 pos = Camera$$World2ScreenPoint[mainCamera](Transform$$position[hitslocal[i1]]());
                Vector3 pos2 = Camera$$World2ScreenPoint[mainCamera](Transform$$position[hitslocal[i2]]());
				Vector3 hppos = Camera$$World2ScreenPoint[mainCamera](Transform$$position[hitslocal[3]]());
                pos.y = glHeight - pos.y;
                pos2.y = glHeight - pos2.y;
				hppos.y = glHeight - hppos.y;
                if (pos.z <= 0 || pos2.z <= 0)
                continue;
                
                ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos2.x, pos2.y), GetColorU32(*(ImVec4 *)EspSkeletonColor), 3);
				if(skeletonOutline) {
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos2.x, pos2.y), ImColor(0, 0, 0), 5);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos2.x, pos2.y), GetColorU32(*(ImVec4 *)EspSkeletonColor), 3);
				}
            	if (EspSkeletonHead) {
                ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(hppos.x, hppos.y - 250 / hppos.z), 250 / hppos.z, GetColorU32(*(ImVec4 *)EspSkeletonColor), 0, 3);
				if(skeletonOutline) {
					ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(hppos.x, hppos.y - 250 / hppos.z), 250 / hppos.z, ImColor(0, 0, 0), 0, 5);
					ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(hppos.x, hppos.y - 250 / hppos.z), 250 / hppos.z, GetColorU32(*(ImVec4 *)EspSkeletonColor), 0, 3);
				}
            }
        }
    }
}
}
}
					
					/*if (espMySkeleton) {
					if (localPlayerTRHB->getPointer()) {
						auto hitbox14 = Camera$$World2ScreenPoint[Camera$$main()](Transform$$position[localPlayerTRHB->getPointer()[14]]());
						hitbox14.y = ImGui::GetIO().DisplaySize.y - hitbox14.y;
						if (hitbox14.z <= 0)
							continue;
								
						auto hitbox13 = Camera$$World2ScreenPoint[Camera$$main()](Transform$$position[localPlayerTRHB->getPointer()[13]]());
						hitbox13.y = ImGui::GetIO().DisplaySize.y - hitbox13.y;
						if (hitbox13.z <= 0)
							continue;
								
						auto hitbox12 = Camera$$World2ScreenPoint[Camera$$main()](Transform$$position[localPlayerTRHB->getPointer()[12]]());
						hitbox12.y = ImGui::GetIO().DisplaySize.y - hitbox12.y;
						if (hitbox12.z <= 0)
							continue;
								
						auto hitbox11 = Camera$$World2ScreenPoint[Camera$$main()](Transform$$position[localPlayerTRHB->getPointer()[11]]());
						hitbox11.y = ImGui::GetIO().DisplaySize.y - hitbox11.y;
						if (hitbox11.z <= 0)
							continue;
								
						auto hitbox10 = ::Camera$$World2ScreenPoint[Camera$$main()](Transform$$position[localPlayerTRHB->getPointer()[10]]());
						hitbox10.y = ImGui::GetIO().DisplaySize.y - hitbox10.y;
						if (hitbox10.z <= 0)
							continue;
							
						auto hitbox8 = Camera$$World2ScreenPoint[Camera$$main()](Transform$$position[localPlayerTRHB->getPointer()[8]]());
						hitbox8.y = ImGui::GetIO().DisplaySize.y - hitbox8.y;
						if (hitbox8.z <= 0)
							continue;
						
						auto hitbox7 = Camera$$World2ScreenPoint[Camera$$main()](Transform$$position[localPlayerTRHB->getPointer()[7]]());
						hitbox7.y = ImGui::GetIO().DisplaySize.y - hitbox7.y;
						if (hitbox7.z <= 0)
							continue;
							
						auto hitbox6 = Camera$$World2ScreenPoint[Camera$$main()](Transform$$position[localPlayerTRHB->getPointer()[6]]());
						hitbox6.y = ImGui::GetIO().DisplaySize.y - hitbox6.y;
						if (hitbox6.z <= 0)
							continue;
								
						auto hitbox5 = Camera$$World2ScreenPoint[Camera$$main()](Transform$$position[localPlayerTRHB->getPointer()[5]]());
						hitbox5.y = ImGui::GetIO().DisplaySize.y - hitbox5.y;
						if (hitbox5.z <= 0)
							continue;
							
						auto hitbox4 = Camera$$World2ScreenPoint[Camera$$main()](Transform$$position[localPlayerTRHB->getPointer()[4]]());
						hitbox4.y = ImGui::GetIO().DisplaySize.y - hitbox4.y;
						if (hitbox4.z <= 0)
							continue;
							
						auto hitbox3 = Camera$$World2ScreenPoint[Camera$$main()](Transform$$position[localPlayerTRHB->getPointer()[3]]());
						hitbox3.y = ImGui::GetIO().DisplaySize.y - hitbox3.y;
						if (hitbox3.z <= 0)
							continue;
						
						auto hitbox2 = Camera$$World2ScreenPoint[Camera$$main()](Transform$$position[localPlayerTRHB->getPointer()[2]]());
						hitbox2.y = ImGui::GetIO().DisplaySize.y - hitbox2.y;
						if (hitbox2.z <= 0)
							continue;
								
						auto hitbox1 = Camera$$World2ScreenPoint[Camera$$main() ](Transform$$position[localPlayerTRHB->getPointer()[1]]());
						hitbox1.y = ImGui::GetIO().DisplaySize.y - hitbox1.y;
						if (hitbox1.z <= 0)
							continue;
						
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox13.x, hitbox13.y), ImVec2(hitbox14.x, hitbox14.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox11.x, hitbox11.y), ImVec2(hitbox12.x, hitbox12.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox10.x, hitbox10.y), ImVec2(hitbox11.x, hitbox11.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox3.x, hitbox3.y), ImVec2(hitbox10.x, hitbox10.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox3.x, hitbox3.y), ImVec2(hitbox2.x, hitbox2.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox2.x, hitbox2.y), ImVec2(hitbox1.x, hitbox1.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox7.x, hitbox7.y), ImVec2(hitbox8.x, hitbox8.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox1.x, hitbox1.y), ImVec2(hitbox7.x, hitbox7.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox4.x, hitbox4.y), ImVec2(hitbox3.x, hitbox3.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox4.x, hitbox4.y), ImVec2(hitbox3.x, hitbox3.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox4.x, hitbox4.y), ImVec2(hitbox5.x, hitbox5.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox6.x, hitbox6.y), ImVec2(hitbox5.x, hitbox5.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(hitbox1.x, hitbox1.y), ImVec2(hitbox13.x, hitbox13.y), ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor), 2);
						ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(hitbox3.x, hitbox3.y), 4.5f, ImGui::GetColorU32(*(ImVec4 *)EspSkeletonColor));
						}
					}*/
				}
			}
			
			
		}


void DrawerESP() {
	if (!aetofeil)
		return;

	void *MainCamera = Camera$$main();
	if (MainCamera == NULL || MainCamera == nullptr || MainCamera == 0 || !MainCamera)
		return;
	
	MovementHistory();
	RenderESP();
	}

