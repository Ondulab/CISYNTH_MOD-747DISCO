#ifndef DWAVESCREENPRESENTER_HPP
#define DWAVESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class dWaveScreenView;

class dWaveScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    dWaveScreenPresenter(dWaveScreenView& v);

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

    virtual ~dWaveScreenPresenter() {};

private:
    dWaveScreenPresenter();

    dWaveScreenView& view;
};

#endif // DWAVESCREENPRESENTER_HPP
