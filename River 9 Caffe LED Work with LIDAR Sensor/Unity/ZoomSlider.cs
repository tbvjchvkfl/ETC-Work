using UnityEngine;
using UnityEngine.UI;

public class ZoomSlider : MonoBehaviour
{
    public GameObject ZoomSlider_Obj;
    public GameObject MainCamera_Obj;

    public void InitializeZoomSlider()
    {
        if (ZoomSlider_Obj)
        {
            Slider zoomSlider = ZoomSlider_Obj.GetComponent<Slider>();
            zoomSlider.minValue = 10.0f;
            zoomSlider.maxValue = 30.0f;
            zoomSlider.value = 30.0f;
            zoomSlider.onValueChanged.AddListener(OnSliderValueChanged);
        }
    }

    void OnSliderValueChanged(float value)
    {
        if (MainCamera_Obj)
        {
            MainCamera_Obj.transform.position = new Vector3(MainCamera_Obj.transform.position.x, value, MainCamera_Obj.transform.position.z);
        }
    }
}
