﻿#pragma once
#include <glm/glm.hpp>

#include <renderer/Texture.h>
#include <util/ImageLoader.h>

#include "util/audioAnalyzer/SpectrumPreProcessor.h"
#include "transition/Transition.h"
#include "editor/Configurable.h"

/*
 * Settings:
 *		Image directory
 *		Image duration
 *		Transition
 *		Audio peak amplifier
 *	Advanced:
 *		Audio base amplifier
 */

class SlideShow : public Configurable {
public:
	SlideShow(Spectrum* spectrum);
	~SlideShow();

	void update(float dt);
	void render(glm::mat4 projection) const;

	// settings
	void loadSettings(boost::property_tree::ptree& configuration) override;
	void setImageDirectory(const std::string& imageDirectory);

	#if SHOW_EDITOR
	void setImageDuration(int duration);
	void setTransition(Transition* transition);
	void setTransitionDuration(float transitionDuration) const;
	void setAudioResponseEnable(bool audioResponseEnable);
	void setBassPeakAmplifier(float peakAmplifier);
	void setHighPeakAmplifier(float peakAmplifier);
	void setBassBaseAmplifier(float baseAmplifier);
	void setHighBaseAmplifier(float baseAmplifier);
#endif


private:

	bool m_swapEnable = false;
	int m_imageDuration = 0;
	float m_dtAccumulated = 0, m_updateInterval = 0;
	Transition* m_transition = nullptr;
	JApp::ImageLoader* m_imageLoader = nullptr;
	JApp::Renderer::Texture *m_currentTexture = nullptr, *m_nextTexture = nullptr;
	std::string m_imageDirectory = "";
	std::vector<std::string> m_filePaths = std::vector<std::string>();

	bool m_audioResponseEnable = false;
	Spectrum* m_audioSpectrum;
	float m_bassBaseAmplifier = 0.f, m_bassPeakAmplifier = 0.f;
	float m_highBaseAmplifier = 0.f, m_highPeakAmplifier = 0.f;

	void scanDirectory(const std::string& directory);

	void preLoadFirstImage(const std::string& path);
	void preLoadImage(const std::string& path);
	void firstImage();
	void nextImage();
	std::string randomImage();
};