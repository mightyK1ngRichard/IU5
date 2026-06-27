$(function(){
    function factorial(n) {
    if (n==0)
      return 1;
    return n ? n * factorial(n - 1) : 1;
    }
    
    $("#go").click(function(){
    var N = + $("#N").val();
    var T0 = + $("#T0").val();
    var Tp = + $("#Tp").val();
    var tk = 0.0001             // + $("#tk").val();
    var C = + $("#C").val();
    var tpr = + $("#tpr").val();
    var td = 0.0001             //+ $("#td").val();
    var Pi = 1                  // 1/$("#m").val();
    var B = 1                   // 1/(1-$("#j").val()); j=0
    var K1 = + $("#K1").val();
    var K2 = + $("#K2").val();
    var delta = + $("#delta").val();
    var Nzn = + $("#Nzn").val();

    var m1 = + (1/(2*tk)); //считает Lf1
    var m2 = + (C/(B*tpr));
    var m3 = + (1/(B*Pi*td));
    var m4 = + ((N-1)/N);
    var min = + Math.min(m1,m2,m3);
    var Lf1 = K1 * min * m4; //Lf1

    console.log("BEGIN")

    var Lstart=Lf1;
    var Tk=0;
    var Tpr=0;
    var Td=0;
    var n=0;
    var Lf=0;

    while(true){ //цикл
        n++;
        Tk = ((2*tk)/(1-2*Lf1*tk));
        var Tnpsub = (B*Lf1*tpr/C)**C;
        Tpr = ((B*tpr)/(1-Tnpsub));
        Td = ((B*td)/(1-B*Pi*Lf1*td));

        Lf=(N-1)/(T0+Tp+Tk+Tpr+Td);
        var d = Math.abs(Lf1-Lf)/Lf;
        if (d<delta || n==99999){ //выход из цикла
            break;
        }
        Lf1=Lf1-(Lf1-Lf)/K2; //переопределяем Lf1
    }
    var Tcycle=T0+Tp+Tk+Tpr+Td;
    var Treac=Tcycle-Tp;
    Treac = Tk+Tpr+Td;
    $("#res8").html(Treac.toFixed(Nzn));
    var rok=2*(N/Tcycle)*tk;
    $("#res4").html(rok.toFixed(Nzn));
    var ropr=B*(N/Tcycle)*tpr/C;
    $("#res5").html(ropr.toFixed(Nzn));
    var rod=B*(N/Tcycle)*Pi*td;
    $("#res6").html(rod.toFixed(Nzn));
    
    $("#res1").html(((T0+Tp)/Tcycle).toFixed(Nzn));
    $("#res2").html((Tp/Tcycle).toFixed(Nzn));
    $("#res3").html((N*(T0+Tp)/Tcycle).toFixed(Nzn));
    $("#res7").html(Tcycle.toFixed(Nzn));
    $("#res9").html(Lstart.toFixed(Nzn));
    $("#res10").html(Lf1.toFixed(Nzn));
    $("#res11").html(n);

    })

    $(".labelForInput").hover(function(){

        $("#obozn").html($(this).attr("name"))              
    },function(){           
        $("#obozn").html("")           
    });
})