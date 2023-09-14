/*
 * Copyright (C) 2013 Emmanuel Durand
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
 * @texture.h
 * The Texture base class
 */

#ifndef SPLASH_TEXTURE_H
#define SPLASH_TEXTURE_H

#include <chrono>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "./core/constants.h"

#include "./core/attribute.h"
#include "./core/graph_object.h"
#include "./core/imagebuffer.h"

namespace Splash
{

class Texture : public GraphObject
{
  public:
    /**
     *  Constructor
     * \param root Root object
     */
    explicit Texture(RootObject* root);

    /**
     *  Destructor
     */
    virtual ~Texture() override;

    /**
     * Constructors/operators
     */
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&&) = delete;
    Texture& operator=(Texture&&) = delete;

    /**
     *  Bind this texture
     */
    virtual void bind() = 0;

    /**
     *  Unbind this texture
     */
    virtual void unbind() = 0;

    /**
     * Get the shader parameters related to this texture. Texture should be locked first.
     * The uniform should at least define the "size" attribute of the texture.
     * \return Return the shader uniforms
     */
    virtual std::unordered_map<std::string, Values> getShaderUniforms() const = 0;

    /**
     *  Get spec of the texture
     * \return Return the texture spec
     */
    virtual ImageBufferSpec getSpec() const { return _spec; }

    /**
     * Get the output texture GL id
     * \return Return the id
     */
    virtual GLuint getTexId() const = 0;

    /**
     *  Get the prefix for the glsl sampler name
     */
    virtual std::string getPrefix() const { return "_tex"; }

    /**
     * Get the timestamp
     * \return Return the timestamp in us
     */
    virtual int64_t getTimestamp() const override { return _spec.timestamp; }

    /**
     * Set the timestamp
     * \param timestamp Timestamp, in us
     */
    virtual void setTimestamp(int64_t timestamp) override { _spec.timestamp = timestamp; }

    /**
     *  Set whether the texture should be resizable
     * \param resizable If true, the texture is resizable
     */
    void setResizable(bool resizable) { _resizable = resizable; }

  protected:
    ImageBufferSpec _spec;

    // Store some texture parameters
    bool _resizable{true};

    /**
     *  Register new functors to modify attributes
     */
    void registerAttributes();
};

} // namespace Splash

#endif // SPLASH_TEXTURE_H
