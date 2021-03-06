
#include "VultModules.hpp"
#include "math.hpp"
#include "VultEngine.h"

struct Lateralus : Module
{
   enum ParamIds
   {
      CUTOFF_PARAM,
      RESONANCE_PARAM,
      CUTOFF_AMT_PARAM,
      RESONANCE_AMT_PARAM,
      NUM_PARAMS
   };
   enum InputIds
   {
      AUDIO_INPUT,
      CUTOFF_INPUT,
      RESONANCE_INPUT,
      NUM_INPUTS
   };
   enum OutputIds
   {
      DB12_OUTPUT,
      DB24_OUTPUT,
      NUM_OUTPUTS
   };

   VultEngine_lateralus_type processor;

   Lateralus();
   void step();
};

Lateralus::Lateralus() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS)
{
   params.resize(NUM_PARAMS);
   inputs.resize(NUM_INPUTS);
   outputs.resize(NUM_OUTPUTS);
   VultEngine_lateralus_init(processor);
}

void Lateralus::step()
{

   float audio = inputs[AUDIO_INPUT].value / 7.0;

   float cutoff_knob = params[CUTOFF_PARAM].value;
   float cutoff_cv = inputs[CUTOFF_INPUT].value / 5.0;
   float cutoff_amt = params[CUTOFF_AMT_PARAM].value;
   float cutoff = cutoff_knob + cutoff_amt * cutoff_cv;

   float resonance_knob = params[RESONANCE_PARAM].value;
   float resonance_cv = inputs[RESONANCE_INPUT].value / 5.0;
   float resonance_amt = params[RESONANCE_AMT_PARAM].value;
   float resonance = resonance_knob + resonance_amt * resonance_cv;

   _tuple___real_real__ out;
   VultEngine_lateralus(processor, audio, cutoff, resonance, out);

   outputs[DB12_OUTPUT].value = out.field_0 * 7.0;

   outputs[DB24_OUTPUT].value = out.field_1 * 7.0;
}

LateralusWidget::LateralusWidget()
{
   Lateralus *module = new Lateralus();
   setModule(module);
   box.size = Vec(15 * 10, 380);

   {
      SVGPanel *panel = new SVGPanel();
      panel->box.size = box.size;
      panel->setBackground(SVG::load(assetPlugin(plugin, "res/Lateralus.svg")));
      addChild(panel);
   }
   addChild(createScrew<VultScrew>(Vec(15, 0)));
   addChild(createScrew<VultScrew>(Vec(box.size.x - 30, 0)));
   addChild(createScrew<VultScrew>(Vec(15, 365)));
   addChild(createScrew<VultScrew>(Vec(box.size.x - 30, 365)));

   addParam(createParam<VultKnobBig>(Vec(25, 75), module, Lateralus::CUTOFF_PARAM, 0.0, 1.0, 0.5));
   addParam(createParam<VultKnob>(Vec(34, 173), module, Lateralus::RESONANCE_PARAM, 0.0, 1.0, 0.0));

   addParam(createParam<VultKnobSmall>(Vec(108, 82), module, Lateralus::CUTOFF_AMT_PARAM, -1.0, 1.0, 0.0));
   addParam(createParam<VultKnobSmall>(Vec(108, 173), module, Lateralus::RESONANCE_AMT_PARAM, -1.0, 1.0, 0.0));

   addInput(createInput<VultJack>(Vec(105, 107), module, Lateralus::CUTOFF_INPUT));
   addInput(createInput<VultJack>(Vec(105, 198), module, Lateralus::RESONANCE_INPUT));

   addInput(createInput<VultJack>(Vec(63, 318), module, Lateralus::AUDIO_INPUT));

   addOutput(createOutput<VultJack>(Vec(27, 253), module, Lateralus::DB12_OUTPUT));
   addOutput(createOutput<VultJack>(Vec(105, 253), module, Lateralus::DB24_OUTPUT));
}
