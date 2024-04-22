using DIKUArcade.Graphics;
using DIKUArcade.Entities;

namespace Breakout.EntityData.Blocks {
    public class SwitchBlock : Block {
        private int hitpoints;
        private string Name;
        int n = 0;
        public override int GetHitpoints {
            get {return hitpoints;}
        }

        public SwitchBlock (StationaryShape shape, IBaseImage image, string name) : base(shape, image, name) {
            hitpoints = 1;
            Image = image;
            Name = name;
        }

        /// <summary>
        /// deletes all unbreakableBlocks and sets the n value to 1 so it only does the loop once
        /// </summary>
        public override void Hit (EntityContainer<Block> blocks) {
            hitpoints--;
            if (n != 1) {
                foreach (Block block in blocks) {
                    if (block is UnbreakableBlock) {
                        block.SpecialEffect();
                    } else if (block is SwitchBlock) {
                        n = 1;
                    }
                }
            }
            if (hitpoints == 0) {
                this.DeleteEntity();
            }
        }
    }
}