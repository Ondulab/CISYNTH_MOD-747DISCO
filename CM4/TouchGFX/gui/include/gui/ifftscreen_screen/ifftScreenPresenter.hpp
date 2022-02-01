#ifndef IFFTSCREENPRESENTER_HPP
#define IFFTSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ifftScreenView;

class ifftScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ifftScreenPresenter(ifftScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ifftScreenPresenter() {};

private:
    ifftScreenPresenter();

    ifftScreenView& view;
};

#endif // IFFTSCREENPRESENTER_HPP
