using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using System.IO;

namespace Breakout.EntityData.Blocks {
    public class InvisibleBlock : Block {
        private int hitpoints;
        private string Name;
        private int n = 0;
        public override int GetHitpoints {
            get {return hitpoints;}
        }
        public InvisibleBlock (StationaryShape shape, IBaseImage image, string name) : base(shape, image, name) {
            hitpoints = 1;
            Name = name;
            Image = new Image (Path.Combine("Assets", "Images", "Blank.png"));
        }
        
        /// <summary>
        /// Detects the amount of hitpoints and 
        /// </summary>
        public override void Hit (EntityContainer<Block> blocks) {
            hitpoints --;
            if (n != 1) {
                blocks.Iterate(block =>{
                    if (block.GetName == this.Name) {
                        block.SpecialEffect(); 
                    }          
                });
            }
            if (this.hitpoints == 0) {
                this.DeleteEntity();
            }
        }

        public override void SpecialEffect () {
            Image = new Image (Path.Combine("Assets", "Images", Name));
            n = 1;
        }
    }
}