#include <cogra/ui/TimeControlUI.h>
#include <cogra/ui/TimeControl.h>
#include <imgui/imgui.h>
namespace cogra
{
namespace ui
{
void TimeControlUI::drawUI(TimeControl & timeControl)
{        
    if(timeControl.isPause() || timeControl.isStop())
    {
        if(ImGui::Button("Play"))
        {
            timeControl.play();
        }
    }
    else
    {
        if(ImGui::Button("Pause"))
        {
            timeControl.pause();
        }
    }
    ImGui::SameLine();
    if(ImGui::Button("Stop"))
    {
        timeControl.stop();
    }
    if(timeControl.isPeriodic())
    {
        auto t = static_cast<float32>(timeControl.getTime());
        if(ImGui::SliderFloat("Timer", &t, 0, static_cast<float32>(timeControl.getPeriode())))
        {
            timeControl.setTime(t);
        }

    }
    else
    {
        ImGui::SameLine();
        ImGui::Text("%f", timeControl.getTime());
    }

    auto s = static_cast<float32>(timeControl.getSpeed());
    if(ImGui::SliderFloat("Speed", &s, 0, 4.0f))
    {
        timeControl.setSpeed(s);
    }
}
}
}