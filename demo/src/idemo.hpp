/*! @file
 *  @brief Demo interface.
 *  @author Igor Sharonov
 *  @date 2022-04-08
 */

#pragma once

#include <filesystem>
#include <vector>
#include <string>

//! Demo interface class.
class idemo
{
public:
    //! Get vector of demos.
    static auto& get_global_registry()
    {
        static std::vector<idemo*> registry;
        return registry;
    }

    //! Construct demo with name.
    idemo(const std::string& name) : name_(name)
    {
        auto& reg = get_global_registry();
        // At least C++11.
        reg.push_back(this);
    }

    /*! @brief Prepare input parameters for demo.
     *  @param[in] resource_dir directory with images
     */
    virtual void prepare(const std::filesystem::path& resource_dir) = 0;

    //! Execute OpenCV kernel for illustration.
    virtual void execute_opencv() = 0;

    //! Execute OpenVX kernel.
    virtual void execute_openvx() = 0;

    //! Make difference of OpenCV and OpenVX output images.
    virtual void make_diff() = 0;

    virtual ~idemo()
    {
    }

    //! Returns demo name.
    const std::string& to_string() const
    {
        return name_;
    }

private:
    std::string name_; //!< Saved demo name.
};
