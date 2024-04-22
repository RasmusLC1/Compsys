using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using DIKUArcade.Math;

namespace Breakout.EntityData.PowerUps {
    public abstract class PowerUp : Entity {
        internal bool IsActive;
        public bool GetIsActive{
            get {return IsActive;}
        }
        
        public PowerUp (DynamicShape shape, IBaseImage image) : base(shape, image) {
            Shape = shape;
            Shape.AsDynamicShape().Direction = new Vec2F (0.0f, -0.006f);
            IsActive = false;
        }

        /// <summary>
        /// Moves the powerUp downwards, individually calculated for each powerup
        /// </summary>
        public void Move () { 
            Shape.AsDynamicShape().Move();
            if (Shape.Position.Y <= 0.00f) {
                this.DeleteEntity();
            }
        }
        public abstract void Effect ();
        public abstract void SpecialEffect();
    }
}