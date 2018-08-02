object Form2: TForm2
  Left = 668
  Top = 229
  BorderStyle = bsSingle
  Caption = #1054#1090#1095#1077#1090#1099
  ClientHeight = 649
  ClientWidth = 867
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 8
    Top = 48
    Width = 849
    Height = 561
    Lines.Strings = (
      'Memo1')
    TabOrder = 8
    Visible = False
  end
  object SG1: TStringGrid
    Left = 8
    Top = 48
    Width = 849
    Height = 561
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing]
    TabOrder = 0
    ColWidths = (
      39
      83
      211
      277
      207)
  end
  object CMon: TComboBox
    Left = 48
    Top = 24
    Width = 89
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Items.Strings = (
      #1071#1085#1074#1072#1088#1100
      #1060#1077#1074#1088#1072#1083#1100
      #1052#1072#1088#1090
      #1040#1087#1088#1077#1083#1100
      #1052#1072#1081
      #1048#1102#1085#1100
      #1048#1102#1083#1100
      #1040#1074#1075#1091#1089#1090
      #1057#1077#1085#1090#1103#1073#1088#1100
      #1054#1082#1090#1103#1073#1088#1100
      #1053#1086#1103#1073#1088#1100
      #1044#1077#1082#1072#1073#1088#1100)
  end
  object COffice: TComboBox
    Left = 136
    Top = 24
    Width = 209
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 2
  end
  object CTovar: TComboBox
    Left = 344
    Top = 24
    Width = 281
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 3
  end
  object Button1: TButton
    Left = 832
    Top = 24
    Width = 25
    Height = 25
    Caption = '?'
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 24
    Width = 41
    Height = 25
    Caption = '-'
    TabOrder = 5
    OnClick = Button2Click
  end
  object CCompany: TComboBox
    Left = 624
    Top = 24
    Width = 209
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 6
    Items.Strings = (
      '123'
      'qwe')
  end
  object Button3: TButton
    Left = 8
    Top = 616
    Width = 81
    Height = 25
    Caption = #1058#1077#1082#1089#1090
    TabOrder = 7
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 728
    Top = 616
    Width = 131
    Height = 25
    Caption = #1054#1090#1095#1077#1090' '#1087#1086' '#1082#1072#1073#1077#1083#1102
    TabOrder = 9
    OnClick = Button4Click
  end
  object Pan1: TPanel
    Left = 608
    Top = 288
    Width = 249
    Height = 321
    BevelWidth = 5
    Color = clSilver
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 10
    Visible = False
    DesignSize = (
      249
      321)
    object Button5: TButton
      Left = 224
      Top = 8
      Width = 17
      Height = 17
      Anchors = [akTop, akRight]
      Caption = #1061
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      TabStop = False
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 88
      Top = 280
      Width = 81
      Height = 25
      Anchors = [akBottom]
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = Button6Click
    end
    object GroupBox3: TGroupBox
      Left = 32
      Top = 24
      Width = 193
      Height = 137
      TabOrder = 0
      object Label1: TLabel
        Left = 80
        Top = 8
        Width = 26
        Height = 14
        Caption = #1054#1092#1080#1089
      end
      object Label2: TLabel
        Left = 8
        Top = 52
        Width = 31
        Height = 14
        Caption = #1052#1077#1089#1103#1094
      end
      object LE1: TLabeledEdit
        Left = 8
        Top = 107
        Width = 177
        Height = 22
        EditLabel.Width = 99
        EditLabel.Height = 14
        EditLabel.Caption = #1050#1086#1083'-'#1074#1086' '#1087#1086#1076#1082#1083#1102#1095#1077#1085#1080#1081
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 3
      end
      object CB2: TComboBox
        Left = 8
        Top = 67
        Width = 113
        Height = 22
        Style = csDropDownList
        ItemHeight = 14
        TabOrder = 1
        Items.Strings = (
          #1071#1085#1074#1072#1088#1100
          #1060#1077#1074#1088#1072#1083#1100
          #1052#1072#1088#1090
          #1040#1087#1088#1077#1083#1100
          #1052#1072#1081
          #1048#1102#1085#1100
          #1048#1102#1083#1100
          #1040#1074#1075#1091#1089#1090
          #1057#1077#1085#1090#1103#1073#1088#1100
          #1054#1082#1090#1103#1073#1088#1100
          #1053#1086#1103#1073#1088#1100
          #1044#1077#1082#1072#1073#1088#1100)
      end
      object LE2: TLabeledEdit
        Left = 128
        Top = 67
        Width = 57
        Height = 22
        EditLabel.Width = 16
        EditLabel.Height = 14
        EditLabel.Caption = #1043#1086#1076
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 2
      end
      object CB1: TComboBox
        Left = 8
        Top = 24
        Width = 177
        Height = 22
        Style = csDropDownList
        ItemHeight = 14
        TabOrder = 0
      end
    end
    object GroupBox1: TGroupBox
      Left = 32
      Top = 168
      Width = 193
      Height = 97
      TabOrder = 1
      object LE4: TLabeledEdit
        Left = 8
        Top = 67
        Width = 177
        Height = 22
        EditLabel.Width = 108
        EditLabel.Height = 14
        EditLabel.Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1085#1086' 4-'#1087#1072#1088#1082#1080
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 1
      end
      object LE3: TLabeledEdit
        Left = 8
        Top = 27
        Width = 177
        Height = 22
        EditLabel.Width = 108
        EditLabel.Height = 14
        EditLabel.Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1085#1086' 2-'#1087#1072#1088#1082#1080
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 0
      end
    end
  end
  object Sorter: TListBox
    Left = 112
    Top = 592
    Width = 241
    Height = 41
    ItemHeight = 13
    Sorted = True
    TabOrder = 11
    Visible = False
  end
end
