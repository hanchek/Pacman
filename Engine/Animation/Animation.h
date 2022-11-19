#pragma once

class RenderComponent;

class Animation
{
public:
    virtual ~Animation() = default;

    // t should be in [0, 1] range
    virtual void ApplyAnimation(float t , RenderComponent& renderComponent) const = 0;

    const std::string& GetName() const { return myName; }
    void SetName(const std::string& name) { myName = name; }

private:
    std::string myName;
};