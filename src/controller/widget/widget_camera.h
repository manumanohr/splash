/*
 * Copyright (C) 2014 Splash authors
 *
 * This file is part of Splash.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Splash is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Splash.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * @widget_camera.h
 * The camera widget, to calibrate cameras
 */

#ifndef SPLASH_WIDGET_GLOBAL_VIEW_H
#define SPLASH_WIDGET_GLOBAL_VIEW_H

#include "./controller/widget/widget.h"
#include "./graphics/camera.h"

namespace Splash
{

/*************/
class GuiCamera : public GuiWidget
{
  public:
    GuiCamera(Scene* scene, const std::string& name = "");
    void render() final;
    void update() final;
    int updateWindowFlags() final;
    std::optional<std::string> getActiveObjectName() const final { return _camera ? _camera->getName() : std::optional<std::string>(); }
    void setJoystick(const std::vector<float>& axes, const std::vector<uint8_t>& buttons);

  protected:
    bool linkIt(const std::shared_ptr<GraphObject>& obj) final;
    void unlinkIt(const std::shared_ptr<GraphObject>& obj) final;

  private:
    std::shared_ptr<Camera> _camera{nullptr};
    std::shared_ptr<Camera> _overviewCamera{nullptr};
    bool _rendered{false};
    bool _camerasHidden{false};
    bool _noMove{false};

    bool _hideCameras{false};
    bool _showCalibrationPoints{true};
    bool _camerasColorized{false};
    bool _camerasColorizedPreviousValue{false};
    bool _joystickActivated{false};

    // Size of the view
    int _camWidth{0}, _camHeight{0};

    // Joystick state
    bool _joystickCaptured{false};
    std::mutex _joystickMutex{};
    std::vector<float> _joyAxes{};
    std::vector<uint8_t> _joyButtons{};
    std::vector<uint8_t> _joyButtonsPrevious{};

    // Store the previous camera values
    struct CameraParameters
    {
        Values eye, target, up, fov, principalPoint;
    };
    std::vector<CameraParameters> _previousCameraParameters;
    Values _newTarget;
    float _newTargetDistance{1.f};

    // Previous point added
    Values _previousPointAdded;

    /**
     * Capture joystick
     */
    void captureJoystick();

    /**
     * Release joystick
     */
    void releaseJoystick();

    void processJoystickState();
    void processKeyEvents();
    void processMouseEvents();

    // Actions
    /**
     * Activate the colorization of the wireframe rendering
     * \param colorize If true, activate the colorization
     */
    void colorizeCameraWireframes(bool colorize);

    /**
     * Call camera's calibration method, after saving the current state
     */
    void doCalibration();

    /**
     * Hide all cameras except for the selected one
     * \param hide Hide cameras if true
     */
    void hideOtherCameras(bool hide);

    void nextCamera();
    void revertCalibration();
    void showAllCalibrationPoints(Camera::CalibrationPointsVisibility showPoints = Camera::CalibrationPointsVisibility::switchVisibility);
    void showAllCamerasCalibrationPoints();

    // Other
    std::vector<glm::dmat4> getCamerasRTMatrices();
    std::vector<std::shared_ptr<Camera>> getCameras();
    void drawVirtualProbes();
};

} // namespace Splash

#endif
