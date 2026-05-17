#include "plugin.hpp"

struct Xenizer : Module
{
    enum ParamId
    {
        SCALE_PARAM,
        PARAMS_LEN
    };
    enum InputId
    {
        PITCH_INPUT,
        INPUTS_LEN
    };
    enum OutputId
    {
        PITCH_OUTPUT,
        OUTPUTS_LEN
    };

    Xenizer()
    {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN);
        configParam(SCALE_PARAM, 0.f, 2.f, 0.f, "Scale");
        paramQuantities[SCALE_PARAM]->snapEnabled = true;
        configInput(PITCH_INPUT, "Pitch");
        configOutput(PITCH_OUTPUT, "Pitch");
    }

    void process(const ProcessArgs &args) override
    {
        // Phase 1: passthrough. Real quantizer logic lands in Phase 2.
        outputs[PITCH_OUTPUT].setVoltage(inputs[PITCH_INPUT].getVoltage());
    }
};


struct XenizerWidget : ModuleWidget
{
    XenizerWidget(Xenizer *module)
    {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Xenizer.svg")));

        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 35)), module, Xenizer::SCALE_PARAM));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.16, 95)), module, Xenizer::PITCH_INPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 115)), module, Xenizer::PITCH_OUTPUT));
    }
};

Model *modelXenizer = createModel<Xenizer, XenizerWidget>("Xenizer");
