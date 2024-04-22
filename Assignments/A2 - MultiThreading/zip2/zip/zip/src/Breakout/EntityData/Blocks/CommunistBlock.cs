using DIKUArcade.Graphics;
using DIKUArcade.Entities;

namespace Breakout.EntityData.Blocks {
    public class CommunistBlock : Block {
        private int hitpoints;
        private string Name;
        public override int GetHitpoints {
            get {return hitpoints;}
        }
        public CommunistBlock (StationaryShape shape, IBaseImage image, string name) : base(shape, image, name) {
            hitpoints = 10;
            Image = image;
            Name = name;
        }
        
        /// <summary>
        /// subtracts lifes from all communist blocks together
        /// </summary>
        public override void Hit (EntityContainer<Block> blocks) {
            foreach (Block block in blocks) {
                if (block.GetName == this.GetName ) {
                    block.SpecialEffect(); 
                }
                if (hitpoints == 0) {
                    this.DeleteEntity();
                }
            }
        }
        public override void SpecialEffect () {
            hitpoints--;
        }
    }
}