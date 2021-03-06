﻿#pragma once
#if SHOW_EDITOR

#include <boost/property_tree/ptree.hpp>

#include "UltimateWallpaper.h"

class Editor : public UltimateWallpaper {
public:
	explicit Editor(boost::property_tree::ptree& configuration);
	~Editor();

	void render() override;
	void renderSlideShowSettings(float speedMod);
	void renderEqualizerSettings(float speedMod);
	void renderParticleEffectSettings(float speedMod);

	void loadSettings(const std::string& name);
	void saveSettings(const std::string& name) const;

private:
	boost::property_tree::ptree m_cfg;
	char* m_currentName = "cfg";
	bool m_fpsCounterEnableOverride;
	bool m_gridEnable = true;
	glm::vec4 m_gridColor = glm::vec4(0.f, 0.f, 0.f, 1.f);

	Renderer::Shader* m_gridShader;
	Renderer::Mesh* m_gridMesh;
};

#endif