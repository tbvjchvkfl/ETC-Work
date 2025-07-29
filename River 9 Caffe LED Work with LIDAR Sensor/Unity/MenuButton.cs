using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class MenuButton : MonoBehaviour
{
    public TMP_Text ButtonText;

    public delegate void MenuButtonClickedDelegate(TMP_Text TitleString);
    public event MenuButtonClickedDelegate OnMenuButtonClicked;

    int buttonIndex;
    Button MenuBtn;

    public void InitializeMenuButton(int ButtonIndex)
    {
        buttonIndex = ButtonIndex;
        MenuBtn = GetComponent<Button>();
        if (MenuBtn)
        {
            MenuBtn.onClick.AddListener(OnClickedMenuButton);
        }
    }

    void OnClickedMenuButton()
    {
        OnMenuButtonClicked?.Invoke(ButtonText);
        //SceneManager.LoadScene()
    }
}
