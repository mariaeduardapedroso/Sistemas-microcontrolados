int estado = 1;

void exibe_disp(int dezena, int unidade) {

  switch (estado) {
    case 1:
      digitalWrite(a, display[unidade][0]);
      digitalWrite(b, display[unidade][1]);
      digitalWrite(c, display[unidade][2]);
      digitalWrite(d, display[unidade][3]);
      digitalWrite(e, display[unidade][4]);
      digitalWrite(f, display[unidade][5]);
      digitalWrite(g, display[unidade][6]);

      //catodo negativo, vamos ligar um de cada vez pra aparecer dezena e unidade
      digitalWrite(port_unidade, LOW);
      digitalWrite(port_dezena, HIGH);
      estado = 2;
      break;

    case 2:
      digitalWrite(a, display[dezena][0]);
      digitalWrite(b, display[dezena][1]);
      digitalWrite(c, display[dezena][2]);
      digitalWrite(d, display[dezena][3]);
      digitalWrite(e, display[dezena][4]);
      digitalWrite(f, display[dezena][5]);
      digitalWrite(g, display[dezena][6]);

      //catodo negativo, vamos ligar um de cada vez pra aparecer dezena e unidade
      digitalWrite(port_unidade, HIGH);
      digitalWrite(port_dezena, LOW);
      estado = 1;
      break;
  }

}
