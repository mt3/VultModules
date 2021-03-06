
#include "VultModules.hpp"
#include "math.hpp"
#include "VultEngine.h"

struct Splie : Module
{
   enum ParamIds
   {
      NUM_PARAMS
   };
   enum InputIds
   {
      IN_A,
      IN_B,
      NUM_INPUTS
   };
   enum OutputIds
   {
      OUT1_A,
      OUT2_A,
      OUT3_A,
      OUT1_B,
      OUT2_B,
      OUT3_B,
      NUM_OUTPUTS
   };

   Splie();
   void step();
};

Splie::Splie() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS)
{
   params.resize(NUM_PARAMS);
   inputs.resize(NUM_INPUTS);
   outputs.resize(NUM_OUTPUTS);
}

void Splie::step()
{

   float in_a = inputs[IN_A].value;
   float in_b = inputs[IN_B].value;

   outputs[OUT1_A].value = in_a;
   outputs[OUT2_A].value = in_a;
   outputs[OUT3_A].value = in_a;

   outputs[OUT1_B].value = in_b;
   outputs[OUT2_B].value = in_b;
   outputs[OUT3_B].value = in_b;
}

SplieWidget::SplieWidget()
{
   Splie *module = new Splie();
   setModule(module);
   box.size = Vec(45, 380);

   {
      SVGPanel *panel = new SVGPanel();
      panel->box.size = box.size;
      panel->setBackground(SVG::load(assetPlugin(plugin, "res/Splie.svg")));
      addChild(panel);
   }
   addChild(createScrew<VultScrew>(Vec(15, 0)));
   addChild(createScrew<VultScrew>(Vec(15, 365)));

   addInput(createInput<VultJack>(Vec(11, 43), module, Splie::IN_A));
   addOutput(createOutput<VultJack>(Vec(11, 80), module, Splie::OUT1_A));
   addOutput(createOutput<VultJack>(Vec(11, 117), module, Splie::OUT2_A));
   addOutput(createOutput<VultJack>(Vec(11, 154), module, Splie::OUT3_A));

   addInput(createInput<VultJack>(Vec(11, 186), module, Splie::IN_B));
   addOutput(createOutput<VultJack>(Vec(11, 223), module, Splie::OUT1_B));
   addOutput(createOutput<VultJack>(Vec(11, 260), module, Splie::OUT2_B));
   addOutput(createOutput<VultJack>(Vec(11, 298), module, Splie::OUT3_B));
}
