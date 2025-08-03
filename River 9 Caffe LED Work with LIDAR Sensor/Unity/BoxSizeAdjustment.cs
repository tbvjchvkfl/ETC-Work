using UnityEngine;
using UnityEngine.UI;

public class BoxSizeAdjustment : MonoBehaviour
{
    public GameObject SizeSlider_Obj;
    public GameObject NonSpawnBox_Obj;

    Slider zoomSlider;
    //float sliderPrevValue = 0.0f;
    float aspectRatio = 9.0f / 16.0f;
    float baseScaleX = 0.0f;
    float minScaleX = 0.0f;
    float maxScaleX = 3.2f;

    public void InitializeBoxSizeAdjustment()
    {
        if (SizeSlider_Obj)
        {
            zoomSlider = SizeSlider_Obj.GetComponent<Slider>();
            zoomSlider.minValue = -2.0f;
            zoomSlider.maxValue = 2.0f;
            zoomSlider.value = 0.0f;
            zoomSlider.onValueChanged.AddListener(OnSliderValueChanged);
        }
        if (NonSpawnBox_Obj)
        {
            baseScaleX = NonSpawnBox_Obj.transform.localScale.x;
        }
    }

    void OnSliderValueChanged(float value)
    {
        if (NonSpawnBox_Obj)
        {
            float zoomFactor = value * 1.1f;
            float newScaleX = Mathf.Clamp(baseScaleX + zoomFactor, minScaleX, maxScaleX);
            float newScaleY = newScaleX * aspectRatio;

            NonSpawnBox_Obj.transform.localScale = new Vector3(newScaleX, newScaleY, NonSpawnBox_Obj.transform.localScale.z);
        }
    }
}
