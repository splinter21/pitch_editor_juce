#pragma once

#include "../JuceHeader.h"
#include "../Utils/Constants.h"

// Forward declaration - EditMode is defined in PianoRollComponent.h
enum class EditMode;

class ToolbarComponent : public juce::Component,
                         public juce::Button::Listener,
                         public juce::Slider::Listener
{
public:
    ToolbarComponent();
    ~ToolbarComponent() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    
    void setPlaying(bool playing);
    void setCurrentTime(double time);
    void setTotalTime(double time);
    void setEditMode(EditMode mode);
    void setZoom(float pixelsPerSecond);  // Update zoom slider without triggering callback
    
    // Progress bar control
    void showProgress(const juce::String& message);
    void hideProgress();
    void setProgress(float progress);  // 0.0 to 1.0, or -1 for indeterminate
    
    std::function<void()> onPlay;
    std::function<void()> onPause;
    std::function<void()> onStop;
    std::function<void()> onOpenFile;
    std::function<void()> onExportFile;
    std::function<void()> onResynthesize;
    std::function<void()> onSettings;
    std::function<void(float)> onZoomChanged;
    std::function<void(EditMode)> onEditModeChanged;
    
private:
    void updateTimeDisplay();
    juce::String formatTime(double seconds);
    
    juce::TextButton openButton { "Open" };
    juce::TextButton exportButton { "Export" };
    
    juce::TextButton playButton { "Play" };
    juce::TextButton stopButton { "Stop" };
    juce::TextButton resynthButton { "Resynth" };
    juce::TextButton settingsButton { "Settings" };
    
    // Edit mode buttons
    juce::TextButton selectModeButton { "Select" };
    juce::TextButton drawModeButton { "Draw" };
    
    juce::Label timeLabel;
    
    juce::Slider zoomSlider;
    juce::Label zoomLabel { {}, "Zoom:" };
    
    // Progress components
    double progressValue = 0.0;  // Must be declared before progressBar
    juce::ProgressBar progressBar { progressValue };
    juce::Label progressLabel;
    bool showingProgress = false;
    
    double currentTime = 0.0;
    double totalTime = 0.0;
    bool isPlaying = false;
    int currentEditModeInt = 0;  // 0 = Select, 1 = Draw
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToolbarComponent)
};
