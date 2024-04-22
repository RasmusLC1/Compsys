using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using System.IO;

namespace Breakout.EntityData.Blocks {
    public class HardenedBlock : Block {
        private int hitpoints;
        private string Name;
        public override int GetHitpoints {
            get {return hitpoints;}
        }

        public HardenedBlock (StationaryShape shape, IBaseImage image, string name) : base(shape, image, name) {
            hitpoints = 2;
            Image = image;
            Name = name;
        }

        /// <summary>
        /// Method to subtract hitpoints from block, 
        /// change the image if hitpoints is 1
        /// and deletes it if 0.
        /// </summary>
        public override void Hit (EntityContainer<Block> blocks) {
            hitpoints --;
            if (hitpoints == 1) {
                Image = new Image(Path.Combine("Assets", "Images", Name.Insert(Name.IndexOf(".png"), "-damaged")));
            } else if (hitpoints == 0) {
                this.DeleteEntity();
            }
        }
    }
}