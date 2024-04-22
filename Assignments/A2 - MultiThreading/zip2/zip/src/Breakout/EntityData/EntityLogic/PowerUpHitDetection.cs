using DIKUArcade.Physics;
using Breakout.EntityData.PowerUps;

namespace Breakout.EntityData.EntityLogic {
    public class PowerUpHitDetection {
        
        /// <summary>
        /// Handles the individual PowerUp logic and updates them
        /// </summary>
        /// <param name="powerUp">individual powerUp</param>
        public void HitDetection(PowerUp powerUp, Player player) {
            powerUp.Move();
            if (CollisionDetection.Aabb(powerUp.Shape.AsDynamicShape(), player.Shape).Collision) {
                powerUp.Effect();
            }
        }
    }
}