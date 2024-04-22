using DIKUArcade.Graphics;
using DIKUArcade.Entities;

namespace Breakout.EntityData.Blocks {
    public class DefaultBlock : Block {
        private int hitpoints;
        private string Name;
        public override int GetHitpoints {
            get {return hitpoints;}
        }
        
        public DefaultBlock (StationaryShape shape, IBaseImage image, string name) : base(shape, image, name) {
            hitpoints = 1;
            this.Image = image;
            this.Name = name;
        }
        
        /// <summary>
        /// Method to subtract hitpoints from block and deletes it if 0.
        /// </summary>
        public override void Hit (EntityContainer<Block> blocks) {
            hitpoints--;
            if (hitpoints == 0) {
                this.DeleteEntity();
            }
        }
    }
}