using DIKUArcade.Entities;
using DIKUArcade.Math;

namespace Breakout.Factories {
    public interface IFactory {
        public Entity Build(Vec2F Position);
    }
}