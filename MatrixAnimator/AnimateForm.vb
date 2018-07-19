Public Class AnimateForm

    'Copyright 2018

    'Permission Is hereby granted, free of charge, to any person obtaining a 
    'copy of this software And associated documentation files (the "Software"), 
    'to deal in the Software without restriction, including without limitation 
    'the rights To use, copy, modify, merge, publish, distribute, sublicense, 
    'And/Or sell copies of the Software, And to permit persons to whom the 
    'Software Is furnished to do so, subject to the following conditions:

    'The above copyright notice And this permission notice shall be included 
    'in all copies Or substantial portions of the Software.

    'THE SOFTWARE Is PROVIDED "AS IS", WITHOUT WARRANTY Of ANY KIND, EXPRESS 
    'Or IMPLIED, INCLUDING BUT Not LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
    'FITNESS FOR A PARTICULAR PURPOSE And NONINFRINGEMENT. IN NO EVENT SHALL THE 
    'AUTHORS Or COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES Or OTHER 
    'LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT Or OTHERWISE, ARISING 
    'FROM, OUT OF Or IN CONNECTION WITH THE SOFTWARE Or THE USE Or OTHER DEALINGS 
    'IN THE SOFTWARE.


    'Global vars
    Dim frameCount As Integer = 0
    Dim anim As New System.Text.StringBuilder() 'Final animation !not stringified!

    Private Sub ExportBtn_Click(sender As Object, e As EventArgs) Handles ExportBtn.Click

        '                                           j                   i
        '                                A  B  C  D  E  F  G  H
        Dim matrix = New Integer(7, 7) {{0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0}}

        Dim i As Integer = 7
        Dim j As Integer = 7
        For Each ctrl As Control In CheckboxPnl.Controls
            If TypeOf ctrl Is CheckBox Then
                'For some reason this reads from bottom right to top left
                System.Console.Write(ctrl.Name + " ")
                System.Console.WriteLine(DirectCast(ctrl, CheckBox).Checked)

                'See if it's checked
                If DirectCast(ctrl, CheckBox).Checked Then
                    'Add 1 to matrix in relevant pos
                    matrix(j, i) = 1
                Else
                    'do something else
                    matrix(j, i) = 0
                End If

                'Keeping track of the pos
                If j = 0 Then
                    If Not i = 0 Then
                        i -= 1 'Goes up
                        j = 7 'Start from right again
                    End If
                Else
                    j -= 1 'Goes left
                End If

            End If
        Next



        Dim sb As New System.Text.StringBuilder()
        sb.Append("{")
        For y = 0 To 7
            If y = 0 Then
                sb.Append("B")
            Else
                sb.Append(",B")
            End If

            For x = 0 To 7
                sb.Append(matrix(x, y).ToString())
            Next
        Next
        sb.Append("}")

        Dim matrixStr As String = sb.ToString

        'Output to single pattern textbox
        OutputTxt.Text = (matrixStr)
        'Copy to clipboard
        Clipboard.SetText(matrixStr)

    End Sub

    Private Sub ClearBtn_Click(sender As Object, e As EventArgs) Handles ClearBtn.Click
        For Each ctrl As Control In CheckboxPnl.Controls
            If TypeOf ctrl Is CheckBox Then
                DirectCast(ctrl, CheckBox).Checked = False
            End If
        Next
    End Sub

    Private Sub AddFrameBtn_Click(sender As Object, e As EventArgs) Handles AddFrameBtn.Click

        '                                           j v                  <i
        '                                A  B  C  D  E  F  G  H
        Dim matrix = New Integer(7, 7) {{0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0}}

        Dim i As Integer = 7
        Dim j As Integer = 7
        For Each ctrl As Control In CheckboxPnl.Controls
            If TypeOf ctrl Is CheckBox Then
                'For some reason this reads from bottom right to top left
                System.Console.Write(ctrl.Name + " ")
                System.Console.WriteLine(DirectCast(ctrl, CheckBox).Checked)

                'See if it's checked
                If DirectCast(ctrl, CheckBox).Checked Then
                    'Add 1 to matrix in relevant pos
                    matrix(j, i) = 1
                Else
                    'do something else
                    matrix(j, i) = 0
                End If

                'Keeping track of the pos
                If j = 0 Then
                    If Not i = 0 Then
                        i -= 1 'Goes up
                        j = 7 'Start from right again
                    End If
                Else
                    j -= 1 'Goes left
                End If

            End If
        Next



        Dim sb As New System.Text.StringBuilder()
        sb.Append("{")
        For y = 0 To 7
            If y = 0 Then
                sb.Append("B")
            Else
                sb.Append(",B")
            End If

            For x = 0 To 7
                sb.Append(matrix(x, y).ToString())
            Next
        Next
        sb.Append("},\" & vbCrLf)

        Dim matrixStr As String = sb.ToString

        'Add current frame to animation string
        anim.Append(matrixStr)
        'Increment frame count
        frameCount += 1
        FrameCnt.Text = frameCount.ToString()


    End Sub

    Private Sub ExportAnimBtn_Click(sender As Object, e As EventArgs) Handles ExportAnimBtn.Click

        If anim.Length > 0 Then
            anim.Length = anim.Length - 4 'Remove arduino newline fluff
        End If

        'Set the final output to the animation textbox
        Dim final As String
        final = "int frames = " & frameCount & ";" & vbCrLf & "byte anim[frames][8]=\" & vbCrLf & "{" & anim.ToString() & "};"
        OutputFrame.Text = final
        'Copy to clipboard
        Clipboard.SetText(final)
    End Sub

    Private Sub ClearAnimBtn_Click(sender As Object, e As EventArgs) Handles ClearAnimBtn.Click
        anim.Clear()
        frameCount = 0
        FrameCnt.Text = 0
        OutputFrame.Text = ""
    End Sub

    Private Sub FillBtn_Click(sender As Object, e As EventArgs) Handles FillBtn.Click
        For Each ctrl As Control In CheckboxPnl.Controls
            If TypeOf ctrl Is CheckBox Then
                DirectCast(ctrl, CheckBox).Checked = True
            End If
        Next
    End Sub

    Private Sub AddTextBtn_Click(sender As Object, eventArgs As EventArgs) Handles AddTextBtn.Click
        'Long sub that provides basic alphabet and numbers
        'Alphanumerical chars below
        Dim alphanum(35, 1) As String
        'a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
        'n1, n2, n3, n4, n5, n6, n7, n8, n9, n0

        alphanum(0, 1) = "a"
        alphanum(1, 1) = "b"
        alphanum(2, 1) = "c"
        alphanum(3, 1) = "d"
        alphanum(4, 1) = "e"
        alphanum(5, 1) = "f"
        alphanum(6, 1) = "g"
        alphanum(7, 1) = "h"
        alphanum(8, 1) = "i"
        alphanum(9, 1) = "j"
        alphanum(10, 1) = "k"
        alphanum(11, 1) = "l"
        alphanum(12, 1) = "m"
        alphanum(13, 1) = "n"
        alphanum(14, 1) = "o"
        alphanum(15, 1) = "p"
        alphanum(16, 1) = "q"
        alphanum(17, 1) = "r"
        alphanum(18, 1) = "s"
        alphanum(19, 1) = "t"
        alphanum(20, 1) = "u"
        alphanum(21, 1) = "v"
        alphanum(22, 1) = "w"
        alphanum(23, 1) = "x"
        alphanum(24, 1) = "y"
        alphanum(25, 1) = "z"
        alphanum(26, 1) = "1"
        alphanum(27, 1) = "2"
        alphanum(28, 1) = "3"
        alphanum(29, 1) = "4"
        alphanum(30, 1) = "5"
        alphanum(31, 1) = "6"
        alphanum(32, 1) = "7"
        alphanum(33, 1) = "8"
        alphanum(34, 1) = "9"
        alphanum(35, 1) = "0"


        alphanum(0, 0) = "{B11111111,B11111111,B11000011,B11000011,B11111111,B11111111,B11000011,B11000011},\" & vbCrLf
        alphanum(1, 0) = "{B11111110,B11000011,B11000011,B11111110,B11111111,B11000011,B11000011,B11111110},\" & vbCrLf
        alphanum(2, 0) = "{B11111111,B11111111,B11000000,B11000000,B11000000,B11000000,B11111111,B11111111},\" & vbCrLf
        alphanum(3, 0) = "{B11111110,B11000111,B11000011,B11000011,B11000011,B11000011,B11000111,B11111110},\" & vbCrLf
        alphanum(4, 0) = "{B11111111,B11111111,B11000000,B11111111,B11111111,B11000000,B11111111,B11111111},\" & vbCrLf
        alphanum(5, 0) = "{B11111111,B11111111,B11000000,B11111111,B11111111,B11000000,B11000000,B11000000},\" & vbCrLf
        alphanum(6, 0) = "{B11111111,B11111111,B11000000,B11001111,B11001111,B11000011,B11111111,B11111111},\" & vbCrLf
        alphanum(7, 0) = "{B11000011,B11000011,B11000011,B11111111,B11111111,B11000011,B11000011,B11000011},\" & vbCrLf
        alphanum(8, 0) = "{B11111111,B11111111,B00011000,B00011000,B00011000,B00011000,B11111111,B11111111},\" & vbCrLf
        alphanum(9, 0) = "{B11111111,B11111111,B00011000,B00011000,B00011000,B00011000,B11111000,B11111000},\" & vbCrLf
        alphanum(10, 0) = "{B11001111,B11011110,B11111100,B11111000,B11111000,B11111100,B11011110,B11001111},\" & vbCrLf
        alphanum(11, 0) = "{B11000000,B11000000,B11000000,B11000000,B11000000,B11000000,B11111111,B11111111},\" & vbCrLf
        alphanum(12, 0) = "{B11111111,B11111111,B11111111,B11011011,B11011011,B11011011,B11011011,B11011011},\" & vbCrLf
        alphanum(13, 0) = "{B11000011,B11100011,B11110011,B11111011,B11011111,B11001111,B11000111,B11000011},\" & vbCrLf
        alphanum(14, 0) = "{B11111111,B11111111,B11000011,B11000011,B11000011,B11000011,B11111111,B11111111},\" & vbCrLf
        alphanum(15, 0) = "{B11111110,B11111111,B11000011,B11000011,B11111111,B11111110,B11000000,B11000000},\" & vbCrLf
        alphanum(16, 0) = "{B11111111,B11111111,B11000011,B11000011,B11001011,B11000111,B11111111,B11111111},\" & vbCrLf
        alphanum(17, 0) = "{B11111110,B11111111,B11000011,B11000011,B11111110,B11111110,B11000111,B11000011},\" & vbCrLf
        alphanum(18, 0) = "{B11111111,B11111111,B11000000,B11111111,B11111111,B00000011,B11111111,B11111111},\" & vbCrLf
        alphanum(19, 0) = "{B11111111,B11111111,B00011000,B00011000,B00011000,B00011000,B00011000,B00011000},\" & vbCrLf
        alphanum(20, 0) = "{B11000011,B11000011,B11000011,B11000011,B11000011,B11000011,B11111111,B11111111},\" & vbCrLf
        alphanum(21, 0) = "{B10000001,B11000011,B11000011,B11100111,B01100110,B01111110,B00111100,B00011000},\" & vbCrLf
        alphanum(22, 0) = "{B11000011,B11000011,B11011011,B11011011,B11011011,B11011011,B11111111,B11111111},\" & vbCrLf
        alphanum(23, 0) = "{B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001},\" & vbCrLf
        alphanum(24, 0) = "{B10000001,B11000011,B01111110,B00111100,B00011000,B00011000,B00011000,B00011000},\" & vbCrLf
        alphanum(25, 0) = "{B11111111,B11111111,B00001110,B00011100,B00111000,B01110000,B11111111,B11111111},\" & vbCrLf
        alphanum(26, 0) = "{B00011000,B00011000,B00011000,B00011000,B00011000,B00011000,B00011000,B00011000},\" & vbCrLf
        alphanum(27, 0) = "{B11111110,B11111111,B00000011,B00000011,B00111110,B01110000,B11111111,B11111111},\" & vbCrLf
        alphanum(28, 0) = "{B11111111,B11111111,B00000011,B01111111,B01111111,B00000011,B11111111,B11111111},\" & vbCrLf
        alphanum(29, 0) = "{B11000011,B11000011,B11000011,B11111111,B11111111,B00000011,B00000011,B00000011},\" & vbCrLf
        alphanum(30, 0) = "{B11111111,B11111111,B11000000,B11111110,B11111110,B00000011,B11111111,B11111110},\" & vbCrLf
        alphanum(31, 0) = "{B11111111,B11111111,B11000000,B11111111,B11111111,B11000011,B11111111,B11111111},\" & vbCrLf
        alphanum(32, 0) = "{B11111111,B11111111,B00000011,B00011111,B00000110,B00001100,B00011000,B00011000},\" & vbCrLf
        alphanum(33, 0) = "{B11111111,B11000011,B11000011,B11111111,B11111111,B11000011,B11000011,B11111111},\" & vbCrLf
        alphanum(34, 0) = "{B11111111,B11111111,B11000011,B11000011,B11111111,B01111111,B00000011,B00000011},\" & vbCrLf
        alphanum(35, 0) = "{B11111111,B11000011,B11000011,B11000011,B11000011,B11000011,B11000011,B11111111},\" & vbCrLf

        Dim rawText As String = TextEntry.Text.ToLower()


        If IsAlphaNum(rawText) Then
            For Each letter In rawText
                Dim j = 0
                While j < 36
                    If letter = alphanum(j, 1) Then
                        Dim i = 0
                        While i < LetterCnt.Value
                            anim.Append(alphanum(j, 0))
                            i += 1
                            frameCount += 1
                            FrameCnt.Text = frameCount
                        End While
                    End If
                    j += 1
                End While
            Next
        End If

    End Sub

    Private Function IsAlphaNum(ByVal strInputText As String) As Boolean
        'Inspired by https://www.codeproject.com/Questions/414509/how-to-check-is-alphanumeric

        Dim IsAlpha As Boolean = False
        If System.Text.RegularExpressions.Regex.IsMatch(strInputText, "^[a-zA-Z0-9]+$") Then
            IsAlpha = True
        Else
            IsAlpha = False
        End If
        Return IsAlpha
    End Function
End Class
