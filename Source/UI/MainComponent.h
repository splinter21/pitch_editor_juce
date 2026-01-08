#pragma once

#include "../JuceHeader.h"
#include "../Models/Project.h"
#include "../Audio/AudioEngine.h"
#include "../Audio/PitchDetector.h"
#include "../Audio/FCPEPitchDetector.h"
#include "../Audio/Vocoder.h"
#include "../Utils/UndoManager.h"
#include "ToolbarComponent.h"
#include "PianoRollComponent.h"
#include "WaveformComponent.h"
#include "ParameterPanel.h"
#include "SettingsComponent.h"

class MainComponent : public juce::Component,
                      public juce::Timer,
                      public juce::KeyListener
{
public:
    MainComponent();
    ~MainComponent() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    void timerCallback() override;
    
    // KeyListener
    bool keyPressed(const juce::KeyPress& key, juce::Component* originatingComponent) override;
    
private:
    void openFile();
    void exportFile();
    void play();
    void pause();
    void stop();
    void seek(double time);
    void resynthesize();
    void resynthesizeIncremental();  // Incremental synthesis for preview
    void showSettings();
    void applySettings();
    
    void onNoteSelected(Note* note);
    void onPitchEdited();
    void onZoomChanged(float pixelsPerSecond);
    void onScrollChanged(double scrollX);
    void onPianoRollScrollChanged(double scrollX);
    
    void loadAudioFile(const juce::File& file);
    void analyzeAudio();
    void segmentIntoNotes();
    
    void loadConfig();
    void saveConfig();
    
    void undo();
    void redo();
    void setEditMode(EditMode mode);
    
    std::unique_ptr<Project> project;
    std::unique_ptr<AudioEngine> audioEngine;
    std::unique_ptr<PitchDetector> pitchDetector;  // Fallback YIN detector
    std::unique_ptr<FCPEPitchDetector> fcpePitchDetector;  // FCPE neural network detector
    std::unique_ptr<Vocoder> vocoder;
    std::unique_ptr<PitchUndoManager> undoManager;
    
    bool useFCPE = true;  // Use FCPE by default if available
    
    ToolbarComponent toolbar;
    PianoRollComponent pianoRoll;
    WaveformComponent waveform;
    ParameterPanel parameterPanel;
    
    std::unique_ptr<SettingsDialog> settingsDialog;
    
    std::unique_ptr<juce::FileChooser> fileChooser;
    
    // Original waveform for incremental synthesis
    juce::AudioBuffer<float> originalWaveform;
    bool hasOriginalWaveform = false;
    
    bool isPlaying = false;
    
    // Sync flags to prevent infinite loops
    bool isSyncingScroll = false;
    bool isSyncingZoom = false;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
