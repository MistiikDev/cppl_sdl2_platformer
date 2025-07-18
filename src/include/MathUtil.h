class MathUtil {
    public:
        static float LerpFloat(double a, double b, float t)
        {
            return a + (b - a) * t;
        }
};