/*
 * Copyright (C) 2017 Emmanuel Durand
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
 * @sink.h
 * The Sink base class
 */

#ifndef SPLASH_SINK_H
#define SPLASH_SINK_H

#include <future>
#include <memory>
#include <mutex>

#include "./core/constants.h"

#include "./core/attribute.h"
#include "./core/graph_object.h"
#include "./graphics/filter.h"
#include "./utils/resizable_array.h"

namespace Splash
{

class Sink : public GraphObject
{
  public:
    /**
     * Constructor
     */
    explicit Sink(RootObject* root);

    /**
     * Destructor
     */
    virtual ~Sink() override;

    /**
     * Constructors/operators
     */
    Sink(const Sink&) = delete;
    Sink& operator=(const Sink&) = delete;
    Sink(Sink&&) = delete;
    Sink& operator=(Sink&&) = delete;

    /**
     * Get the current buffer as a resizable array
     * \return Return the buffer
     */
    ResizableArray<uint8_t> getBuffer() const { return _buffer; };

    /**
     * Generate a caps from the input texture spec
     * \return Return the generated caps
     */
    std::string getCaps() const;

    /**
     * Get the current buffer spec type
     * \return Return the buffer spec type
     */
    ImageBufferSpec getSpec() const { return _spec; };

    /**
     * Update the inner buffer of the sink
     */
    void update() override;

    /**
     * Send the inner buffer to the sink's output
     */
    void render() override;

  protected:
    uint32_t _framerate{30}; //!< Maximum framerate
    bool _sixteenBpc{false};
    int _captureSize[2]{512, 512};
    bool _keepRatio{false};

    /**
     * Try to link the given GraphObject to this object
     * \param obj Shared pointer to the (wannabe) child object
     */
    bool linkIt(const std::shared_ptr<GraphObject>& obj) override;

    /**
     * Try to unlink the given GraphObject from this object
     * \param obj Shared pointer to the (supposed) child object
     */
    void unlinkIt(const std::shared_ptr<GraphObject>& obj) override;

    /**
     * Register new functors to modify attributes
     */
    void registerAttributes();

  private:
    std::shared_ptr<Filter> _inputFilter{nullptr};
    ImageBufferSpec _spec{};
    ImageBuffer _image{};
    std::mutex _lockPixels{};
    ResizableArray<uint8_t> _buffer{};

    bool _opened{false}; //!< If true, the sink lets frames through

    uint64_t _lastFrameTiming{0};
    uint32_t _pboCount{3};
    std::vector<GLuint> _pbos{};
    int _pboWriteIndex{0};
    GLubyte* _mappedPixels{nullptr};

    /**
     * Class to be implemented to copy the _mappedPixels somewhere
     */
    virtual void handlePixels(const char* pixels, const ImageBufferSpec& spec);

    /**
     * Update the pbos according to the parameters
     * \param width Width
     * \param height Height
     * \param bytes Bytes per pixel
     */
    void updatePbos(int width, int height, int bytes);
};

} // namespace Splash

#endif
