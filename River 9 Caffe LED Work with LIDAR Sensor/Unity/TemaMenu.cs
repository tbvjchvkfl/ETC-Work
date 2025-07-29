using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class TemaMenu : MonoBehaviour
{
    [Header("UI Component")]
    public Image Arrow_Img;
    public TMP_Text Main_Txt;

    [Header("Object Component")]
    public Button Main_Btn;
    public GameObject MenuPanel;
    public List<GameObject> MenuButtonList = new List<GameObject>();

    bool bIsMainButtonClicked = false;

    void Update()
    {
        
    }

    public void InitializeTemaMenu()
    {
        for (int i = 0; i < MenuButtonList.Count; i++)
        {
            MenuButtonList[i].GetComponent<MenuButton>().InitializeMenuButton(i);
            MenuButtonList[i].GetComponent<MenuButton>().OnMenuButtonClicked -= OnClickedMenuButton;
            MenuButtonList[i].GetComponent<MenuButton>().OnMenuButtonClicked += OnClickedMenuButton;
        }
        if (MenuPanel && Main_Btn)
        {
            MenuPanel.SetActive(false);
            Main_Btn.onClick.AddListener(OnClickedMainButton);
        }
    }

    void OnClickedMainButton()
    {
        if (bIsMainButtonClicked)
        {
            bIsMainButtonClicked = false;
            StartCoroutine(ResetButtonArrow());
            
        }
        else
        {
            bIsMainButtonClicked = true;
            StartCoroutine(ButtonArrowRotation());
        }
        ToggleMenuPanel();
    }

    void OnClickedMenuButton(TMP_Text TitleString)
    {
        StartCoroutine(ResetButtonArrow());
        ToggleMenuPanel();
        Main_Txt.text = TitleString.text;
    }

    IEnumerator ButtonArrowRotation()
    {
        if (Arrow_Img)
        {
            while (Arrow_Img.transform.rotation.eulerAngles.z < 180.0f)
            {
                yield return null;
                Arrow_Img.transform.rotation = Quaternion.Slerp(Arrow_Img.transform.rotation, Quaternion.Euler(0, 0, 180.0f), Time.deltaTime * 2.0f);
            }
            Arrow_Img.transform.rotation = Quaternion.Euler(0, 0, 180.0f);
        }
    }

    IEnumerator ResetButtonArrow()
    {
        if(Arrow_Img)
        {
            while (Arrow_Img.transform.rotation.eulerAngles.z > 0.0f)
            {
                yield return null;
                Arrow_Img.transform.rotation = Quaternion.Slerp(Arrow_Img.transform.rotation, Quaternion.Euler(0, 0, 0.0f), Time.deltaTime * 2.0f);
            }
            Arrow_Img.transform.rotation = Quaternion.Euler(0, 0, 0.0f);
        }
    }

    void ToggleMenuPanel()
    {
        if(MenuPanel.activeSelf)
        {
            MenuPanel.SetActive(false);
        }
        else
        {
            MenuPanel.SetActive(true);
        }
    }
}
